////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		TestModel.h
//	Class Name:		hTestModel
//	Description:	ADO数据库的对象模型示例
//	Author:			Fawdlstty
//
//	Date:			Nov 19, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __TEST_MODEL_H__
#define __TEST_MODEL_H__

#pragma once



#include <vector>

#include <Windows.h>

#include "SqlObjectModel.h"



class hTestModel : public hSqlObjectModel {

	H_OBJECT_MODEL (hTestModel, _T ("test_table_name"))

public:
	string_t m_field1;
	int m_field2;

protected:
	//初始化类所有成员
	void init () override {
		_init_value (m_field1);
		_init_value (m_field2);
	}

	//读取数据库记录
	void get_record () override {
		_get_value (_T ("col_name1"), m_field1);
		_get_value (_T ("col_name2"), m_field2);
	}

	//写入数据库记录
	void set_record () override {
		_set_value (_T ("col_name1"), m_field1);
		_set_value (_T ("col_name2"), m_field2);
	}

	//等号复制
	hSqlObjectModel &operator= (hSqlObjectModel &o) override {
		hTestModel *p = dynamic_cast<hTestModel*>(&o);
		if (p) {
			m_field1 = p->m_field1;
			m_field2 = p->m_field2;
		} else {
			::MessageBox (NULL, _T ("等号重载运算符参数错误"), _T ("提示"), MB_ICONHAND);
		}

		return hSqlObjectModel::operator=(o);
	}
};

#endif //__TEST_MODEL_H__
