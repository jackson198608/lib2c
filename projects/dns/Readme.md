测试使用程序:

	#include <stdio.h>
	#include <string.h>
	#include <ask_dns.h>
	
	int main(){
	    unsigned result[4];
	    char doamin[MAX_SIZE]="www.163.com";
	    getARecord(result,4,doamin,strlen(doamin));
	    printf("%u.%u.%u.%u\n",result[0],result[1],result[2],result[3]);
		return 0;
	}


编译方法:
	gcc -o main main.c -laskDns



函数列表：
	void setHead(unsigned char *buf)
		dns查询报文创建头部,传入缓冲区数组


	int changeDN(char *domain,int domainLen,char *name)
		字符串类型的domain转换成报文中对应的内容
		
	void setQuery(char *name, unsigned char *buf, int len)
		构造最终的dns包

	int sendDNSPacket(unsigned char *buf, int len, char *recvMsg)
		发送dns请求包
		
	void resolve(unsigned char *recvMsg, int len, int len_recvMsg,unsigned* result,int resultLen)
		解析返回地址

	void getARecord(unsigned *result,int resultLen,char* domain,int domainLen)
		对外接口函数
