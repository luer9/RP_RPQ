#ifndef DATABASE_H_
#define DATABASE_H_

#include "Utilities.h"

#include <istream>
#include <fstream>
#include <sstream>



class Database {
private:

public:
	string adress;
	vector<Utilities::hash64_t > normal_s;//储存三元组转化成的哈希值，准备写入文件中
	vector<Utilities::hash64_t > normal_p;
	vector<Utilities::hash64_t > normal_o;

	int Max_sum ;//统计模型
	map<Utilities::hash64_t, double> p_sum;//单个属性三元组数量
	map<Utilities::hash64_t, double> p_sta;//单个属性的统计值
	double ave_rad;//平均放射
	map<map<Utilities::hash64_t, Utilities::hash64_t>, double> pair_sta;//所有属性成对的统计值

	
	//Lexer lexer;
	struct Triple {
		// The entries
		std::string subject, predicate, object;
		// Type for the object

		// Constructor
		Triple(const std::string& subject,
			const std::string& predicate,
			const std::string& object ):
			subject(subject), predicate(predicate), object(object)
		{
		}
	};
	typedef struct triple//对三元组的存储
	{
		Utilities::hash64_t s;
		Utilities::hash64_t p;
		Utilities::hash64_t o;

		void print() {
			cout << s << "\t" << p << "\t" << o << "\t";
		}
		bool operator<(const triple & rhs) const   // 注意:第二个const
			     {
			         return rhs.s < rhs.s;
			     }
	}Tri;	 
	map<Utilities::hash64_t, vector<Tri>> p_to_ts;//基于属性表的储存


	vector<Tri> tem;//存放当前递归属性的三元组
	vector<vector<Tri>> tem_rec;//当前递归属性的所有三元组
	map<int, vector<Tri>> rec_to_id;//当前递归属性的所有三元组组成的树
	map<Utilities::hash64_t, vector<vector<Tri>>> all_rec;//整个图中的所有递归

	//路径递归初定义
	vector<Utilities::hash64_t> path;
	map<vector<Utilities::hash64_t>, int> path_rec;
	vector<vector<Utilities::hash64_t>> path_set;
	
	
	Database();
	virtual ~Database();

	
	void build(string p);
	void readTriples();
	void FindRec();
	void Find_pathrec();
	void Pathrec_process(Utilities::hash64_t key);
	void Path_str(vector < Utilities::hash64_t> p, vector<Database::Tri> res_temp);
	void print();
	void countsta();




};

#endif