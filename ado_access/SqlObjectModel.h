////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		SqlObjectModel.h
//	Class Name:		hSqlObjectModel
//	Description:	�����ṩADO���ݿ�Ķ���ģ�ͽӿ�
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
		/*����*/																							\
		class_name (hSqlConn *pConn, _RecordsetPtr pRec = nullptr)											\
			: hSqlObjectModel (pConn, pRec) { init (); }													\
		class_name (_RecordsetPtr pRec = nullptr, hSqlConn *pConn = nullptr)								\
			: hSqlObjectModel (pConn, pRec) { init (); }													\
																											\
		/*����*/																							\
		virtual ~class_name () {}																			\
																											\
		/*������������*/																					\
		class_name (class_name&) = delete;																	\
																											\
	protected:																								\
		/*��ȡ���ݿ����ʵ��*/																				\
		hSqlObjectModel *get_entity (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr) override {	\
			return new class_name (pConn, pRec);															\
		}																									\
																											\
		/*��ȡ����*/																						\
		LPCTSTR get_table_name () const override {															\
			return table_name;																				\
		}



class hSqlObjectModel {
public:
	//����
	hSqlObjectModel (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr);

	//����
	virtual ~hSqlObjectModel ();

	//������������
	hSqlObjectModel (hSqlObjectModel&) = delete;

protected:
	//��ȡ���ݿ����ʵ��
	virtual hSqlObjectModel *get_entity (hSqlConn *pConn = nullptr, _RecordsetPtr pRec = nullptr) = 0;

	//��ȡ����
	virtual LPCTSTR get_table_name () const = 0;

public:
	//���һ����¼
	bool add_item ();

	//ɾ��һ����¼
	bool del_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool del_item (LPCTSTR lpColName, int iValue);

	//�������ݿ��¼��ֵ
	bool set_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool set_item (LPCTSTR lpColName, int iValue);

	//��ȡ���ݿ��¼��ֵ
	bool get_item (LPCTSTR lpColName, LPCTSTR lpValue);
	bool get_item (LPCTSTR lpColName, int iValue);

	//��ȡ�������ݿ����
	bool get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName = _T (""), LPCTSTR lpValue = _T (""));
	bool get_table (std::vector<hSqlObjectModel*> &v, LPCTSTR lpColName, int iValue);

protected:
	//��ʼ�������г�Ա
	virtual void init () = 0;

	//��ȡ���ݿ��¼
	virtual void get_record () = 0;

	//д�����ݿ��¼
	virtual void set_record () = 0;

	//�ȺŸ���
	virtual hSqlObjectModel &operator= (hSqlObjectModel &o);

	//��ʼ��һ��uuid��ֵ
	void _init_uuid (string_t &strValue);

	//��ʼ��һ���ַ���������ֵ
	void _init_value (string_t &strValue);

	//��ʼ��һ�����ͱ�����ֵ
	void _init_value (int &iValue);

	//��ȡһ���ַ���������ֵ
	void _get_value (LPCTSTR lpColName, string_t &strValue);

	//��ȡһ�����ͱ�����ֵ
	void _get_value (LPCTSTR lpColName, int &iValue);

	//����һ���ַ���������ֵ
	void _set_value (LPCTSTR lpColName, string_t &strValue);

	//����һ�����ͱ�����ֵ
	void _set_value (LPCTSTR lpColName, int &iValue);

	hSqlConn *m_pConn;
	_RecordsetPtr m_pRec;
};

#endif //__SQL_OBJECT_MODEL_H__
