
#pragma comment( lib,"winmm.lib" )
#include"Utilities.h"
#include "Result.h"
#include<fstream>
#include<time.h>

using namespace std;




int main() {
	/*d.print();
	string str = "<http://db.uwaterloo.ca/~galuc/wsdbm/userId>";
	Utilities::hash64_t cur_p = Utilities::hash64(str, 0);
	cout << cur_p << endl;*/
	
	Parser query;
	query.d.build("lubm_10.nt");
	//query.d.print();
		
	int num = 8;

	query.path_query = "(<http://swat.cse.lehigh.edu/onto/univ-bench.owl#doctoralDegreeFrom>\\<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)";
	query.Build_se();
	Parser::Query_seq child_query1 = query.query_se_tem;
	Query q1;
	q1.cur_query = child_query1;
	q1.d = &query.d;
	int i1 = 10;
	dataFile << num-- << endl;
	while (i1--) {
		Query x = q1;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//DWORD end_time = timeGetTime();
		dataFile << "The run time is:" << seconds *1.00 << "ms!" << endl;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "(<http://swat.cse.lehigh.edu/onto/univ-bench.owl#worksFor>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#teacherOf>)";
	query.Build_se();
	Parser::Query_seq child_query2 = query.query_se_tem;
	Query q2;
	q2.cur_query = child_query2;
	q2.d = &query.d;
	int i2 = 10;
	dataFile << num-- << endl;
	while (i2--) {
		Query x = q2;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "(<http://swat.cse.lehigh.edu/onto/univ-bench.owl#name>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#teacherOf>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#mastersDegreeFrom>)";
	query.Build_se();
	Parser::Query_seq child_query3 = query.query_se_tem;
	Query q3;
	q3.cur_query = child_query3;
	q3.d = &query.d;
	int i3 = 10;
	dataFile << num-- << endl;
	while (i3--) {
		Query x = q3;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "(<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#name>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#emailAddress>*)";
	query.Build_se();
	Parser::Query_seq child_query4 = query.query_se_tem;
	Query q4;
	q4.cur_query = child_query4;
	q4.d = &query.d;
	int i4 = 10;
	dataFile << num-- << endl;
	while (i4--) {
		Query x = q4;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "(<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#name>)";
	query.Build_se();
	Parser::Query_seq child_query5 = query.query_se_tem;
	Query q5;
	q5.cur_query = child_query5;
	q5.d = &query.d;
	int i5 = 10;
	dataFile << num-- << endl;
	while (i5--) {
		Query x = q5;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "(<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#name>\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#memberOf>)";
	query.Build_se();
	Parser::Query_seq child_query6 = query.query_se_tem;
	Query q6;
	q6.cur_query = child_query6;
	q6.d = &query.d;
	int i6 = 10;
	dataFile << num-- << endl;
	while (i6--) {
		Query x = q6;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "((<http://swat.cse.lehigh.edu/onto/univ-bench.owl#takesCourse>\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#telephone>)*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#emailAddress> )";
	query.Build_se();
	Parser::Query_seq child_query7 = query.query_se_tem;
	Query q7;
	q7.cur_query = child_query7;
	q7.d = &query.d;
	int i7 = 10;
	dataFile << num-- << endl;
	while (i7--) {
		Query x = q7;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;

	query.path_query = "((<http://swat.cse.lehigh.edu/onto/univ-bench.owl#takesCourse>\\<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#name>*\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#advisor>\\<http://swat.cse.lehigh.edu/onto/univ-bench.owl#publicationAuthor>)";
	query.Build_se();
	Parser::Query_seq child_query8 = query.query_se_tem;
	Query q8;
	q8.cur_query = child_query8;
	q8.d = &query.d;
	int i8 = 10;
	dataFile << num-- << endl;
	while (i8--) {
		Query x = q8;
		clock_t start, end;
		start = clock();           
		//DWORD start_time = timeGetTime();
		Query::one result = x.control();
		end = clock(); 
		double seconds  =(double)(end - start)/CLOCKS_PER_SEC;
		//cout << "The run time is:" << (end_time - start_time)*1.00  << "ms!" << endl;//输出运行时间
	}
	dataFile << "++++++++++++++++++++++++++++++++" << endl;




	return 1;
}