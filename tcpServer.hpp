#ifndef INCLUDED_TCPSERVER
#define INCLUDED_TCPSERVER

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <libc.h>
#include <sys/socket.h>
#include <string>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer( std::string& ip_address, int port );
        ~TcpServer();
    private:
		void	startServer();

		std::string	m_ip_address;
		int			m_port;
		int			m_socket;

		int			m_new_socket;
		long		m_incomingMsg;
		struct sockaddr_in	m_socketAddress;
		unsigned int		m_socketAddress_len;
		std::string			m_serverMsg;
    };
} // namespace http
#endif