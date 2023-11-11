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
	typedef struct Single//�������һ�������ڵĲ�ѯ����
	{
		vector< Utilities::hash64_t> cur_p;
		vector< vector<Database::Tri>> cur_T;
		//set<map<Utilities::hash64_t, Utilities::hash64_t>> p_two;
		deque<vector< Database::Tri>> res_q;
		vector<int> rec_cover;
		map<Utilities::hash64_t, map<Database::Tri, int>> Wild_T;
		int to;//����0��1��
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
	Query::one control();//�ܵ���ڣ���󷵻ص�ǰ��ε�ȫ��·��
	Query::one query_process_c(vector<Utilities::hash64_t> query, vector<char > Wild);
	Query::one query_process_p(vector<Utilities::hash64_t> query, vector<char > Wild, vector< Database::Tri> pre_res);//��һ�������ڵĲ�ѯ����
	Query::one query_process(vector<Utilities::hash64_t> query, vector<char > Wild);//��һ�������ڵĲ�ѯ����
	void printf(Query::one res);

private:

};


#endif