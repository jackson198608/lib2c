#ifndef _ASK_DNS_H_
#define _ASK_DNS_H_

	#define MAX_SIZE 1024
	#define SERVER_PORT 53
	#define DNS_SERVER "114.114.114.114"
	
	typedef struct dnsResult{
		char result[100];
		int len;
	}dnsResult;

	void getARecord(dnsResult *result,char* domain,int domainLen,int type);

#endif
