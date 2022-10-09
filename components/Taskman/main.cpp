#include "stdafx.h"

int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3869);
#endif

 tfCommandLineNode CmdNodes;
 shared::Win::ParseCommandLineParameters(argc, argv, CmdNodes);

 const EnTaskType task_type = static_cast<const EnTaskType>(::atol(CmdNodes[mapCommandLineIdentify.at(EnCmdType::TaskType)].c_str()));
 const unsigned int host_port = ::atol(CmdNodes[mapCommandLineIdentify.at(EnCmdType::HostPort)].c_str());

 bool bReady = false;
 do {//!@ Ready.
  if (host_port <= 0)
   break;



  bReady = true;
 } while (0);

 if (!bReady) {

  return 1;
 }

 switch (task_type) {
 case EnTaskType::Extractor: {

 }break;
 case EnTaskType::Download: {

 }break;
 case EnTaskType::Guard: {

 }break;
 default:
  break;
 }///switch




 const DWORD HostPID = ::atol(CmdNodes[mapCommandLineIdentify.at(EnCmdType::HostPID)].c_str());
 const DWORD HostTID = ::atol(CmdNodes[mapCommandLineIdentify.at(EnCmdType::HostTID)].c_str());
 const std::string OutPath = CmdNodes[mapCommandLineIdentify.at(EnCmdType::OutPath)];
 const std::string InPathname = CmdNodes[mapCommandLineIdentify.at(EnCmdType::InPathname)];

 std::atomic_ulong current_process_id = ::GetCurrentProcessId();
 std::atomic_ulong message_thread_id = 0;
 std::atomic_bool main_exit = false;
 std::atomic_bool extract_break_flag = false;
 std::vector<std::thread> threads;
 std::shared_ptr<shared::Bit7zExtractObj> pBit7zExtractObj;
 bool result = false;
 std::string lib7zPathname = shared::Win::GetModulePathA() + LIB7Z_DEPENDENCY_IDENTIFY;
 do {
  if (HostTID <= 0)
   break;
  if (!shared::Win::AccessA(lib7zPathname)) {
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
   if (!shared::Win::File::Write(lib7zPathname, lib7zBuffer))
    break;
  }
  if (!shared::Win::AccessA(lib7zPathname))
   break;
  if (!shared::Win::AccessA(InPathname))
   break;
  if (!shared::Win::IsPathA(OutPath))
   break;
  if (!shared::Win::AccessA(OutPath))
   shared::Win::CreateDirectoryA(OutPath);
  if (!shared::Win::AccessA(OutPath))
   break;
  pBit7zExtractObj = std::make_shared<shared::Bit7zExtractObj>(
   shared::IConv::MBytesToWString(lib7zPathname),
   shared::IConv::MBytesToWString(InPathname),
   shared::IConv::MBytesToWString(OutPath),
   [&](
    const std::uint64_t& target_total_size,
    const std::uint64_t& extract_total_size,
    const std::uint64_t& current_extract_total_size,
    const double& progress)->bool {
     bool progress_result = !extract_break_flag.load();
     do {
      if (!progress_result)
       break;
      if (!::PostThreadMessageW(
       HostTID,
       UINT(pchacker::EnLocalMessage::ExtractProgress),
       WPARAM(shared::Win::GetCurrentThreadId()),
       static_cast<LPARAM>(progress * 10000.0)))
       break;
      auto success = 1;
     } while (0);
     return progress_result;
   },
   [&](std::wstring extract_filename) {
   }, true/*Clear the release directory if unzipping is abnormal.*/);
  if (!pBit7zExtractObj)
   break;
  result = true;
 } while (0);

 if (!result) {
  ::PostThreadMessageW(
   HostTID,
   UINT(pchacker::EnLocalMessage::ExtractFailed),
   WPARAM(message_thread_id.load()),
   LPARAM(current_process_id.load()));
  return -1;
 }

 threads.emplace_back(
  [&]() {
   message_thread_id.store(shared::Win::GetCurrentThreadId());

   auto route = new pchacker::ExtractRouteData();
   route->ExtractProcessId = current_process_id.load();
   route->ExtractMessageThreadId = message_thread_id.load();

   ::PostThreadMessageW(
    HostTID,
    UINT(pchacker::EnLocalMessage::ExtractReady),
    WPARAM(message_thread_id.load()),
    reinterpret_cast<LPARAM>(route));
   do {
    ::MSG msg = { 0 };
    do {
     if (FALSE == ::PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
      break;
     switch (pchacker::EnLocalMessage(msg.message)) {
     case pchacker::EnLocalMessage::ExtractBreak: {
      extract_break_flag.store(true);
      main_exit.store(true);
     }break;
     case pchacker::EnLocalMessage::ExtractPerform: {

      pBit7zExtractObj->Perform();
      ::PostThreadMessageW(
       HostTID,
       UINT(pchacker::EnLocalMessage::ExtractSuccess),
       WPARAM(message_thread_id.load()),
       LPARAM(current_process_id.load()));
      main_exit.store(true);
     }break;
     default:
      break;
     }
    } while (0);

    if (main_exit.load())
     break;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
   } while (1);

  });

 for (auto& t : threads)
  t.join();
 threads.clear();


 return 0;



}
