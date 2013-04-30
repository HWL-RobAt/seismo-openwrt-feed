
#include "NetworkHandler.h"
#include "NetworkTopology.h"
#include "BlockMember.h"
#include <boost/tokenizer.hpp>
#include <boost/iostreams/stream.hpp>
#include <stdlib.h>

//#include <blockClass_node.hpp>

//NetworkHandler::NetworkHandler(Network::blockClass_node& node)
//:	node(node)
//{}

NetworkHandler::NetworkHandler(int listenPort):
peer(*this, listenPort, RTDS::SDLProcess::ioService), listenPort(listenPort)
{}


void NetworkHandler::registerConnection(BoostNetwork::Connection<>& connection)
{
	//	std::cout << "REGISTER CONNECTION: " << connection.get_ip_port() << std::endl;
	//	connectionMap[connection.get_ip_port()] = &connection;
}

void NetworkHandler::unregisterConnection(BoostNetwork::Connection<>& connection)
{
	std::cout << "disconnected" << std::endl;
	connectionMap.erase(connection.get_ip_port());
}

std::pair<NetworkHandler::iterator, bool>
NetworkHandler::match(iterator begin, iterator end)
{
	if (begin != end) {
		std::string s(begin,end);
		std::stringstream ss;
		ss << s;
		RTDS_mUnicast_data unidataptr;

		try {
			boost::archive::binary_iarchive archive(ss);
			archive >> unidataptr;
//			if (begin + ss.tellg() != end) {
//				std::cerr << "read " << ss.tellg() << " < " << s.length() << std::endl;
//			}
			return std::pair<iterator, bool>(begin + ss.tellg(), true);
		} catch (std::exception &e) {
			if (ss.tellg() != s.length()) {
				std::cerr << "data corruption detected, ABORT " << std::endl;
				abort();
			}
		}
	}
	return std::pair<iterator, bool>(begin, false );
}

void
NetworkHandler::handle(BoostNetwork::Connection<>& c, char* msgBuf, std::size_t size)
{
	//unpack the payload
	RTDS_QueueId receiver = node->p_Creator[0]->blockMember->getBlockMember(TRANSPORT_RECEIVER);

	RTDS_mUnicast_data* unidataptr = new RTDS_mUnicast_data();

	try {
		std::stringstream os;
		os.write(msgBuf, size);
		std::cout << "receiving size: " << size << std::endl;
		boost::archive::binary_iarchive archive(os);

		archive >> *unidataptr;

		RTDS::MsgHeader* msg = new RTDS::MsgHeader(RTDS_message_mUnicast, *receiver, sizeof(RTDS_mUnicast_data), reinterpret_cast<unsigned char *>(unidataptr));
		msg->sequenceNumber = 0;
		receiver->put(msg);
	} catch (...) {
		std::cerr << "error while decoding message: \"" << msgBuf << "\" with size: " << size << std::endl;
	}
}

BoostNetwork::Connection<>*
NetworkHandler::getConnection(const std::string& ip_port)
{
	BoostNetwork::Connection<>* c = connectionMap[ip_port];

	if (c == NULL)
	{
		c = new BoostNetwork::Connection<>(peer.get_io_service());
		connectionMap[ip_port] = c;
		std::string ip;
		int port;
		splitIpPort(ip_port,ip,port);
		c->connect(ip, *this, port);
	}
	return c;
}

int
NetworkHandler::getListenPort() {
	return listenPort;
}

/**
 * splits 127.0.0.1:1234 into ip and port number
 */
void
NetworkHandler::splitIpPort(const std::string& ip_port, std::string& ip, int& port) {
	typedef boost::tokenizer<boost::char_separator<char> >
	tokenizer;
	boost::char_separator<char> sep(":");
	tokenizer tokens(ip_port, sep);
	tokenizer::iterator tok_iter = tokens.begin();
	ip = *tok_iter;
	++tok_iter;
	port = atoi((*tok_iter).c_str());
}
