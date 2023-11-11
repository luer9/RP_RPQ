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
	vector<Utilities::hash64_t > normal_s;//������Ԫ��ת���ɵĹ�ϣֵ��׼��д���ļ���
	vector<Utilities::hash64_t > normal_p;
	vector<Utilities::hash64_t > normal_o;

	int Max_sum ;//ͳ��ģ��
	map<Utilities::hash64_t, double> p_sum;//����������Ԫ������
	map<Utilities::hash64_t, double> p_sta;//�������Ե�ͳ��ֵ
	double ave_rad;//ƽ������
	map<map<Utilities::hash64_t, Utilities::hash64_t>, double> pair_sta;//�������ԳɶԵ�ͳ��ֵ

	
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
	typedef struct triple//����Ԫ��Ĵ洢
	{
		Utilities::hash64_t s;
		Utilities::hash64_t p;
		Utilities::hash64_t o;

		void print() {
			cout << s << "\t" << p << "\t" << o << "\t";
		}
		bool operator<(const triple & rhs) const   // ע��:�ڶ���const
			     {
			         return rhs.s < rhs.s;
			     }
	}Tri;	 
	map<Utilities::hash64_t, vector<Tri>> p_to_ts;//�������Ա�Ĵ���


	vector<Tri> tem;//��ŵ�ǰ�ݹ����Ե���Ԫ��
	vector<vector<Tri>> tem_rec;//��ǰ�ݹ����Ե�������Ԫ��
	map<int, vector<Tri>> rec_to_id;//��ǰ�ݹ����Ե�������Ԫ����ɵ���
	map<Utilities::hash64_t, vector<vector<Tri>>> all_rec;//����ͼ�е����еݹ�

	//·���ݹ������
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