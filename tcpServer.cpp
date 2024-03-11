#include "tcpServer.hpp"
namespace http
{
    TcpServer::TcpServer( std::string& ip_address, int port ) : m_ip_address(ip_address), m_port(port),
																m_incomingMsg(), m_socket(), m_new_socket(),
																m_socketAddress_len(sizeof(m_socketAddress)), m_socketAddress(), m_serverMsg()
{
	int	opts = 1;
	this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->m_socket < 0) {
		std::perror("Could not create a socket.");
		exit(1);
	}
	std::cout << "Server socket is : " << m_socket << std::endl;

	setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opts, sizeof(opts));

	if((opts = fcntl(m_socket, F_GETFL)) < 0) { // Get current options
		perror("error fcntl");
		exit(1);
	}
	opts = (opts | O_NONBLOCK); // Don't clobber your old settings
	if(fcntl(m_socket, F_SETFL, opts) < 0) {
		perror("error fcntl");
		exit(1);
	}

	m_socketAddress.sin_family = AF_INET;
	m_socketAddress.sin_port = htons(m_port);
	m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());

	if (bind(m_socket,(sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
	{
		std::perror("Cannot connect socket to address");
		exit(1);
	}

	/*	Function will allow to have input connections,
		limits the connections in the created socket´s listen queue up to 1 */
	if (listen(m_socket, 1024) == -1) {
		std::perror("Could not create a socket.");
		exit(1);
	}

	/*	startServer: Configure the base structure with data & bind the socket to it */
	startServer();
	//setConnection();

	std::cout << "The code for the socket is: " << this->m_socket << std::endl;
    }
    TcpServer::~TcpServer()
    {
		close(this->m_socket);
		std::cout << "Connection was closed on " << m_socket << std::endl;
    }

void	TcpServer::startServer( void ) {

	fd_set	cSockets, rSockets;

	FD_ZERO(&cSockets);
	FD_SET(m_socket, &cSockets);
	while (true) {
		rSockets = cSockets;

		std::cout << "Arrived before-select" << std::endl;
		if (select(FD_SETSIZE, &rSockets, NULL, NULL, NULL) < 0) { // Waits until file descriptor has info
			perror("error: select");
			exit(EXIT_FAILURE);
		}
		std::cout << "Arrived after-select" << std::endl;

		for (int i = 0; i < FD_SETSIZE; i++) { // Check every file descriptor
			if (FD_ISSET(i, &rSockets)) { // True if 'i' has the same file descriptor as 'rSockets'
				if (i == m_socket) {
					std::cout << "I : " << i << std::endl;
					int clientSocket = setConnection();
					FD_SET(clientSocket, &cSockets);
				}
			}
			else {
				FD_CLR(i, &cSockets);
			}
		}
	}
}

int		TcpServer::setConnection ( void ) {

		struct sockaddr_in	address;
		socklen_t			address_len;

		address_len = sizeof(address);
		int ret = accept(m_socket,(struct sockaddr *)&address, &address_len);
		if (ret >= 0) {
			std::cout << "Connection established!" << std::endl << "Congratulations!" << std::endl;

			std::cout << "(Non-formatted)Address of client : " << (address.sin_addr.s_addr) << std::endl;
			std::cout << "(Non-formatted)Port of client : " << (address.sin_port) << std::endl;

			std::cout << "Address of client : " << ntohs(address.sin_addr.s_addr) << std::endl;
			std::cout << "Port of client : " << ntohs(address.sin_port) << std::endl;
			
			char buffer[1024]; // Allocate buffer
			ssize_t bytes_read;
			while ((bytes_read = read(ret, buffer, sizeof(buffer))) > 0) {
				std::cout.write(buffer, bytes_read); // Print what's read
			}
			close(ret); // Close accepted socket
		}
		else if ( ret == -1) {
			std::perror("Could not create a socket.");
		}
		return ret;
}
} // namespace http