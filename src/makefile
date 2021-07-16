CFLAGS = -O -Wall -Wextra -pedantic -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
CC = g++-11
main: main.o
	$(CC) $(CFLAGS) -o main main.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm -f core *.o%   
