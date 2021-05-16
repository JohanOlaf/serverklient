#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080


int klient(){
	int socket_fd = 0;
	int valread = 0;
	char ip[16] = "127.0.0.1";
	int running = 1;
	
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	
	//socket descriptor
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket creation failure");
		return -1;	
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	

	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) < 1){
		printf("unsupported address");
		return -1;
	}
	if(connect(socket_fd, (struct sockaddr* )& serv_addr, sizeof(serv_addr)) < 0){
		printf("connection failed");
		return -1;
	}
	while(running != 0){
		printf(": ");
		fgets(buffer, sizeof(buffer), stdin);
		send(socket_fd, &buffer, sizeof(buffer), 0);
		bzero(buffer, sizeof(buffer));
		valread = read(socket_fd, buffer, sizeof(buffer));
		printf("%s", buffer);

	}
	return 1;
}









int main(int argc, char** argv){
	klient();

	return 1;
}
