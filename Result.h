#pragma once
#include "Parser.h"
#ifndef RESULT_H
#define RESULT_H
class Query
{
public:
	Database *d;
	Parser::Query_seq cur_query;
	int cur_qysums ;
	typedef struct Single//用来存放一个括号内的查询内容
	{
		vector< Utilities::hash64_t> cur_p;
		vector< vector<Database::Tri>> cur_T;
		//set<map<Utilities::hash64_t, Utilities::hash64_t>> p_two;
		deque<vector< Database::Tri>> res_q;
		vector<int> rec_cover;
		map<Utilities::hash64_t, map<Database::Tri, int>> Wild_T;
		int to;//方向0左1右
		int cur_psums;
		vector<map<Database::Tri, Database::Tri>> o_s;
		vector<int > recover;

		Single() : cur_psums(0) , to(1){};
		void merge(Single& first, Single& second) {
			for (int i = 0; i < first.res_q.size(); i++)
				first.res_q[i].insert(first.res_q[i].end(), second.res_q[i].begin(), second.res_q[i].end());
		}
	
	}one;

	vector<one> res_cluster;
	vector<one> res_child;
	Query();
	Query(Parser::Query_seq x, Database* data) : cur_query(x) , cur_qysums(0), d(data){};
	~Query();

	map<Database::Tri, int> find_rec(vector< Database::Tri>& res_col, Utilities::hash64_t key);
	Query::one control();//总的入口，最后返回当前层次的全部路径
	Query::one query_process_c(vector<Utilities::hash64_t> query, vector<char > Wild);
	Query::one query_process_p(vector<Utilities::hash64_t> query, vector<char > Wild, vector< Database::Tri> pre_res);//对一个括号内的查询操作
	Query::one query_process(vector<Utilities::hash64_t> query, vector<char > Wild);//对一个括号内的查询操作
	void printf(Query::one res);

private:

};


#endif