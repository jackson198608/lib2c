basic: basicPipWithName.o basicTest.o
	g++ -o basicTest basicPipWithName.o basicTest.o
basicPipWithName.o: basicPipWithName.h basicPipWithName.cpp
	g++ -c basicPipWithName.cpp
basicTest.o: basicPipWithName.h basicTest.cpp
	g++ -c basicTest.cpp
clean:
	rm basicTest basicPipWithName.o basicTest.o
