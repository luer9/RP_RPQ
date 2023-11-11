#pragma once
#include "database.h"
#ifndef PARSER_H_
#define PARSER_H_



class Parser {
public:
	

	class Query_seq {
	public:
		vector<vector<Utilities::hash64_t>> COM_query;//��ͨ�Ĳ�ѯ�����飬��������Ϊ�ֽ��
		vector<int > COM_ques;//��ͨ��Ĳ�ѯִ��˳��
		vector<Query_seq> child_query;//�Ӳ�ѯ�����飬ÿ����ǰ���ÿ��������һ��
		vector<int > child_ques;//�Ӳ�ѯ��˳��
		vector<char > Wild;//��ǰ������η�����ǰ����������η���������� ** ++ ��ʾ
		double total_sa = 0.0;//��ǰ����ܴ���
		Database database;
		vector<vector<int >> To;//��ѯ���򣬴�Ÿ����Ӳ�ѯ���ڲ�����
		map<Utilities::hash64_t, double> p_sum;//����������Ԫ������
		map<Utilities::hash64_t, double> p_sta;//�������Ե�ͳ��ֵ

		Query_seq() {}
		Query_seq(Database d) : database(d) {}
		~Query_seq() {}

		double conut_sa(Query_seq& root){//���쵱ǰ��εĲ�ѯ���У�ÿ�����˳��
			if (root.COM_query.empty() && root.child_query.empty())
				return 0;
			vector<double> temp_COMnums;
			for (auto iter1 : root.COM_query ) {
				double temp_sa = 0;
				for (auto  &iter11 : iter1) {

					temp_sa += p_sta[iter11];
				}
				total_sa += temp_sa;
				temp_COMnums.push_back(temp_sa);
			}
			unordered_set<int > index;

			for (int i = 0; temp_COMnums.size() != 0 && i < temp_COMnums.size(); i++) {
				int max = i;
				for (int j = 0; j < temp_COMnums.size(); j++) {
					if (temp_COMnums[j] > temp_COMnums[i] && index.find(j) == index.end())
						max = j;
				}
				index.insert(max);
			}
			COM_ques.assign(index.begin(), index.end());

			index.clear();
			temp_COMnums.clear();
			for (auto &iter2 : root.child_query) {
				iter2.p_sta = p_sta;
				double temp_sa = 0;
				temp_sa = iter2.conut_sa(iter2);
				temp_COMnums.push_back(temp_sa);
				total_sa += temp_sa;
			}
			for (int i = 0; temp_COMnums.size() != 0 && i < temp_COMnums.size(); i++) {
				int max = i;
				for (int j = 0; j < temp_COMnums.size(); j++) {
					if (temp_COMnums[j] > temp_COMnums[i] && index.find(j) == index.end())
						max = j;
				}
				index.insert(max);
			}
			child_ques.assign(index.begin(), index.end());
			/*if (stoi(Wild.back()) == '*' || stoi(Wild.back()) == '+')
				total_sa *= (COM_ques.size() + child_query.size());*/

			return total_sa;
		}

		void pritf_se() {
			for (int i = 0; i < COM_ques.size(); i++)
				cout << COM_ques[i] << endl;
			for (int i = 0; i < child_ques.size(); i++)
				cout << child_ques[i] << endl;
		}

		Utilities::hash64_t find_first(vector<Utilities::hash64_t>& COM_query, vector<char > Wild) {
			Utilities::hash64_t res = 0;
			for (int i = 0; i < COM_query.size(); i++) {
				if (res < database.p_sum[COM_query[i]])
					res = COM_query[i];
			}
			return res;
		}

		double child_allsa(vector<Utilities::hash64_t> child, char total_wild) {
			double res = 0;
			for (int i = 0; i < child.size(); i++) {
				res += database.p_sum[child[i]];
			}
			if (total_wild == '+' || total_wild == '*')
				res *= child.size();
			return res;
		}
	};


	Database d;
	string path_query;//ԭ��ѯ
	map<int ,Utilities::hash64_t > Hash_query;//��ѯ���Ե�hashֵ
	vector<string > Code_query;//����Ҫȥ����ı���õĲ�ѯ����
	Query_seq query_se_tem;//��ѯ����

	vector <vector<Utilities::hash64_t >> query_se;//��ѯ���У����ź���
	
	
	void Hash(const string query);
	int Query_Parser(const vector<string >& query, vector<Query_seq>& query_se);
	void Build_se();

	Parser();
	~Parser();

};


#endif