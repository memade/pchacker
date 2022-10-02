#if !defined(INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__)
#define INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__

namespace local {

 const size_t NormalUserLimitDownSpeedValue = 200 * 1024;

 const wchar_t PathUISkin[] = LR"(\skin\)";

 const char SystemConfigFilename[] = R"(system_configure.json)";
 const char FolderNameDownCache[] = R"(caches)";
 const char FolderNameInstalled[] = R"(res)";

 enum class CommonColorType {
  Red,
  Green,
  White,
  Black,
  Blue,
 };

 enum class CommonStringType {
  DownTaskPaused = int(EnDownActionType::Pause),
  DownTaskStop = int(EnDownActionType::Stop),
  Downing = int(EnDownActionType::Beworking),
  InPreparation= int(EnDownActionType::End)+1,
  NetworkDisconnection= InPreparation+1,
  DownTaskReady= InPreparation+2,
 };

 static const std::map<CommonStringType, std::wstring> CommonStringMap = {
  {CommonStringType::InPreparation,LR"(正在准备)"},
  {CommonStringType::NetworkDisconnection,LR"(网络断开)"},
  {CommonStringType::DownTaskReady,LR"(准备就绪)"},
  {CommonStringType::DownTaskPaused,LR"(任务暂停)"},
  {CommonStringType::DownTaskStop,LR"(任务停止)"},
  {CommonStringType::Downing,LR"(正在下载)"},
 };

 static const std::map<CommonColorType, DWORD> CommonColorMap = {
 {CommonColorType::Red,RGB(255,0,0)},
 {CommonColorType::Green,RGB(0,255,0)},
 {CommonColorType::Blue,RGB(0,0,255)},
 {CommonColorType::White,RGB(255,255,255)},
 {CommonColorType::Black,RGB(0,0,0)},
 };

 typedef struct tagProgressRoute {
  __int64 dltotal/*+ ResumeFromLarge*/;
  __int64 dlnow/*+ ResumeFromLarge*/;
  __int64 ultotal;
  __int64 ulnow;
  tagProgressRoute(const __int64& _dltotal, const __int64& _dlnow, const __int64& _ultotal, const __int64& _ulnow) {
   dltotal = _dltotal;
   dlnow = _dlnow;
   ultotal = _ultotal;
   ulnow = _ulnow;
  }
  tagProgressRoute() {
   ::memset(this, 0x00, sizeof(*this));
  }
  void operator=(const tagProgressRoute& obj) {
   ::memcpy(this, &obj, sizeof(*this));
  }
 }ProgressRoute;


}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_13T20:41:48.7855704Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___F92F8D7A_B486_4872_A589_75BEA5FC22DF__HEAD__
