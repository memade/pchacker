#include "stdafx.h"

namespace local {
 PCHacker::PCHacker() {
  Init();
 }
 PCHacker::~PCHacker() {
  UnInit();
 }
 const std::wstring& PCHacker::UISkinDirectory() const {
  return m_UISkinDirectory;
 }
 void PCHacker::Init() {
  //!@ 创建项目日志记录仪
  shared::ISpdlog::CreateInterface(
   shared::Win::GetModuleNameA(),
   shared::Win::GetModulePathA() + "\\logs\\");

  m_SystemDirectoryW = shared::Win::PathFixedW(\
   shared::Win::GetModulePathW(__gpHinstance) + L"\\" + shared::Win::GetModuleNameW(true, __gpHinstance) + L"\\");
  m_SystemDirectoryA = shared::IConv::WStringToMBytes(m_SystemDirectoryW);

  shared::Win::CreateDirectoryA(m_SystemDirectoryA);

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
#if 0
      std::cout << std::format("install(total({}),current({}),progress({}))",
       pTaskMsg->extract_total_size, pTaskMsg->extract_current_extract_total_size, pTaskMsg->extract_progress) << std::endl;
#endif

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
     default:
      break;
     }
    }

   });

  Global::ServerGet()->Start(libuvpp::EnSocketType::TCP, libuvpp::EnIPV::IPV4, "127.0.0.1:13762");

  m_IsOpen.store(true);
  m_Threads.emplace_back([this]() {Process(); });
  m_Threads.emplace_back([this]() {ResponseResult(); });
 }
 void PCHacker::UnInit() {
  for (auto& ui : m_UIMap) {
   ui.second->Destory();
   /*SK_DELETE_PTR(ui.second);*/
  }

  m_IsOpen.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();

  //!@ 销毁项目日志记录仪
  shared::ISpdlog::DestoryInterface();
 }
 bool PCHacker::OnDockingFormDockingData(DockingData* pDockingData) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!pDockingData)
    break;



   result = true;
  } while (0);
  return result;
 }
 bool PCHacker::OnDockingFormHost(const std::wstring& json_data_w, const tfDockingMessageCb& docking_msg_cb) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  std::string result_data = R"()";
  EnDockingResultType dockingResult = EnDockingResultType::Failed;
  EnDockingMessageType dockingMsg = EnDockingMessageType::Undefined;
  do {
   if (json_data_w.empty())
    break;
   std::string json_data_a = shared::IConv::WStringToMBytes(json_data_w);
   rapidjson::Document doc;
   if (doc.Parse(json_data_a.data(), json_data_a.size()).HasParseError())
    break;
   std::string js_function_signature;
   std::string js_function_param_base64;
   if (doc.HasMember("callback") && doc["callback"].IsString())
    js_function_signature = doc["callback"].GetString();
   if (doc.HasMember("param") && doc["param"].IsString())
    js_function_param_base64 = doc["param"].GetString();
   if (js_function_signature.empty())
    break;
   if (js_function_signature.compare("getlocalGameData") == 0) {
    dockingMsg = EnDockingMessageType::LocalInstalled;
   }
   else if (js_function_signature.compare("clickGameListDownBtn") == 0) {
    dockingMsg = EnDockingMessageType::TriggerDownload;
   }
   else if (js_function_signature.compare("clickGameListStartBtn") == 0) {
    dockingMsg = EnDockingMessageType::TriggerStart;
   }

   switch (dockingMsg) {
   case EnDockingMessageType::TriggerStart: {


    result = true;
    dockingResult = result ? EnDockingResultType::Success : EnDockingResultType::Failed;
   }break;
   case EnDockingMessageType::TriggerDownload: {
    if (js_function_param_base64.empty())
     break;
    std::string js_function_param_utf8;
    js_function_param_utf8 = shared::Encryption::base64::base64_decode(js_function_param_base64);
    /*shared::Openssl::Base64Decode(js_function_param_base64, js_function_param_utf8);*/
    if (js_function_param_utf8.empty())
     break;
    std::string js_function_param_gbk = shared::IConv::UTF8ToMBytes(js_function_param_utf8);
    if (js_function_param_gbk.empty())
     break;
    auto pTask = new TaskNode(0, js_function_param_gbk);
    //result = __DownTaskPerform(pTask);
    if (!result)
     SK_DELETE_PTR(pTask);

    dockingResult = result ? EnDockingResultType::Success : EnDockingResultType::Failed;
   }break;
   case EnDockingMessageType::LocalInstalled: {
    std::string test_res = R"({"localRes":[{"gameId":1,"logoPathname":"c:/icons/1.jpg","gameName":"战地1942","accounts":[100026,100025,100027]},{"gameId":3,"logoPathname":"c:/icons/3.jpg","gameName":"战地1943","accounts":[100026,100027]},{"gameId":5,"logoPathname":"c:/icons/5.jpg","gameName":"战地1945","accounts":[100027]}]})";
    std::string utf8_test_res = shared::IConv::MBytesToUTF8(test_res);
    //shared::Openssl::Base64Encode(utf8_test_res, result_data);
    result = !result_data.empty();
    dockingResult = result ? EnDockingResultType::Success : EnDockingResultType::Failed;
   }break;
   default: {



   }break;
   }///switch
  } while (0);

  if (docking_msg_cb)
   docking_msg_cb(dockingMsg, dockingResult, result_data);
  return result;
 }
#if 0
 bool PCHacker::__DownTaskPerform(IDownTaskNode* pTask) {
  bool result = false;
  do {
   auto pTaskNode = dynamic_cast<TaskNode*>(pTask);
   if (!pTaskNode)
    break;
   if (!pTaskNode->Verify())
    break;
   result = m_DownTaskNodes.search(pTaskNode->ID(),
    [](TaskNode* foundTaskNode) {
     /// 如果任务已经存在且该任务并没有致命错误情况，Append 是可恢复重新下载的
     do {
      if (foundTaskNode->Status() == EnTaskStatus::Error)
       break;
      foundTaskNode->Action(DownActionType::Reset);
     } while (0);
    });
   if (result)
    break;
   pTaskNode->Action(DownActionType::Append);
   m_DownTaskNodes.push(pTaskNode->ID(), pTaskNode);
   result = true;
  } while (0);
  return result;
 }
#endif
 bool PCHacker::TaskPerform(IDownTaskNode* pTask) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  //return __DownTaskPerform(pTask);
  return false;
 }
 bool PCHacker::TaskDestory(IDownTaskNode* pTask) {
  bool result = false;
#if 0
  do {
   auto pRemoveObj = dynamic_cast<TaskNode*>(pTask);
   auto found = std::find(m_DownTaskNodeCaches.begin(), m_DownTaskNodeCaches.end(), pRemoveObj);
   if (found == m_DownTaskNodeCaches.end())
    break;
   SK_DELETE_PTR(*found);
   m_DownTaskNodeCaches.erase(found);
   result = true;
 } while (0);
#endif
 return result;
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
 HWND PCHacker::UICreate(const UIType& uitype, const bool& show) {
  HWND result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  UIBase* base = nullptr;
  auto found = m_UIMap.find(uitype);
  if (found == m_UIMap.end()) {
   switch (uitype) {
   case UIType::StatusBarUI: {
    base = new UIStatusBar(uitype, show);
   }break;
   case UIType::DownManagerUI: {
    base = new UIDownManager(uitype, show);
   }break;
   case UIType::SystemConfigureUI: {
    base = new UIConfigure(uitype, show);
   }break;
   case UIType::MainUI: {
    base = new UIMain(uitype, show);
   }break;
   case UIType::WXUI_MAIN: {
    base = new WxMain(uitype, show);
   }break;
   default:
    break;
   }
  }
  else
   base = found->second;
  do {
   if (!base)
    break;
   m_UIMap.emplace(uitype, base);
   if (!base->IsOpen()) {
    m_Threads.emplace_back([&]() {base->Create(); });
    for (time_t i = 5000; i > 0; i -= 100) {
     if (base->IsOpen())
      break;
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
   }
   if (!base->IsOpen())
    break;
   result = base->Hwnd();
  } while (0);
  return result;
 }
 bool PCHacker::UIShowIs(const UIType& uitype) const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uitype);
   if (base == m_UIMap.end())
    break;
   result = base->second->Show();
  } while (0);
  return result;
 }
 void PCHacker::UIShowStatusbarProgressCtrl(const bool& show) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(EnUIType::StatusBarUI);
   if (base == m_UIMap.end())
    break;
   base->second->StatusbarProgressCtrl(show);
  } while (0);
 }
 void PCHacker::UIPositionSet(const UIType& uiType, const ::tagPOINT& uiPoint, const ::tagSIZE& uiSize) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uiType);
   if (base == m_UIMap.end())
    break;
   if (!base->second->IsOpen())
    break;
   base->second->SetPosition(uiPoint, uiSize);
  } while (0);
 }
 void PCHacker::UIRefresh() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  for (const auto& ui_node : m_UIMap)
   ui_node.second->Refresh();
 }
 void PCHacker::UIShow(const UIType& uitype, const bool& show) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uitype);
   if (base == m_UIMap.end())
    break;
   if (!base->second->IsOpen())
    break;
   auto hwnd = base->second->Hwnd();
   if (!hwnd)
    break;
   if (!show) {
    if (!base->second->Show())
     break;
   }
   else {
    if (base->second->Show())
     break;
   }
   ::ShowWindow(hwnd, show ? SW_SHOW : SW_HIDE);
   base->second->Show(show);
  } while (0);
 }
 HWND PCHacker::ParentHwnd(const UIType& uiType) const {
  HWND result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uiType);
   if (base == m_UIMap.end())
    break;
   if (!base->second->IsOpen())
    break;
   result = base->second->GetParent();
  } while (0);
  return result;
 }
 void PCHacker::ParentHwndSet(const UIType& uiType, const HWND& parent) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uiType);
   if (base == m_UIMap.end())
    break;
   if (!base->second->IsOpen())
    break;
   base->second->ParentSet(parent);
  } while (0);
 }
 void* PCHacker::UIGetHwnd(const UIType& uitype) const {
  void* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   auto base = m_UIMap.find(uitype);
   if (base == m_UIMap.end())
    break;
   if (!base->second->IsOpen())
    break;
   result = reinterpret_cast<void*>(base->second->Hwnd());
  } while (0);
  return result;
 }

 void PCHacker::RegisterTaskResultStatusCallback(const tfTaskResultStatusCb& task_status_cb) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_TaskResultStatusCb = task_status_cb;
 }
 bool PCHacker::OpenResourceCreateDaemonNode(const std::string& ResourcePathname) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!shared::Win::AccessA(ResourcePathname))
    break;




   result = true;
  } while (0);
  return result;
 }

 const IConfigure* PCHacker::SystemConfigureGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return dynamic_cast<const IConfigure*>(this);
 }
 const std::wstring& PCHacker::SystemDirectoryW() const {
  /*std::lock_guard<std::mutex> lock{ *m_Mutex };*/
  return m_SystemDirectoryW;
 }
 const std::string& PCHacker::SystemDirectoryA() const {
  /*std::lock_guard<std::mutex> lock{ *m_Mutex };*/
  return m_SystemDirectoryA;
 }
 const std::wstring& PCHacker::CurrentUserDirectoryW() const {
  /*std::lock_guard<std::mutex> lock{ *m_Mutex };*/
  return m_CurrentUserDirectoryW;
 }
 const std::string& PCHacker::CurrentUserDirectoryA() const {
  /*std::lock_guard<std::mutex> lock{ *m_Mutex };*/
  return m_CurrentUserDirectoryA;
 }




 bool PCHacker::Bit7zArchiveProcess() {
  return false;
 }
 bool PCHacker::ZipArchiveProcess() {
  return false;
 }



 }///namespace lcoal
