libaskDns.so: ask_dns.o
	gcc -shared  -o libaskDns.so ask_dns.o
ask_dns.o: ask_dns.c ask_dns.h
	gcc -fpic -o ask_dns.o -c ask_dns.c 
clean:
	rm -rf libaskDns.so ask_dns.o
install:
	cp -p ask_dns.h /usr/include/
	cp -p libaskDns.so /usr/lib/ 
