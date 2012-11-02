#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	
	/* delete the old socket name, 
	 * create  a socket for the server */
	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	/* name the socket */
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	/* create a queue, and wait for clients */
	listen(server_sockfd, 5);
	
	while ( 1 ) {
		char ch;

		printf ( "server waiting\n" );

		/* accept a connection */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, 
				(struct sockaddr *)&client_sockfd,
			       	&client_len);

		/* we can write and read on client_sockfd */
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}
}

