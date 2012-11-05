#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *host, **names,  **address;
	struct hostent *hostinfo;

	if ( argc == 1 ) {
		char myname[256];
		gethostname(myname, 255);
		host = myname;
	} else {
		host = argv[1];
	}

	hostinfo = gethostbyname(host);
	if ( hostinfo == NULL ) {
		fprintf(stderr, "can't get info from host: %s\n", host);
		exit(1);
	}

	printf ( "result for host %s:\n", host );
	printf ( "names: %s\n", hostinfo->h_name );
	printf ( "aliases:\n" );
	names = hostinfo->h_aliases;
	while ( *names ) {
		printf ( " %s", *names );
		names++;
	}
	printf ( "\n" );
	
	if ( hostinfo->h_addrtype != AF_INET ) {
		fprintf(stderr, "not an IP host\n");
		exit(1);
	}
	address = hostinfo->h_addr_list;
	while ( *address ) {
		printf ( " %s", inet_ntoa(*(struct in_addr *)*address) );
		address++;
	}
	printf ( "\n" );
	exit(0);

}
