#if !defined(INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__)
#define INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__

namespace local {

 class Configure final : public IConfigure {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Configure();
  virtual ~Configure();
 private:
  void Init();
  void UnInit();
 public:
  void ProjectCurrentPath(const std::string&) override final;
  const std::string& ProjectCurrentPath() const override final;
  bool DownResourceCachePath(const std::string&) override final;
  const std::string& DownResourceCachePath() const override final;
  bool FinishInstalledPath(const std::string&) override final;
  const std::string& FinishInstalledPath() const override final;
  bool DownPreparedResourcePath(const std::string&) override final;
  const std::string& DownPreparedResourcePath() const override final;
  bool ProjectLoggerRecorderPath(const std::string&) override final;
  const std::string& ProjectLoggerRecorderPath() const override final;
  bool ProjectLoggerRecorderModuleName(const std::string&) override final;
  const std::string& ProjectLoggerRecorderModuleName() const override final;
  void LocalServiceTcpAddr(const std::string&) override final;
  const std::string& LocalServiceTcpAddr() const override final;
  void DefaultDownloadCacheFileFormat(const std::string&) override final;
  const std::string& DefaultDownloadCacheFileFormat() const override final;
  void EnableLibuvppServer(const bool&) override final;
  const bool& EnableLibuvppServer() const override final;
  void EnableLibcurlpp(const bool&) override final;
  const bool& EnableLibcurlpp() const override final;
 public:
  void operator<<(const Configure*);
 private:
  bool m_EnableLibcurlpp = false;
  bool m_EnableLibuvppServer = false;
  std::string m_FinishInstalledPath;
  std::string m_DownResourceCachePath;
  std::string m_DownPreparedResourcePath;
  std::string m_ProjectLoggerRecorderPath;
  std::string m_ProjectLoggerRecorderModuleName;
  std::string m_LocalServiceTcpAddr;
  std::string m_DefaultDownloadCacheFileFormat;
  std::string m_ProjectCurrentPath;
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_09_16T03:07:55.0643444Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___23A9599C_F765_499B_92C0_68A11186B448__HEAD__

