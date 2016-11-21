////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		SqlConn.h
//	Class Name:		hSqlConn
//	Description:	用于ADO数据库连接对象管理的类
//	Author:			Fawdlstty
//
//	Date:			Nov 19, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __SQL_CONN_H__
#define __SQL_CONN_H__

#pragma once



#include <functional>

#include <Windows.h>
#include <tchar.h>

#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename ("EOF", "adoEOF")



class hSqlConn {
public:
	hSqlConn (LPCTSTR lpConnStr);
	~hSqlConn ();
	hSqlConn (hSqlConn&) = delete;

	bool exec_sql (LPCTSTR lpSql, std::function<bool(_RecordsetPtr)> f_callback);
	bool exec (LPCTSTR lpTable, std::function<bool (_RecordsetPtr)> f_callback, LPCTSTR lpColName = _T (""), LPCTSTR lpValue = _T (""));

private:
	_ConnectionPtr m_pConn;
};

#endif //__SQL_CONN_H__
