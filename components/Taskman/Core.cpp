#include "stdafx.h"

namespace local {

 Core::Core() {
  Init();
 }
 Core::~Core() {
  UnInit();
 }
 void Core::Init() {

 }
 void Core::UnInit() {

 }


 bool Core::Open() {
  do {
   if (m_IsOpen.load())
    break;

   Global::ClientGet()->StatusCb(
    [](const libuvpp::EnClientStatus& status) {
     switch (status) {
     case libuvpp::EnClientStatus::ConnectSuccess: {
     }break;
     default: {
      Global::SystemExitFlag(true);
     }break;
     }
    });
   Global::ClientGet()->MessageCb(
    [&](const std::string& msg, const libuvpp::tfOnClientMessageGetSendData& send_data_get_cb) {
     const shared::PPACKETHEAD pMsg = (const shared::PPACKETHEAD)msg.data();
     do {
      if (!pMsg->Verify())
       break;
      auto pTaskMsg = reinterpret_cast<pchacker::PTASKMANMSG>(pMsg->data);
      switch (pMsg->command) {
      case pchacker::TYPE_TASKMAN_MSG_WELCOME: {
       pchacker::TASKMANMSG msg;
       msg.ProcessId = ::GetCurrentProcessId();
       msg.TaskId = Global::TaskId();

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
       Global::SystemExitFlag(true);
      }break;
      case pchacker::TYPE_TASKMAN_MSG_EXTRACT: {
       pchacker::PTASKMANMSG pMsg = new pchacker::TASKMANMSG();
       ::memcpy(pMsg, pTaskMsg, pchacker::LENTASKMANMSG);
       m_Threads.emplace_back([this, pMsg]() {Extract(pMsg); });
      }break;

      default:
       break;
      }
     } while (0);
    });
   if (!Global::ClientGet()->Start(libuvpp::EnSocketType::TCP, libuvpp::EnIPV::IPV4, "127.0.0.1:13762"))
    break;
   m_IsOpen.store(true);
   m_Threads.emplace_back([this]() {Process(); });
  } while (0);
  return m_IsOpen.load();
 }
 void Core::Close() {
  do {
   if (!m_IsOpen.load())
    break;



   m_IsOpen.store(false);
   for (auto& t : m_Threads)
    t.join();
   m_Threads.clear();
  } while (0);
 }

 void Core::Extract(pchacker::PTASKMANMSG pMsg) {
  do {
   if (!pMsg)
    break;
   std::shared_ptr<shared::Bit7zExtractObj> pBit7zExtractObj;
   std::string current_work_outpath = pMsg->OutPath;
   std::string current_work_inpathname = pMsg->InPathname;
   bool extract_execute_result = false;
   for (int i = 0; i < 2; ++i) {
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
      shared::IConv::MBytesToWString(Global::lib7zPathname()),
      shared::IConv::MBytesToWString(current_work_inpathname),
      shared::IConv::MBytesToWString(current_work_outpath),
      [&](
       const std::uint64_t& target_total_size,
       const std::uint64_t& extract_total_size,
       const std::uint64_t& current_extract_total_size,
       const double& progress)->bool {
        bool progress_result = !Global::SystemExitFlag();
        do {
         if (!progress_result)
          break;

         pMsg->ProcessId = ::GetCurrentProcessId();
         pMsg->TaskId = Global::TaskId();
         pMsg->extract_current_extract_total_size = current_extract_total_size;
         pMsg->extract_progress = static_cast<unsigned long>(progress * 10000l);
         pMsg->extract_target_total_size = target_total_size;
         pMsg->extract_total_size = extract_total_size;

         std::string write_;
         shared::Win::Packet::Made(
          pchacker::TYPE_TASKMAN_MSG_EXTRACT_NOTIFY,
          std::string((char*)pMsg, pchacker::LENTASKMANMSG),
          write_);

         Global::ClientGet()->Write(write_);

        } while (0);
        return progress_result;
      },
      [&](std::wstring extract_filename) {
      }, true/*Clear the release directory if unzipping is abnormal.*/);
     if (!pBit7zExtractObj)
      break;
     if (!pBit7zExtractObj->Perform()) {
      Global::SystemExitFlag(true);
      break;
     }
     extract_execute_result = true;

    } while (0);

    if (!extract_execute_result)
     break;
    //!@ 递归释放
    //! 
    //! 
    tfEnumFolderNode founds;
    shared::Win::FindFileAssignPathOnce(current_work_outpath, { "#YouXun#" ,"gameyxdown.dat" }, founds);

    if (founds.size() != 2)
     break;

    for (const auto& node : founds) {
     if (::StrStrIA(node.first.c_str(), "#YouXun#")) {
      current_work_outpath = shared::Win::GetPathByPathnameA(node.second) + "\\Game\\";
      current_work_inpathname = node.second;
     }
     else if (::_stricmp(node.first.c_str(), "gameyxdown.dat") == 0) {
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
      ::GetPrivateProfileStringA("main", "FileName", "", FileName, sizeof(FileName), node.second.c_str());
      ::GetPrivateProfileStringA("main", "ico", "", ico, sizeof(ico), node.second.c_str());
      ::GetPrivateProfileStringA("main", "GameName", "", pMsg->Details.ProductName, sizeof(pMsg->Details.ProductName), node.second.c_str());
      pMsg->Details.ProductID = ::GetPrivateProfileIntA("main", "GameId", 0, node.second.c_str());

      if (pMsg->Details.ProductID <= 0) {
       extract_execute_result = false;
       break;
      }
      //D:\__Github__\Windows\bin\Win32\Debug\pchacker\finishs\4027\CS16_chs_setup\CS16_chs\Game\Game\cstrike.exean_chs\Game\shanghai.exe
      std::string strFileName = shared::Win::PathFixedA(current_work_outpath + "\\" + FileName);
      std::string strico = shared::Win::PathFixedA(current_work_outpath + "\\" + ico);
      ::memset(pMsg->Details.StartupPEPathname,0x00, sizeof(pMsg->Details.StartupPEPathname));
      ::memset(pMsg->Details.ProductLogoPathname, 0x00, sizeof(pMsg->Details.ProductLogoPathname));
      ::memcpy(pMsg->Details.ProductLogoPathname, strico.c_str(), strico.size());
      ::memcpy(pMsg->Details.StartupPEPathname, strFileName.c_str(), strFileName.size());
     }
    }

    if (!extract_execute_result)
     break;
   }///for count 2

   pMsg->ProcessId = ::GetCurrentProcessId();
   pMsg->TaskId = Global::TaskId();
   pMsg->extract_current_extract_total_size = 0;
   pMsg->extract_progress = 0;
   pMsg->extract_target_total_size = 0;
   pMsg->extract_total_size = 0;

   std::string write_;

   if (extract_execute_result && shared::Win::AccessA(pMsg->Details.StartupPEPathname)) {
    shared::Win::Packet::Made(pchacker::TYPE_TASKMAN_MSG_EXTRACT_SUCCESS,
     std::string((char*)pMsg, pchacker::LENTASKMANMSG),
     write_);
   }
   else {
    shared::Win::Packet::Made(pchacker::TYPE_TASKMAN_MSG_EXTRACT_FAILED,
     std::string((char*)pMsg, pchacker::LENTASKMANMSG),
     write_);
   }

   Global::ClientGet()->Write(write_);
  } while (0);
  SK_DELETE_PTR(pMsg);
  Global::SystemExitFlag(true);
 }

 void Core::Process() {
  do {

   do {





   } while (0);


   std::this_thread::sleep_for(std::chrono::milliseconds(10));
   if (!m_IsOpen.load())
    break;
  } while (1);
 }

}///namespace local