////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		SqlObjectModel.h
//	Class Name:		hSqlObjectModel
//	Description:	用于提供ADO数据库的对象模型接口
//	Author:			Fawdlstty
//
//	Date:			Nov 19, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __SQL_OBJECT_MODEL_H__
#define __SQL_OBJECT_MODEL_H__

#pragma once



#include <vector>

#include <Windows.h>

#include "String.hpp"
#include "SqlConn.h"



#define H_OBJECT_MODEL(class_name, table_name)																\
	public:																									\
		/*构造*/																							\
		class_name (hSqlConn *pConn, _RecordsetPtr pRec = nullptr)											\
			: hSqlObjectModel (pConn, pRec) { init (); }													\
		class_name (_RecordsetPtr pRec = nullptr, hSqlConn *pConn = nullptr)								\
			: hSqlObjectModel (pConn, pRec) { init (); }													\
																											\
		/*析构*/																							\
		virtual ~class_name () {}																			\
																											\
		/*不允许拷贝构造*/																					\
		class_name (class_name&) = delete;																	\
																											\
	protected:																								\
		/*获取数据库对象实例*/																				\
		hSqlObjectModel *get_entity (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr) override {	\
			return new class_name (pConn, pRec);															\
		}																									\
																											\
		/*获取表名*/																						\
		LPCTSTR get_table_name () const override {															\
			return table_name;																				\
		}



class hSqlObjectModel {
public:
	//构造
	hSqlObjectModel (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr);

	//析构
	virtual ~hSqlObjectModel ();

	//不允许拷贝构造
	hSqlObjectModel (hSqlObjectModel&) = delete;

protected:
	//获取数据库对象实例
	virtual hSqlObjectModel *get_entity (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr) = 0;

	//获取表名
	virtual LPCTSTR get_table_name () const = 0;

public:
	//添加一条纪录
	bool add_item ();

	//删除一条纪录
	bool del_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool del_item (LPCTSTR lpColName, int iValue);

	//设置数据库记录的值
	bool set_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool set_item (LPCTSTR lpColName, int iValue);

	//获取数据库记录的值
	bool get_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool get_item (LPCTSTR lpColName, int iValue);

	//获取整个数据库对象
	bool get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName = _T (""), LPCTSTR lpValue = _T (""));
	bool get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName, int iValue);

protected:
	//初始化类所有成员
	virtual void init () = 0;

	//读取数据库记录
	virtual void get_record () = 0;

	//写入数据库记录
	virtual void set_record () = 0;

	//等号复制
	virtual hSqlObjectModel &operator= (hSqlObjectModel &o);

	//初始化一个uuid的值
	void _init_uuid (string_t &strValue);

	//初始化一个字符串变量的值
	void _init_value (string_t &strValue);

	//初始化一个整型变量的值
	void _init_value (int &iValue);

	//获取一个字符串变量的值
	void _get_value (LPCTSTR lpColName, string_t &strValue);

	//获取一个整型变量的值
	void _get_value (LPCTSTR lpColName, int &iValue);

	//设置一个字符串变量的值
	void _set_value (LPCTSTR lpColName, string_t &strValue);

	//设置一个整型变量的值
	void _set_value (LPCTSTR lpColName, int &iValue);

	hSqlConn *m_pConn;
	_RecordsetPtr m_pRec;
};

#endif //__SQL_OBJECT_MODEL_H__
