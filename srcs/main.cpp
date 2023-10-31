#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>

#define PORT 8080
#define CLIENTS_MAX_ALLOW 5

int nArrClient[CLIENTS_MAX_ALLOW];
fd_set fr, fw, fe;

void processTheNewRequest(int sockFd)
{
	// New connection request
	if (FD_ISSET(sockFd, &fr))
	{
		int nClientSocket = accept(sockFd, NULL, NULL);
		int nIndex;
		if (nClientSocket > 0)
		{
			for (nIndex = 0; nIndex < 5; nIndex++)
			{
				if (nArrClient[nIndex] == 0)
				{
					nArrClient[nIndex] = nClientSocket;
					send(nClientSocket, "Connection done successfully!", 30, 0);
					break;
				}
			}

			if (nIndex == CLIENTS_MAX_ALLOW)
			{
				std::cout << "No space for a new connection" << std::endl;
			}
		}
		else
		{
			// for (int nIndex = 0; nIndex < 5; nIndex++)
			// {
			// 	if
			// }
		}
	};
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// initialize the socket
	struct sockaddr_in srvAddress;
	int nMaxFd;
	int nRet = 0;

	int sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockFd < 0)
	{
		std::cout << "Socket could not open" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Socket open successfully!" << std::endl;

	// initalize the environment for sockaddr structure
	srvAddress.sin_family = AF_INET;
	srvAddress.sin_port = htons(PORT);
	srvAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&srvAddress.sin_zero, 0, 8);

	// set socket options - allow use port if already being used
	int optVal = 0;
	int optLen = sizeof(optVal);
	nRet = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optVal, optLen);
	if (nRet < 0)
	{
		std::cout << "Could not set socket options" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Successfully set socket options" << std::endl;
	}

	// make socket non-blocking
	int currSockFlags = fcntl(sockFd, F_GETFL, 0);
	if (nRet < 0)
	{
		std::cout << "Could not get current socket flags" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Successfully got current socket flags" << std::endl;
	}
	nRet = fcntl(sockFd, F_SETFL, currSockFlags | O_NONBLOCK);
	if (nRet < 0)
	{
		std::cout << "Error when making socket non-blocking" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Successfully made socket non-blocking" << std::endl;
	}

	// Bind the socket to the local port
	nRet = bind(sockFd, (sockaddr *)&srvAddress, sizeof(sockaddr));
	if (nRet < 0)
	{
		std::cout << "Fail to bind to local port" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Successfully bind to local port" << std::endl;
	}

	nRet = listen(sockFd, CLIENTS_MAX_ALLOW);
	if (nRet < 0)
	{
		std::cout << "Fail to start to listen to local port" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Start to listen to local port" << std::endl;
	}

	nMaxFd = sockFd;
	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);
		FD_SET(sockFd, &fr);
		FD_SET(sockFd, &fe);

		for (int nIndex = 0; nIndex < CLIENTS_MAX_ALLOW; nIndex++)
		{
			if (nArrClient[nIndex] != 0)
			{
				FD_SET(nArrClient[nIndex], &fr);
				FD_SET(nArrClient[nIndex], &fe);
			}
		}

		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &timeOut);
		if (nRet > 0)
		{
			std::cout << nRet << "are ready to read" << std::endl;
			// When someone connects or communicates over a dedicated connection
			processTheNewRequest(sockFd);
		}
		else if (nRet == 0)
		{
			std::cout << "Nothing on port " << PORT << std::endl;
		}
		else
		{
			std::cout << "Failed in select" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}