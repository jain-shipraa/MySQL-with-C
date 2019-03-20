#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#define b 200
#define s 100
#define PORT 43454

#include<string.h>

#include "/usr/include/mysql/mysql.h"


static char *host="localhost";
static char *user="root";
static char *pass="test";

static char *dbname="mysql";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag=0;


int main()
{

 printf("DATABASE CONNECTION USING C \n\n\n");
  //Connection to mysql server !!
  MYSQL *conn=mysql_init(NULL);
   if(!(mysql_real_connect(conn,host,user,pass,dbname,port,unix_socket,flag)))
     {
      fprintf(stderr,"\nError: %s [%d]\n", mysql_error(conn),mysql_errno(conn));
      exit(1);
     }
   else
      printf("!!!! DATABASE CONNECTION SUCESSFULL !!!\n\n");
//Creating Table test !!

  if (mysql_query(conn, "CREATE TABLE chat(Message TEXT,Date DATE,Time TIME)"))     
     printf("Connected to Chat Table\n\n");
  else
     printf("NOT connected to Chat Table\n\n");

/*  if (mysql_query(conn, "CREATE TABLE server(Message TEXT,Date DATE,Time TIME)"))     
     printf("Connected to Server Table\n\n");
  else
     printf("NOT connected to Server Table\n\n");*/

  int num , ch;

  char s1[50];
  char s2[50];
  
  char s3[50];
  
  char st[50];
  strcpy(st,",NOW(),NOW()");
  char s7[10]= ");";
  char s5[10] = "\'";


  struct sockaddr_in servaddr,cliaddr;
  int sd,con,r,w;
  char msgsnd[b],msgrcv[b];
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  servaddr.sin_port=htons(PORT);
  sd=socket(AF_INET,SOCK_STREAM,0);
  printf("\n\nclient socket created:%d\n\n",sd);
  con=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  printf("\n\nclient connected:%d\n\n",con);

  //Switch case to perform Various operations !!
  printf("Enter \n1: for Chatting\n");
  printf("2: for Retrieving Messages\n");
  scanf("%d" , &num);


  switch(num)
  {
   case 1 :

   while(1)
    {
    strcpy(s1,"INSERT INTO chat VALUES(") ;
    printf("\nClient: ");
    scanf("%s",msgsnd);
    w=write(sd,&msgsnd,b);
    if((msgsnd[0]=='Q'&&msgsnd[1]=='\0')||(msgsnd[0]=='Q'&&msgsnd[1]=='U'&&msgsnd[2]=='I'&&msgsnd[3]=='T'&&msgsnd[4]=='\0'))
     {
       printf("\n\n***YOU EXITED***\n\n\n");
       break;
     }
    else
     {
     strcpy(s2,"Client: ");
     strncat(s2,msgsnd , strlen(msgsnd)) ;
     strncat(s1, s5 , strlen(s5)) ;
     strncat(s1, s2 , strlen(s2)) ;
     strncat(s1, s5 , strlen(s5)) ;
     strncat(s1,st,strlen(st));
     strncat(s1, s7 , strlen(s7)) ;
     //puts(s1);
       if (mysql_query(conn, s1))
         printf("\n\nNot inserted\n\n");

     }

   strcpy(s1,"INSERT INTO chat VALUES(") ;
   r=read(sd,&msgrcv,b);
   if((msgrcv[0]=='Q'&&msgrcv[1]=='\0')||(msgrcv[0]=='Q'&&msgrcv[1]=='U'&&msgrcv[2]=='I'&&msgrcv[3]=='T'&&msgrcv[4]=='\0'))
    {
     printf("\n\n***SERVER EXITED***\n\n\n");break;
    }
   else{
     printf("\nServer: %s",msgrcv);
     strcpy(s3,"Server: ");
     strncat(s3,msgrcv , strlen(msgrcv)) ;
     strncat(s1, s5 , strlen(s5)) ;
     strncat(s1, s3 , strlen(s3)) ;
     strncat(s1, s5 , strlen(s5)) ;
     strncat(s1,st,strlen(st));
     strncat(s1, s7 , strlen(s7)) ;
     //puts(s1);
     
     if (mysql_query(conn, s1))
       printf("\n\nNot inserted\n\n");
    }
  }
  break;
  
 case 2 :

  //Executing query for fetching Result
  if (mysql_query(conn, "SELECT * FROM chat")) 
  {
      //finish_with_error(con);
  }

  //storing result
  MYSQL_RES *result = mysql_store_result(conn);
  
  if (result == NULL) 
  {
      printf("No data");
  }

//printing result

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s\n", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n\n\n"); 
  }
  mysql_free_result(result);
  break ;
}

  close(sd);
  return 0;
}
