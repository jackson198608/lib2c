#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define MAX_SIZE 1024
#define SERVER_PORT 53
#define DNS_SERVER "114.114.114.114"

void setHead(unsigned char *buf)
{

  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  buf[4] = 0;
  buf[5] = 1;
  buf[6] = 0;
  buf[7] = 0;
  buf[8] = buf[9] = buf[10] = buf[11] = 0;
}

void setQuery(char *name, unsigned char *buf, int len)
{
  strcat(buf+12,name);
  int pos = len + 12;
  buf[pos] = 0;
  buf[pos+1] = 1;
  buf[pos+2] = 0;
  buf[pos+3] = 1;
}

int changeDN(char *domain,int domainLen,char *name)
{
  int i = domainLen - 1;
  int j = i + 1;
  int k;
  name[j+1] = 0;
  for(k = 0; i >= 0; i--,j--) {
    if(domain[i] == '.') {
      name[j] = k;
      k = 0;
    }
    else {
      name[j] = domain[i];
      k++;
    }
  }
  name[0] = k;
  return (domainLen + 2);
}
void printName(int len, char *name)
{
  int i;
  for(i = 0; i < len; i++) printf("%x.",name[i]);
  printf("\n");
}

int sendDNSPacket(unsigned char *buf, int len, char *recvMsg)
{
  int s;
  struct sockaddr_in sin;

  memset(&sin,0,sizeof(sin));
  sin.sin_addr.s_addr = inet_addr(DNS_SERVER);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(SERVER_PORT);

  s = socket(PF_INET,SOCK_DGRAM,0);
  sendto(s,buf,len,0,(struct sockaddr *)&sin,sizeof(sin));
  return recv(s,recvMsg,MAX_SIZE,0);

}
void resolve(unsigned char *recvMsg, int len, int len_recvMsg,unsigned* result,int resultLen)
{
	printf("testdddd\n");
  int pos = len;
  int cnt = 12;
  while(pos < len_recvMsg) {
    unsigned char now_pos = recvMsg[pos+1];
    unsigned char retype = recvMsg[pos+3];
    unsigned char reclass = recvMsg[pos+5];
    unsigned char offset = recvMsg[pos+11];
    if(retype == 1) {
      if(now_pos == cnt && reclass == 1) {
        printf("%u.%u.%u.%u\n",recvMsg[pos+12],recvMsg[pos+13],recvMsg[pos+14],recvMsg[pos+15]);
		result[0]=recvMsg[pos+12];
		result[1]=recvMsg[pos+13];
		result[2]=recvMsg[pos+14];
		result[3]=recvMsg[pos+15];
		return;
      }
    }
    else if(retype == 5) {
      cnt = pos + 12 ;
    }
    pos = pos + 12 + offset;
  }
}

/*
result: the array save the ip result
resultLen: len of result array
domain: char array save the search domain name
domainLen: len of the domain array
*/
void getARecord(unsigned *result,int resultLen,char* domain,int domainLen)
{
  unsigned char buf[MAX_SIZE]; /* socket发送的数据 */
  char name[MAX_SIZE]; /* 转换为符合DNS报文格式的域名 */
  char recvMsg[MAX_SIZE]; /* 接收的数据 */
  int len; /* socket发送数据的长度 */
  int s; /* socket handler */

  len = changeDN(domain,domainLen,name);
  //printName(len,name); /* 打印转换后的域名，检测是否转换正确 */
  int j;
  //printf("len is %d\n",len);
  setHead(buf);
  setQuery(name,buf,len);
  len += 16;
  int len_recvMsg = sendDNSPacket(buf,len,recvMsg);
  int i;
  resolve(recvMsg,len,len_recvMsg,result,resultLen);

}


int main(){
	unsigned result[4];
	char doamin[MAX_SIZE]="www.163.com";
	getARecord(result,4,doamin,strlen(doamin));
	printf("%u\n",result[0]);

}
