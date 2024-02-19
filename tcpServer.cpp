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

		startServer();

		std::cout << "The code for the socket is: " << this->m_socket << std::endl;
    }
    TcpServer::~TcpServer()
    {
		close(this->m_socket);
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