////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		SqlObjectModel.cpp
//	Class Name:		hSqlObjectModel
//	Description:	�����ṩADO���ݿ�Ķ���ģ�ͽӿ�
//	Author:			Fawdlstty
//
//	Date:			Nov 20, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#include "Codec.hpp"
#include "SqlObjectModel.h"



//����
hSqlObjectModel::hSqlObjectModel (hSqlConn *pConn, _RecordsetPtr pRec) : m_pConn (pConn), m_pRec (pRec) {
}



//����
hSqlObjectModel::~hSqlObjectModel () {
}



//
//
//

//���һ����¼
bool hSqlObjectModel::add_item () {
	return m_pConn->exec (get_table_name (), [this] (_RecordsetPtr pRec) {
		m_pRec = pRec;
		if (FAILED (pRec->AddNew ())) return false;
		set_record ();
		return SUCCEEDED (pRec->Update ());
	});
}



//ɾ��һ����¼
bool hSqlObjectModel::del_item (LPCTSTR lpColName, LPCTSTR lpValue) {
	return m_pConn->exec (get_table_name (), [this] (_RecordsetPtr pRec) {
		this->m_pRec = pRec;
		if (pRec->GetadoEOF ()) return true;
		if (FAILED (pRec->Delete(adAffectCurrent))) return true;
		return SUCCEEDED (pRec->Update ());
	}, lpColName, lpValue);
}

bool hSqlObjectModel::del_item (LPCTSTR lpColName, int iValue) {
	return del_item (lpColName, hString_t::format (_T ("%d"), iValue).c_str ());
}




//�������ݿ��¼��ֵ
bool hSqlObjectModel::set_item (LPCTSTR lpColName, LPCTSTR lpValue) {
	return m_pConn->exec (get_table_name (), [this] (_RecordsetPtr pRec) {
		this->m_pRec = pRec;
		if (pRec->GetadoEOF ()) return false;
		set_record ();
		return SUCCEEDED (pRec->Update ());
	}, lpColName, lpValue);
}

bool hSqlObjectModel::set_item (LPCTSTR lpColName, int iValue) {
	return set_item (lpColName, hString_t::format (_T ("%d"), iValue).c_str ());
}



//��ȡ���ݿ��¼��ֵ
bool hSqlObjectModel::get_item (LPCTSTR lpColName, LPCTSTR lpValue) {
	return m_pConn->exec (get_table_name (), [this] (_RecordsetPtr pRec) {
		this->m_pRec = pRec;
		if (pRec->GetadoEOF ()) return false;
		get_record ();
		return true;
	}, lpColName, lpValue);
}

bool hSqlObjectModel::get_item (LPCTSTR lpColName, int iValue) {
	return get_item (lpColName, hString_t::format (_T ("%d"), iValue).c_str ());
}



//��ȡ�������ݿ����
bool hSqlObjectModel::get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName, LPCTSTR lpValue) {
	return m_pConn->exec (get_table_name (), [this, &v] (_RecordsetPtr pRec) {
		this->m_pRec = pRec;
		v.clear ();
		while (!pRec->GetadoEOF ()) {
			hSqlObjectModel *o = this->get_entity ();
			o->get_record ();
			if (FAILED (pRec->MoveNext ())) break;
		}
		return v.size () > 0;
	}, lpColName, lpValue);
}

bool hSqlObjectModel::get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName, int iValue) {
	return get_table (v, lpColName, hString_t::format (_T ("%d"), iValue).c_str ());
}



//
//
//

//�ȺŸ���
hSqlObjectModel &hSqlObjectModel::operator= (hSqlObjectModel &o) {
	m_pConn = o.m_pConn;
	m_pRec = o.m_pRec;
	return *this;
}



//��ʼ��һ��uuid��ֵ
void hSqlObjectModel::_init_uuid (string_t &strValue) {
	GUID guid;
	wchar_t wBuf [40];
	::CoCreateGuid (&guid);
	::StringFromGUID2 (guid, wBuf, 39);
	if (lstrlenW (wBuf) > 36) {
		for (int i = 0; i < 36; ++i) wBuf [i] = wBuf [i + 1];
		wBuf [36] = L'\0';
	}
#ifdef _UNICODE
	strValue = wBuf;
#else
	hCodec::UnicodeToAnsi (std::wstring(wBuf), strValue);
#endif //_UNICODE
}



//��ʼ��һ���ַ���������ֵ
void hSqlObjectModel::_init_value (string_t &strValue) {
	strValue = _T ("");
}



//��ʼ��һ�����ͱ�����ֵ
void hSqlObjectModel::_init_value (int &iValue) {
	iValue = 0;
}



//��ȡһ���ַ���������ֵ
void hSqlObjectModel::_get_value (LPCTSTR lpColName, string_t &strValue) {
	_variant_t vValue = m_pRec->GetCollect (lpColName);
	if (vValue.vt != VT_NULL) {
		strValue = vValue.bstrVal;
	}
}



//��ȡһ�����ͱ�����ֵ
void hSqlObjectModel::_get_value (LPCTSTR lpColName, int &iValue) {
	_variant_t vValue = m_pRec->GetCollect (lpColName);
	if (vValue.vt != VT_NULL) {
		iValue = vValue.lVal;
	}
}



//����һ���ַ���������ֵ
void hSqlObjectModel::_set_value (LPCTSTR lpColName, string_t &strValue) {
	m_pRec->PutCollect (lpColName, strValue.c_str ());
}



//����һ�����ͱ�����ֵ
void hSqlObjectModel::_set_value (LPCTSTR lpColName, int &iValue) {
	m_pRec->PutCollect (lpColName, iValue);
}


