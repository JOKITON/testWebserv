#include "tcpServer.hpp"
namespace http
{
    TcpServer::TcpServer( std::string& ip_address, int port ) : m_ip_address(ip_address), m_port(port),
																m_incomingMsg(), m_socket(), m_new_socket(),
																m_socketAddress_len(sizeof(m_socketAddress)), m_socketAddress(), m_serverMsg()
    {
		this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (this->m_socket < 0) {
			std::perror("Could not create a socket.");
			exit(1);
		}

		/*	startServer: Configure the base structure with data & bind the socket to it */
		startServer();

		/*	Function will allow to have input connections,
			limits the connections in the created socket´s listen queue up to 1 */
		if (listen(m_socket, 1) == -1) {
			std::perror("Could not create a socket.");
			exit(1);
		}

		struct sockaddr_in	address;
		socklen_t			address_len;

		address_len = sizeof(address);
		int ret = accept(m_socket,(struct sockaddr *)&address, &address_len);
		if (ret != -1) {
			std::cout << "Connection established!" << std::endl << "Congratulations!" << std::endl;

			std::cout << "(Non-formatted)Address of client : " << (address.sin_addr.s_addr) << std::endl;
			std::cout << "(Non-formatted)Port of client : " << (address.sin_port) << std::endl;

			std::cout << "Address of client : " << ntohs(address.sin_addr.s_addr) << std::endl;
			std::cout << "Port of client : " << ntohs(address.sin_port) << std::endl;
			
			close(m_socket);
			exit(1);
		}
		else if ( ret == -1) {
			std::perror("Could not create a socket.");
			exit(1);
		}


		std::cout << "The code for the socket is: " << this->m_socket << std::endl;
    }
    TcpServer::~TcpServer()
    {
		close(this->m_socket);
		std::cout << "Connection was closed on " << m_socket << std::endl;
    }

	void	TcpServer::startServer( void ) {
		m_socketAddress.sin_family = AF_INET;
		m_socketAddress.sin_port = htons(m_port);
		m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());

		if (bind(m_socket,(sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
		{
			std::perror("Cannot connect socket to address");
			exit(1);
		}
	}
} // namespace http