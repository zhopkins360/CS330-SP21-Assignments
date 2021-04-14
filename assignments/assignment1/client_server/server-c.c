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
  int sockArry[10] = { 0 };//creates a zero array to hold sockInts later
  int sockInt, new_sockId, recvErr; //creates int for sockets
  char data[RECV_BUFFER_SIZE];
  struct addrinfo portSpecs, *res, *res0; //creates structer vars
  memset(&portSpecs,0,sizeof(portSpecs)); //zeros portSpecs
  //sets up portSpecs for getaddrinfo()
  portSpecs.ai_family = AF_UNSPEC;
  portSpecs.ai_socktype = SOCK_STREAM;
  //tries to find ports with the specs given in portSpecs
  if((getaddrinfo("127.0.0.1",server_port,&portSpecs,&res) != 0)){
    fprintf(stderr,"server: getaddrinfo failed\n");
    exit(EXIT_FAILURE);//couldn't find a port open
  }
  //tries to create a file descriptor with the given socket info
  if((sockInt = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) < 0){
    perror("server: socket failed\n");//uses perror b/c this error won't break the program
  }
  //tries to bind the fd
  if((bind(sockInt, res->ai_addr, res->ai_addrlen)) < 0){
    perror("server: bind failed\n");
  }
  //preparing for incoming requests
  if(listen(sockInt,QUEUE_LENGTH) == -1){
    perror("server: listen failed\n");
    exit(EXIT_FAILURE);
  }
  //looping for someone to connect
  while(1){
    //tires accept a client connecting on on the socket
    if((new_sockId = accept(sockInt, NULL, NULL)) < 0){
      perror("server: accept failed\n");
      continue;
    }
    //loops while there is data to be taken and prints it out
    while((recvErr = recv(new_sockId,&data,RECV_BUFFER_SIZE,0)) > 0){
      fprintf(stdout,"%s",data);
    }
    //pushes the output of stdout and closes the client socket
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
