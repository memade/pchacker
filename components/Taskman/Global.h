#if !defined(INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__)
#define INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__

namespace local {
 class Global final {
 public:
  Global();
  ~Global();
 private:
  void Init();
  void UnInit();
 public:
  static pchacker::TypeID TaskId();
  static Core* CoreGet();
  static bool Ready();
  static void SystemExitFlag(const bool&);
  static bool SystemExitFlag();
  static std::string lib7zPathname();
  static libuvpp::IClient* ClientGet();
 private:
  bool m_Ready = false;
  Core* m_pCore = nullptr;
  pchacker::TypeID m_TaskId = 0;
  std::atomic_bool m_SystemExitFlag = false;
  libuvpp::ILibuv* m_pUvpp = nullptr;
  libuvpp::IClient* m_pClient = nullptr;
  std::string m_lib7zPathname;
 };


 extern Global* GlobalGet();
}///namespace local

/// /*新生®（上海）**/
/// /*2022_10_17T03:51:52.7028977Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__
