#include "Result.h"

extern "C" int testgpu(vector<Database::Tri> first, vector<Database::Tri> second);
Query::Query()
{
	cur_qysums = 0;
}

Query::~Query()
{
}

vector<vector< Database::Tri>> Two_pro(vector<Database::Tri> first, vector<Database::Tri> second) {
	vector<vector< Database::Tri>> new_res(2);
	for (auto iter1 : first) {
		for (auto iter2 : second) {
			if (iter2.s == iter1.o) {
				new_res[0].push_back(iter1);
				new_res[1].push_back(iter2);
			}
				
		}
	}
	return new_res;
}

vector<vector< Database::Tri>> Two_pro_to(vector<Database::Tri> first, vector<Database::Tri> second) {
	vector<vector< Database::Tri>> new_res(2);
	for (auto iter1 : first) {
		for (auto iter2 : second) {
			if (iter2.s == iter1.o) {
				new_res[0].push_back(iter1);
				new_res[1].push_back(iter2);
			}

		}
	}
	return new_res;
}

map<Database::Tri, int> Query::find_rec(vector< Database::Tri>& res_col, Utilities::hash64_t key) {//初遇克林闭包，找到第一次连接对应的递归组
	map<Database::Tri, int> rec_res;
	int res;

	set<Database::Tri> col (res_col.begin(), res_col.end());
	vector<vector<Database::Tri>> rec_curp = d->all_rec[key];
	for (int i = 0; i < rec_curp.size(); i++) {//从该属性的所有组查找
		vector<Database::Tri> temp = rec_curp[i];
		for (int j = 0; j < temp.size(); j++) {//获得某组的三元组并判断是否存在于结果列中
			if (col.find(temp[j]) != col.end()) {//如果存在，个位记录第i组，十位记录结果列的三元组所在的位置，百位记录后面跟着的三元组的位置
				for (int k = j + 1; k < temp.size(); k++) {
					res = k * 100 + j * 10 + i;
					res_col.push_back(temp[k]);
					rec_res[temp[k]] = res;
					
				}
				break;
			}		
		}
	}
	
	return rec_res;
}

Query::one Query::query_process_c(vector<Utilities::hash64_t> query, vector<char > Wild) {
	Query::one res_one;
	res_one = query_process(query, Wild);
	if (Wild[Wild.size() - 1] == '/')
	{
		int num;
		vector< Database::Tri> res_set;
		vector< Query::one> res;
		res_set = res_one.res_q.back();
		res_one.recover.push_back(res_one.res_q.front().size());
		num = d->path_rec[query];
		while (num--) {
			res.push_back(query_process_p(query, Wild, res_set));
			res_set = res.back().res_q.back(); 
		}
		for (int i = 0; i < res.size(); i++) {
			res_one.recover.push_back(res[i].res_q.front().size());
			res_one.merge(res_one, res[i]);
			res_one.o_s.push_back(res[i].o_s[0]);
		}
	}

	return res_one;
}

Query::one Query::query_process_p(vector<Utilities::hash64_t> query, vector<char > Wild, vector< Database::Tri> pre_res) {//单个括号内的查询过程


	Query::one res_one;

	int size = query.size();
	for (int i = 0; i < size; i++) {//首先把所有的查询对应的三元组传入
		Utilities::hash64_t p = query[i];
		map<Utilities::hash64_t, vector<Database::Tri>> p_cur;
		p_cur[p] = d->p_to_ts[p];
		res_one.cur_T.push_back(p_cur[p]);
		res_one.cur_p.push_back(p);
		res_one.cur_psums++;
		res_one.rec_cover.push_back(res_one.cur_T.size());
	}
	res_one.res_q.push_back(res_one.cur_T[0]);
	//vector<vector< Database::Tri>> t = testgpu(pre_res, res_one.res_q[0]);
	//testgpu(pre_res, res_one.res_q[0]);
	vector<vector< Database::Tri>> t = Two_pro(pre_res,res_one.res_q[0]);
	res_one.res_q.pop_back();
	res_one.res_q.push_back(t[1]);
	
	if (Wild[0] == '*') {//为结果表第一列赋值，并且判定*
		Utilities::hash64_t key = res_one.cur_p[0];
		res_one.Wild_T[key] = find_rec(res_one.res_q[0], key);
	}
	for (int i = 0; i < res_one.cur_psums - 1; i++) {
		vector<vector< Database::Tri>> temp = Two_pro(res_one.res_q[i], res_one.cur_T[i + 1]);
		res_one.res_q.pop_back();
		res_one.res_q.push_back(temp[0]);
		res_one.rec_cover[i] = res_one.res_q[i].size();
		res_one.res_q.push_back(temp[1]);
		res_one.rec_cover[i + 1] = res_one.res_q[i + 1].size();
		if (Wild[i + 1] == '*') {//如果是向前连接出*则只需要判断右侧就好，此时rec_cover是右侧的正常结果
			Utilities::hash64_t key = res_one.cur_p[i + 1];
			res_one.Wild_T[key] = find_rec(res_one.res_q[i + 1], key);
		}
		int s = res_one.res_q.size();
		if (s > 2) {
			for (int j = s - 1; j > 0; j--) {
				vector< Database::Tri> first = res_one.res_q[j];
				vector< Database::Tri> second = res_one.res_q[j - 1];
				if (Wild[j - 1] == '*') {//向后连接需要判定rec_cover内
					vector<vector< Database::Tri>> temp_t = Two_pro_to(first, vector<Database::Tri>(second.begin(), second.begin() + res_one.rec_cover[j - 1]));
					res_one.res_q[j] = (temp_t[0]);
					res_one.res_q[j - 1] = (temp_t[1]);
					res_one.res_q[j - 1].insert(res_one.res_q[j - 1].end(), second.begin() + res_one.rec_cover[j - 1], second.end());
				}
				else {
					vector<vector< Database::Tri>> temp_t = Two_pro_to(first, second);
					res_one.res_q[j] = (temp_t[0]);
					res_one.res_q[j - 1] = (temp_t[1]);
				}
			}
		}
	}

	vector<vector< Database::Tri>> two = Two_pro(pre_res, res_one.res_q[0]);
	map<Database::Tri, Database::Tri> m;
	for (int i = 0; i < two[0].size(); i++) {
		m[two[0][i]] = two[1][i];
	}
	res_one.o_s.push_back(m);
	return res_one;

}

Query::one Query::query_process(vector<Utilities::hash64_t> query, vector<char > Wild) {//单个括号内的查询过程
	

	Query::one res_one;

	int size = query.size();
	for (int i = 0; i < size; i++) {//首先把所有的查询对应的三元组传入
		Utilities::hash64_t p = query[i];
		map<Utilities::hash64_t, vector<Database::Tri>> p_cur;
		p_cur[p] = d->p_to_ts[p];
		res_one.cur_T.push_back(p_cur[p]);
		res_one.cur_p.push_back(p);
		res_one.cur_psums++;
		res_one.rec_cover.push_back(res_one.cur_T.size());
	}
	res_one.res_q.push_back(res_one.cur_T[0]);


	if (Wild[0] == '*') {//为结果表第一列赋值，并且判定*
		Utilities::hash64_t key = res_one.cur_p[0];
		res_one.Wild_T[key] = find_rec(res_one.res_q[0], key);
	}
	for (int i = 0; i < res_one.cur_psums - 1; i++) {
		//testgpu(res_one.res_q[i], res_one.cur_T[i + 1]);
		//testgpu(res_one.res_q[i], res_one.cur_T[i + 1]);
		vector<vector< Database::Tri>> temp = Two_pro(res_one.res_q[i], res_one.cur_T[i + 1]);
		res_one.res_q.pop_back();
		res_one.res_q.push_back(temp[0]);
		res_one.rec_cover[i] = res_one.res_q[i].size();
		res_one.res_q.push_back(temp[1]);
		res_one.rec_cover[i + 1] = res_one.res_q[i + 1].size();
		if (Wild[i + 1] == '*') {//如果是向前连接出*则只需要判断右侧就好，此时rec_cover是右侧的正常结果
			Utilities::hash64_t key = res_one.cur_p[i + 1];
			res_one.Wild_T[key] = find_rec(res_one.res_q[i + 1], key);
		}
		int s = res_one.res_q.size();
		if (s > 2) {
			for (int j = s - 1; j > 0; j--) {
				vector< Database::Tri> first = res_one.res_q[j];
				vector< Database::Tri> second = res_one.res_q[j - 1];
				if (Wild[j - 1] == '*') {//向后连接需要判定rec_cover内
					vector<vector< Database::Tri>> temp_t = Two_pro_to(first, vector<Database::Tri>(second.begin(),second.begin() + res_one.rec_cover[j - 1]));
					res_one.res_q[j] = (temp_t[0]);
					res_one.res_q[j - 1] = (temp_t[1]);
					res_one.res_q[j - 1].insert(res_one.res_q[j - 1].end(), second.begin() + res_one.rec_cover[j - 1], second.end());
				}
				else {
					vector<vector< Database::Tri>> temp_t = Two_pro_to(first, second);
					res_one.res_q[j] = (temp_t[0]);
					res_one.res_q[j - 1] = (temp_t[1]);
				}
				
	/*			if (Wild[j] == '*') {
					Utilities::hash64_t key = res_one.cur_p[j];
					res_one.Wild_T[key] = find_rec(res_one.res_q[j], key);
				}*/
				
			}
		}
	}

	return res_one;

}

Query::one Query::control() {//总入口
	
	int com_sum = cur_query.COM_query.size();//获得普通属性组的多少
	int child_sum = cur_query.child_query.size();//获得孩子属性组的大小
	Query::one res_cur;
	
	/*res_cluster.resize(com_sum);
	res_child.resize(child_sum);*/
	/*for (auto iter1 : cur_query.child_query) {
		Query temp(iter1, d);
		res_child.push_back(temp.control);
	}

	for (auto iter2 : cur_query.COM_query) {
		res_cluster.push_back(query_process(iter2));
	}*/

	for (int i = 0; i < cur_query.COM_ques.size(); i++) {//对每个普通属性组都进行一次操作并按序号放入res_cluster中（一个普通属性组就是已经不带括号的属性）
		int j = cur_query.COM_ques[i];
		if(!cur_query.COM_query[j].empty())

			res_cluster.push_back(query_process_c(cur_query.COM_query[j], cur_query.Wild));
	}
	for (int i = 0; i < cur_query.child_ques.size(); i++) {//对每个孩子属性组查询，递归调用该算法
		int j = cur_query.child_ques[i];
		Query temp(cur_query.child_query[j], d);

		res_child.push_back(temp.control());
	}

	vector<Query::one>	res_all;
	int size = res_cluster.size();
	for (int i = 0; i < size; i++) {//把孩子属性组的答案和普通属性组答案拼接，顺序就是一个pt属性组后跟对应下标的孩子属性组答案，最后多一个普通属性组
		res_all.push_back(res_cluster[i]);
		if(res_child.size())
			res_all.push_back(res_child[i]);
	}
	//res_all.push_back(res_cluster[size - 1]);
	if (size == 0 && !res_child.empty()) {
		res_all.push_back(res_child[res_child.size() - 1]);
	}
	size = res_all.size();
	res_cur.cur_p.insert(res_cur.cur_p.end(), res_all[0].cur_p.begin(), res_all[0].cur_p.end());//为最后的链接做准备
	res_cur.res_q.insert(res_cur.res_q.end(), res_all[0].res_q.begin(), res_all[0].res_q.end());
	res_cur.cur_psums += res_all[0].cur_psums;
	res_cur.rec_cover.insert(res_cur.rec_cover.end(), res_all[0].rec_cover.begin(), res_all[0].rec_cover.end());
	res_cur.recover.insert(res_cur.recover.end(), res_all[0].recover.begin(), res_all[0].recover.end());
	for (auto iter0 : res_all[0].Wild_T) {
		res_cur.Wild_T[iter0.first]= iter0.second;
	}
	

	for (int i = 1; i < res_all.size(); i ++) {//最后的连接操作

		int set_num = 0;
		int first_size = res_cur.cur_psums;
		res_cur.cur_p.insert(res_cur.cur_p.end(), res_all[i].cur_p.begin(), res_all[i].cur_p.end());//以pt和孩子的交界为点，向孩子的尽头和pt的尽头延伸链接。
		res_cur.res_q.insert(res_cur.res_q.end(), res_all[i].res_q.begin(), res_all[i].res_q.end());
		res_cur.rec_cover.insert(res_cur.rec_cover.end(), res_all[i].rec_cover.begin(), res_all[i].rec_cover.end());
		for (auto iter0 : res_all[i].Wild_T) {
			res_cur.Wild_T[iter0.first] = iter0.second;
		}

		res_cur.cur_psums += res_all[i].cur_psums;
		int second_size = res_cur.cur_psums;
		vector<Database::Tri> first = res_cur.res_q[first_size - 1];
		vector<Database::Tri> second;
		vector<Database::Tri> temp_second = res_cur.res_q[first_size];
		if (!res_all[i].recover.empty())
		{
			set_num = res_all[i].recover[0];
			second = vector<Database::Tri>(res_cur.res_q[first_size].begin(), res_cur.res_q[first_size].begin() + set_num);
		}
		else
			second = temp_second;

		vector<vector< Database::Tri>> temp_t = Two_pro(first, second); //获得交界点的链接
		res_cur.res_q[first_size - 1] = temp_t[0];
		res_cur.res_q[first_size ] = temp_t[1];
		res_cur.res_q[first_size].insert(res_cur.res_q[first_size].end(), temp_second.begin() + set_num, temp_second.end());
		
		for (int j = first_size - 1; j > 0; j--) {//左连接操作
			vector<Database::Tri> left_f(res_cur.res_q[j].begin(), res_cur.res_q[j].begin() + res_cur.rec_cover[j]);
			vector<Database::Tri> left_s(res_cur.res_q[j - 1].begin(), res_cur.res_q[j - 1].begin() + res_cur.rec_cover[j - 1 ]);

			vector<vector< Database::Tri>> left = Two_pro_to(left_f, left_s);
			res_cur.res_q[j - 1] = left[0];
			res_cur.res_q[j] = left[1];
		}

		for (int j = first_size ; j < second_size - 1; j ++) {//右连接操作
			vector<Database::Tri> right_f;
			vector<Database::Tri> right_s;
		//	vector<Database::Tri> right_f = res_cur.res_q[j];
		//	vector<Database::Tri> right_s = res_cur.res_q[j + 1];
			if (res_cur.res_q[j].empty())
				return res_cur;
			if (set_num) {
				right_f = vector<Database::Tri>(res_cur.res_q[j].begin(), res_cur.res_q[j].begin() + set_num);
				right_s = vector<Database::Tri>(res_cur.res_q[j + 1].begin(), res_cur.res_q[j + 1].begin() + set_num);
			}

			else {
				right_f = vector<Database::Tri>(res_cur.res_q[j]);
				right_s = vector<Database::Tri>(res_cur.res_q[j + 1]);
			}

			vector<vector< Database::Tri>> right = Two_pro_to(right_f, right_s);
			res_cur.res_q[j] = right[0];
			res_cur.res_q[j + 1] = right[1]; 
			if (set_num) {
				res_cur.res_q[j + 1].insert(res_cur.res_q[j + 1].end(), res_cur.res_q[j + 1].begin() + set_num, res_cur.res_q[j + 1].end());
				res_cur.res_q[j].insert(res_cur.res_q[j].end(), res_cur.res_q[j].begin() + set_num, res_cur.res_q[j].end());
			}
			/*vector<vector< Database::Tri>> right = Two_pro(right_f, right_s);
			res_cur.res_q[j ] = right[0];
			res_cur.res_q[j + 1] = right[1];*/
		}

	}

	return res_cur;
}
  
void Query::printf(Query::one res) {
	for (auto iter1 : res.res_q) {
		for (auto iter2 : iter1)
			 iter2.print();
	}

}