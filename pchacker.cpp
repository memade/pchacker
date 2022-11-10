#include "stdafx.h"

namespace local {
 PCHacker::PCHacker() {
  Init();
 }
 PCHacker::~PCHacker() {
  UnInit();
 }
 void PCHacker::Init() {
  m_pZip = new Zip();
  m_pWin = new Win();
  m_pCom = new Com();
  m_pConfigure = new Configure();
  m_pEncryption = new Encryption();
 }
 void PCHacker::UnInit() {
  SK_DELETE_PTR(m_pZip);
  SK_DELETE_PTR(m_pWin);
  SK_DELETE_PTR(m_pCom);
  SK_DELETE_PTR(m_pConfigure);
  SK_DELETE_PTR(m_pEncryption);

 }

 bool PCHacker::Start(const IConfigure* pConfigure) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_IsOpen.load())
    break;
   if (pConfigure)
    *m_pConfigure << dynamic_cast<const Configure*>(pConfigure);
   //!@ Create project module log recorder
   shared::ISpdlog::CreateInterface(
    m_pConfigure->ProjectLoggerRecorderModuleName(),
    m_pConfigure->ProjectLoggerRecorderPath());

   do {
    if (!m_pConfigure->EnableLibcurlpp())
     break;
    if (!Global::LibcurlGet()->Start())
     break;

   } while (0);

   do {
    if (!m_pConfigure->EnableLibuvppServer())
     break;

    Global::ServerGet()->SessionCreateAfterCb(
     [this](libuvpp::ISession* pSession) {
      pSession->Write(pchacker::TYPE_TASKMAN_MSG_WELCOME, "");
     });
    Global::ServerGet()->SessionDestoryBeforeCb(
     [&](libuvpp::ISession* pSession) {
      m_TaskmanPtrQ.pop(pSession->BindTaskId(),
       [&](const auto&, auto& pTaskman) {
        pTaskman->Release();
       });
     });
    Global::ServerGet()->MessageCb(
     [&](libuvpp::ISession* pSession, const std::string& message) {
      auto pMsg = (shared::PPACKETHEAD)message.data();
      if (pMsg->Verify()) {
       auto pTaskMsg = reinterpret_cast<pchacker::PTASKMANMSG>(pMsg->data);
       switch (pMsg->command) {
       case pchacker::TYPE_TASKMAN_MSG_HELLO: {
        pSession->BindTaskId(pTaskMsg->TaskId);
        m_TaskmanPtrQ.search(pTaskMsg->TaskId,
         [&](Taskman* pTaskman) {
          pTaskMsg->ProcessId = ::GetCurrentProcessId();
          ::memcpy(pTaskMsg->InPathname, pTaskman->InPathname().data(), pTaskman->InPathname().size());
          ::memcpy(pTaskMsg->OutPath, pTaskman->OutPath().data(), pTaskman->OutPath().size());
          pSession->Write(pchacker::TYPE_TASKMAN_MSG_EXTRACT, std::string((char*)pTaskMsg, pchacker::LENTASKMANMSG));
         });
       }break;
       case pchacker::TYPE_TASKMAN_MSG_EXTRACT_NOTIFY: {
        m_TaskPool.search(pTaskMsg->TaskId,
         [&](const auto&, pchacker::ITaskNode* pTask) {
          pchacker::ExtractProgressInfo progress;
          progress.extract_current = pTaskMsg->extract_current_extract_total_size;
          progress.extract_percentage = pTaskMsg->extract_progress;
          progress.extract_total = pTaskMsg->extract_total_size;

          *pTask << progress;

          if (pTask->Status() != EnActionType::InstallBeworking)
           pTask->Action(EnActionType::InstallBeworking);
          m_ResponseResultQ.push(pTask);
         });

       }break;
       case pchacker::TYPE_TASKMAN_MSG_EXTRACT_SUCCESS: {

        m_TaskPool.search(pTaskMsg->TaskId,
         [&](const auto&, pchacker::ITaskNode* pTask) {
          *pTask << pTaskMsg->Details;
          pTask->Action(EnActionType::InstallFinish);
          m_ResponseResultQ.push(pTask);
         });
        //shared::Win::Process::Terminate(pTaskMsg->ProcessId);
       }break;
       case pchacker::TYPE_TASKMAN_MSG_EXTRACT_FAILED: {
        //shared::Win::Process::Terminate(pTaskMsg->ProcessId);
        m_TaskPool.search(pTaskMsg->TaskId,
         [&](const auto&, pchacker::ITaskNode* pTask) {
          pTask->Action(EnActionType::InstallFailed);
          m_ResponseResultQ.push(pTask);
         });
       }break;
       case pchacker::TYPE_CARDPACKAGE_MSG_HELLO: {
        auto sk = 0;
       }break;
       case pchacker::TYPE_CARDPACKAGE_MSG_EXIT: {
        
        if (!m_OpenResourceCb)
         break;
        std::vector<std::string> parses;
        shared::Win::File::ParseA(message, '@', parses);
        if (parses.size() < 2)
         break;
        unsigned long long id = atoll(parses[1].c_str());
        if (id <= 0)
         break;
        m_OpenResourceCb(id);
       }break;
       case pchacker::TYPE_CARDPACKAGE_MSG_CHECK_FAILED: {
        auto sk = 0;
       }break;
       case pchacker::TYPE_CARDPACKAGE_MSG_CHECK_SUCCESS: {
        auto sk = 0;
       }break;

       default:
        break;
       }
      }

     });

    if (!Global::ServerGet()->Start(libuvpp::EnSocketType::TCP, libuvpp::EnIPV::IPV4, m_pConfigure->LocalServiceTcpAddr()))
     break;
    //::MessageBoxA(NULL, "EnableLibuvpp start success.", NULL, MB_TOPMOST);
   } while (0);


   m_IsOpen.store(true);
   m_Threads.emplace_back([this]() {Process(); });
  } while (0);
  return m_IsOpen.load();
 }
 void PCHacker::Stop() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;

   if (m_pConfigure->EnableLibcurlpp())
    Global::LibcurlGet()->Stop();

   if (m_pConfigure->EnableLibuvppServer())
    Global::ServerGet()->Stop();

   m_IsOpen.store(false);
   for (auto& t : m_Threads)
    t.join();
   m_Threads.clear();


   //!@ Destory project module log recorder
   shared::ISpdlog::DestoryInterface();
  } while (0);
 }
 bool PCHacker::TaskAction(const TypeID& resid, const EnActionType& action) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  result = m_TaskPool.search(resid,
   [&](TaskNode* pTask) {
    pTask->Action(action);
   });
  return result;
 }
 IDownTaskNode* PCHacker::TaskCreate(const TypeID& task_id) {
  IDownTaskNode* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  result = new TaskNode(task_id);
  m_TaskPool.push(task_id, dynamic_cast<TaskNode*>(result));
  return result;
 }
 void PCHacker::RegisterOpenResourceCallback(const tfOpenResourceCallback& cb) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_OpenResourceCb = cb;
 }
 void PCHacker::RegisterTaskResultStatusCallback(const tfTaskResultStatusCb& task_status_cb) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_TaskResultStatusCb = task_status_cb;
 }

 IConfigure* PCHacker::ConfigureGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IConfigure*>(m_pConfigure);
 }

 IEncryption* PCHacker::EncryptionGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IEncryption*>(m_pEncryption);
 }

 ICom* PCHacker::ComGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<ICom*>(m_pCom);
 }

 IWin* PCHacker::WinGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IWin*>(m_pWin);
 }

 IZip* PCHacker::ZipGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<IZip*>(m_pZip);
 }
 libcurlpp::ILibcurlpp* PCHacker::LibcurlppGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return Global::LibcurlGet();
 }
 libuvpp::ILibuv* PCHacker::LibuvppGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return Global::LibuvGet();
 }
}///namespace lcoal
