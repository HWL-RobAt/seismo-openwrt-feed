/*
 * NetworkTopology.h
 *
 *  Created on: 09.04.2009
 *      Author: ingmar
 */

#ifndef NETWORKTOPOLOGY_H_
#define NETWORKTOPOLOGY_H_

#include "Common.h"
#include <map>
#include <set>
#include <vector>
#include <limits.h>
#include <list>
#include <iostream>
#include "RTDS_MACRO.h"

/*http://www.reviewmylife.co.uk/blog/2008/07/15/dijkstras-algorithm-code-in-c/ */
class Node;
class Edge;

typedef std::vector< Node* > node_vector;
typedef std::vector< Edge* > edge_vector;
typedef std::map< ID , Node* > node_map;

class Node
{
public:
	Node(ID id, ExternalRef senderRef, ExternalRef receiverRef)
		: id(id), senderRef(senderRef), receiverRef(receiverRef), previous(NULL), distanceFromStart(INT_MAX)
	{
	}
public:
	//important node properties
	ID id;
	ExternalRef senderRef;
	ExternalRef receiverRef;

	//temporary data for algorithms
	Node* previous;
	int distanceFromStart;
};

class Edge
{
public:
	Edge(Node* node1, Node* node2, int distance)
		: node1(node1), node2(node2), distance(distance)
	{
	}

	bool Connects(Node* node1, Node* node2)
	{
		return (
			(node1 == this->node1 &&
			node2 == this->node2) ||
			(node1 == this->node2 &&
			node2 == this->node1));
	}
public:
	Node* node1;
	Node* node2;
	int distance;
};

class Graph {

	node_map nodesMap;

public:
	node_vector nodes;
	edge_vector edges;



	void addNode(ID id, ExternalRef senderRef, ExternalRef receiverRef) {
		Node* node = new Node(id, senderRef, receiverRef);
		nodes.push_back(node);
		nodesMap[id] = node;
	}

	void addNode(Node* node) {
		nodes.push_back(node);
	}

	bool addEdge (ID node1ID, ID node2ID, int distance) {
		Node* node1 = nodesMap[node1ID];
		Node* node2 = nodesMap[node2ID];
		if (node1 && node2) {
			edges.push_back(new Edge(node1, node2, distance));
			return true;
		} else
			return false;
	}

	void addEdge(Node* node1, Node* node2, int distance) {
		edges.push_back(new Edge(node1, node2, distance));
	}

	void addEdge(Edge* edge) {
		edges.push_back(edge);
	}

	std::set< Node* > getNeighbor (ID node) {
		return getNeighbor(nodesMap[node]);
	}

	std::set< Node* > getNeighbor (Node* node) {
		std::set< Node* > neighbor;
		for (edge_vector::iterator it = edges.begin(); it != edges.end(); it++) {
			if ((*it)->node1 == node)
				neighbor.insert((*it)->node2);
			if ((*it)->node2 == node)
				neighbor.insert((*it)->node1);
		}
		return neighbor;
	}

	bool isNeighbor(ID node1 , ID node2) {
		return isNeighbor(nodesMap[node1], nodesMap[node2]);
	}

	bool isNeighbor(Node* node1 , Node* node2) {
		for (edge_vector::iterator it = edges.begin(); it != edges.end(); it++) {
			if ((*it)->node1 == node1 && (*it)->node2 == node2)
				return true;
		}
		return false;
	}

	void Dijkstras()
	{
		while (nodes.size() > 0)
		{
			Node* smallest = ExtractSmallest(nodes);
			std::vector<Node*>* adjacentNodes =
				AdjacentRemainingNodes(smallest);
			const int size = adjacentNodes->size();
			for (int i=0; i<size; ++i)
			{
				Node* adjacent = adjacentNodes->at(i);
				int distance = Distance(smallest, adjacent) +
					smallest->distanceFromStart;
				if (distance < adjacent->distanceFromStart)
				{
					adjacent->distanceFromStart = distance;
					adjacent->previous = smallest;
				}
			}
			delete adjacentNodes;
		}
	}

private:
	// Find the node with the smallest distance,
	// remove it, and return it.
	Node* ExtractSmallest(std::vector<Node*>& nodes)
	{
		int size = nodes.size();
		if (size == 0) return NULL;
		int smallestPosition = 0;
		Node* smallest = nodes.at(0);
		for (int i=1; i<size; ++i)
		{
			Node* current = nodes.at(i);
			if (current->distanceFromStart <
				smallest->distanceFromStart)
			{
				smallest = current;
				smallestPosition = i;
			}
		}
		nodes.erase(nodes.begin() + smallestPosition);
		return smallest;
	}
	// Return all nodes adjacent to 'node' which are still
	// in the 'nodes' collection.
	std::vector<Node*>* AdjacentRemainingNodes(Node* node)
	{
		std::vector<Node*>* adjacentNodes = new std::vector<Node*>();
		const int size = edges.size();
		for(int i=0; i<size; ++i)
		{
			Edge* edge = edges.at(i);
			Node* adjacent = NULL;
			if (edge->node1 == node)
			{
				adjacent = edge->node2;
			}
			else if (edge->node2 == node)
			{
				adjacent = edge->node1;
			}
			if (adjacent && Contains(nodes, adjacent))
			{
				adjacentNodes->push_back(adjacent);
			}
		}
		return adjacentNodes;
	}
	// Return distance between two connected nodes
	int Distance(Node* node1, Node* node2)
	{
		const int size = edges.size();
		for(int i=0; i<size; ++i)
		{
			Edge* edge = edges.at(i);
			if (edge->Connects(node1, node2))
			{
				return edge->distance;
			}
		}
		return -1; // should never happen
	}

	// Does the 'nodes' vector contain 'node'
	bool Contains(std::vector<Node*>& nodes, Node* node)
	{
		const int size = nodes.size();
		for(int i=0; i<size; ++i)
		{
			if (node == nodes.at(i))
			{
				return true;
			}
		}
		return false;
	}

	void PrintShortestRouteTo(Node* destination)
	{
		Node* previous = destination;
		std::cout << "Distance from start: "
			<< destination->distanceFromStart << std::endl;
		while (previous)
		{
			std::cout << previous->id << " ";
			previous = previous->previous;
		}
		std::cout << std::endl;
	}
};

class NetworkTopology {
private:
	ID myID;
	ExternalRef myReceiverReference;
	std::map<ID, double> connectivityMap;
	
	std::map<ID, ExternalRef> externalReceiverReferences;
	std::map<ID, ExternalRef> externalSenderReferences;
	std::map<ID, ExternalRef> neighborExternalReceiverReferences;

	std::map<ExternalRef, ID> nodeIds;
	
public:

	NetworkTopology();
	virtual ~NetworkTopology();

	void setMyId(ID id);
	ID getMyId() const;
	
	void setMyReceiverReference(ExternalRef reference) ;
	ExternalRef getMyReceiverReference() const;

	double getConnectivity(ID id) ;

	void setIdReferenceMapping(ID id, ExternalRef receiver_reference, ExternalRef sender_reference, bool isNeighbor);
	void setConnectivity(ID id, double connectivity);
	
	std::list<ExternalRef> getAllNeighborReferences();
	
	std::list<ExternalRef> getAllConnectedReferences();
	ExternalRef getReceiverReference(ID id);
	ExternalRef getSenderReference(ID id);

  ID getIDbyReference(ExternalRef reference);
};

typedef NetworkTopology* NetworkTopologyPtr;

#endif /* NETWORKTOPOLOGY_H_ */
