/***************************************************************************//**
 * @file NetworkPeer.h
 * @author Dorian Weber
 * @brief Contains a template class that is used to listen at a local port.
 ******************************************************************************/

#ifndef NETWORKPEER_H_INCLUDED
#define NETWORKPEER_H_INCLUDED

#include <iostream>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace BoostNetwork
{
	
	/**@brief Global io service object that is used if no io service has been
	 * specified.
	 */
	extern boost::asio::io_service default_io_service;
	
	/* forward declaration */
	template <typename Protocol>
	class Peer;
	
}

#include "NetworkConnection.h"

namespace BoostNetwork
{
	
	/**@brief Opens a port, listens and accepts connections using a given
	 * transport protocol.
	 * 
	 * %Peer objects invoke message handlers that have to be passed during
	 * construction. Message handlers are objects of any class that implement the
	 * following four methods:
	 *  
	 *  -# void \c registerConnection(Network::Connection&): this method gets
	 *     called when a new network connection has been established with the
	 *     connection passed as parameter
	 *  -# void \c unregisterConnection(const Network::Connection&): invoked
	 *     during unexpected disconnecting from the remote socket (\e unexpected
	 *     means that the connection has been closed remotely rather than the
	 *     \c disconnect method from the Connection has been called)
	 *  -# std::pair<iterator,bool> \c match(iterator,iterator): a method that
	 *     checks wether a message can be decoded successfully and returns an exit
	 *     code indicating success; refer to the boost::asio documention of
	 *     \c async_read_until for further information about this method
	 *  -# void \c handle(Network::Connection&, char*, std::size_t): after
	 *     a message has successfully been tested if it could be decoded, this
	 *     method is invoked with the connection object (the source of the
	 *     message), a char* (pointer to the input buffer) and the number of
	 *     transferred bytes
	 */
	template <typename Protocol = boost::asio::ip::tcp>
	class Peer
	:	boost::noncopyable
	{
		/**@brief Reference to OS dependent IO service.
		 */
		boost::asio::io_service& _io_service;
		
		/**@brief Accepts new connections.
		 */
		boost::asio::basic_socket_acceptor<Protocol> _acceptor;
		
		/**@brief Internal function used to set up a new connection after an attempt
		 * to connect from a remote machine has been detected.
		 * 
		 * @param[in] con         specifies the connection object to use
		 * @param[in] msgHandler  specifies a message handler
		 * @param[in] e           contains the error code
		 */
		template <class MessageHandler>
		void handle_accept(Connection<Protocol>* con, MessageHandler& msgHandler,
		                   const boost::system::error_code& e)
		{
			if (!e)
			{
				/* perform final initialization steps */
				con->setup(msgHandler);
				
				/* create a new one */
				con = new Connection<Protocol>(_io_service);
			}
			else
			{
				/* promote error */
				std::cerr << "[" BOOST_STRINGIZE(__LINE__) "]: " << e.message() << '\n';
			}
			
			/* prepare to accept another connection */
			_acceptor.async_accept(con->get_socket(),
			                       boost::bind(&Peer::template handle_accept<MessageHandler>,
			                                   this, con, boost::ref(msgHandler),
			                                   boost::asio::placeholders::error));
		}
		
	public:
		
		/**@brief Creates a new peer object and instructs it to listen at a
		 * specified port.
		 * 
		 * @param[in] msgHandler    specifies an object that can be used as a
		 *                          message handler
		 * @param[in] incomingPort  port number to listen at
		 * @param[in] io_service    OS dependent IO service object
		 */
		template <class MessageHandler>
		Peer(MessageHandler& msgHandler,
		     unsigned short incomingPort = 1998,
		     boost::asio::io_service& io_service = default_io_service)
		:	_io_service(io_service),
			_acceptor(io_service,
			          typename Protocol::endpoint(Protocol::v4(), incomingPort))
		{
			Connection<Protocol>* ncon = new Connection<Protocol>(io_service);
			
			_acceptor.async_accept(ncon->get_socket(),
			                       boost::bind(&Peer::template handle_accept<MessageHandler>,
			                                   this, ncon, boost::ref(msgHandler),
			                                   boost::asio::placeholders::error));
		}
		
		/**@brief Returns the io service object used by this peer.
		 * @return the io service object used by this peer
		 */
		boost::asio::io_service& get_io_service()
		{
			return _io_service;
		}
		
	};
	
}

#endif
