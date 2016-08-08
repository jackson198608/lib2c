say: sleep.o say.o talk.o
	cc -o say sleep.o say.o talk.o

say.o: sayhello.c
	cc -c sayhello.c -o say.o

sleep.o: sleep.c
	cc -c sleep.c -o sleep.o

talk.o: talk.c
	cc -c talk.c -o talk.o 

clean:
	rm say say.o sleep.o talk.o 
