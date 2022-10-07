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
  void SetDownDownTimeRemain(const size_t& size_remain, const size_t& current_down_speed_value = NormalUserLimitDownSpeedValue,const DWORD& color = 0);
  void StartingSwitch(const bool&);
 };

 class TaskNode final : public ITaskNode {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  TaskNode();
  TaskNode(const std::string& json_data);
  virtual ~TaskNode();
 public:
  void ID(const TypeID&) override final;
  TypeID ID() const override final;
  void Url(const std::string&) override final;
  const std::string& Url() const override final;
  void Logo(const std::string&) override final;
  const std::string& Logo() const override final;
  EnTaskStatus Status() const override final;
  void Action(const DownActionType&) override final;
  bool Verify() const override final;
  const unsigned int& VipLevel() const override final;
  void VipLevel(const unsigned int&) override final;
  void LocalResDir(const std::string&) override final;
  const std::string& LocalResDir() const override final;
  void Name(const std::string&) override final;
  const std::string& Name() const override final;
  bool operator<<(const DockingData&) override final;
 public:
  void Status(const EnTaskStatus&);
 protected:
  ///!@ 本地资源目录
  std::string m_LocalResDir;
  std::string m_Name;
  std::string m_LogoUrl;
  std::string m_Cmd;
  std::string m_Account = "test_account_123456789";
  unsigned int m_ResType = 0;
  time_t m_ResTime = 0;
  TypeID m_ID = 0;
  unsigned int m_VipLevel = 0;
  std::string m_Url;
  std::string m_LogoPathname;
  std::string m_FinishPathname;
  std::string m_DownCacheFilePathname;
  EnTaskStatus m_Status = EnTaskStatus::Normal;
  std::atomic<DownActionType> m_ActionType = DownActionType::Normal;
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
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_12T01:54:44.1160141Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___1A6471C5_4138_4ACA_86CE_EA737976F331__HEAD__
