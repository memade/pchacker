#if !defined(INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__)
#define INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__

namespace local {
 class Global final {
  using tf_api_object_init = void* (__stdcall*)(const void*, unsigned long);
  using tf_api_object_uninit = void(__stdcall*)(void);
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
  static pchacker::libuvpp::IClient* ClientGet();
  static std::string IPAddr();
 private:
  bool m_Ready = false;
  Core* m_pCore = nullptr;
  pchacker::TypeID m_TaskId = 0;
  std::atomic_bool m_SystemExitFlag = false;
  pchacker::libuvpp::IClient* m_pClient = nullptr;
  pchacker::IPCHacker* m_pPCHacker = nullptr;
  std::string m_lib7zPathname;

  std::string m_IPAddr;

  shared::Win::PE::HMEMORYMODULE m_hPELoad = nullptr;
  tf_api_object_init m_peload_api_object_init = nullptr;
  tf_api_object_uninit m_peload_api_object_uninit = nullptr;
 };


 extern Global* GlobalGet();
}///namespace local

/// /*新生®（上海）**/
/// /*2022_10_17T03:51:52.7028977Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___B53A216B_52BF_4909_AA81_02ADA577B1AA__HEAD__
