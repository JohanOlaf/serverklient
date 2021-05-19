#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h> //read
#define PORT 8080



int server(){
	int running = 1;
	int server_fd;
	int socket_fd;
	int valread;

	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};//en buffer hvor innkommet skal lande
	char str[1024];
	

	//lager en socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed");	
	}
	
	//koble socket til en port
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
		perror("setsockopt");	
	}
	//hvorfor gjør vi dette
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	//binder server til socketaddr
	if (bind(server_fd, (struct sockaddr* ) & address, sizeof(address)) < 0){
		perror("Bind failed");
	}
	//lytter etter ny tilkobling
	if (listen(server_fd, 3) < 0){
		perror("Listen failure");	
	}
	
	while(running != 0){ //vil alltid lete etter nye klienter
		if(socket_fd < 1){ //hvis det finnes en socket fra før kobles ikke en ny en til
			if((socket_fd = accept(server_fd, (struct sockaddr* )& address, 			(socklen_t*)&addrlen)) < 0){
				perror("failure accepting");	
			}
		}
		valread = recv(socket_fd, buffer, sizeof(buffer),0);
		char* temp = buffer;
		char* end = "END";

		if(strcmp(temp, end) == 0){
			send(socket_fd, &str, sizeof(str),0);
			bzero(str, sizeof(str));
		}
		else{
			strcat(str, buffer);
			printf("%s\n", str);
			send(socket_fd, &str, sizeof(str), 0);

		}
		bzero(buffer, sizeof(buffer));
		
	}

	return 1;
}




int main(int argc, char** argv){
	server();
	return 1;
}
