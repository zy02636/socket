#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'a';

	/* create a socket for client. */
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	/* name the socket across to the server */
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	/* connect the client socket to the server socket */
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if ( result == -1 ) {
		perror("oops: client1");
		exit(1);
	}

	/* now we can use sockfd to write and read */
	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf ( "char from server = %c\n", ch );
	exit(0);
}
