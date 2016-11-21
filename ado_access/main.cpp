#include <vector>
using namespace std;

#include "SqlConn.h"
#include "TestModel.hpp"

int main (int argc, char* argv []) {
	hSqlConn *pConn = new hSqlConn (_T (""));

	//���һ����¼
	hTestModel o1 (pConn);
	o1.m_field1 = _T ("abc");
	o1.m_field2 = 3;
	o1.add_item ();

	//ɾ��һ����¼
	hTestModel (pConn).del_item (_T ("col_name1"), _T ("abc"));

	//�޸�һ����¼
	hTestModel o2 (pConn);
	o2.m_field1 = _T ("abcde");
	o2.m_field2 = 5;
	o2.set_item (_T ("col_name1"), _T ("abc"));

	//��ȡһ����¼
	hTestModel o3 (pConn);
	o3.get_item (_T ("col_name1"), _T ("value"));

	//��ѯ�������ݱ�
	vector<hTestModel*> v;
	hTestModel (pConn).get_table ((vector<hSqlObjectModel*>&)v);

	delete pConn;
	return 0;
}
