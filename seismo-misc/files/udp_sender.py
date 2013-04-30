#!/usr/bin/python

# UDP Sender


from socket import *
import string
import time

#host = "127.0.0.1"
host = "224.0.0.1"
port = 8105
seq = 0

UDPSock = socket(AF_INET,SOCK_DGRAM)

print "\nStarting client end.  Control-C to quit."

while (1):
    seq = seq + 1
    if(UDPSock.sendto(str(seq),(host,port))):
        print "SEQ(" + str(seq) + ") sent" 
    else:
        print "SEQ(" + str(seq) + ") NOT sent" 
    
    time.sleep(1)
	
print "Done."


UDPSock.close()