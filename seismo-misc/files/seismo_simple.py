 # a simple tcp server which uses slinktool to serve a stream of a seedlink server
 # first argument is the seedlink stream, second host:port of the server
 # service is running on port 18001, output is "[seconds].[milliseconds],[acceleration-value]"

import SocketServer
import subprocess
import sys
import thread
import time
import socket
import signal
import os

def serve_seismo( request ):
    slinktool = subprocess.Popen(["./slinktool", "-u", "-S", args_stream, args_server], stdout=subprocess.PIPE)
    output = "dummy"
    timestamp = 0.0
    
    while(output):
        try:
            output = slinktool.stdout.readline()
            #print "read: ", output
            if(output.startswith("   ")):
                data = output.split(" ")
                #print "data split: ", data
                for item in data:
                    if(item.isdigit()):
                        request.send("%.2f,%s\n" % (timestamp, item))
                        timestamp += 0.01
            else:
                header = output.split(" ")
                if(len(header)<6):
                    continue
                #print "header split: ", header
                #header split:  ['SW_S61B0_ENN,', '263', 'samples,', '100', 'Hz,', '2010,012,08:27:14.050000', '(latency', '~-4.1', 'sec)\n']
                time_strings = header[5].split(".")
                timestamp = time.mktime(time.strptime(time_strings[0], "%Y,%j,%H:%M:%S")) + float("0." + time_strings[1])
                #print "timestamp set to: ", timestamp
        except socket.error:
            break
        except:
            print "Unexpected error: ", sys.exc_info()[0]
    
    os.kill(slinktool.pid, signal.SIGTERM)


class EchoRequestHandler(SocketServer.BaseRequestHandler ):

    def setup(self):
        print self.client_address, 'connected!'
        #self.request.send('hi ' + str(self.client_address) + '\n')
        thread.start_new_thread(serve_seismo, (self.request,))

    def handle(self):
        data = 'dummy'
        while data:
            data = self.request.recv(1024)


    def finish(self):
        print self.client_address, 'disconnected!'
        #self.request.send('bye ' + str(self.client_address) + '\n')


args_stream = sys.argv[1]
args_server = sys.argv[2]
server = SocketServer.ThreadingTCPServer(('', 18001), EchoRequestHandler)
server.serve_forever()

