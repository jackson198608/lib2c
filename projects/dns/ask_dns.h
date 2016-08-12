#ifndef _ASK_DNS_H_
#define _ASK_DNS_H_

	#define MAX_SIZE 1024
	#define SERVER_PORT 53
	#define DNS_SERVER "114.114.114.114"

	void getARecord(unsigned *result,int resultLen,char* domain,int domainLen);

#endif
