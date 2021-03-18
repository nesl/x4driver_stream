#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
 
using namespace std;
 
typedef unsigned char uchar;
 
int main()
{
	int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr_s;
	adr_s.sin_family = AF_INET;
	adr_s.sin_addr.s_addr = inet_addr("127.0.0.1");
	adr_s.sin_port =htons(1235);
	bind(s, (struct sockaddr *)&adr_s, sizeof(adr_s));
	listen(s,20);
	struct sockaddr_in adr_c;
	socklen_t c_size = sizeof(struct sockaddr_in);
	int c=  accept(s, (struct sockaddr *)&adr_c, &c_size);
	float buffer[160]={0};
	int len=0;
	int cnt=0;
	while((len = recv(c, buffer, 160*sizeof(float), 0))>0)
	{	cnt++;
		printf("Frame:%d{",cnt);					
		for(int i=0;i<160;i++)
		    printf("%f,",buffer[i]);
		printf("}\n");
		
	}
	close(s);
	close(c);
	return 0;


}
