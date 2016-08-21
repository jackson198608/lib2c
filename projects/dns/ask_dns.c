#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include "ask_dns.h"

/*
	设置dns报文头部12个字节
	仅仅一般仅仅在问题数部分写成1
	结构如下：
	2字节标识：dns传输id，这里设置成00
	2字节标志
	2字节问题数:设置成1
	2字节资源记录数：查询包设置成0
	2字节授权资源记录数：查询包设置成0
	2字节额外资源记录数：查询包设置成0
	
*/
void setAHead(unsigned char *buf)
{
  buf[0] = 0x0;
  buf[1] = 0x0;
  buf[2] = 0x0;
  buf[3] = 0x0;
  buf[4] = 0x0;
  buf[5] = 0x1;
  buf[6] = 0x0;
  buf[7] = 0x0;
  buf[8] = buf[9] = buf[10] = buf[11] = 0x0;
}

/*
	将要查询的域名，改成可以填充到报文"查询问题"部分的格式
	www.goumin.com  =>   3www5goumin3com0
	改后的字符串肯定是之前的domainLen+2
	结果保存在name数组中
*/
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

/*
	拼装出最后的请求报文，放到buf中
	查询最终报文=  header + "查询问题:查询名部分" + 
				"查询问题:查询类型部分(2个字节,第一个为0,第二个为1)" +
				 "查询问题:查询类型部分(2个字节，第一个为0,第二个为1)" 

	因为是查询报文，所以回答字段，授权字段,附件信息字段都为空
	
*/
void setQuery(char *name, unsigned char *buf, int len,int type)
{
  strcat(buf+12,name);
  int pos = len + 12;
  buf[pos] = 0;
  buf[pos+1] = (type == 0)?1:5;
  buf[pos+2] = 0;
  buf[pos+3] = 1;
}

int sendDNSPacket(unsigned char *buf, int len, char *recvMsg)
{
	int s;
	struct sockaddr_in sin;
	
	memset(&sin,0,sizeof(sin));
	sin.sin_addr.s_addr = inet_addr(DNS_SERVER);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERVER_PORT);

	//SOCK_DGRAM:面向无连接  SOCK_STREAM:面向有连接
	s = socket(PF_INET,SOCK_DGRAM,0); 	

	//send, sendto, sendmsg - send a message on a socket
	sendto(s,buf,len,0,(struct sockaddr *)&sin,sizeof(sin));
	return recv(s,recvMsg,MAX_SIZE,0);

}

/*
	len：之前请求包的长度
	len_recvMsg: 响应包的长度
	响应报文会包含之前请求报文的部分，所以查看答案信息之前从len之后找
*/
void resolve(unsigned char *recvMsg, int len, int len_recvMsg,dnsResult* result)
{
  int pos = len;
  int cnt = 12;
  if(pos < len_recvMsg) {
	/*
		回答部分的第2个字节,因为域名和查询问题部分一致
		所有不在保存实际数据，用2个字节的指针替代,直接报文中查询域名部分的offset
	*/
    unsigned char now_pos = recvMsg[pos+1];  											
    unsigned char retype = recvMsg[pos+3];   //回答部分的第4个字节
    unsigned char reclass = recvMsg[pos+5];  //回答部分的第6个字节
    unsigned char offset = recvMsg[pos+11];	 //回答部分的第12个字节		
    if(retype == 1) { //a record
      if(now_pos == cnt && reclass == 1) {
		result->result[0]=recvMsg[pos+12];
		result->result[1]=recvMsg[pos+13];
		result->result[2]=recvMsg[pos+14];
		result->result[3]=recvMsg[pos+15];
		result->len=4;
		return;
      }
    }
    else if(retype == 5) {  //cname record
		if(now_pos == cnt && reclass == 1) {
			int msgResultPartLen=len_recvMsg - (pos+12);
			int copyLen= (result->len-1)>msgResultPartLen?msgResultPartLen:(result->len-1);
			for(int i=0;i<copyLen;i++){
				result->result[i]=recvMsg[pos+12+i];
			}		

			printf("hellodfas: %d\n",copyLen);
			result->len=copyLen;
			return;
		}
    }
  }
}

/*
result: the array save the ip result
resultLen: len of result array
domain: char array save the search domain name
domainLen: len of the domain array
type:  0: A 1:cname
*/
void getARecord(dnsResult *result,char* domain,int domainLen,int type)
{
	unsigned char buf[MAX_SIZE]; /* socket发送的数据 */
	char name[MAX_SIZE]; /* 转换为符合DNS报文格式的域名 */
	char recvMsg[MAX_SIZE]; /* 接收的数据 */
	int len; /* socket发送数据的长度 */
	
	len = changeDN(domain,domainLen,name);
	//printName(len,name); /* 打印转换后的域名，检测是否转换正确 */
	//printf("len is %d\n",len);
	setAHead(buf);
	setQuery(name,buf,len,type);
	
	len += 16;
	int len_recvMsg = sendDNSPacket(buf,len,recvMsg);
	resolve(recvMsg,len,len_recvMsg,result);
}

/*
int main(){
	unsigned result[4];
	char doamin[MAX_SIZE]="www.163.com";
	getARecord(result,4,doamin,strlen(doamin));
	printf("%u.%u.%u.%u\n",result[0],result[1],result[2],result[3]);
}
*/
