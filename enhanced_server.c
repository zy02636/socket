#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int server_sockfd, client_sockfd;
	int client_len;
	
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(9374);
	
	bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	listen(server_sockfd, 5);

	signal(SIGCHLD, SIG_IGN);

	while (1) {
		char ch;
		printf ( "server waiting.....\n" );

		client_len = sizeof(client_addr);
		client_sockfd = accept(server_sockfd,
				(struct sockaddr *)&client_addr, &client_addr);

		if (fork() == 0) {
			/* childern */
			read(client_sockfd, &ch, 1);
			sleep(5);
			ch++;
			write(client_sockfd, &ch, 1);
			close(client_sockfd);
			exit(0);
		}
		else {
			close(client_sockfd);
		}
	}
}
