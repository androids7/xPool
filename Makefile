all: accessdb sbpool

accessdb: main.c
	gcc -g -o accessdb main.c -lmysqlclient

sbpool: mine.cpp pool.cpp
	g++ -g -o sbpool mine.cpp pool.cpp -lmysqlclient -lpthread

clean:
	rm -f *.o accessdb sbpool core*
