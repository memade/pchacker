#include "stdafx.h"

std::atomic_bool system_exit_flag = true;
std::atomic_bool extract_execute_result = false;
shared::container::queue<std::string> ExtractNotifyWriteQ;
int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3869);
#endif
 


 do {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  if (local::Global::SystemExitFlag())
   break;
 } while (1);

 return 0;
#if 0
 std::vector<std::thread> threads;

 DWORD dwCurrentProcessId = ::GetCurrentProcessId();
 pchacker::TypeID TaskId = 0;

 tfCommandLineNode CmdNodes;
 shared::Win::ParseCommandLineParameters(argc, argv, CmdNodes);
 do {
  auto found_starup_verify = CmdNodes.find(mapCommandLineIdentify.at(EnCmdType::Verify));
  if (found_starup_verify == CmdNodes.end())
   break;
  if (found_starup_verify->second.compare(STARUP_VERIFY) != 0)
   break;

  auto found_task_id = CmdNodes.find(mapCommandLineIdentify.at(EnCmdType::TaskId));
  if (found_task_id == CmdNodes.end())
   break;
  TaskId = ::strtoul(found_task_id->second.c_str(), nullptr, 10);
  if (TaskId <= 0)
   break;

  system_exit_flag.store(false);
 } while (0);
 if (system_exit_flag.load())
  return -1;

 libuvpp::ILibuv* pUvpp = libuvpp::ILibuv::CreateInterface(R"(D:\__Github__\Windows\bin\Win32\Debug\libuvpp.dll)");
 libuvpp::IClient* pClient = pUvpp->CreateClient();

 pClient->Start(libuvpp::EnSocketType::TCP, libuvpp::EnIPV::IPV4, "127.0.0.1:13762");
 pClient->StatusCb(
  [](const libuvpp::EnClientStatus& status) {
   switch (status) {
   case libuvpp::EnClientStatus::ConnectSuccess: {
    auto sk = 0;
   }break;
   default: {
    system_exit_flag.store(true);
   }break;
   }
  });
 pClient->MessageCb(
  [&](const std::string& msg, const libuvpp::tfOnClientMessageGetSendData& send_data_get_cb) {
   const shared::PPACKETHEAD pMsg = (const shared::PPACKETHEAD)msg.data();
   do {
    if (!pMsg->Verify())
     break;

    auto pTaskMsg = reinterpret_cast<pchacker::PTASKMANMSG>(pMsg->data);

    switch (pMsg->command) {
    case pchacker::TYPE_TASKMAN_MSG_WELCOME: {
     pchacker::TASKMANMSG msg;
     msg.ProcessId = dwCurrentProcessId;
     msg.TaskId = TaskId;

     do {
      if (!send_data_get_cb)
       break;
      std::string write_;
      shared::Win::Packet::Made(
       pchacker::TYPE_TASKMAN_MSG_HELLO,
       std::string((char*)&msg, sizeof(msg)),
       write_);
      send_data_get_cb(write_.data(), write_.size());

     } while (0);

    }break;
    case pchacker::TYPE_TASKMAN_MSG_EXIT: {

    }break;
    case pchacker::TYPE_TASKMAN_MSG_EXTRACT: {
     pchacker::PTASKMANMSG pMsg = new pchacker::TASKMANMSG();
     ::memcpy(pMsg, pTaskMsg, pchacker::LENTASKMANMSG);
     threads.emplace_back(
      [pMsg, dwCurrentProcessId,TaskId]() {
       const std::string lib7zPathname = shared::Win::GetModulePathA() + LIB7Z_DEPENDENCY_IDENTIFY;
       std::shared_ptr<shared::Bit7zExtractObj> pBit7zExtractObj;
       std::string current_work_outpath = pMsg->OutPath;
       std::string current_work_inpathname = pMsg->InPathname;
       for (int i = 0; i < 2; ++i) {
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
        if (!shared::Win::AccessA(current_work_inpathname))
         break;
        if (!shared::Win::IsPathA(current_work_outpath))
         break;
        if (!shared::Win::AccessA(current_work_outpath))
         shared::Win::CreateDirectoryA(current_work_outpath);
        if (!shared::Win::AccessA(current_work_outpath))
         break;

        do {
         pBit7zExtractObj = std::make_shared<shared::Bit7zExtractObj>(
          shared::IConv::MBytesToWString(lib7zPathname),
          shared::IConv::MBytesToWString(current_work_inpathname),
          shared::IConv::MBytesToWString(current_work_outpath),
          [&](
           const std::uint64_t& target_total_size,
           const std::uint64_t& extract_total_size,
           const std::uint64_t& current_extract_total_size,
           const double& progress)->bool {
            bool progress_result = !system_exit_flag.load();
            do {
             if (!progress_result)
              break;

             pMsg->ProcessId = dwCurrentProcessId;
             pMsg->TaskId = TaskId;
             pMsg->extract_current_extract_total_size = current_extract_total_size;
             pMsg->extract_progress = static_cast<unsigned long>(progress * 10000l);
             pMsg->extract_target_total_size = target_total_size;
             pMsg->extract_total_size = extract_total_size;

             /*std::string write_;
             shared::Win::Packet::Made(
              pchacker::TYPE_TASKMAN_MSG_EXTRACT_NOTIFY,
              std::string((char*)pTaskMsg, pchacker::LENTASKMANMSG),
              write_);*/

             ExtractNotifyWriteQ.push(std::string((char*)pMsg, pchacker::LENTASKMANMSG));
#if 0
             do {
              if (!send_data_get_cb)
               break;
              std::string write_;
              shared::Win::Packet::Made(
               pchacker::TYPE_TASKMAN_MSG_EXTRACT_NOTIFY,
               std::string((char*)pTaskMsg, pchacker::LENTASKMANMSG),
               write_);
              send_data_get_cb(write_.data(), write_.size());

            } while (0);
#endif

          } while (0);
          return progress_result;
        },
          [&](std::wstring extract_filename) {
        }, true/*Clear the release directory if unzipping is abnormal.*/);
         if (!pBit7zExtractObj)
          break;
         extract_execute_result.store(pBit7zExtractObj->Perform());
       } while (0);

       if (!extract_execute_result.load())
        break;
       //!@ 递归释放
       //! 
       //! 
       tfEnumFolderNode founds;
       shared::Win::FindFileAssignPath(current_work_outpath, { "#YouXun#" ,"gameyxdown.dat" }, founds);

       if (founds.size() != 2)
        break;

       bool error = false;
       for (const auto& node : founds) {
        if (::StrStrIA(node.first.c_str(), "#YouXun#")) {
         current_work_outpath = shared::Win::GetPathByPathnameA(node.first) + "\\Game\\";
         current_work_inpathname = node.first;
        }
        else if (::StrStrIA(node.first.c_str(), "gameyxdown.dat")) {
         /*
         * [main]
         FileName=cstrike.exe
         GameName=反恐精英CS1.6
         CanShu=
         GameId=4027
         ico=CS16_chs.ico
         */
         char FileName[_MAX_PATH] = { 0 };
         char ico[_MAX_PATH] = { 0 };
         ::GetPrivateProfileStringA("main", "FileName", "", FileName, sizeof(FileName), node.first.c_str());
         ::GetPrivateProfileStringA("main", "ico", "", ico, sizeof(ico), node.first.c_str());
         ::GetPrivateProfileStringA("main", "GameName", "", pMsg->Details.ProductName, sizeof(pMsg->Details.ProductName), node.first.c_str());
         pMsg->Details.ProductID = ::GetPrivateProfileIntA("main", "GameId", 0, node.first.c_str());

         if (pMsg->Details.ProductID <= 0) {
          error = true;
          break;
         }

         std::string strFileName = shared::Win::PathFixedA(shared::Win::GetPathByPathnameA(node.first) + "\\Game\\" + FileName);
         std::string strico = shared::Win::PathFixedA(shared::Win::GetPathByPathnameA(node.first) + "\\Game\\" + ico);
         ::memcpy(pMsg->Details.ProductLogoPathname, strico.c_str(), strico.size());
         ::memcpy(pMsg->Details.StartupPEPathname, strFileName.c_str(), strFileName.size());
        }
       }

       if (error)
        break;
      }///for count 2
      

      if (shared::Win::AccessA(pMsg->Details.StartupPEPathname))
      {

      }

      delete pMsg;
      });




     pMsg->ProcessId = dwCurrentProcessId;
     pMsg->TaskId = TaskId;
     pMsg->extract_current_extract_total_size = 0;
     pMsg->extract_progress = 0;
     pMsg->extract_target_total_size = 0;
     pMsg->extract_total_size = 0;

     do {
      if (!send_data_get_cb)
       break;
      std::string write_;
      shared::Win::Packet::Made(
       extract_execute_result.load() ? pchacker::TYPE_TASKMAN_MSG_EXTRACT_SUCCESS : pchacker::TYPE_TASKMAN_MSG_EXTRACT_FAILED,
       std::string((char*)pMsg, pchacker::LENTASKMANMSG),
       write_);
      send_data_get_cb(write_.data(), write_.size());
     } while (0);




     system_exit_flag.store(true);
    }break;
    case pchacker::TYPE_TASKMAN_MSG_DOWNLOAD: {

    }break;
    default:
     break;
    }

   } while (0);
  });

 threads.emplace_back(
  [&]() {
   do {
    
    do {
     if (!pClient)
      break;
     auto write_dats_s = ExtractNotifyWriteQ.pops();
     for (const auto& data : write_dats_s)
      pClient->Write(pchacker::TYPE_TASKMAN_MSG_EXTRACT_NOTIFY, data);
    } while (0);

    if (system_exit_flag.load())
     break;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
   } while (1);
  
  });
 threads.emplace_back([]() {
  do {
   if (system_exit_flag.load())
    break;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  } while (1);
  });

 for (auto& t : threads)
  t.join();
 threads.clear();
 libuvpp::ILibuv::DestoryInterface(pUvpp);
 return 0;
#endif
}
