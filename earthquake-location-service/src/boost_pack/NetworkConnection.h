/***************************************************************************//**
 * @file NetworkConnection.h
 * @author Dorian Weber
 * @brief Contains a template class to handle socket connections using TCP or
 * UDP as underlying transport protocols.
 ******************************************************************************/

#ifndef NETWORKCONNECTION_H_INCLUDED
#define NETWORKCONNECTION_H_INCLUDED

#include <iostream>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <cstddef>
#include <string>

namespace BoostNetwork
{
	
	/**@brief Connection objects provide an interface to a network connection
	 * connecting two remote machines in both directions.
	 * 
	 * %Connection objects invoke message handlers that have to be passed during
	 * connection attempts. Message handlers are objects of any class that
	 * implement the following four methods:
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
	class Connection;
	
}

#include "NetworkPeer.h"

namespace BoostNetwork
{
	
	/* ******************************************************** specializations */
	
	
	/**@brief Specialization of the connection class to use TCP as its transport
	 * protocol.
	 * 
	 * Transmission Control Protocol is a connection-oriented protocol, which
	 * means that it requires handshaking to set up end-to-end communications.
	 * Once a connection is set up user data may be sent bi-directionally over the
	 * connection.
	 * 
	 * - \e Reliable – TCP manages message acknowledgement, retransmission and
	 *   timeout. Many attempts to reliably deliver the message are made. If it
	 *   gets lost along the way, the server will re-request the lost part. In
	 *   TCP, there's either no missing data, or, in case of multiple timeouts,
	 *   the connection is dropped.
	 * - \e Ordered – if two messages are sent over a connection in sequence, the
	 *   first message will reach the receiving application first. When data
	 *   segments arrive in the wrong order, TCP buffers the out-of-order data
	 *   until all data can be properly re-ordered and delivered to the
	 *   application.
	 * - \e Heavyweight – TCP requires three packets to set up a socket
	 *   connection, before any user data can be sent. TCP handles reliability and
	 *   congestion control.
	 * - \e Streaming – Data is read as a byte stream, no distinguishing
	 *   indications are transmitted to signal message (segment) boundaries.
	 */
	template <>
	class Connection<boost::asio::ip::tcp>
	:	boost::noncopyable
	{
		friend class Peer<boost::asio::ip::tcp>;
		
		/**@brief Socket associated with the connection.
		 */
		boost::asio::ip::tcp::socket _socket;

		/**@brief Buffers for incoming and outgoing data.
		 */
		boost::asio::streambuf _in, _out;
		
		/**@brief User friendly alias for \c _out.
		 */
		std::ostream _ostream;
		
		
		enum stateEnum
		{
			DISCONNECTED,        /**<@brief The connection is not available yet. */
			CONNECTION_ATTEMPT,  /**<@brief Attempting to establish the connection. */
			CONNECTED            /**<@brief Connection successfully established. */
		} _state;  /**<@brief Marks the internal state of the connection. */
		
		/**@brief Internal wrapper functor that calls the \c match method from a
		 * message handler.
		 */
		template <class MessageHandler>
		class Matcher
		{
			MessageHandler& handler;
			
		public:
			
			Matcher(MessageHandler& msgHandler)
			:	handler(msgHandler)
			{}
			
			template <class iterator>
			std::pair<iterator, bool>
			operator()(const iterator& begin, const iterator& end)
			{
				return handler.match(begin, end);
			}
			
		};
		
		/**@brief Internal function that handles connection attempts.
		 * @param[in] msgHandler  specifies the message handler as an interface to
		 *                        the next layer
		 * @param[in] e           contains the error code
		 */
		template <class MessageHandler>
		void handleConnect(MessageHandler& msgHandler,
		                   const boost::system::error_code& e)
		{
			if (!e)
			{
				setup(msgHandler);
				commit();
			}
			else
			{
				_state = DISCONNECTED;
				
				/* inform the caller that the connection attempt failed */
				std::cerr << "[" BOOST_STRINGIZE(__LINE__) "]: " << e.message() << '\n';
			}
		}
		
		/**@brief Internal function that handles asynchron writes to the socket.
		 * 
		 * @param[in] e         contains the error code
		 * @param[in] transfer  number of bytes written
		 */
		void handleWrite(const boost::system::error_code& e, std::size_t transfer)
		{
			if (!e)
			{
				_out.consume(transfer);
			}
			else
			{
				/* inform the caller that the write attempt failed */
				std::cerr << "[" BOOST_STRINGIZE(__LINE__) "]: " << e.message() << '\n';
			}
		}
		
		/**@brief Internal function that reads asynchronely from the socket and
		 * informs the next layer of any incoming message.
		 * 
		 * @param[in] e         contains the error code
		 * @param[in] transfer  number of bytes read
		 */
		template <class MessageHandler>
		void handleRead(MessageHandler& msgHandler,
		                const boost::system::error_code& e, std::size_t transfer)
		{
			if (!e)
			{
				std::istream is(&_in);
				char buf[transfer];
				
				is.read(buf, transfer);
				
				/* promote the message to the next layer */
				msgHandler.handle(*this, buf, transfer);
				
				listen(msgHandler);
			}
			else
			{
				/* inform the next layer of the loss of the connection */
				msgHandler.unregisterConnection(*this);
				disconnect();
			}
		}
		
		/**@brief Internal function used to issue asynchron reading operations from
		 * the socket.
		 * 
		 * @param[in] msgHandler  specifies the message handler as an interface to
		 *                        the next layer
		 */
		template <class MessageHandler>
		void listen(MessageHandler& msgHandler)
		{
			boost::asio::async_read_until(_socket, _in, Matcher<MessageHandler>(msgHandler),
			                              boost::bind(&Connection::template handleRead<MessageHandler>,
			                                          this, boost::ref(msgHandler),
			                                          boost::asio::placeholders::error,
			                                          boost::asio::placeholders::bytes_transferred));
		}
		
		/**@brief Internal function that performs final preparations before the
		 * connection is fully established.
		 * 
		 * @param[in] msgHandler  specifies the message handler as an interface to
		 *                        the next layer
		 */
		template <class MessageHandler>
		void setup(MessageHandler& msgHandler)
		{
			_state = CONNECTED;
			msgHandler.registerConnection(*this);
			listen(msgHandler);
		}
		
	public:
		
		/* ********************************************** CONSTRUCTORS/DESTRUCTOR */
		
		/**@brief Creates a new connection object using a custom or default io
		 * service object.
		 * @note The connection object has yet to establish a connection using 
		 * establish().
		 * 
		 * @param[in] io_service  the OS dependent IO service object
		 */
		Connection(boost::asio::io_service& io_service = default_io_service)
		:	_socket(io_service),
			_ostream(&_out),
			_state(DISCONNECTED)
		{
			// empty
		}
		
		/**@brief Creates a new connection object and tries to establish a
		 * connection.
		 * 
		 * @param[in] ip_address  contains the IP address as C string
		 * @param[in] port        specifies the destination port
		 * @param[in] io_service  reference to the io service object to use
		 */
		template <class MessageHandler>
		Connection(const char* ip_address,
		           MessageHandler& msgHandler,
		           unsigned short port = 1998,
		           boost::asio::io_service& io_service = default_io_service)
		:	_socket(io_service),
			_ostream(&_out),
			_state(DISCONNECTED)
		{
			connect(ip_address, msgHandler, port);
		}
		
		/**@brief Creates a new connection object and tries to establish a
		 * connection.
		 * 
		 * @param[in] ip_address  contains the IP address as std string
		 * @param[in] port        specifies the destination port
		 * @param[in] io_service  reference to the io service object to use
		 */
		template <class MessageHandler>
		Connection(const std::string& ip_address,
		           MessageHandler& msgHandler,
		           unsigned short port = 1998,
		           boost::asio::io_service& io_service = default_io_service)
		:	_socket(io_service),
			_ostream(&_out),
			_state(DISCONNECTED)
		{
			connect(ip_address, msgHandler, port);
		}
		
		/**@brief Disconnects from the remote target if a connection has been
		 * established.
		 */
		~Connection()
		{
			disconnect();
		}
		
		/* ************************************************************** METHODS */
		
		/**@brief Tries to establish a connection to a remote machine.
		 * 
		 * @param[in] ip_address  C string containing the ip address
		 * @param[in] msgHandler  specifies the message handler as an interface to
		 *                        the next layer
		 * @param[in] port        destination port
		 */
		template <class MessageHandler>
		void connect(const char* ip_address, MessageHandler& msgHandler,
		             unsigned short port = 1998)
		{
			boost::asio::ip::tcp::endpoint
			    peer(boost::asio::ip::address::from_string(ip_address), port);
			boost::system::error_code ec;
			
			switch (_state)
			{
			case CONNECTED:
				_state = DISCONNECTED;
				_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
				
			case CONNECTION_ATTEMPT:
				_socket.close(ec);
				
			case DISCONNECTED:
				_state = CONNECTION_ATTEMPT;
				_socket.async_connect(peer,
				                      boost::bind(&Connection::template handleConnect<MessageHandler>,
				                                  this, boost::ref(msgHandler),
				                                  boost::asio::placeholders::error));
			}
		}
		
		/**@brief Tries to establish a connection to a remote machine.
		 * 
		 * @param[in] ip_address  std string containing the ip address
		 * @param[in] msgHandler  specifies the message handler as an interface to
		 *                        the next layer
		 * @param[in] port        destination port
		 */
		template <class MessageHandler>
		void connect(const std::string& ip_address, MessageHandler& msgHandler,
		             unsigned short port = 1998)
		{
			connect(ip_address.c_str(), msgHandler, port);
		}
		
		/**@brief Disconnects from the remote target if the connection exists.
		 */
		void disconnect()
		{
			boost::system::error_code ec;
			stateEnum state = _state;
			
			_state = DISCONNECTED;
			
			switch (state)
			{
			case CONNECTED:
				_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
				
			case CONNECTION_ATTEMPT:
				_socket.close(ec);
				
			default:
				break;
			}
		}
		
		/**@brief Commits the buffered data to the socket.
		 * @note If the connection is not established yet, this function doesn't
		 * do anything. The data is going to be committed automatically when the
		 * connection is established.
		 */
		void commit()
		{
			if (isConnected() && _out.size())
			{
				boost::asio::async_write(_socket, _out, 
				                         boost::bind(&Connection::handleWrite, this,
				                                     boost::asio::placeholders::error,
				                                     boost::asio::placeholders::bytes_transferred));
			}
		}
		
		/**@brief Returns \c true if the connection has been established.
		 * @return \c true if the connection exists
		 */
		bool isConnected() const
		{
			return _state == CONNECTED;
		}
		
		/**@brief Returns an \c ostream that can be used to write data to the
		 * socket. 
		 * @note The data written to the stream is not passed to the socket until
		 * you call commit().
		 * 
		 * @return an \c ostream representing the socket
		 */
		std::ostream& get_ostream()
		{
			return _ostream;
		}
		
		/**@brief Returns the socket that is internally used.
		 * @return the socket
		 */
		boost::asio::ip::tcp::socket& get_socket()
		{
			return _socket;
		}
		
		/**@brief Returns the ip address and port this connection points to.
		 * @return the ip address ":" port as string
		 */
		std::string get_ip_port() const
		{
			std::stringstream ss;
			ss << _socket.remote_endpoint().address().to_string() << ":" << _socket.remote_endpoint().port();
			return ss.str();
		}
		
		/**@brief Returns the ip address this connection points to.
		 * @return the ip address as string
		 */
		std::string get_ip() const
		{
			return _socket.remote_endpoint().address().to_string();
		}

	};
	
}

/* register internal "Matcher" class for usage with boost::asio */

namespace boost
{
	namespace asio
	{
		template <class MH>
		struct is_match_condition<
			::BoostNetwork::Connection<ip::tcp>::template Matcher<MH> >
		:	boost::true_type
		{};
	}
}

#endif
