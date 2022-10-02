#include "stdafx.h"

namespace local {
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 void IDownTaskElement::SetDownDownTimeRemain(const size_t& size_remain,
  const size_t& current_down_speed_value /*= NormalUserLimitDownSpeedValue*/, const DWORD& color /*= 0*/) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"D1C4FD362124");
   if (!ui)
    break;
   std::wstring time_text = L"--:--:--";
   if (size_remain > 0 && current_down_speed_value > 0) {
    time_t total_s = size_remain / current_down_speed_value;
    time_text = shared::IConv::MBytesToWString(shared::Win::Time::TimePeriodUnMade(static_cast<UINT>(total_s)));
   }
   ui->SetText(time_text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::SetDownloadCompletionRate(const size_t& total, const size_t& current) {
  std::wstring text = L"0.0%";
  CLabelUI* ui_label = nullptr;
  CProgressUI* ui_progress = nullptr;
  do {
   ui_progress = GetSubCtrl<CProgressUI>(L"90352B27A442");
   ui_label = GetSubCtrl<CLabelUI>(L"56E157AE72A8");
   if (!ui_progress || !ui_label)
    break;
   if (total <= 0 || current <= 0)
    break;
   const auto max = ui_progress->GetMaxValue();
   double current_progress = (current * 1.0) / (total * 1.0);
   int value = static_cast<int>(current_progress * max);
   double RatioProgress = current_progress * max / 100.0;
   text = std::format(L"{:.2f}%", RatioProgress);
  } while (0);
  if (ui_label)
   ui_label->SetText(text.c_str());
 }
 void IDownTaskElement::StartingSwitch(const bool& status) {
  do {
   auto ui = GetSubCtrl<COptionUI>(L"06A057E7350B");
   if (!ui)
    break;
   auto current_status = ui->IsSelected();
   if (current_status == status)
    break;
   ui->Selected(status);
  } while (0);
 }
 void IDownTaskElement::SetLogo(const std::wstring& logo_pathname) {
  do {
   if (!shared::Win::AccessW(logo_pathname))
    break;
   auto ui = GetSubCtrl<CLabelUI>(L"CCB822F77204");
   if (!ui)
    break;
   ui->SetBkImage(logo_pathname.c_str());
  } while (0);
 }
 void IDownTaskElement::SetDownSpeedValueVip(const size_t& real_speed/*-NormalUserLimitDownSpeedValue*/) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"F5E1F8FAD133");
   if (!ui)
    break;
   auto speed = shared::Win::RealtimeSpeed(real_speed);
   ui->SetText(shared::IConv::MBytesToWString(speed).c_str());
  } while (0);
 }
 void IDownTaskElement::SetDownSpeedValue(const size_t& value) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"76E1ED97A767");
   if (!ui)
    break;
   auto speed = shared::Win::RealtimeSpeed(value);
   ui->SetText(shared::IConv::MBytesToWString(speed).c_str());
  } while (0);
 }
 void IDownTaskElement::SetProgressValue(const size_t& total, const size_t& current) {
  do {
   if (total <= 0 || current <= 0)
    break;
   auto ui = GetSubCtrl<CProgressUI>(L"90352B27A442");
   if (!ui)
    break;
   const auto max = ui->GetMaxValue();
   double current_progress = (current * 1.0) / (total * 1.0);
   int value = static_cast<int>(current_progress * max);
   ui->SetValue(static_cast<int>(value));
  } while (0);
 }
 void IDownTaskElement::SetName(const std::wstring& name, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"DD0FB204BE1D");
   if (!ui)
    break;
   ui->SetText(name.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::StatusTextSet(const std::wstring& text, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"E509EB1128BD");
   if (!ui)
    break;
   ui->SetText(text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::ResourceSizeTextSet(const size_t& total, const size_t& current, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"E4BD5BC33011");
   if (!ui)
    break;
   if (total <= 0 && current <= 0) {
    ui->SetText(L"--/--");
    break;
   }
   auto realTotal = shared::Win::RealtimeSpeed(total);
   auto realCurrent = shared::Win::RealtimeSpeed(current);
   ui->SetText(std::format(L"{}/{}", shared::IConv::MBytesToWString(realCurrent), shared::IConv::MBytesToWString(realTotal)).c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 void IDownTaskElement::DownTotalTimeTextSet(const std::wstring& text, const DWORD& color) {
  do {
   auto ui = GetSubCtrl<CLabelUI>(L"D1C4FD362124");
   if (!ui)
    break;
   ui->SetText(text.c_str());
   if (color)
    ui->SetTextColor(color);
  } while (0);
 }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 DownTaskNode::DownTaskNode() {
  m_pRequestObj = Global::HttpGet()->CreateRequest();
 }
 DownTaskNode::DownTaskNode(const std::string& gbk_json_data) {
  do {
   if (gbk_json_data.empty())
    break;   
#if 0
   {
    "module":"runGame",
     "vip" : 1,
     "gameId" : 3,
     "gameName" : "战地1942.rar",
     "gameTime" : 120,
     "type" : 0,
     "ico" : "http://test.xitieba.com//admin/images/未标题-1.jpg",
     "url" : "https://ss.bscstorage.com/goodgame-mifang9ku/yxdown.com_BF1942_en.rar",
     "cmd" : ""
   }
#endif
   rapidjson::Document doc;
   if (doc.Parse(gbk_json_data.data(), gbk_json_data.size()).HasParseError())
    break;
   if (!doc.IsObject())
    break;
   if (doc.HasMember("vip") && doc["vip"].IsNumber())
    m_VipLevel = doc["vip"].GetUint();
   if (doc.HasMember("gameId") && doc["gameId"].IsNumber())
    m_ID = doc["gameId"].GetUint();
   if (doc.HasMember("gameName") && doc["gameName"].IsString())
    m_Name = doc["gameName"].GetString();
   if (doc.HasMember("gameTime") && doc["gameTime"].IsNumber())
    m_ResTime = doc["gameTime"].GetInt64();
   if (doc.HasMember("type") && doc["type"].IsNumber())
    m_ResType = doc["type"].GetUint();
   if (doc.HasMember("ico") && doc["ico"].IsString())
    m_LogoUrl = doc["ico"].GetString();
   if (doc.HasMember("url") && doc["url"].IsString())
    m_Url = doc["url"].GetString();
   if (doc.HasMember("cmd") && doc["cmd"].IsString())
    m_Cmd = doc["cmd"].GetString();
   if (doc.HasMember("account") && doc["account"].IsString())
    m_Account = doc["account"].GetString(); 
  } while (0);
  m_pRequestObj = Global::HttpGet()->CreateRequest();
 }
 DownTaskNode::~DownTaskNode() {

 }
 void DownTaskNode::LocalResDir(const std::string& path) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LocalResDir = path;
 }
 const std::string& DownTaskNode::LocalResDir() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LocalResDir;
 }
 void DownTaskNode::Name(const std::string& name) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Name = name;
 }
 const std::string& DownTaskNode::Name() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Name;
 }
 bool DownTaskNode::operator<<(const DockingData& dockingData) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!dockingData.Verify())
    break;

   m_Url = shared::IConv::WStringToMBytes(dockingData.pXL_DownTaskParam->szTaskUrl);
   if (dockingData.YXInstallData.ResIcoUrl[0] != 0)
    m_LogoUrl = shared::IConv::WStringToMBytes(dockingData.YXInstallData.ResIcoUrl);
   //TODO : Further padding is required here



   result = true;
  } while (0);
  return result;
 }
 void DownTaskNode::ID(const TypeID& id) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ID = id;
 }
 TypeID DownTaskNode::ID() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ID;
 }
 bool DownTaskNode::Verify() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ID <= 0)
    break;
   if (m_Url.empty())
    break;
   if (!m_pRequestObj)
    break;
   result = true;
  } while (0);
  return result;
 }
 IDownTaskElement* DownTaskNode::UIDownTaskElementCreate() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  CDialogBuilder builder;
  m_pUIDownTaskElement = builder.Create<IDownTaskElement>(LR"(nodes\uidwontasknode.xml)");
  if (!m_Name.empty())
   m_pUIDownTaskElement->SetName(shared::IConv::MBytesToWString(m_Name));
  return m_pUIDownTaskElement;
 }
 IDownTaskElement* DownTaskNode::UIDownTaskElementGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_pUIDownTaskElement;
 }
 EnTaskStatus DownTaskNode::Status() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Status;
 }
 void DownTaskNode::Status(const EnTaskStatus& status) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Status = status;
 }
 void DownTaskNode::Url(const std::string& url) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Url = url;
 }
 const std::string& DownTaskNode::Url() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Url;
 }
 const unsigned int& DownTaskNode::VipLevel() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_VipLevel;
 }
 void DownTaskNode::VipLevel(const unsigned int& level) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_VipLevel = level;
 }
 void DownTaskNode::Logo(const std::string& logo_buffer) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_LogoPathname = logo_buffer;
 }
 const std::string& DownTaskNode::Logo() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LogoPathname;
 }
 void DownTaskNode::Action(const DownActionType& type) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ActionType.store(type);
 }
 DownActionType DownTaskNode::Action() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ActionType.load();
 }
 bool DownTaskNode::Pause() {
  return Stop();
 }
 bool DownTaskNode::Start() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
#if 0
  do {
   if (m_ActionType != EnDownActionType::Start)
    break;

   if (!m_IsOpenThread.load()) {
    m_IsOpenThread.store(true);
    m_Threads.emplace_back([this]() {OnProgressChanged(); });
   }

   //!@ 任务节点开始下载
   auto pReqObj = Global::PCDownGet()->HttpObj()->RouteCreate();
   if (!pReqObj)
    break;
   pReqObj->Push(
    [&](shared::http::RequestObj* reqObj) {
     do {
      auto fixUrl = shared::Win::UrlFixedByDowntool(m_Url);
      reqObj->Url(fixUrl);
      reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_DOWN);
      reqObj->Header(false);
      if (m_VipLevel <= 0)
       reqObj->MaxRecvSpeedLarge(NormalUserLimitDownSpeedValue);
      reqObj->TimeoutResponseMS(10 * 1000);//!@ 超时
      reqObj->DownCacheFilePathname(m_DownCacheFilePathname);
      reqObj->ResultCb(
       [&](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {

        auto sk = 0;
       });
      //!@ dltotal + ResumeFromLarge, dlnow + ResumeFromLarge, ultotal, ulnow, nullptr
      reqObj->ProgressCb(
       [&](
        const __int64& dltotal/*+ ResumeFromLarge*/,
        const __int64& dlnow/*+ ResumeFromLarge*/,
        const __int64& ultotal,
        const __int64& ulnow,
        void*)->int {
         int result = static_cast<int>(shared::http::EnDownProgressStatus::EN_DOWN_PROGRESS_STATUS_ON);
         do {
          m_ProgressRouteQ.push(ProgressRoute(dltotal, dlnow, ultotal, ulnow));
         } while (0);
         return result;
       });
     } while (0);
     return true;
    });

   if (!Global::PCDownGet()->HttpObj()->Perform(pReqObj))
    break;

   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StartingSwitch(true);
   m_ActionType = EnDownActionType::Running;
   m_pUIDownTaskElement->StatusTextSet(CommonStringMap.at(CommonStringType::Downing));
   result = true;
  } while (0);
#endif
  return result;
 }
 bool DownTaskNode::Stop() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ActionType != EnDownActionType::Stop && m_ActionType != EnDownActionType::Pause)
    break;
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StartingSwitch(false);

   m_pUIDownTaskElement->SetDownDownTimeRemain(0, 0);
   m_pUIDownTaskElement->StatusTextSet(CommonStringMap.at(CommonStringType::DownTaskStop));
   m_ActionType = EnDownActionType::Stop;
   result = true;
  } while (0);

  m_IsOpenThread.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();
  return result;
 }
 bool DownTaskNode::Preparation() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (m_ID <= 0)
    break;
   if (m_Url.empty())
    break;
   std::string file_name;
   std::string file_format;
   shared::Win::GetFileNameAndFormat(m_LogoUrl, file_name, file_format);
   m_LogoPathname = shared::Win::PathFixedA(Global::PCHacherGet()->SystemDirectoryA() + "\\logos\\" + std::to_string(m_ID) + file_format);
   //!@ 初始化最终下载文件名
   shared::Win::GetFileNameAndFormat(m_Url, file_name, file_format);
   m_FinishPathname = shared::Win::PathFixedA(Global::PCHacherGet()->SystemDirectoryA() + "\\finishs\\" + std::to_string(m_ID) + file_format);
   //!@ 初始化下载缓冲文件路径名
   m_DownCacheFilePathname = shared::Win::PathFixedA(Global::PCHacherGet()->SystemDirectoryA() + "\\caches\\" + std::to_string(m_ID) + file_format);

   auto reqHead = Global::HttpGet()->CreateRequest();
   reqHead->RequestUrl(m_Url);
   reqHead->Header(true);
   reqHead->RequestType(malware::http::EnRequestType::REQUEST_TYPE_HEAD);
   reqHead->FinishCb(
    [&](const malware::http::IResponse* resObj) {
    

     result = true;
    });
   auto reqLogo = Global::HttpGet()->CreateRequest();
   reqLogo->RequestUrl(m_LogoUrl);
   reqLogo->RequestType(malware::http::EnRequestType::REQUEST_TYPE_GET);
   //reqLogo->HeadersAdd(R"(content-type: application/x-www-form-urlencoded)");
   reqLogo->FinishCb(
    [&](const malware::http::IResponse* resObj) {

     auto sk = 0;
    });
   Global::HttpGet()->PerformM({ reqLogo,reqHead });
   Global::HttpGet()->DestoryRequest({ reqLogo,reqHead });

#if 0
   auto pReqObj = Global::PCDownGet()->HttpObj()->RouteCreate();
   if (!pReqObj)
    break;
   if (!m_LogoUrl.empty() && !shared::Win::AccessA(m_LogoPathname)) {
    pReqObj->Push(
     [this](shared::http::RequestObj* reqObj) {
      auto fixUrl = shared::Win::UrlFixedByDowntool(shared::IConv::MBytesToUTF8(m_LogoUrl));
      reqObj->Url(fixUrl);
      reqObj->HttpHeaderAppend({ {"content-type", "application/x-www-form-urlencoded"} });
      reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_GET);
      reqObj->ResultCb(
       [&](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {
        do {
         if (resObj->HttpCode() != 200)
          break;
         shared::Win::File::Write(m_LogoPathname, resObj->ContentBody());
        } while (0);
       });
      return true;
     });
   }

   pReqObj->Push(
    [&](shared::http::RequestObj* reqObj) {
     auto fixUrl = shared::Win::UrlFixedByDowntool(shared::IConv::MBytesToUTF8(m_Url));
     reqObj->Url(fixUrl);
     reqObj->Type(shared::http::EnRequestType::EN_REQUEST_TYPE_HEAD);
     reqObj->ResultCb(
      [this, &result](const shared::http::RequestObj* reqObj, const shared::http::ResponseObj* resObj) {
       do {
        if (!resObj)
         break;
        if (resObj->HttpCode() != 200)
         break;
        m_ResourceTotalSize = resObj->ContentLength();
        result = m_ResourceTotalSize > 0;
       } while (0);
       if (!result) {
        m_Status = EnTaskStatus::Error;
        m_ActionType = EnDownActionType::Pause;
       }
      });
     return true;
    });
   Global::PCDownGet()->HttpObj()->Perform(pReqObj);
  } while (0);

  do {
   if (!m_pUIDownTaskElement)
    break;
   //!@ 设置资源(游戏)Logo
   if (shared::Win::AccessA(m_LogoPathname))
    m_pUIDownTaskElement->SetLogo(shared::IConv::MBytesToWString(m_LogoPathname));

   if (!result)
    break;
   //!@ 设置资源大小
   m_pUIDownTaskElement->ResourceSizeTextSet(static_cast<size_t>(m_ResourceTotalSize), 0);
   //!@ 初始化进度条数值
   m_pUIDownTaskElement->SetProgressValue(0, 0);
   //!@ 初始化实时下载速度
   m_pUIDownTaskElement->SetDownSpeedValue(0);
   //!@ 初始化VIP加速度
   m_pUIDownTaskElement->SetDownSpeedValueVip(0);
   //!@ 初始化[预测下载时间]
   m_pUIDownTaskElement->SetDownDownTimeRemain(static_cast<size_t>(m_ResourceTotalSize), \
    NormalUserLimitDownSpeedValue);
#endif


  } while (0);

  return result;
 }

 void DownTaskNode::SetStatusText(const std::wstring& text, const DWORD& color /*= CommonColorMap.at(CommonColorType::White)*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->StatusTextSet(text, color);
  } while (0);
 }
 void DownTaskNode::SetResourceSizeText(const size_t& total, const size_t& current, const DWORD& color /*= CommonColorMap.at(CommonColorType::White)*/) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_pUIDownTaskElement)
    break;
   m_pUIDownTaskElement->ResourceSizeTextSet(total, current, color);
  } while (0);
 }

 void DownTaskNode::OnProgressChanged() {
  const time_t calc_down_speed_interval = 500;
  volatile time_t prev_time_mark = shared::Win::Time::TimeStamp<std::chrono::milliseconds>();
  volatile __int64 prev_down_total = 0;//!@ 前一次下载量
  volatile __int64 prev_down_current = 0;
  do {

   do {
    if (m_ProgressRouteQ.empty())
     break;
    auto routes = m_ProgressRouteQ.pops();
    for (auto it = routes.begin(); it != routes.end(); ++it) {
     const auto current_time_ms = shared::Win::Time::TimeStamp<std::chrono::milliseconds>();
     do {
      if (it->dlnow == prev_down_total)
       break;
      if (!m_pUIDownTaskElement)
       break;
      m_pUIDownTaskElement->SetDownloadCompletionRate(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->SetDownDownTimeRemain(static_cast<size_t>(it->dltotal) - static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->ResourceSizeTextSet(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));
      m_pUIDownTaskElement->SetProgressValue(static_cast<size_t>(it->dltotal), static_cast<size_t>(it->dlnow));


      do {//!@ 计算下载速度
       if (current_time_ms - prev_time_mark < calc_down_speed_interval)
        break;
       if (it->dlnow < prev_down_total)
        break;
       if (m_VipLevel > 0) {
        size_t noVip = static_cast<size_t>((it->dlnow - prev_down_current) / 3 * 1);
        size_t Vip = static_cast<size_t>((it->dlnow - prev_down_current) / 3 * 2);
        m_pUIDownTaskElement->SetDownSpeedValue(noVip);
        m_pUIDownTaskElement->SetDownSpeedValueVip(Vip);
       }
       else
       {
        m_pUIDownTaskElement->SetDownSpeedValue(static_cast<size_t>(it->dlnow - prev_down_current));
       }

       prev_time_mark = current_time_ms;
       prev_down_current = it->dlnow;
      } while (0);

      prev_down_total = it->dlnow;
     } while (0);

    }

   } while (0);



   if (!m_IsOpenThread.load())
    break;
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   prev_time_mark += 100;
  } while (1);
 }
}///namespace lcoal
