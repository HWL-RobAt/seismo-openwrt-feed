#!/usr/bin/python

# udp_receiver.py 


from socket import *
import time

# we want to bind on all possible IP addresses
host = "0.0.0.0"

#if you change the port, change it in the client program as well
port = 8105
buffer = 102400

# Create socket and bind to address
UDPSock = socket(AF_INET,SOCK_DGRAM)
UDPSock.bind((host,port))


while 1:
    data,addr = UDPSock.recvfrom(buffer)	
    print "RCVD %i bytes from %s: %s\n" % (len(data), addr, data)

UDPSock.close()