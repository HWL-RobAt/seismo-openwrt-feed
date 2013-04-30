#!/usr/bin/python

#
# This program creates a simple statics over the wirless links
# (ping with 64b, ping with 1000b and rssi value).
# The argument is a space seperated list of ips, if none are given
# it gets the IPs out of the link table of the OLSR txtinfo plugin
# (expected to be running on 127.0.0.1:2007).
#

import socket;
import os;
import subprocess;
import sys;


numpings = "5"; # Number of pings

#
# recvline recives a line from a socket
#

def recvline(s):
    line = "";
    while 1:
         t = s.recv(1);
	 if not t: return None;
         if t=='\n': break;
         line += t;
    return line;

# Function to get the current rssi value for an ip.
# The ip must be in the arp cache, because the function uses the
# arp command to get the interface and mac address for a given ip adress
# to find the rssi value in /proc/net/madwifi/iface/associated_sta
# (this is ensured for example by pinging that host beforehand, like it is
# done in this program).

def get_rssi_from_ip(ip):
    pingpipe = subprocess.Popen("arp "+ip, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout;
    line = pingpipe.readline();

    if not line:
        return "-";

    splitted = line.split();

    if len(splitted)!=7 or splitted[0]!="?": 
        return "--";
    else:
        mac = splitted[3].lower();
        iface = splitted[6];
        assoc = open("/proc/net/madwifi/"+iface+"/associated_sta", "r");
        nextline = False;

        for line in open("/proc/net/madwifi/"+iface+"/associated_sta", "r"):
            if nextline:             return line.split()[1];
            if line.find(mac) >= 0:  nextline = True;
        return "--";

#
# ping_ip pings an ip with a given size and returns the packet 
# loss percentage.
#

def ping_ip(ip, size):
    pingpipe = subprocess.Popen("ping "+ip+" -c "+numpings+" -q -s "+str(size), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout;
    while 1:
        line = pingpipe.readline();
        if not line: 
            return "-";
        if line.find("packet loss") >= 0:
            return line.split()[6];

#
# get_neighbors_from_olsr returns a list of neighbor ips which are seen by OLSR
# (using olsr's txtinfo plugin exptected to be running at 127.0.0.1:2007).
#

def get_neighbors_from_olsr():
    mySocket = socket.socket ( socket.AF_INET, socket.SOCK_STREAM );
    mySocket.connect ( ( '127.0.0.1', 2007 ) );
    mySocket.send ( '\n' );

    while 1:
        test = recvline(mySocket);
        if test == "Table: Links":
            recvline(mySocket);
            break;
    # Now in Link table

    neighbors = [];

    while 1:
        line = recvline(mySocket);
        if line == "": break;
        neighbors += [ line.split()[1] ];


    mySocket.close();
    return neighbors;


###
###  Main
###

if len(sys.argv) > 1: neighbors = sys.argv[1:];
else                : neighbors = get_neighbors_from_olsr();

print "IPs = ", neighbors;

print "IP".ljust(16), "loss(64b)".ljust(10), "loss(1kb)".ljust(10), "RSSI".ljust(5);

for ip in neighbors:
    print ip.ljust(16),;

    print ping_ip(ip, 64).ljust(10),;

    print ping_ip(ip, 1000).ljust(10),;

    print get_rssi_from_ip(ip).ljust(5);

