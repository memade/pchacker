﻿#include "stdafx.h"

namespace local {
	Global* __gpGlobal = nullptr;
	Global* GlobalGet() { return __gpGlobal; }
	HINSTANCE __gpHinstance = nullptr;

	Global::Global() {

	}

	Global::~Global() {
		UnInit();
	}

	bool Global::Init() {
		do {
			if (m_Ready.load())
				break;
#if ENABLE_MODULE_CEF3
			m_pCef3Obj = shared::cef3::ICef3Api::CreateInterface((shared::Win::GetModulePathA(__gpHinstance) + "cef3.dll").c_str());
			if (!m_pCef3Obj)
				break;
#endif
			m_pHttpObj = libcurlpp::IHttpApi::CreateInterface((shared::Win::GetModulePathA(__gpHinstance) + "libcurlpp.dll").c_str());
			if (!m_pHttpObj)
				break;
			m_pPCHacker = new PCHacker();
			m_Ready.store(true);
		} while (0);
		return m_Ready.load();
	}

	void Global::UnInit() {
		SK_DELETE_PTR(m_pPCHacker);
		libcurlpp::IHttpApi::DestoryInterface(m_pHttpObj);
#if ENABLE_MODULE_CEF3
		shared::cef3::ICef3Api::DestoryInterface(m_pCef3Obj);
#endif
	}


	PCHacker* Global::PCHackerGet() {
		PCHacker* result = nullptr;
		do {
			if (!__gpGlobal)
				break;
			result = __gpGlobal->m_pPCHacker;
		} while (0);
		return result;
	}
	libcurlpp::IHttpApi* Global::HttpGet() {
		libcurlpp::IHttpApi* result = nullptr;
		do {
			if (!__gpGlobal)
				break;
			result = __gpGlobal->m_pHttpObj;
		} while (0);
		return result;
	}
#if ENABLE_MODULE_CEF3
	shared::cef3::ICef3Api* Global::Cef3Get() {
		shared::cef3::ICef3Api* result = nullptr;
		do {
			if (!__gpGlobal)
				break;
			result = __gpGlobal->m_pCef3Obj;
		} while (0);
		return result;
	}
#endif
}///namespace local