#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 59000





int main(void){
	
	int fd, ret, nread, addrlen;
	struct hostent *hostptr;
	struct sockaddr_in serveraddr, clientaddr;
	int addrlen;
	
	if((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)exit(1);//ERROR
	
	memset((void*)&serveraddr,(int)’\0’,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons((u_short)PORT);
	
	ret=bind(fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(ret==-1)exit(1);

	while(1){
		addrlen=sizeof(clientaddr);
		nread=recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&clientaddr,	&addrlen);
		if(nread==-1)exit(1);
		ret=sendto(fd,msg,strlen(msg)+1,0,(struct sockaddr*)&clientaddr,addrlen);
		if(ret==-1)exit(1);
	}
	close(fd); 
}
