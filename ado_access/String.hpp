////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		String.hpp
//	Class Name:		hString
//	Description:	�����ַ��������չ����
//	Author:			Fawdlstty
//
//	Date:			Nov 19, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __STRING_HPP__
#define __STRING_HPP__



#include <string>
#include <vector>
#include <memory>
#include <cstdarg>

#include <tchar.h>



template<typename charT>
class hString {
public:
	//����ַ�����ʼ���ֿո�
	static void trimLeft (std::basic_string<charT> &str) {
		str.erase (0, str.find_first_not_of (' '));
	}

	//����ַ����������ֿո�
	static void trimRight (std::basic_string<charT> &str) {
		str.erase (str.find_last_not_of (' ') + 1);
	}

	//������˿ո�
	static void trim (std::basic_string<charT> &str) {
		str.erase (0, str.find_first_not_of (' '));
		str.erase (str.find_last_not_of (' ') + 1);
	}

	//ɾ���ַ�����ָ���ַ�
	static void erase (std::basic_string<charT> &str, const charT &charactor) {
		str.erase (remove_if (str.begin (), str.end (), bind2nd (std::equal_to<charT> (), charactor)), str.end ());
	}

	//�滻�ַ�����ָ���ַ���
	static int replace (std::basic_string<charT> &str, const std::basic_string<charT> &strObj, const std::basic_string<charT> &strDest) {
		int ret = 0;
		charT pos = str.find (strObj);
		while (pos != std::basic_string<charT>::npos) {
			ret++;
			str.replace (pos, strObj.size (), strDest);
			pos = str.find (strObj);
		}
		return ret;
	}

	//һ���е��ַ����ضϣ�����תΪ��������
	template<typename T>
	static int split_aLine_conv (const std::basic_string<charT> &str, std::vector<T> &seq, charT separator) {
		if (str.empty ()) return 0;
		int count = 0;
		std::basic_stringstream<charT> bs (str);
		for (std::basic_string<charT> s; std::getline (bs, s, separator); count++) {
			typename T val;
			std::basic_stringstream<charT> bss (s);
			bss >> val;
			seq.push_back (val);
		}
		return count;
	}

	//�ַ����ض�
	static void split (std::basic_string<charT> s, std::vector<std::basic_string<charT> >& v, char ch = ' ') {
		ptrdiff_t start = 0, p, len = s.length ();
		do {
			p = s.find (ch, start);
			if (p == -1) p = len;
			s [p] = '\0';
			if (s [start] != '\0') v.push_back (&s [start]);
			start = p + 1;
		} while (start < len);
	}

	//�ַ�����ʽ��
	static std::basic_string<charT> format (std::basic_string<charT> fmt_str, ...) {
		//��Դ��http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
		ptrdiff_t final_n, n = ((ptrdiff_t) fmt_str.size ()) * 2;
		std::basic_string<charT> str;
		std::unique_ptr<charT []> formatted;
		va_list ap;
		while (1) {
			formatted.reset (new charT [n]);
			//strcpy_s (&formatted [0], fmt_str.size (), fmt_str.c_str ());
			va_start (ap, fmt_str);
			final_n = _vsntprintf_s (&formatted [0], n, _TRUNCATE, fmt_str.c_str (), ap);
			va_end (ap);
			if (final_n < 0 || final_n >= n)
				n += abs (final_n - n + 1);
			else
				break;
		}
		return std::basic_string<charT> (formatted.get ());
	}
};



typedef hString<char> hStringA;
typedef hString<wchar_t> hStringW;
#ifdef _UNICODE
typedef hStringW hString_t;
typedef std::wstring string_t;
#else
typedef hStringA hString_t;
typedef std::string string_t;
#endif



#endif //__STRING_HPP__
