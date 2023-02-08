main: main.o Wrapper.o
	g++ -g main.o Wrapper.o -o main
	-rm *.o
main.o: main.cpp Wrapper.h
	g++ -c -g main.cpp -o main.o
Wrapper.o: Wrapper.cpp Wrapper.h List.h
	g++ -c -g Wrapper.cpp -o Wrapper.o
clean:
	-rm *.o main