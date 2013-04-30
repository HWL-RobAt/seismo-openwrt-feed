/*
 * NetworkTopology.cpp
 *
 *  Created on: 09.04.2009
 *      Author: ingmar
 */

#include "NetworkTopology.h"

NetworkTopology::NetworkTopology() {
}

NetworkTopology::~NetworkTopology() {
}

ID NetworkTopology::getMyId() const {
	return myID;
}

void NetworkTopology::setMyId(ID id) {
	this->myID = id;
}


void NetworkTopology::setMyReceiverReference(ExternalRef reference) {
	this->myReceiverReference = reference;
}

ExternalRef NetworkTopology::getMyReceiverReference() const {
	return myReceiverReference;
}

void NetworkTopology::setConnectivity(ID id, double connectivity) {
	connectivityMap[id] = connectivity;
}

double NetworkTopology::getConnectivity(ID id) {
	return connectivityMap[id];
}

void NetworkTopology::setIdReferenceMapping(ID id, ExternalRef receiver_reference, ExternalRef sender_reference, bool isNeighbor) {
	externalReceiverReferences[id] = receiver_reference;
	externalSenderReferences[id] = sender_reference;
	nodeIds[receiver_reference] = id;
	nodeIds[sender_reference] = id;
	if (isNeighbor)
		neighborExternalReceiverReferences[id] = receiver_reference;
}

ID NetworkTopology::getIDbyReference(ExternalRef reference) {
	ID res = nodeIds[reference];

	//assert(res != "");

	return res;
} 
ExternalRef NetworkTopology::getReceiverReference(ID id) {
	return externalReceiverReferences[id];
}

ExternalRef NetworkTopology::getSenderReference(ID id) {
	return externalSenderReferences[id];
}

std::list<ExternalRef> NetworkTopology::getAllConnectedReferences() {
	std::list<ExternalRef> connectedReferences;
	std::map<ID,ExternalRef>::iterator it;
	for (it = externalReceiverReferences.begin(); it != externalReceiverReferences.end(); it++) {
		connectedReferences.push_back((*it).second);
	}
	return connectedReferences;
}

std::list<ExternalRef> NetworkTopology::getAllNeighborReferences(){
	std::list<ExternalRef> connectedReferences;
	std::map<ID,ExternalRef>::iterator it;
	for (it = neighborExternalReceiverReferences.begin(); it != neighborExternalReceiverReferences.end(); it++) {
		connectedReferences.push_back((*it).second);
	}
	return connectedReferences;
}
