
#ifndef NETWORK_HANDLER_H_INCLUDED
#define NETWORK_HANDLER_H_INCLUDED

#include "NetworkConnection.h"
#include "NetworkPeer.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "RTDS_gen.h"
#include "RTDS_SDLPROCESS.h"
#include "Common.h"
#include "RTDS_messages.h"

#include <iostream>
#include <map>

namespace Network {
	struct blockClass_node;
}

class NetworkHandler
{
	typedef boost::asio::buffers_iterator<
		boost::asio::streambuf::const_buffers_type> iterator;
	
	std::map<std::string,BoostNetwork::Connection<>*> connectionMap;

	BoostNetwork::Peer<> peer;

	int listenPort;


public:

	Network::blockClass_node* node;
	
	//	NetworkHandler(Network::blockClass_node& node);
	NetworkHandler(int listenPort);
	
	void registerConnection(BoostNetwork::Connection<>& connection);
	
	void unregisterConnection(BoostNetwork::Connection<>& connection);
	
	std::pair<iterator, bool>
	match(iterator begin, iterator end);
	
	void handle(BoostNetwork::Connection<>& c, char* msgBuf, std::size_t size);
	
	BoostNetwork::Connection<>* getConnection(const std::string& ip_port);

	int getListenPort();

	/**
	 * splits 127.0.0.1:1234 into ip and port number
	 */
	static void splitIpPort(const std::string& ip_port, std::string& ip, int& port);

};


template<class Archive>
inline void serialize(
    Archive & ar,
    RTDS_mUnicast_data & t,
    const unsigned int file_version
){
	ar & t.param1;
	ar & t.param2;
	switch (t.param2) {
		case RTDS_message_mPing:
			ar & t.param3.ping;
			break;
		case RTDS_message_mPong:
			ar & t.param3.pong;
			break;
		default:
			std::cerr << "don't know how to serialize message type: " << t.param2 << ". ignore the payload." << std::endl;
			break;
	}
}
#endif
