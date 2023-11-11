#include "database.h"

Database::Database() {
	
	Max_sum = 0;
	ave_rad = 1;
}

Database::~Database() {
}

void Database::build(string p) {
	adress = p;
	readTriples();
	countsta();
	FindRec();
	Find_pathrec();
}

// Read new characters



void Database::readTriples() {
	ifstream infile;
	infile.open(adress);
	if (!infile) cout << "error" << endl;

	string str;
	while (getline(infile, str)) {
		stringstream ss(str);
		string tmp;
		vector<string> v;
		while (getline(ss, tmp, ' ')) {
			v.push_back((tmp));
		}
		Triple newtri = Triple(v[0], v[1], v[2]);
		Tri newTri;
		newTri.s = Utilities::hash64(newtri.subject, 0);
		newTri.p = Utilities::hash64(newtri.predicate, 0);
		newTri.o = Utilities::hash64(newtri.object, 0);
		Tri newTrio;
		newTrio.s = Utilities::hash64(newtri.object, 0);
		newTrio.p = Utilities::hash64(newtri.predicate, 0);
		newTrio.o = Utilities::hash64(newtri.subject, 0);

		p_to_ts[newTri.p].push_back(newTri);

		Max_sum ++;
		cout << Max_sum << endl;
	}
	cout << "--------------" << endl;
	cout << p_to_ts.size() << endl;
}

void Database::countsta() {
	
	int ps = 0;
vector<Utilities::hash64_t> temp_p;
for (auto iter = p_to_ts.begin(); iter != p_to_ts.end(); iter++) {//计算单个属性的代价
	Utilities::hash64_t fir = iter->first;
	double size = iter->second.size();
	p_sum[fir] = size;
	p_sta[fir] = Max_sum / size;
	temp_p.push_back(fir);
	ps++;
	cout << ps << endl;
	cout << p_to_ts.size() << endl;
}

ave_rad = Max_sum / ps;

for (int i = 0; i < temp_p.size(); i++) {//对所有的属性都做2 2 成对代价计算
	Utilities::hash64_t fir = temp_p[i];
	for (int j = 0; j < temp_p.size(); j++) {
		if (j == i)
			continue;
		double	p_sta = 0.0;
		Utilities::hash64_t sec = temp_p[j];
		p_sta = (p_sum[fir] * ave_rad + p_sum[sec] * ave_rad / p_sum[fir] * p_sum[sec]);
		map<Utilities::hash64_t, Utilities::hash64_t> m;
		m[fir] = sec;
		pair_sta[m] = p_sta;
		cout << i <<"\\"<<j<< endl;
		cout << p_to_ts.size() << endl;
	}
}
}

int vecFind(vector<Utilities::hash64_t > index, Utilities::hash64_t t) {
	for (int i = 0; i < index.size(); i++) {
		if (index[i] == t)
			return i;

	}
	return 0;

}

void Database::FindRec() {
	int x = 0;
	for (auto iter = p_to_ts.begin(); iter != p_to_ts.end(); iter++) {//从整个属性组出发，因为递归必然出现在同一个属性组
		tem.clear();
		Utilities::hash64_t cur_p = iter->first;
		vector<Tri> cur_pt = iter->second;
		vector<Utilities::hash64_t > indexs;
		vector<Utilities::hash64_t > indexo;
		for (int i = 0; i < cur_pt.size(); i++) {//记录该属性组的 s o
			indexs.push_back(cur_pt[i].s);
			indexo.push_back(cur_pt[i].o);
		}
		vector<int > rec_start;
		vector<int > rec_end;
		int s = 0;
		for (auto i = indexs.begin(), j = indexo.begin(); i != indexs.end(); i++, j++) {//寻找递归起点，其必定s不在o的序列，o必在s的序列
			Utilities::hash64_t ts = *i;
			Utilities::hash64_t to = *j;
			if (vecFind(indexs, to) && !vecFind(indexo, ts))
				rec_start.push_back(s);//获得起点的索引值
			if (!vecFind(indexs, to) && vecFind(indexo, ts))
				rec_end.push_back(s);//获得终点的索引值
			s++;
			cout << s << "\\"<<indexs.size()<<endl;
		}

		map<int, int > end_judge;//判断终点是否都已经包含

		for (int i = 0; i < rec_start.size(); i++) {//从起点出发寻找递归树
			tem.clear(); //递归组重置
			Tri cur = cur_pt[rec_start[i]];
			tem.push_back(cur);
			int end_flag = 0;//终点flag
			while (int x = vecFind(indexs, cur.o)) {
				cur = cur_pt[x];
				end_flag = x;
				tem.push_back(cur);
			}
			end_judge[end_flag] ++;
			tem_rec.push_back(tem);
			
		}

		for (int i = 0; i < rec_end.size(); i++) {//从终点出发寻找递归树
			tem.clear(); //递归组重置
			if (!end_judge[rec_end[i]]) {
				Tri cur = cur_pt[rec_end[i]];
				tem.push_back(cur);
				int end_flag = 0;//终点flag
				while (int x = vecFind(indexo, cur.s)) {
					cur = cur_pt[x];
					tem.push_back(cur);
				}
				std::reverse(tem.begin(), tem.end());
				tem_rec.push_back(tem);
			}

		}
		if (!tem_rec.empty())
			all_rec[cur_p] = tem_rec;
		tem_rec.clear();
		cout << "cur p_size：" << cur_pt.size() << endl;
		cout << "cur pos" << x ++<< "\\" << p_to_ts.size() << endl;
	}
}

vector<vector< Database::Tri>> Two(vector<Database::Tri> first, vector<Database::Tri> second) {
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

void Database::Path_str(vector < Utilities::hash64_t> p, vector<Database::Tri> res_temp) {
	if (res_temp.empty()) {
		res_temp = p_to_ts[p[0]];
		for (int i = 1; i < p.size(); i++) {
			vector<Database::Tri> cur = p_to_ts[p[i]];
			res_temp = Two(res_temp, cur)[1];
			if (res_temp.empty())
				return;
		}
	}
	else {
		for (int i = 0; i < p.size(); i++) {
			vector<Database::Tri> cur = p_to_ts[p[i]];
			res_temp = Two(res_temp, cur)[1];
			if (res_temp.empty())
				return;
		}
	}
	path_rec[p] ++;
	return Path_str(p, res_temp);
		

}

void Database::Pathrec_process(Utilities::hash64_t key) {
	path.push_back(key);
	if (path.size() > 1)
		path_set.push_back(path);
	if (path.size() > 2)
	{
		//path.clear();
		return;
	}
	for (auto iter1 = p_to_ts.begin(); iter1 != p_to_ts.end(); iter1++){
		set<Utilities::hash64_t> temp_find(path.begin(), path.end());
		if (temp_find.find(iter1->first) != temp_find.end()) {
			continue;
		}
		else {
			Pathrec_process(iter1->first);
			path.pop_back();
		}
}
}

void Database::Find_pathrec() {
	int p = 0;
	cout << p << endl;
	for (auto iter = p_to_ts.begin(); iter != p_to_ts.end(); iter++) {//从整个属性组出发，因为递归必然出现在同一个属性组
		Utilities::hash64_t key = iter->first;
		path.clear();
		Pathrec_process(key);
		cout << p++<<endl;
	}
	vector<Database::Tri> n;
	cout << path_set.size() << endl;
	p = -1;
	for (auto iter : path_set) {
		Path_str(iter, n);
		cout << p-- << endl;
	}
		
}

void Database::print() {
	
	for (auto iter = p_to_ts.begin(); iter != p_to_ts.end(); iter++) {
		cout << "___________________________________" << endl;
		cout << "属性：" << iter->first << "三元组：" << endl;
		for (int i = 0; i < iter->second.size(); i++) {

			cout << iter->second[i].s <<"\t"<< iter->second[i].p << "\t" << iter->second[i].o<< endl;
		}
	}
	for (auto iter = pair_sta.begin(); iter != pair_sta.end(); iter++) {
		auto iter1 = iter->first.begin();
		cout << "属性对：" << iter1->first << "\t" << iter1->second << "\t" << ":";
		cout << "\t" << iter->second << endl;
	}

	for (auto iter = all_rec.begin(); iter != all_rec.end(); iter++) {
		cout << "当前属性"<<iter->first << ":" << endl;
		for (int i = 0; i < iter->second.size(); i++) {
			cout << "第"<<i <<"组"<< endl;
			for (int j = 0; j < iter->second[i].size(); j++)
			{
				iter->second[i][j].print();
				cout << endl;
			}
			
		}
		cout << "+++++++++++++++++++++++++++++++++++++++"<<endl;
	}
	for (auto iter : path_set) {
		cout << "路径 : " ;
		for (auto iter1 : iter) {
			cout << iter1 << "\t";
		}
		cout << ":";
		cout << path_rec[iter] << endl;
		cout << endl;
		
	}
	cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
}