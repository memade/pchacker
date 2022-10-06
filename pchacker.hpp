/*===- pchacker.hpp - Wrapper for 'extern "C"' ---------------*- C -*-=========*\
|*                                                                             *|
|* Part of the PCHacker® Project, under the Apache License v2.0 with PCHacker® *|
|* Exceptions.                                                                 *|
|* See http://skstu.com/pchacker/LICENSE.txt for license information.          *|
|* SPDX-License-Identifier: Apache-2.0 WITH PCHACKER-exception                 *|
|*                                                                             *|
|*===----------------------------------------------------------------------=== *|
|*                                                                             *|
|* This file is a summary of the interface for this project.                   *|
|*                                                                             *|
\*===----------------------------------------------------------------------====*/
#if !defined(INC_H___E0CDC3C1_8FD7_4C35_8638_D30703A362DE__HEAD__)
#define INC_H___E0CDC3C1_8FD7_4C35_8638_D30703A362DE__HEAD__
#if 0
@brief  @param  @return @author @date @version是代码书写的一种规范
@brief  ：简介，简单介绍函数作用
@param  ：介绍函数参数
@return：函数返回类型说明
@exception NSException 可能抛出的异常.
@author zhangsan：  作者
@date 2011 - 07 - 27 22:30 : 00 ：时间
@version 1.0 ：版本
@property ：属性介绍
#endif

#include <functional>

namespace xlapi_3_2_2_30 {
#pragma pack(push, 1)
 typedef struct tagDownTaskParam {
  int nReserved;
  wchar_t szTaskUrl[2084];          // 任务URL
  wchar_t szRefUrl[2084];           // 引用页
  wchar_t szCookies[4096];          // 浏览器cookie
  wchar_t szFilename[MAX_PATH];     // 下载保存文件名.
  wchar_t szReserved0[MAX_PATH];
  wchar_t szSavePath[MAX_PATH];     // 文件保存目录
  HWND  hReserved;
  BOOL bReserved;
  wchar_t szReserved1[64];
  wchar_t szReserved2[64];
  BOOL IsOnlyOriginal;            // 是否只从原始地址下载
  UINT nReserved1;
  BOOL DisableAutoRename;         // 禁止智能命名
  BOOL IsResume;                  // 是否用续传
  DWORD reserved[2048];
  tagDownTaskParam() {
   memset(this, 0, sizeof(*this));
   nReserved1 = 5;
   bReserved = FALSE;
   DisableAutoRename = FALSE;
   IsOnlyOriginal = FALSE;
   IsResume = TRUE;
  }
 }DownTaskParam;

 enum class DOWN_TASK_STATUS {
  NOITEM = 0,
  TSC_ERROR,
  TSC_PAUSE,
  TSC_DOWNLOAD,
  TSC_COMPLETE,
  TSC_STARTPENDING,
  TSC_STOPPENDING
 };
 enum class TASK_ERROR_TYPE {
  TASK_ERROR_UNKNOWN = 0x00,   // 未知错误
  TASK_ERROR_DISK_CREATE = 0x01,   // 创建文件失败
  TASK_ERROR_DISK_WRITE = 0x02,   // 写文件失败
  TASK_ERROR_DISK_READ = 0x03,   // 读文件失败
  TASK_ERROR_DISK_RENAME = 0x04,   // 重命名失败
  TASK_ERROR_DISK_PIECEHASH = 0x05,   // 文件片校验失败
  TASK_ERROR_DISK_FILEHASH = 0x06,   // 文件全文校验失败
  TASK_ERROR_DISK_DELETE = 0x07,   // 删除文件失败失败
  TASK_ERROR_DOWN_INVALID = 0x10,   // 无效的DOWN地址
  TASK_ERROR_PROXY_AUTH_TYPE_UNKOWN = 0x20,   // 代理类型未知
  TASK_ERROR_PROXY_AUTH_TYPE_FAILED = 0x21,   // 代理认证失败
  TASK_ERROR_HTTPMGR_NOT_IP = 0x30,   // http下载中无ip可用
  TASK_ERROR_TIMEOUT = 0x40,   // 任务超时
  TASK_ERROR_CANCEL = 0x41,   // 任务取消
  TASK_ERROR_TP_CRASHED = 0x42,   // MINITP崩溃
  TASK_ERROR_ID_INVALID = 0x43,   // TaskId 非法
 };
 typedef struct tagDownTaskInfo {
  DOWN_TASK_STATUS	stat;
  TASK_ERROR_TYPE		fail_code;
  wchar_t		szFilename[MAX_PATH];
  wchar_t		szReserved0[MAX_PATH];
  __int64     nTotalSize;         // 该任务总大小(字节)
  __int64     nTotalDownload;     // 下载有效字节数(可能存在回退的情况)
  float		fPercent;           // 下载进度
  int			nReserved0;
  int			nSrcTotal;          // 总资源数
  int			nSrcUsing;          // 可用资源数
  int			nReserved1;
  int			nReserved2;
  int			nReserved3;
  int			nReserved4;
  __int64     nReserved5;
  __int64		nDonationP2P;       // p2p贡献字节数
  __int64		nReserved6;
  __int64		nDonationOrgin;		// 原始资源共享字节数
  __int64		nDonationP2S;		// 镜像资源共享字节数
  __int64		nReserved7;
  __int64     nReserved8;
  int			nSpeed;             // 即时速度(字节/秒)
  int			nSpeedP2S;          // 即时速度(字节/秒)
  int			nSpeedP2P;          // 即时速度(字节/秒)
  bool		bIsOriginUsable;    // 原始资源是否有效
  float		fHashPercent;       // 现不提供该值
  int			IsCreatingFile;     // 是否正在创建文件
  DWORD		reserved[64];
  tagDownTaskInfo() {
   memset(this, 0, sizeof(DownTaskInfo));
   stat = DOWN_TASK_STATUS::TSC_PAUSE;
   fail_code = TASK_ERROR_TYPE::TASK_ERROR_UNKNOWN;
   fPercent = 0;
   bIsOriginUsable = false;
   fHashPercent = 0;
  }
 }DownTaskInfo;
 enum class DOWN_PROXY_TYPE {
  PROXY_TYPE_IE = 0,
  PROXY_TYPE_HTTP = 1,
  PROXY_TYPE_SOCK4 = 2,
  PROXY_TYPE_SOCK5 = 3,
  PROXY_TYPE_FTP = 4,
  PROXY_TYPE_UNKOWN = 255,
 };
 enum class DOWN_PROXY_AUTH_TYPE {
  PROXY_AUTH_NONE = 0,
  PROXY_AUTH_AUTO,
  PROXY_AUTH_BASE64,
  PROXY_AUTH_NTLM,
  PROXY_AUTH_DEGEST,
  PROXY_AUTH_UNKOWN,
 };
 typedef struct tagDOWN_PROXY_INFO {
  BOOL		bIEProxy;
  BOOL		bProxy;
  DOWN_PROXY_TYPE	stPType;
  DOWN_PROXY_AUTH_TYPE	stAType;
  wchar_t		szHost[2048];
  INT32		nPort;
  wchar_t		szUser[50];
  wchar_t		szPwd[50];
  wchar_t		szDomain[2048];
  tagDOWN_PROXY_INFO() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }DOWN_PROXY_INFO;
 //struct WSAPROTOCOL_INFOW;
 // BT任务相关数据结构
 typedef struct tagTrackerInfo {
  wchar_t szTrackerUrl[1024];
  tagTrackerInfo() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }TrackerInfo;
 typedef struct tagDownBTTaskParam {
  wchar_t szSeedFullPath[MAX_PATH];					//种子文件的全路径
  wchar_t szFilePath[MAX_PATH];						//文件保存目录
  DWORD dwNeedDownloadFileCount;						//指定要下载文件的个数
  DWORD* dwNeedDownloadFileIndexArray;				//要下载文件的在种子文件中的序号，从0开始计数
  DWORD dwTrackerInfoCount;							//下载使用的tracker服务器的个数
  TrackerInfo* pTrackerInfoArray;						//下载使用的tracker服务器的信息
  BOOL IsResume;										// 是否用续传
  tagDownBTTaskParam() {
   ::memset(this, 0x00, sizeof(*this));
  }
 }DownBTTaskParam;
 typedef struct tagBTTaskInfo {
  LONG lTaskStatus;				//任务状态, 0--正在运行,  10--暂停, 11--成功, 12--下载失败 
  DWORD dwUsingResCount;			//使用的资源数
  DWORD dwSumResCount;			//总资源数
  ULONGLONG ullRecvBytes;			//表示这个任务收到的字节数，这个值用来计算速度，不能用来计算进度
  ULONGLONG ullSendBytes;			//这个任务发送的字节
  BOOL bFileCreated;				//文件是否创建
  DWORD dwSeedCount;				//连接成功的种子peer个数
  DWORD dwConnectedBTPeerCount;	//连接成功的bt peer个数
  DWORD dwAllBTPeerCount;			//搜索到的总bt peer个数
  DWORD dwHealthyGrade;			//健康度，如健康度为987%时，healty_ grade的值为987
  tagBTTaskInfo() {
   ::memset(this, 0, sizeof(*this));
  }
 }BTTaskInfo;
 typedef struct tag_tracker_info {
  DWORD tracker_url_len;
  CHAR tracker_url[1024];		//tracker的url
  tag_tracker_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }tracker_info;
 typedef struct tag_bt_file_info {
  ULONGLONG file_size;				//文件大小
  DWORD path_len;
  CHAR file_path[256];				//文件相对路径
  DWORD name_len;
  CHAR file_name[1024];				//文件名称
  tag_bt_file_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_file_info;
 typedef struct tag_bt_seed_file_info {
  CHAR info_id[20];
  DWORD title_len;
  CHAR title[1024];					//标题
  DWORD file_info_count;				//种子文件中包含可下载文件的个数
  bt_file_info* file_info_array;		//指针指向bt_file_info结构的数组
  DWORD tracker_count;				//种子文件中包含的tracker服务器的个数
  tracker_info* tracker_info_array;	//指针指向tracker_info数组
  DWORD publisher_len;
  CHAR publisher[8192];				//发布者说明
  DWORD publisher_url_len;
  CHAR publisher_url[1024];			//发布者url
  tag_bt_seed_file_info() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_seed_file_info;
 typedef struct tag_bt_data_file_item {
  DWORD path_len;
  CHAR file_path[256];				//文件绝对路径
  DWORD name_len;
  CHAR file_name[1024];				//文件名称
  tag_bt_data_file_item() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_data_file_item;
 typedef struct tag_bt_data_file_list {
  DWORD item_count;
  bt_data_file_item* item_array;
  tag_bt_data_file_list() {
   ::memset(this, 0, sizeof(*this));
  }
 }bt_data_file_list;
#pragma pack(pop)
}///namespace xlapi_3_2_2_30

namespace pchacker {
 using TypeID = unsigned long long;
 using tf_api_object_init = void* (__stdcall*)(const void*, unsigned long);
 using tf_api_object_uninit = void(__stdcall*)(void);


 namespace protocol {

  enum class EnMessage : unsigned int {
   Begin = WM_USER + 0x2710 + 1,
   ProcessActivate = Begin + 0,
   ProcessQuit = Begin + 1,
   ThreadActivate = Begin + 2,
   ThreadQuit = Begin + 3,
   ExtractProgress = Begin + 4,
   ExtractReady = Begin + 5,
   ExtractSuccess = Begin + 6,
   ExtractFailed = Begin + 7,
   ExtractPerform = Begin + 8,
   ExtractBreak = Begin + 9,

   End = ExtractProgress,
   Total = 5,
  };

#pragma pack(push,1)
  /*@tagProtocolExtractInitData
  * When the decompression process is ready, send the data structure.
  * When the decompression process completes its task, send this data structure.
  * This structure data is sent when the decompression process terminates the task
  * abnormally or completes the task, normally sending the 'ExtractProgress' message ID
  */
  typedef struct tagExtractRouteData {
   unsigned long ExtractProcessId;
   unsigned long ExtractMessageThreadId;
   unsigned long long ExtractTargetDataTotalSize;
   unsigned long long ExtractFinishDataTotalSize;
   char ExtractPath[_MAX_PATH];
   char ExtractTargetDataPathname[_MAX_PATH];
   char ExtractFailedReason[256];

   tagExtractRouteData() { ::memset(this, 0x00, sizeof(*this)); }
   void operator=(const tagExtractRouteData& obj) { ::memcpy(this, &obj, sizeof(*this)); }
  }EXTRACTROUTEDATA, ExtractRouteData, * PEXTRACTROUTEDATA;
#pragma pack(pop)


 }///namespace protocol



#pragma pack(push,1)

 typedef struct tagDockingData {
  struct tagYXInstallData {//!@ 游戏游戏盒安装数据
   unsigned int VipLevel;
   wchar_t ResId[256];
   wchar_t ResName[512];
   wchar_t ResIcoUrl[2084];
   int ResStyle;
   int InternalType;
   int LocalType;

   tagYXInstallData() { ::memset(this, 0x00, sizeof(*this)); }
  };

  tagYXInstallData YXInstallData;
  xlapi_3_2_2_30::DownTaskParam* pXL_DownTaskParam;

  bool Verify() const {
   bool result = false;
   do {
    if (!pXL_DownTaskParam)
     break;
    if (pXL_DownTaskParam->szTaskUrl[0] == 0)
     break;
    result = true;
   } while (0);
   return result;
  }
  tagDockingData() { ::memset(this, 0x00, sizeof(*this)); }
 }DockingData, DOCKINGDATA, * PDOCKINGDATA;

#pragma pack(pop)


 typedef enum class EnUIType : unsigned long long {
  UnknownUI = 0x0000,
  DownManagerUI = 0x1000,
  SystemConfigureUI = 0x2000,
  DownManagerUI2 = 0x2001,
  StatusBarUI = 0x3000,
  MessageBoxUI = 0x4000,
  MainUI = 0x5000,

  Begin = UnknownUI,
  End = MainUI,
 }UIType;

 typedef enum class EnDownActionType : unsigned long long {
  Normal = 0x0000, // empty action is no handle.
  Pause = 0x0001,// 暂停任务
  Start = 0x0002,// 开始
  Stop = 0x0003,// 暂停或停止任务
  Remove = 0x0004,// 移除任务
  Append = 0x0005,// 添加任务
  Reset = 0x0006,// 任务重置
  Ready = 0x0007,// 任务已就绪
  Preparation = 0x0008,// 装备任务
  Waitinline = 0x0009,// 排队等待
  Runtime = 0x000A,// 任务运行时|运行中|正在工作
  Beworking = 0x000A,
  Running = 0x000A,

  Begin = Normal,
  End = Running,
 }DownActionType;

 typedef enum class EnTaskStatus : unsigned long long {
  Normal = 0x0000, // or Downloading .
  Success = 0x0001,
  Failed = 0x0002,
  Error = 0x0003,
  Pause = 0x0004,
  InPreparation = 0x0005,
 }TaskStatus;

 enum class EnDockingMessageType : unsigned long long {
  Undefined = 0x0000,
  LocalInstalled = 0x0001,
  TriggerDownload = 0x0002,
  TriggerStart = 0x0003,
 };

 enum class EnDockingResultType : unsigned long long {
  Success = 0x0000,
  Failed = 0x0001,
 };
 using tfDockingMessageCb = std::function<void(const EnDockingMessageType&, const EnDockingResultType&, const std::string&)>;


 class IDownTaskNode {
 public:
  virtual void ID(const TypeID&) = 0;
  virtual TypeID ID() const = 0;
  virtual void Url(const std::string&) = 0;
  virtual const std::string& Url() const = 0;
  virtual void Logo(const std::string&) = 0;
  virtual const std::string& Logo() const = 0;
  virtual EnTaskStatus Status() const = 0;
  virtual void Action(const DownActionType&) = 0;
  virtual bool Verify() const = 0;
  virtual const unsigned int& VipLevel() const = 0;
  virtual void VipLevel(const unsigned int&) = 0;
  virtual void LocalResDir(const std::string&) = 0;
  virtual const std::string& LocalResDir() const = 0;
  virtual void Name(const std::string&) = 0;
  virtual const std::string& Name() const = 0;
  virtual bool operator<<(const DockingData&) = 0;
 };

 class IConfigure {
 public:
  /// 开机自动启动
  virtual bool StartsAutomaticallyWhenStarts() const = 0;
  /// 启动时自动下载上次未完成的下载
  virtual bool LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup() const = 0;
  /// 下载完成后自动安装游戏
  virtual bool AutomaticallyInstalledAfterDownloading() const = 0;
  /// 打开后不显示推广广告
  virtual bool NoPromotionalAdsAreDisplayedWhenOpened() const = 0;
  /// 每次关闭时不再提醒我
  virtual bool NoMoreRemindersEverytimeItClosesInClickCloseBtn() const = 0;
  /// 最小化到系统托盘区
  virtual bool MinimizeToSystemTrayInClickCloseBtn() const = 0;
  /// 立即退出
  virtual bool ExitImmediatelyInClickCloseBtn() const = 0;
  /// 安装包存储路径
  virtual const std::string& PathForStoringTheInstallationPackage() const = 0;
  /// 安装路径
  virtual const std::string& ProgramInstallationPath() const = 0;
  /// 不限制下载速度
  virtual bool NolimitOnDownloadSpeed() const = 0;
  /// 下载速度阀值
  virtual const unsigned int& DownloadSpeedThreshold() const = 0;
  /// 自动下载安装包至默认路径
  virtual bool InstallationPackageAutomaticallyDownloadedToDefaultPath() const = 0;
  /// 安装包保留天数
  virtual const unsigned int& TheInstallationPackageIsReservedDays() const = 0;
  /// 下载完成后关机
  virtual bool ShutDownAfterDownloading() const = 0;
  /// 关闭延迟分钟数
  virtual const unsigned int& DisableDelayInMinutes() const = 0;
 };

 class IPCHacker {
 public:
  /**
  * @brief 1
  * @param 2
  * @return 3
  */
  virtual bool Bit7zArchiveProcess() = 0;
  virtual bool ZipArchiveProcess() = 0;
























 public:
  virtual void ParentHwndSet(const UIType&, const HWND&) = 0;
  virtual void* UIGetHwnd(const UIType&) const = 0;
  virtual HWND UICreate(const UIType&, const bool& show) = 0;
  virtual void UIShow(const UIType&, const bool& show) = 0;
  virtual bool UIShowIs(const UIType&) const = 0;
  virtual void UIRefresh() const = 0;
  virtual void UIPositionSet(const UIType&, const ::tagPOINT&, const ::tagSIZE&) = 0;
  //!@ 状态栏的进度条显示控制
  virtual void UIShowStatusbarProgressCtrl(const bool&) = 0;
  virtual IDownTaskNode* DownTaskCreate() = 0;
  virtual bool DownTaskAction(const TypeID&, const DownActionType&) = 0;
  virtual bool DownTaskDestory(IDownTaskNode*) = 0;
  virtual bool DownTaskPerform(IDownTaskNode*) = 0;
  virtual const std::wstring& SystemDirectoryW() const = 0;
  virtual const std::string& SystemDirectoryA() const = 0;
  virtual const std::wstring& CurrentUserDirectoryW() const = 0;
  virtual const std::string& CurrentUserDirectoryA() const = 0;
  virtual const IConfigure* SystemConfigureGet() const = 0;
  virtual bool OnDockingFormDockingData(DockingData*) = 0;
  virtual bool OnDockingFormHost(const std::wstring& json_data, const tfDockingMessageCb&) = 0;

  //!@ OpenResourceCreateDaemonNode
  //!@ 1. Create a desktop shortcut icon (*customization)
  //!@ 2. Create resource(*executable file) process.
  //!@ 3. Join the Resource service daemon package
  virtual bool OpenResourceCreateDaemonNode(const std::string&) = 0;
 protected:
  void* hModule = nullptr;
  tf_api_object_init api_object_init = nullptr;
  tf_api_object_uninit api_object_uninit = nullptr;
  //-------------------------------------------------------------------------------------------------------
 protected:
  inline IPCHacker();
  inline ~IPCHacker();
 public:
  inline static IPCHacker* CreateInterface(
   const char* pchacher_pe_pathname, const void* route, unsigned long nroute);
  inline static void DestoryInterface(IPCHacker*& pchacher_obj);
 };

 //////////////////////////////////////////////////////////////////////////////////////////
 inline IPCHacker::IPCHacker() {}
 inline IPCHacker::~IPCHacker() {}
 inline void IPCHacker::DestoryInterface(IPCHacker*& instance) {
  do {
   if (!instance)
    break;
   if (!instance->hModule || !instance->api_object_uninit)
    break;
   HMODULE freeMod = reinterpret_cast<HMODULE>(instance->hModule);
   instance->api_object_uninit();
   instance = nullptr;
   ::FreeLibrary(freeMod);
   freeMod = nullptr;
  } while (0);
 }
 inline IPCHacker* IPCHacker::CreateInterface(const char* module_pathname, const void* param = nullptr, unsigned long size_param = 0) {
  IPCHacker* result = nullptr;
  HMODULE hModule = nullptr;
  do {
   if (!module_pathname)
    break;
   hModule = ::LoadLibraryA(module_pathname);
   if (!hModule)
    break;
   auto api_object_init = reinterpret_cast<tf_api_object_init>(::GetProcAddress(hModule, "api_object_init"));
   auto api_object_uninit = reinterpret_cast<tf_api_object_uninit>(::GetProcAddress(hModule, "api_object_uninit"));
   if (!api_object_init || !api_object_uninit)
    break;
   result = reinterpret_cast<decltype(result)>(api_object_init(param, size_param));
   if (!result)
    break;
   result->hModule = hModule;
   result->api_object_init = api_object_init;
   result->api_object_uninit = api_object_uninit;
  } while (0);
  if (nullptr == result && hModule != nullptr) {
   ::FreeLibrary(hModule);
   hModule = nullptr;
  }
  return result;
 }


}///namespace pchacker

/// /*新生®（上海）**/
/// /*2022_10_01T04:07:40.6988834Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___E0CDC3C1_8FD7_4C35_8638_D30703A362DE__HEAD__


