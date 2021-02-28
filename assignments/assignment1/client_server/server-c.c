/*****************************************************************************
 * server-c.c                                                                 
 * Name: Zackary Hopkisn
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) {
  int sockInt, new_sockId; //creates int for sockets
  char data[RECV_BUFFER_SIZE];
  struct addrinfo portSpecs, *res, *res0; //creates structer vars
  struct sockaddr clientAddr;
  socklen_t clientAddr_size;
  memset(&portSpecs,0,sizeof(portSpecs)); //zeros portSpecs
  //sets up portSpecs for getaddrinfo()
  portSpecs.ai_family = AF_UNSPEC;
  portSpecs.ai_socktype = SOCK_STREAM;
  //tries to find ports with the specs given in portSpecs
  if((getaddrinfo("127.0.0.1",server_port,&portSpecs,&res0) != 0)){
    fprintf(stderr,"server: getaddrinfo failed\n");
    exit(EXIT_FAILURE);//couldn't find a port open
  }
  //loops through all ports given by getaddrinfo
  for(res = res0; res != NULL; res=res->ai_next){
    if((sockInt = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) < 0){
      perror("server: socket failed\n");//uses perror b/c this error won't break the program
      continue;//keeps looping to find a good socket
    }
    if((bind(sockInt, res->ai_addr, res->ai_addrlen)) < 0){
      perror("server: bind failed\n");
      continue;//keeps looping to find a good socket
    }
    break;//break out of loop b/c bound to a port
  }
  if(res == NULL){
    fprintf(stderr,"server: failed to create a fd");
    exit(EXIT_FAILURE);
  }
  //preparing for incoming requests
  if(listen(sockInt,QUEUE_LENGTH) == -1){
    perror("server: listen failed\n");
    exit(EXIT_FAILURE);
  }
  //looping for someone to connect
  while(1){
    //sets the size of the clientAddr
    clientAddr_size = sizeof(clientAddr);
    //tires accept a client connecting on on the socket
    if((new_sockId = accept(sockInt, &clientAddr, &clientAddr_size)) < 0){
      perror("server: accept failed\n");
      continue;
    }
    //NEED TO TAKE IN INPUT AND PRINT IT OUT
    recv(new_sockId,&data,RECV_BUFFER_SIZE,0);
    fprintf(stdout,"%s",data);
    fflush(stdout);
    close(new_sockId);
}
  return 0;
}

/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
