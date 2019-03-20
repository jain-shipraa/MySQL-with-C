#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define buff 200
#define PORT 43454
int main(){
struct sockaddr_in servaddr,cliaddr;
int sd,sesfd,clilen,bi,r,w;
char msgsnd[buff],msgrcv[buff];
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);
clilen=sizeof(cliaddr);
sd=socket(AF_INET,SOCK_STREAM,0);
printf("\n\nServer socket created:%d\n\n",sd);
bi=bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("\n\nBinded:%d\n\n",bi);
listen(sd,20);
printf("\n\nserver listening\n\n");
while(1){
sesfd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
printf("\n\nAccepted\n\n");while(1)
{
r=read(sesfd,&msgrcv,buff);
if((msgrcv[0]=='Q'&&msgrcv[1]=='\0')||
(msgrcv[0]=='Q'&&msgrcv[1]=='U'&&msgrcv[2]=='I'&&msgrcv[3]=='T'&&msgrcv[4]=='\0')){
printf("\n\n***CLIENT EXITED***\n\n\n");
break;
}
else{
printf("\nClient: %s",msgrcv);
}
printf("\nServer: ");
gets(msgsnd);
w=write(sesfd,&msgsnd,buff);
if((msgsnd[0]=='Q'&&msgsnd[1]=='\0')||
(msgsnd[0]=='Q'&&msgsnd[1]=='U'&&msgsnd[2]=='I'&&msgsnd[3]=='T'&&msgsnd [4]=='\0')){
printf("\n\n***YOU EXITED***\n\n\n");
break;
}
}
close(sesfd);
}
close(sd);
return 0;
}
