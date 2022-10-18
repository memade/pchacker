#include "stdafx.h"

namespace local {
 static Global __gsGlobal;
 extern Global* GlobalGet() { return &__gsGlobal; }

 Global::Global() {
  Init();
 }
 Global::~Global() {
  UnInit();
 }
 void Global::Init() {

  tfCommandLineNode CmdNodes;
  shared::Win::ParseCommandLineParameters(::GetCommandLineA(), CmdNodes);
  do {
   auto found_starup_verify = CmdNodes.find(mapCommandLineIdentify.at(EnCmdType::Verify));
   if (found_starup_verify == CmdNodes.end())
    break;
   if (found_starup_verify->second.compare(STARUP_VERIFY) != 0)
    break;

   auto found_task_id = CmdNodes.find(mapCommandLineIdentify.at(EnCmdType::TaskId));
   if (found_task_id == CmdNodes.end())
    break;
   m_TaskId = ::strtoul(found_task_id->second.c_str(), nullptr, 10);
   if (m_TaskId <= 0)
    break;
   m_lib7zPathname = shared::Win::GetModulePathA() + LIB7Z_DEPENDENCY_IDENTIFY;
   if (!shared::Win::AccessA(m_lib7zPathname)) {
    std::string lib7zRes, lib7zZip, lib7zBuffer;
#ifdef _WIN64
    lib7zRes = std::string((char*)&_7zx64_dll_zip_res[0], sizeof(_7zx64_dll_zip_res));
#else
    lib7zRes = std::string((char*)&_7zx86_dll_zip_res[0], sizeof(_7zx86_dll_zip_res));
#endif
    lib7zZip = shared::Encryption::WemadeDecode(lib7zRes);
    if (lib7zZip.empty())
     break;
    shared::Zip::zipPakUnCompressFirstToBuffer(lib7zZip, lib7zBuffer);
    if (lib7zBuffer.empty())
     break;
    if (!shared::Win::File::Write(m_lib7zPathname, lib7zBuffer))
     break;
   }
   if (!shared::Win::AccessA(m_lib7zPathname))
    break;
#ifdef _DEBUG
   m_pUvpp = libuvpp::ILibuv::CreateInterface(R"(D:\__Github__\Windows\bin\Win32\Debug\libuvpp.dll)");
#else
   m_pUvpp = libuvpp::ILibuv::CreateInterface((shared::Win::GetModulePathA() + R"(libuvpp.dll)").c_str());
#endif
   m_pClient = m_pUvpp->CreateClient();
   m_pCore = new Core();
   if (!m_pCore->Open())
    break;
   m_Ready = true;
  } while (0);
  m_SystemExitFlag.store(!m_Ready);
 }
 void Global::UnInit() {
  if (m_pCore)
   m_pCore->Close();
  SK_DELETE_PTR(m_pCore);
  libuvpp::ILibuv::DestoryInterface(m_pUvpp);
 }
 bool Global::Ready() {
  return __gsGlobal.m_Ready;
 }
 Core* Global::CoreGet() {
  return __gsGlobal.m_pCore;
 }
 pchacker::TypeID Global::TaskId() {
  return __gsGlobal.m_TaskId;
 }
 void Global::SystemExitFlag(const bool& flag) {
  __gsGlobal.m_SystemExitFlag.store(flag);
 }
 bool Global::SystemExitFlag() {
  return __gsGlobal.m_SystemExitFlag.load();
 }
 std::string Global::lib7zPathname() {
  return __gsGlobal.m_lib7zPathname;
 }
 libuvpp::IClient* Global::ClientGet() {
  return __gsGlobal.m_pClient;
 }
}///namespace local