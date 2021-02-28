/*****************************************************************************
 * client-c.c                                                                 
 * Name: Zackary Hopkins
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

#define SEND_BUFFER_SIZE 2048


/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
*/
int client(char *server_ip, char *server_port) {
  //vars needed
  struct addrinfo portSpec, *res, *res0;
  int sockInt;
  char *data = NULL;
  size_t length = SEND_BUFFER_SIZE;
  //set up port spects 
  memset(&portSpec,0,sizeof(portSpec));
  portSpec.ai_family = AF_UNSPEC;
  portSpec.ai_socktype = SOCK_STREAM;
  //looks for ports to use 
  if((getaddrinfo(server_ip,server_port,&portSpec,&res0)) != 0){
    fprintf(stderr,"client: getaddrinfo fail\n");
    exit(EXIT_FAILURE);
  }
  //loops through the ports 
  for(res=res0; res != NULL; res = res->ai_next){
    //tries to create a file descriptor with the given socket info
    if((sockInt = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
      perror("client: socket failed\n");
      continue;
    }
    //tires to connect ot server on the socket
    if((connect(sockInt,res->ai_addr,res->ai_addrlen)) < 0){
      perror("client: connect failed\n");
      continue;
    }
  }
  //gets the data from stdin and gets a refrence to it in data
  if((getline(&data,&length,stdin)) < 0){
    fprintf(stderr,"client: getline fail\n");
    exit(EXIT_FAILURE);
  }
  //tries to send the data on the file descriptor
  if((send(sockInt,data,SEND_BUFFER_SIZE,0)) < 0){
    fprintf(stderr,"client: send failed\n");
    exit(EXIT_FAILURE);
  }
  //releses the socket after sending the message
  close(sockInt);
  return 0;
}

/*
 * main()
 * Parse command-line arguments and call client function
*/
int main(int argc, char **argv) {
  char *server_ip;
  char *server_port;

  if (argc != 3) {
    fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}
