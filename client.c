#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#define PORT 58011

char awt[128], topic[128], name[128], ECPname[128];
int num,QID, i=0;
int tesIp, tesPort;


void list(){
	sscanf(awt, "AWT %d %[^\t\n]\n", &num, topic);
	while (i < num) {
		sscanf(topic, "%s %[^\t\n]",name,topic);
		printf( "%d - %s\n", i+1, name);
		i++;
	}
}

void request(int Tnn){
	int fd, nbytes, nleft, nwritten, nread,n;
	char responseServer[128], buffer[128], *ptr;
	n=sendto(fd,"TER %d\n",Tnn,6,0,(struct sockaddr*)&addr,addrlen);
	if(n==-1)exit(1);
	
	n=recvfrom(fd,responseServer,128,0,(struct sockaddr*)&addr,&addrlen);
	if(n==-1)exit(1);
	
	sscanf(responseServer, "AWTES %d %d\n", &num, %tesIp, %tesPort);
	
	fd=socket(AF_INET,SOCK_STREAM,0); //socket tcp
	if(fd==-1)exit(1);
	
	hostptr=gethostbyname(tesIP); 
	
	memset((void*)&serveraddr,(int)’\0’, sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port=htons((u_short)tesPort);
	
	n=connect(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(n==-1)exit(1);
	
	prt=strcpy(buffer, "RQT %d\n", studentNum)
	nbytes=10;
	
	nleft=nbytes;
	while(nleft>0){nwritten=write(fd,ptr,nleft); //write to TCP "RQT number"
					if(nwritten<=0)exit(1);
					nleft-=nwritten;
					prt+=nwritten;}
	nleft=nbytes;
	ptr=&buffer[0];
	while(nleft>0){nread=read(fd,ptr,nleft); //read from tcp
					if(nread==-1)exit(1);
					else if(nread==0)break;
					nleft-=nread;
					ptr+=nread;}
	nread=nbytes-nleft;
	sscanf(buffer, "AQT %s %s %d ")
	close(fd);
}

void submit(char* V1, char* V2, char* V3, char* V4, char* V5){
	int fd, nbytes, nleft, nwritten, nread;
	char responseServer[128], buffer[128], *ptr;
	n=sendto(fd,"TER %d\n",Tnn,6,0,(struct sockaddr*)&addr,addrlen);
	if(n==-1)exit(1);
	
	n=recvfrom(fd,responseServer,128,0,(struct sockaddr*)&addr,&addrlen);
	if(n==-1)exit(1);
	
	sscanf(responseServer, "AWTES %d %d\n", &num, %tesIp, %tesPort);
	
	fd=socket(AF_INET,SOCK_STREAM,0); //socket tcp
	if(fd==-1)exit(1);
	
	hostptr=gethostbyname(tesIP); 
	
	memset((void*)&serveraddr,(int)’\0’, sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
	serveraddr.sin_port=htons((u_short)tesPort);
	
	n=connect(fd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(n==-1)exit(1);
	
	prt=strcpy(buffer, "RQS %d %d %s %s %s %s\n", studentNum, QID, V1, V2, V3, V4, V5)
	nbytes=43;
	
	nleft=nbytes;
	while(nleft>0){nwritten=write(fd,ptr,nleft); //write to TCP "RQS number QID answers"
					if(nwritten<=0)exit(1);
					nleft-=nwritten;
					prt+=nwritten;}
					
	
	nleft=nbytes;
	ptr=&buffer[0];
	while(nleft>0){nread=read(fd,ptr,nleft); //read from tcp
					if(nread==-1)exit(1);
					else if(nread==0)break;
					nleft-=nread;
					ptr+=nread;}
	nread=nbytes-nleft;
	sscanf(buffer, "AQT %s %s %d ")
	close(fd);
}

void exit(){
	exit(0);
}

 int main(int studentNum, char* ECPname, int ECPport) {
 	int fd, addrlen, n, c;
 	struct hostent *hostptr;
 	struct sockaddr_in addr;

 	if((fd=socket(AF_INET, SOCK_DGRAM,0))==-1)exit(1);
 	
 	hostptr=gethostbyname(ECPname);
 	
 	memset((void*)&addr, (int)'\0',sizeof(addr));
 	addr.sin_family=AF_INET;
 	addr.sin_addr.s_addr=((struct in_addr *)(hostptr->h_addr_list[0]))->s_addr;
 	addr.sin_port=htons((u_short)ECPport);
	
	
	addrlen=sizeof(addr);
	
	n=sendto(fd,"TQR\n",4,0,(struct sockaddr*)&addr,addrlen);
	if(n==-1)exit(1);
	
	n=recvfrom(fd,awt,128,0,(struct sockaddr*)&addr,&addrlen);
	if(n==-1)exit(1);

	write(1,awt,n);
	list();
	close(fd);
 }

