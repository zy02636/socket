#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	char *host;
	int sockfd;
	int len, result;
	struct sockaddr_in addr;
	struct hostent *hostinfo;
	struct servent *servinfo;
	char buffer[128];

	if (argc ==1)
		host = "localhost";
	else
		host = argv[1];

	hostinfo = gethostbyname(host);
	if (!hostinfo) {
		fprintf(stderr, "no host: %s\n", host);
		exit(1);
	}

	servinfo = getservbyname("daytime", "udp");
	if (!servinfo) {
		fprintf(stderr, "no daytime service\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = servinfo->s_port;
	addr.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
	len = sizeof(struct sockaddr_in);

	result = sendto(sockfd, buffer, 1, 0, (struct sockaddr *)&addr, len);
	result = recvfrom(sockfd, buffer, 128, 0, (struct sockaddr *)&addr, &len);

	buffer[result] = '\0';
	printf ("read %d gytes: %s\n", result, buffer);

	close(sockfd);
	exit(0);
}
