#include "Parser.h"


Parser::Parser() {
	path_query = "1";
}

Parser::~Parser() {

}


int Parser::Query_Parser(const vector<string >& query, vector<Query_seq>& query_se) {
	int len = query.size();
	int child_id = 0;
	string chile_query = "";
	//vector<Utilities::hash64_t> child_query;
	
	char c;
	//int x = 0;
	int brackets_num = 0;
	Query_seq temp_query;
	int size = 0;
	for (int i = 0; i < len; i++) {
		if (stoi(query[i]) == '(')
			size++;
	}
	temp_query.COM_query.assign(size, vector<Utilities::hash64_t>());
	size = 0;
	for (int i = 0; i < len; i++) {
		if (stoi(query[i]) == '\\')
			size++;
	}
	temp_query.Wild.assign(size + 1,NULL);
	

	for (int i = 1; i < len; i++) {
		c = stoi(query[i]);
		if (c == '(') {
			brackets_num++;
			i += Query_Parser(vector<string>(query.begin() + i , query.end()), temp_query.child_query);
		}	
		else if (c == '+' || c == '*' )
		{
			temp_query.Wild[child_id] = c;
		}
		else if (c <= 9 && c >= 0 ) {
			Utilities::hash64_t p = Hash_query[c];
			temp_query.COM_query[brackets_num].push_back(p);
			child_id++;
		}
		else if (c == '\\' && stoi(query[i + 1]) != '(')
		{
			//child_query.push_back(x);
			
			//x = 0;
		}
		else if (c == ')') {
	
			if (i < len - 1 && stoi(query[i + 1]) == '*') {
				temp_query.Wild.push_back('/');
				i++;
			}
			else if (i < len - 1 && stoi(query[i + 1]) == '+') {
				temp_query.Wild.push_back('-');
				i++;
			}
			//else if (i < len && path_query[i + 1] == '|') {
			//	wild.push_back("||");
			//	i++;
			//}
			//Build_onese(child_query, wild);
			//child_query.clear();
			temp_query.COM_query.resize(brackets_num + 1);
			query_se.push_back(temp_query);
			return i;
		}
	}
}

void Parser::Hash(const string query) {//将查询转化为编码表和编码形式，编码形式用于做处理
	string long_long = "";
	int id_childq = 0;
	for (int i = 0; i < query.size(); i++) {
		if (query[i] == '(' || query[i] == '*' || query[i] == '+' || query[i] == '|' )
			Code_query.push_back(to_string(query[i]));
		else if ( (query[i] == '\\' || (query[i] == ')' && query[i - 1] != '(' )))
		{
			if (long_long != "") {
				Utilities::hash64_t hash_value = Utilities::hash64(long_long);
				Hash_query[id_childq] = hash_value;
				Code_query.push_back(to_string(id_childq));
				long_long = "";
				id_childq++;
			}
			
			Code_query.push_back(to_string(query[i]));
			
		} 
		else if(query[i] == ')')
			Code_query.push_back(to_string(query[i]));
		else
		{
			long_long += query[i];
		}
	}
}

void pritf(const Parser::Query_seq zhongjie) {
	cout << "父查询" << endl;
	for (auto iter1 : zhongjie.COM_query) {
		for (auto iter11 : iter1)
			cout << iter11 << endl;
	}
	cout << "子查询" << endl;
	if (!zhongjie.child_query.empty()) {
		vector<Parser::Query_seq> child = zhongjie.child_query;
		for (auto iter2 : child)
			pritf(iter2);
	}
}

void Parser::Build_se() {
	
	int len = path_query.size();
	Hash(path_query);
	for (auto iter : Hash_query) {
		cout << iter.second << "\t";

	}
	cout << endl;
	for (auto iter : Code_query) {
		cout << iter << "\t";

	}
	cout << endl;
	Query_seq zhongjie;
	zhongjie.p_sta = d.p_sta;
	int i = Query_Parser(Code_query, zhongjie.child_query);
	pritf(zhongjie);
	zhongjie.conut_sa(zhongjie);
	
	query_se_tem = zhongjie.child_query[0];
}

