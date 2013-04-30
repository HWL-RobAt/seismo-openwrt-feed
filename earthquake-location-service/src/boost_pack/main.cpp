#include <iostream>
#include <string>
#include <iosfwd>
#include "NetworkHandler.h"
#include "NetworkConnection.h"
#include "RTDS_gen.h"
#include "RTDS_messages.h"

std::list<NetworkTopology*> getTopologyList (Graph* g);

void addNodesToGraph(Graph* g);
void addLinksToGraph(Graph* g);

void submitTopologies (Network::blockClass_node * node , NetworkTopology* topology);

int main(int argc, const char* argv[])
{
	Graph* g = new Graph();
	addNodesToGraph(g);
	addLinksToGraph(g);

	std::list<NetworkTopology*> topologyList = getTopologyList(g);

	std::map < std::string, Network::blockClass_node*> blockClassNodeMap;

	//create all nodes
	for (std::list<NetworkTopology*>::iterator it = topologyList.begin(); it != topologyList.end(); it++) {
		std::cout << "create node instance and handler for: " << (*it)->getMyId() << std::endl;
		std::string ip;
		int port;
		NetworkHandler::splitIpPort((*it)->getMyId(),ip,port);
		NetworkHandler* handler = new NetworkHandler(port);
		Network::blockClass_node* node = new Network::blockClass_node();
		node->handler = handler;
		handler->node = node;
		node->activate();
		//save for later use
		blockClassNodeMap[(*it)->getMyId()] = node;
	}

	//wait until everything is setup
	sleep(1);

	//now submit topology information
	for (std::list<NetworkTopology*>::iterator it = topologyList.begin(); it != topologyList.end(); it++) {
		submitTopologies(blockClassNodeMap[(*it)->getMyId()], *it);
	}

	RTDS::SDLProcess::ioService.run();

	return 0;
}

void submitTopologies (Network::blockClass_node * node , NetworkTopology* topology) {
	RTDS_QueueId transport_receiver = node->p_Creator[0]->blockMember->getBlockMember(TRANSPORT_RECEIVER);
	//EXPLORED MACRO:
	//RTDS_MSG_SEND_mSubmitTopology_TO_ID(transport_receiver,networkTopologies[it->first]);
	//macro does not work, because it needs a local msgQueueWriter as sender reference
	unsigned char* RTDS_msgData = (unsigned char *) new RTDS_mSubmitTopology_data();
	((RTDS_mSubmitTopology_data*)RTDS_msgData)->param1 = topology;
	RTDS::MsgHeader* msg =	new RTDS::MsgHeader(RTDS_message_mSubmitTopology, *transport_receiver, sizeof(RTDS_mSubmitTopology_data), RTDS_msgData);
	msg->sequenceNumber = 0;
	transport_receiver->put(msg);
}

#ifndef NODETARGET
#include <initializer_list>

std::list<NetworkTopology*> getTopologyList (Graph* g) {
	std::list<NetworkTopology*> topologyList;
	for (node_vector::iterator it = g->nodes.begin(); it != g->nodes.end(); it++) {
		NetworkTopology* topology = new NetworkTopology();
		topology->setMyId((*it)->id);
		topology->setMyReceiverReference((*it)->receiverRef);

		for (node_vector::iterator it2 = g->nodes.begin(); it2 != g->nodes.end(); it2++) {
			if (*it2 != *it) {
				topology->setConnectivity((*it2)->id, 1.0);
				topology->setIdReferenceMapping((*it2)->id,(*it2)->id,(*it2)->id, g->isNeighbor(*it, *it2));
			}
		}
		topologyList.push_back(topology);
	}
	return topologyList;
}

void addNodesToGraph(Graph* g) {
	std::list<std::string> nodeList = {"127.0.0.1:1998", "127.0.0.1:1999","127.0.0.1:2000",
			"127.0.0.1:2001","127.0.0.1:2002","127.0.0.1:2003","127.0.0.1:2004",
			"127.0.0.1:2005","127.0.0.1:2006","127.0.0.1:2007","127.0.0.1:2008"
	};
	for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
		std::cout << "Added node: " << *it << " to graph." << std::endl;
		g->addNode(*it, *it, *it);
	}
}

void addLinksToGraph(Graph* g) {
	for (auto it = g->nodes.begin(); it != g->nodes.end(); ++it) {
		for (auto it2 = it; ++it2 != g->nodes.end(); ) {
			g->addEdge((*it)->senderRef, (*it2)->senderRef, 1);
			g->addEdge((*it2)->senderRef, (*it)->senderRef, 1);
		}
	}
}

/*void addLinksToGraph(Graph* g) {
	g->addEdge("127.0.0.1:1998","127.0.0.1:1999",1);
	g->addEdge("127.0.0.1:1998","127.0.0.1:2000",1);
	g->addEdge("127.0.0.1:1998","127.0.0.1:2001",1);

	g->addEdge("127.0.0.1:1999","127.0.0.1:1998",1);
	g->addEdge("127.0.0.1:1999","127.0.0.1:2000",1);
	g->addEdge("127.0.0.1:1999","127.0.0.1:2001",1);

	g->addEdge("127.0.0.1:2000","127.0.0.1:1998",1);
	g->addEdge("127.0.0.1:2000","127.0.0.1:1999",1);
	g->addEdge("127.0.0.1:2000","127.0.0.1:2001",1);

	g->addEdge("127.0.0.1:2001","127.0.0.1:1998",1);
	g->addEdge("127.0.0.1:2001","127.0.0.1:1999",1);
	g->addEdge("127.0.0.1:2001","127.0.0.1:2000",1);
}*/

#else

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define INTERFACE "ath1"
#define LOCALPORT ":1999"

std::string getLocalIP(std::string interface) {
	struct ifreq ifa;
	struct sockaddr_in *i;
	int fd;

	if (strlen (interface.c_str()) >= sizeof ifa.ifr_name) {
		fprintf (stderr, "%s is to long\n", interface.c_str());
		return NULL;
	}

	strcpy (ifa.ifr_name, interface.c_str());

	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror ("socket");
		return NULL;
	}

	if(ioctl(fd, SIOCGIFADDR, &ifa)) {
		perror ("ioctl");
		return NULL;
	}

	i = (struct sockaddr_in*)&ifa.ifr_addr;
	return std::string(inet_ntoa(i->sin_addr));
}

/*
 * only return the topology for the local node
 */
std::list<NetworkTopology*> getTopologyList (Graph* g) {
	std::list<NetworkTopology*> topologyList;
	std::string localIP = getLocalIP(INTERFACE);
	localIP.append(LOCALPORT);
	for (node_vector::iterator it = g->nodes.begin(); it != g->nodes.end(); it++) {
		if ( ((*it)->id).compare(localIP) == 0) {

			NetworkTopology* topology = new NetworkTopology();
			topology->setMyId((*it)->id);
			topology->setMyReceiverReference((*it)->receiverRef);

			for (node_vector::iterator it2 = g->nodes.begin(); it2 != g->nodes.end(); it2++) {
				if (*it2 != *it) {
					topology->setConnectivity((*it2)->id, 1.0);
					topology->setIdReferenceMapping((*it2)->id,(*it2)->id,(*it2)->id, g->isNeighbor(*it, *it2));
				}
			}
			topologyList.push_back(topology);
		}
	}
	return topologyList;
}

// helper: reads a line into linebuf from a socket (socket descriptor sd) and returns length of line
int recv_line(int sd, char* linebuf){
	int i = 0;

	// Receive 1 byte until newline is found
	while (recv(sd, &linebuf[i], 1, 0) > 0) {
		i++;
		// If newline is found terminate line and return length
		if(linebuf[i-1] == '\n'){
			linebuf[i] = '\0';
			return i;
		}
	}
	// If code goes here no more chars were available from the socket, terminate also and return length
	linebuf[i] = '\0';
	return i;
}

void addNodesToGraph(Graph* g) {
	// Socket stuff
	int socketDescriptor;
	struct sockaddr_in serverAddress;
	char buf[1024];

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(2006);
	serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");

	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketDescriptor < 0) {
		printf("ns3__getStationStatus: cannot create socket\n");
		exit(-1);
	}

	if (connect(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		printf("cannot connect\n");
		exit(-1);
	}

	// Receive lines loop
	while(recv_line(socketDescriptor, buf) > 0){
		char station_name[256];

		// PARSE: Lines look like "10.12.116.48,524295,135313,636,2" (ipname,longitude,latitude,height,syncstate)
		int i = 0;
		int fieldstart = 0;
		int len = strlen(buf);

		// Name
		while((buf[i]!=',') && (i<len)){
			i++;
		}
		if(i>=len){
			continue; // malformed line
		}
		else {
			buf[i] = '\0';
			i++;
			strcpy(station_name, buf);
		}
		std::string remoteIP(station_name);
		remoteIP.append(LOCALPORT);
		g->addNode(remoteIP,remoteIP,remoteIP);
		std::cout << "Added node: " << remoteIP << " to graph." << std::endl;

	}

	close(socketDescriptor);
}

void addLinksToGraph(Graph* g) {
	std::string localIP = getLocalIP(INTERFACE);

	// Socket stuff
	int socketDescriptor;
	struct sockaddr_in serverAddress;
	char buf[1024];

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(2004);
	serverAddress.sin_addr.s_addr=inet_addr("127.0.0.1");

	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketDescriptor < 0) {
		printf("cannot create socket\n");
		exit(-1);
	}

	// Connect to server.

	if (connect(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		printf("cannot connect\n");
		exit(-1);
	}

	// Receive lines loop
	while(recv_line(socketDescriptor, buf) > 0){
		// Output of socket is like this:
		//digraph topology
		//{
		//"10.12.116.48" -> "10.12.116.70"[label="1.00", style=solid];
		//"10.12.116.48" -> "10.12.116.70"[label="1.00"];
		//"10.12.116.70" -> "10.12.116.48"[label="1.00"];
		//"10.12.116.70" -> "192.168.200.222"[label="11.38"];
		//}

		// Link line starting with '"', parse it
		if(buf[0]=='"'){
			char source_name[256];
			char dest_name[256];
			float link_quality;

			int i = 0;
			int fieldstart = 0;
			int len = strlen(buf);

			// Src-Name
			while((buf[i]!='"') && (i<len)){
				i++;
			}
			if(i>=len){
				continue; // malformed line
			}
			else {
				buf[i] = '\0';
				i++;
				fieldstart = i;
			}

			while((buf[i]!='"') && (i<len)){
				i++;
			}
			if(i>=len){
				continue; // malformed line
			}
			else {
				buf[i] = '\0';
				i++;
				strcpy(source_name, &buf[fieldstart]);
			}

			// Dst-Name
			while((buf[i]!='"') && (i<len)){
				i++;
			}
			if(i>=len){
				continue; // malformed line
			}
			else {
				buf[i] = '\0';
				i++;
				fieldstart = i;
			}

			while((buf[i]!='"') && (i<len)){
				i++;
			}
			if(i>=len){
				continue; // malformed line
			}
			else {
				buf[i] = '\0';
				i++;
				strcpy(dest_name, &buf[fieldstart]);
			}

			std::string srcIP (source_name);
			srcIP.append(LOCALPORT);
			std::string destIP (dest_name);
			destIP.append(LOCALPORT);

			g->addEdge(srcIP, destIP, 1);
			std::cout << "Added link to graph: " << srcIP << " : " << destIP << std::endl;

		}
		// Last line starting with '}', quit here
		else if(buf[0]=='}') {
			break;
		}
	}
	close(socketDescriptor);
}
#endif
