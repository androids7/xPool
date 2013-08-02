#include "pool.h" 
#include <unistd.h>
#include <stdlib.h>
using std::cout;
using std::endl;

void* handler(void* arg){
	long tid = (long)arg;

	//cout << "tid =[" << tid << "]" << endl;
	Connection* conn = Pool::getConnection();

	if(!conn){
		cout << "getConnection NULL pointer" << endl;
		exit(-1);
	}
	
	//cout << "Connection.this:" << conn << endl;

	const char* query;
	query = "select * from student;";

	QueryResult queryResult = conn->executeQuery(query);

	Pool::releaseConnection(conn);

	//for(int i=0;i<queryResult.getRowCount();i++){
	//	for(int j=0;j<queryResult.getColumnCount();j++){
	//		cout << queryResult.getElement(i,j) << " ";
	//	}
	//	cout << endl;
	//}
}


int main(int argc,  char* argv[]){
	string host = "localhost";
	string user = "root";
	string pass = "jiqim1ma";
	string dbname = "hcx";
	int poolSize = 152;

	Pool::initPool(host,user,pass,dbname,poolSize);
	
	///std::cin.get();

	unsigned int count = -1;
	if(argc>1){
		count = atoi(argv[1]);
	}

	for(int i=0;i < count;i++){

		const int THREAD_COUNT = 250;
		pthread_t threads[THREAD_COUNT];
		for(long i=0;i<THREAD_COUNT;i++){
			pthread_create(&threads[i],NULL,handler,(void*)i);
			//sleep(1);
		}

		for(int i=0;i<THREAD_COUNT;i++){
			pthread_join(threads[i],0);
		}

		cout << "==============================LOOPBACK=================================" << endl;
	}

	Pool::destroyPool();



	return 0;
}
