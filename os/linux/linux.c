#include "platform.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>

void debug_print(char *format, ...)
{
	;
}
void video_init()
{
	printf("Initing video");
}

void video_exit()
{
	printf("Exiting video");
}

int vnc_connect(char *addr, char *port)
{
	struct addrinfo hints, *addrinfo;
	int fd;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(addr, port, &hints, &addrinfo))
		return -1;
	fd = socket(addrinfo->ai_family, addrinfo->ai_socktype,
			addrinfo->ai_protocol);

	if (connect(fd, addrinfo->ai_addr, addrinfo->ai_addrlen) == -1) {
		close(fd);
		fd = -2;
	}
	freeaddrinfo(addrinfo);
	return fd;
}

size_t vnc_sock_read(int sock, void *buf, size_t size)
{
	return read(sock, buf, size);
}

size_t vnc_sock_write(int sock, void *buf, size_t size)
{
	return write(sock, buf, size);
}