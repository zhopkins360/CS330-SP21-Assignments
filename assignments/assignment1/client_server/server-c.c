/*****************************************************************************
 * server-c.c                                                                 
 * Name:
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
  int sockInt, new_sockId, errorInt; //creates int
  struct addrinfo portSpecs,res,res0; //creates structer vars
  memset(&portSpecs,0,sizeof(portSpecs)); //zeros portSpecs
  //sets up portSpecs for getaddrinfo()
  portSpecs.ai_family = AF_UNSPEC;
  portSpecs.ai_socktype = SOCK_STREAM;
  //tries to find ports with the specs given in portSpecs
  if((errorInt = getaddrinfo(NULL,server_port,&portSpecs,&res) != 0)){
    fprintf(stderr,"server: getaddrinfo failed");
    exit(EXIT_FAILURE);//couldn't find a port open
  }
  //loops through all ports given by getaddrinfo
  for(res = res0; res != NULL; res=res->ai_next){
    if((sockInt = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) == -1){
      perror("server: socket failed");//uses perror b/c this error won't break the program
      continue;//keeps looping to find a good socket
    }
    if((bind(sockInt, res->ai_addr, res->addrlen)) == -1){
      perror("server: bind failed");
      continue;//keeps looping to find a good socket
    }
    break;//break out of loop b/c bound to a port
  }
//preparing for incoming requests
if(listen(sockInt,QUEUE_LENGTH) == -1){
  perror("server: listen failed");
  exit(EXIT_FAILURE);
}
//telling me where in the code the server is
printf("Server is listening...");
//looping for someone to connect
while(true){
  if((new_sockId = accept(sockInt,NULL,NULL))==-1){//NEED TO FILL IN
    perror("server: accept failed");
    continue;
  }
  //
  recv(new_sockId,,RECV_BUFFER_SIZE,0)
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
