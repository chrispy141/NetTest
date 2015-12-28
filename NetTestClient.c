#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main(int argc, char* argv[])
{
  int sockfd = 0,n = 0;
  char recvBuff[1024];
  int num1, num2, mySum;
  int tranSize = 1025 * sizeof(char);
  
  num1 = atoi(argv[1]);
  num2 = atoi(argv[2]);
  struct sockaddr_in serv_addr;
 
  memset(recvBuff, '0' ,sizeof(recvBuff));
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);
  serv_addr.sin_addr.s_addr = inet_addr("192.168.0.15");
  int cntst = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  if(cntst<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }
  
  printf("connection status = %d\n", cntst); 
  // while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
  // {
      //      recvBuff[n] = 0;
      printf("flip\n");
      recv(sockfd, recvBuff, tranSize, 0);
      printf("first recieve complete\n");
      printf("%s\n", recvBuff);
      printf("sending numbers %d and %d\n", num1, num2);
      send(sockfd, &num1, sizeof(int), 0);
      send(sockfd, &num2, sizeof(int), 0);
      printf("package sent\n");
      recv(sockfd, &mySum, sizeof(int), 0);
      printf("response recieved: %d\n", mySum);
     
       // }
 
  
  return 0;
}
