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
   m_pServer = dynamic_cast<libuvpp::Server*>(m_pLibuv->CreateServer());
   m_pLibcurl = new libcurlpp::Libcurlpp();
   m_pPCHacker = new PCHacker();
   m_Ready.store(true);
  } while (0);
  return m_Ready.load();
 }

 void Global::UnInit() {
  do {
   if (!m_Ready.load())
    break;
   SK_DELETE_PTR(m_pLibuv);
   m_pLibcurl->Release();
   m_Ready.store(false);
  } while (0);

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
 libcurlpp::Libcurlpp* Global::LibcurlGet() {
  libcurlpp::Libcurlpp* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pLibcurl;
  } while (0);
  return result;
 }
 libuvpp::Server* Global::ServerGet() {
  libuvpp::Server* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pServer;
  } while (0);
  return result;
 }
 libuvpp::Libuv* Global::LibuvGet() {
  libuvpp::Libuv* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pLibuv;
  } while (0);
  return result;
 }
}///namespace local