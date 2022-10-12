#if !defined(INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__)
#define INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__

namespace local {

 class IDownTaskElement : public CListContainerElementUI {
 public:
  static IDownTaskElement* Create();
 public:
  void StatusTextSet(const std::wstring&, const DWORD& color = 0);
  void ResourceSizeTextSet(const size_t& total, const size_t& current, const DWORD& color = 0);
  void DownTotalTimeTextSet(const std::wstring&, const DWORD& color = 0);
  void SetName(const std::wstring&, const DWORD& color = 0);
  void SetLogo(const std::wstring& logo_pathname);
  void SetProgressValue(const size_t& total, const size_t& current);
  void SetDownSpeedValue(const size_t&);
  void SetDownloadCompletionRate(const size_t& size_totoal, const size_t& size_current);
  void SetDownSpeedValueVip(const size_t& real_speed/*-200kb*/);
  void SetDownDownTimeRemain(const size_t& size_remain, const size_t& current_down_speed_value = NormalUserLimitDownSpeedValue, const DWORD& color = 0);
  void StartingSwitch(const bool&);
 };


 class ITaskCommonData {
 public:
  ITaskCommonData(const TypeID& id) : m_ID(id) {}
 protected:
  ///!@ 本地资源目录
  void* m_RoutePtr = nullptr;
  void* m_BindUI = nullptr;
  std::string m_DownPath;
  std::string m_DownPathname;
  std::string m_OpenCommandLine;
  std::string m_LocalResDir;
  std::string m_Name;
  std::string m_LogoUrl;
  std::string m_Cmd;
  std::string m_Account = "test_account_123456789";
  unsigned int m_ResType = 0;
  time_t m_ResTime = 0;
  const TypeID m_ID;
  unsigned int m_VipLevel = 0;
  std::string m_Url;
  std::string m_LogoPathname;
  std::string m_FinishPathname;
  std::string m_DownCacheFilePathname;
  size_t m_ContentLength = 0;
  std::atomic<EnTaskType> m_TaskType = EnTaskType::Unknow;
  std::atomic<DownActionType> m_ActionType = DownActionType::Normal;
  long long m_DownLimitSpeed = 5 * 1024 * 1024;
 };

 class TaskResult final : public ITaskResultStatus, public ITaskCommonData {
  friend class TaskNode;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  TaskResult(const TypeID& id, void* tasknodeptr) : ITaskCommonData(id), m_pTaskNodePtr(tasknodeptr) {}
 protected:
  const TypeID& TaskID() const override final;
  void* RoutePtr() const override final;
  const size_t& ContentLength() const override final;
  const std::string& Name() const override final;
  const std::string& LogoPathname() const override final;
  const unsigned int& VipLevel() const override final;
  EnActionType Status() const override final;
  EnTaskType TaskType() const override final;
  void* TaskNodePtr() const override final;
  void* BindUI() const override final;
  const long long& DownLimitSpeed() const override final;

  const double& total() const override final;
  const double& current() const override final;
  const double& speed_s() const override final;
  const double& percentage() const override final;
  const long long& time_s() const override final;
 private:
  void* m_pTaskNodePtr = nullptr;

  /// IProgressInfo
  double m_total = 0;
  double m_current = 0;
  double m_speed_s = 0;
  long long m_time_s = 0;
  double m_percentage = 0;
  /// IResponse

 private:
  void operator<<(const libcurlpp::IProgressInfo*);
  void operator<<(const libcurlpp::IResponse*);
 };
 class TaskNode final : public ITaskNode, public ITaskCommonData {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  TaskNode(const TypeID&);
  TaskNode(const TypeID&, const std::string& json_data);
  virtual ~TaskNode();
 public:
  const TypeID& ID() const override final;
  void Url(const std::string&) override final;
  const std::string& Url() const override final;
  void LogoUrl(const std::string&) override final;
  void LogoPathname(const std::string&) override final;
  EnActionType Status() const override final;
  void Action(const DownActionType&) override final;
  bool Verify() const override final;
  const unsigned int& VipLevel() const override final;
  void VipLevel(const unsigned int&) override final;
  void LocalResDir(const std::string&) override final;
  const std::string& LocalResDir() const override final;
  void Name(const std::string&) override final;
  void DownPath(const std::string&) override final;
  void DownPathname(const std::string&) override final;
  void OpenCommandLine(const std::string&) override final;
  bool operator<<(const DockingData&) override final;
  void RoutePtr(void*) override final;
  void BindUI(void*) override final;
  void DownLimitSpeed(const long long&/*b*/) override final;
 public:
  TaskResult* TaskResultGet() const;
  void TaskType(const EnTaskType&);
 protected:
  libcurlpp::IRequest* m_pHeadRequest = nullptr;
  libcurlpp::IRequest* m_pDownRequest = nullptr;
  libcurlpp::IRequest* m_pReadyRequest = nullptr;
  TaskResult* m_pTaskResult = nullptr;
 public:
  bool Preparation();
  bool Perform();

#if 0
 public:
  IDownTaskElement* UIDownTaskElementCreate();
  IDownTaskElement* UIDownTaskElementGet() const;
  DownActionType Action() const;
  /// @Preparation()
  /// 1.请求资源头部信息 获取资源数据情况
  /// 2.请求Logo相关资源
  /// 3.本类初始化工作
  bool Preparation();
  bool Start();
  bool Stop();
  bool Pause();
  void SetStatusText(const std::wstring&, const DWORD& color = CommonColorMap.at(CommonColorType::White));
  void SetResourceSizeText(const size_t& total, const size_t& current, const DWORD& color = CommonColorMap.at(CommonColorType::White));
 private:
  IDownTaskElement* m_pUIDownTaskElement = nullptr;
 private:
  std::atomic_bool m_IsOpenThread = false;
  __int64 m_ResourceTotalSize = 0;
  shared::container::queue<ProgressRoute> m_ProgressRouteQ;
  void OnProgressChanged();
  std::vector<std::thread> m_Threads;
#endif
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_12T01:54:44.1160141Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__
