#if !defined(INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__)
#define INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__

namespace local {

 class Configure final : public IConfigure {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Configure(const std::string& configure_file);
  virtual ~Configure();
 private:
  void Init();
  void UnInit();
  void operator>>(std::string&) const;
  bool operator<<(const std::string&);
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
 public:
  void Finish();
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
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_16T03:07:55.0643444Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__

