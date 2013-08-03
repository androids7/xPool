all: sbpool

sbpool: mine.cpp pool.cpp
	g++ -g -o sbpool mine.cpp pool.cpp -lmysqlclient -lpthread

clean:
	rm -f *.o sbpool core*
