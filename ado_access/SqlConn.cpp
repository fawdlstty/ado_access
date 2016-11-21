////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		SqlConn.cpp
//	Class Name:		hSqlConn
//	Description:	用于ADO数据库连接对象管理的类
//	Author:			Fawdlstty
//
//	Date:			Nov 19, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#include "String.hpp"

#include "SqlConn.h"



hSqlConn::hSqlConn (LPCTSTR lpConnStr) : m_pConn (nullptr) {
	try {
		m_pConn.CreateInstance ("ADODB.Connection");
		try {
			m_pConn->Open (_bstr_t (lpConnStr), _T (""), _T (""), adConnectUnspecified);
		} catch (_com_error &e) {
			::MessageBox (NULL, e.ErrorMessage (), _T ("提示"), MB_ICONHAND);
			m_pConn.Release ();
			m_pConn = nullptr;
		} catch (...) {
			m_pConn.Release ();
			m_pConn = nullptr;
		}
	} catch (_com_error &e) {
		::MessageBox (NULL, e.ErrorMessage (), _T ("提示"), MB_ICONHAND);
		m_pConn = nullptr;
	} catch (...) {
		m_pConn = nullptr;
	}
}


hSqlConn::~hSqlConn () {
	if (m_pConn) {
		m_pConn->Close ();
		m_pConn.Release ();
	}
}

bool hSqlConn::exec_sql (LPCTSTR lpSql, std::function<bool (_RecordsetPtr)> f_callback) {
	if (!m_pConn) {
		::MessageBox (NULL, _T ("数据库连接对象未初始化，无法调用exec方法"), _T ("提示"), MB_ICONHAND);
		return false;
	}

	try {
		_RecordsetPtr pRecs (__uuidof (Recordset));
		pRecs->Open (_variant_t (lpSql), _variant_t((IDispatch*)m_pConn), adOpenDynamic, adLockOptimistic, adCmdText);
		//_RecordsetPtr pRecs = m_pConn->Execute (_bstr_t (lpSql), nullptr, adCmdText);

		if (pRecs) {
			bool bRet = f_callback (pRecs);
			pRecs->Close ();
			pRecs.Release ();
			return bRet;
		}
	} catch (_com_error &e) {
		::MessageBox (NULL, e.ErrorMessage (), _T ("提示"), MB_ICONHAND);
	} catch (...) {
		::MessageBox (NULL, _T ("未知错误"), _T ("提示"), MB_ICONHAND);
	}

	return false;
}

bool hSqlConn::exec (LPCTSTR lpTable, std::function<bool (_RecordsetPtr)> f_callback, LPCTSTR lpColName, LPCTSTR lpValue) {
	string_t strSql;
	if (lpColName && lpColName [0] != _T ('\0')) {
		strSql = hString_t::format (_T ("select * from %s where %s = '%s'"), lpTable, lpColName, lpValue);
	} else {
		strSql = hString_t::format (_T ("select * from %s"), lpTable);
	}

	return exec_sql (strSql.c_str (), f_callback);
}
