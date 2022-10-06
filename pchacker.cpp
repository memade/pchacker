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
  m_SystemDirectoryW = shared::Win::PathFixedW(\
   shared::Win::GetModulePathW(__gpHinstance) + L"\\" + shared::Win::GetModuleNameW(true, __gpHinstance) + L"\\");
  m_SystemDirectoryA = shared::IConv::WStringToMBytes(m_SystemDirectoryW);

  shared::Win::CreateDirectoryA(m_SystemDirectoryA);

  /*m_pSystemConfigure = new Configure(m_SystemDirectoryA + SystemConfigFilename);*/

  do {//!@ 释放UI资源
#ifdef _DEBUG
   m_UISkinDirectory = LR"(D:\__SVN__\Memade\projects\pcdown\res\skin\)";
   break;
#endif // _DEBUG

   m_UISkinDirectory = shared::Win::PathFixedW(m_SystemDirectoryW + L"\\" + PathUISkin + L"\\");
   shared::Win::CreateDirectoryW(m_UISkinDirectory);
   /*if (!shared::Win::AccessW(m_UISkinDirectory)) */
   {
    std::string res = std::string((char*)&skin_zip_res[0], sizeof(skin_zip_res));
    res = shared::Encryption::WemadeDecode(res);
    if (!shared::Zip::IsZipCompress(res))
     break;
    if (!shared::Zip::zipBufferUnCompress(res,
     [](const std::string&, const std::string&, bool&) {
      return true;
     },
     shared::IConv::WStringToMBytes(m_UISkinDirectory)))
     break;
   }
  } while (0);


  auto discard = ::CoInitialize(NULL);
  m_IsOpen.store(true);
  m_Threads.emplace_back([this]() {Process(); });
 }
 void PCHacker::UnInit() {
  for (auto& ui : m_UIMap) {
   ui.second->Close();
   /*SK_DELETE_PTR(ui.second);*/
  }
  m_IsOpen.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();
  ::CoUninitialize();
 }
 bool PCHacker::OnDockingFormDockingData(DockingData* pDockingData) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!pDockingData)
    break;
   if (!pDockingData->pXL_DownTaskParam)
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
    auto pTask = new DownTaskNode(js_function_param_gbk);
    result = __DownTaskPerform(pTask);
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
   docking_msg_cb(dockingMsg, dockingResult,result_data);
  return result;
 }

 bool PCHacker::__DownTaskPerform(IDownTaskNode* pTask) {
  bool result = false;
  do {
   auto pTaskNode = dynamic_cast<DownTaskNode*>(pTask);
   if (!pTaskNode)
    break;
   if (!pTaskNode->Verify())
    break;
   result = m_DownTaskNodes.search(pTaskNode->ID(),
    [](DownTaskNode* foundTaskNode) {
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
 bool PCHacker::DownTaskPerform(IDownTaskNode* pTask) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return __DownTaskPerform(pTask);
 }
 bool PCHacker::DownTaskDestory(IDownTaskNode* pTask) {
  bool result = false;
  do {
   auto pRemoveObj = dynamic_cast<DownTaskNode*>(pTask);
   auto found = std::find(m_DownTaskNodeCaches.begin(), m_DownTaskNodeCaches.end(), pRemoveObj);
   if (found == m_DownTaskNodeCaches.end())
    break;
   SK_DELETE_PTR(*found);
   m_DownTaskNodeCaches.erase(found);
   result = true;
  } while (0);
  return result;
 }
 bool PCHacker::DownTaskAction(const TypeID& resid, const DownActionType& action) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  result = m_DownTaskNodes.search(resid,
   [&](DownTaskNode* pTask) {
    pTask->Action(action);
   });
  return result;
 }
 IDownTaskNode* PCHacker::DownTaskCreate() {
  IDownTaskNode* result = nullptr;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  result = dynamic_cast<IDownTaskNode*>(m_DownTaskNodeCaches.emplace_back(new DownTaskNode()));
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
    m_Threads.emplace_back([&]() {base->Open(); });
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
 void PCHacker::Process() {
#if ENABLE_MODULE_UI
  UIBase* pUIDownMgr = nullptr;
  UIBase* pUIStatusbar = nullptr;
#endif

  std::vector<DownTaskNode*> RemoveTasks;
  do {
   do {
    if (m_DownTaskNodes.empty())
     break;
    do {
#if ENABLE_MODULE_UI
     if (pUIStatusbar)
      break;
     auto found_ui = m_UIMap.find(EnUIType::StatusBarUI);
     if (found_ui == m_UIMap.end())
      break;
     pUIStatusbar = found_ui->second;
    } while (0);
    if (!pUIStatusbar)
     break;
#endif
    m_DownTaskNodes.iterate_clear(
     [&](const TypeID& identify, DownTaskNode* pTaskNode, bool& itbreak, bool& itclear) {
      switch (pTaskNode->Action()) {
      case EnDownActionType::Normal: {

      }break;
      case EnDownActionType::Append: {
       if (pTaskNode->UIDownTaskElementGet())
        break;

#if ENABLE_MODULE_UI
       if (!pUIDownMgr) {
        auto found_ui_downmgr = m_UIMap.find(EnUIType::DownManagerUI);
        if (found_ui_downmgr == m_UIMap.end())
         break;
        pUIDownMgr = found_ui_downmgr->second;
       }
       if (!pUIDownMgr)
        break;
       if (!pUIDownMgr->AppendDownTaskNode(pTaskNode))
        break;
#endif
       pTaskNode->Action(EnDownActionType::Preparation);
      }break;
      case EnDownActionType::Preparation: {
       if (pTaskNode->Status() == EnTaskStatus::InPreparation)
        break;
       pTaskNode->Status(EnTaskStatus::InPreparation);
       do {
        if (!pTaskNode->Preparation())
         break;

        pTaskNode->Action(EnDownActionType::Ready);
       } while (0);
      }break;
      case EnDownActionType::Ready: {
       pTaskNode->Action(EnDownActionType::Start);
      }break;
      case EnDownActionType::Pause: {
       pTaskNode->Stop();
      }break;
      case EnDownActionType::Remove: {
       itclear = true;
       RemoveTasks.emplace_back(pTaskNode);
      }break;
      case EnDownActionType::Reset: {
       auto sk = 0;
      }break;
      case EnDownActionType::Start: {
       do {
        if (!pTaskNode->Start())
         break;


       } while (0);
      }break;
      case EnDownActionType::Stop: {
       auto sk = 0;
      }break;
      case EnDownActionType::Waitinline: {
       auto sk = 0;
      }break;
      default:
       break;
      }

     });
   } while (0);


#if ENABLE_MODULE_UI
   do {//!@ 实时检测下载任务总数
    if (!pUIStatusbar || !pUIDownMgr)
     break;
    auto dwon_task_total = pUIDownMgr->UIListDownTaskCount();
    /// 如果下载任务不为空就切换到下载列表分页，否则切换到下载空提示分页
    if (dwon_task_total > 0)
     pUIDownMgr->SwitchPage(EnChildPageType::Normal);
    else
     pUIDownMgr->SwitchPage(EnChildPageType::Empty);
    pUIStatusbar->DownStatusTotalCount(dwon_task_total);


    //!@ 需要移除的任务
    for (auto it = RemoveTasks.begin(); it != RemoveTasks.end();) {
     pUIDownMgr->RemoveDownTaskNode(*it);
     SK_DELETE_PTR(*it);
     it = RemoveTasks.erase(it);
    }
#endif


   } while (0);






   if (!m_IsOpen.load())
    break;
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
  } while (1);
 }












 bool PCHacker::Bit7zArchiveProcess() {
  return false;
 }
 bool PCHacker::ZipArchiveProcess() {
  return false;
 }




}///namespace lcoal
