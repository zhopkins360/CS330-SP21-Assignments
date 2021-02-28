#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

//Used to test how to grab input from the consol

//testing if works from diffrent functions
int grabInput(){
    char *input = NULL;
    size_t length = 0;
    getline(&input,&length,stdin);
    
    fprintf(stdout,"%s",input);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 1) {
        fprintf(stderr, "Usage: ./testing < [message]\n");
        exit(EXIT_FAILURE);
    }

    return grabInput();
}