#include "stdafx.h"

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
   m_pLibuv = new libuvpp::Libuv();
   m_pServer = m_pLibuv->CreateServer();
   m_pHttpObj = new libcurlpp::Http();
   m_pPCHacker = new PCHacker();
   m_Ready.store(true);
  } while (0);
  return m_Ready.load();
 }

 void Global::UnInit() {
  m_pLibuv->Release();
  m_pHttpObj->Release();
  SK_DELETE_PTR(m_pPCHacker);
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
 libuvpp::IServer* Global::ServerGet() {
  libuvpp::IServer* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pServer;
  } while (0);
  return result;
 }
 libuvpp::ILibuv* Global::LibuvGet() {
  libuvpp::ILibuv* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pLibuv;
  } while (0);
  return result;
 }
}///namespace local