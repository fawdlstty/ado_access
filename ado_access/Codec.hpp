////////////////////////////////////////////////////////////////////////////////
//
//	File Name:		Codec.h
//	Class Name:		hCodec
//	Description:	用于编码转换
//	Author:			Fawdlstty
//
//	Date:			Nov 20, 2016
//	Log:			Create this file.
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __CODEC_HPP__
#define __CODEC_HPP__

#pragma once



#include <Windows.h>
#include <string>



class hCodec {
	//不可实例化
	hCodec () = delete;
	~hCodec () = delete;

	static bool hCodec::_conv_Down (std::wstring& _old, std::string& _new, UINT ToType) {
		int lenOld = lstrlenW (_old.c_str ());
		int lenNew = ::WideCharToMultiByte (ToType, 0, _old.c_str (), lenOld, NULL, 0, NULL, NULL);
		std::string s;
		s.resize (lenNew);
		bool bRet = !!::WideCharToMultiByte (ToType, 0, _old.c_str (), lenOld, const_cast<char*>(s.c_str ()), lenNew, NULL, NULL);
		_new.clear ();
		_new = s.c_str ();
		return bRet;
	}
	static bool hCodec::_conv_Up (std::string& _old, std::wstring& _new, UINT ToType) {
		int lenOld = lstrlenA (_old.c_str ());
		int lenNew = ::MultiByteToWideChar (ToType, 0, _old.c_str (), lenOld, NULL, 0);
		std::wstring s;
		s.resize (lenNew);
		bool bRet = !!::MultiByteToWideChar (ToType, 0, _old.c_str (), lenOld, const_cast<wchar_t*>(s.c_str ()), lenNew);
		_new.clear ();
		_new = s.c_str ();
		return bRet;
	}

public:
	static bool hCodec::AnsiToUnicode (std::string& _old, std::wstring& _new) {
		return hCodec::_conv_Up (_old, _new, CP_ACP);
	}
	static bool hCodec::UnicodeToAnsi (std::wstring& _old, std::string& _new) {
		return hCodec::_conv_Down (_old, _new, CP_ACP);
	}
	static bool hCodec::Utf8ToUnicode (std::string& _old, std::wstring& _new) {
		return hCodec::_conv_Up (_old, _new, CP_UTF8);
	}
	static bool hCodec::UnicodeToUtf8 (std::wstring& _old, std::string& _new) {
		return hCodec::_conv_Down (_old, _new, CP_UTF8);
	}
	static bool hCodec::AnsiToUtf8 (std::string& _old, std::string& _new) {
		std::wstring t;
		if (!hCodec::AnsiToUnicode (_old, t)) return false;
		return hCodec::UnicodeToUtf8 (t, _new);
	}
	static bool hCodec::Utf8ToAnsi (std::string& _old, std::string& _new) {
		std::wstring t;
		if (!hCodec::Utf8ToUnicode (_old, t)) return false;
		return hCodec::UnicodeToAnsi (t, _new);
	}
};

#endif //__CODEC_HPP__
