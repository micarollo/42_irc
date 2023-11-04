#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#define PORT 8080

int nClientSocket;
struct sockaddr_in srv;

int main(void)
{
	int nRet = 0;

	nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nClientSocket < 0)
	{
		std::cout << "Socket could not open" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Socket open successfully!" << std::endl;

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&srv.sin_zero, 0, 8);

	nRet = connect(nClientSocket, (sockaddr *)&srv, sizeof(srv));
	if (nRet < 0)
	{
		std::cout << "Connection failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Connected to server" << std::endl;
		char buff[256];
		recv(nClientSocket, buff, 256, 0);
		std::cout << buff << std::endl;
		std::cout << "Send your message to the server:";
		while (1)
		{
			fgets(buff, 256, stdin);
			if (buff[0])
			{
				send(nClientSocket, buff, 256, 0);
				recv(nClientSocket, buff, 256, 0);
				std::cout << buff << std::endl;
			}
			std::cout << "Send another message: ";
		}
	}
}