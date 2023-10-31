#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define CLIENTS_MAX_ALLOW 5

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	struct sockaddr_in srvAddress;
	fd_set fr, fw, fe;
	int nMaxFd;

	int sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockFd < 0)
	{
		std::cout << "Socket could not open" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Socket open successfully!" << std::endl;

	srvAddress.sin_family = AF_INET;
	srvAddress.sin_port = htons(PORT);
	srvAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&srvAddress.sin_zero, 0, 8);

	int nRet = 0;
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

		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &timeOut);
		if (nRet > 0)
		{
			std::cout << nRet << "are ready to read or exception" << std::endl;
			// When someone connects or communicates over a dedicated connection
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