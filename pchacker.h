#if !defined(INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__)
#define INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__

namespace local {

 class PCHacker final : public IPCHacker, public IConfigure {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  PCHacker();
  virtual ~PCHacker();
 private:
  void Init();
  void UnInit();
 public:
  void ParentHwndSet(const UIType&, const HWND&) override final;
  void* UIGetHwnd(const UIType&) const override final;
  bool UIShowIs(const UIType&) const override final;
  void UIShow(const UIType&, const bool& show) override final;
  void UIShowStatusbarProgressCtrl(const bool&) override final;
  void UIRefresh() const override final;
  void UIPositionSet(const UIType&, const ::tagPOINT&, const ::tagSIZE&) override final;
  HWND UICreate(const UIType&, const bool& show) override final;
  IDownTaskNode* TaskCreate(const TypeID&) override final;
  bool TaskAction(const TypeID&, const EnActionType&) override final;
  bool TaskDestory(IDownTaskNode*) override final;
  bool TaskPerform(IDownTaskNode*) override final;
  const std::wstring& SystemDirectoryW() const override final;
  const std::string& SystemDirectoryA() const override final;
  const std::wstring& CurrentUserDirectoryW() const override final;
  const std::string& CurrentUserDirectoryA() const override final;
  const IConfigure* SystemConfigureGet() const override final;
  bool OnDockingFormDockingData(DockingData*) override final;
  bool OnDockingFormHost(const std::wstring& json_data, const tfDockingMessageCb&) override final;
 protected:
  bool OpenResourceCreateDaemonNode(const std::string&) override final;
  void RegisterTaskResultStatusCallback(const tfTaskResultStatusCb&) override final;
 public:
  HWND ParentHwnd(const UIType&) const;
  const std::wstring& UISkinDirectory() const;
 private:
  void Process();
  void ResponseResult();
 private:
  std::vector<std::thread> m_Threads;
  std::atomic_bool m_IsOpen = false;
  std::map<UIType, UIBase*> m_UIMap;
  std::wstring m_CurrentUserDirectoryW;
  std::string m_CurrentUserDirectoryA;
  std::wstring m_SystemDirectoryW;
  std::string m_SystemDirectoryA;
  std::wstring m_UISkinDirectory;
  shared::container::map<TypeID/*res(game) id*/, TaskNode*> m_TaskPool;
  shared::container::queue<std::shared_ptr<ITaskResultStatus>> m_ResultQ;
  shared::container::queue<ITaskNode*> m_ResponseResultQ;
 public:
  shared::container::map<TypeID, Taskman*> m_TaskmanPtrQ;
 protected:
  bool Bit7zArchiveProcess() override final;
  bool ZipArchiveProcess() override final;
 private:
  tfTaskResultStatusCb m_TaskResultStatusCb = nullptr;
 private:
  /// 安装包存储路径
  std::string m_PathForStoringTheInstallationPackage;
  /// 安装路径
  std::string m_ProgramInstallationPath;
  /// 配置映射文件路径名
  const std::string m_ConfigureFilePathname;
  /// 开机自动启动
  bool m_StartsAutomaticallyWhenStarts = false;
  /// 启动时自动下载上次未完成的下载
  bool m_LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup = false;
  /// 下载完成后自动安装游戏
  bool m_AutomaticallyInstalledAfterDownloading = false;
  /// 打开后不显示推广广告
  bool m_NoPromotionalAdsAreDisplayedWhenOpened = false;
  /// 每次关闭时不再提醒我
  bool m_NoMoreRemindersEverytimeItClosesInClickCloseBtn = false;
  /// 最小化到系统托盘区
  bool m_MinimizeToSystemTrayInClickCloseBtn = false;
  /// 立即退出
  bool m_ExitImmediatelyInClickCloseBtn = false;
  /// 不限制下载速度
  bool m_NolimitOnDownloadSpeed = false;
  /// 下载速度阀值
  unsigned int m_DownloadSpeedThreshold = 4096 * 1024;
  /// 自动下载安装包至默认路径
  bool m_InstallationPackageAutomaticallyDownloadedToDefaultPath = false;
  /// 安装包保留天数
  unsigned int m_TheInstallationPackageIsReservedDays = 0;
  /// 下载完成后关机
  bool m_ShutDownAfterDownloading = false;
  /// 关闭延迟分钟数
  unsigned int m_DisableDelayInMinutes = 240;
 public:
  bool StartsAutomaticallyWhenStarts() const override final;
  bool LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup() const override final;
  bool AutomaticallyInstalledAfterDownloading() const override final;
  bool NoPromotionalAdsAreDisplayedWhenOpened() const override final;
  bool NoMoreRemindersEverytimeItClosesInClickCloseBtn() const override final;
  bool MinimizeToSystemTrayInClickCloseBtn() const override final;
  bool ExitImmediatelyInClickCloseBtn() const override final;
  const std::string& PathForStoringTheInstallationPackage() const override final;
  const std::string& ProgramInstallationPath() const override final;
  bool NolimitOnDownloadSpeed() const override final;
  const unsigned int& DownloadSpeedThreshold() const override final;
  bool InstallationPackageAutomaticallyDownloadedToDefaultPath() const override final;
  const unsigned int& TheInstallationPackageIsReservedDays() const override final;
  bool ShutDownAfterDownloading() const override final;
  const unsigned int& DisableDelayInMinutes() const override final;
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_10T10:25:26.4661499Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___A18B6A9B_FF85_41C8_98A5_267B32FB8AAC__HEAD__