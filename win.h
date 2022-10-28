#if !defined(INC_H___CC04FAD7_7E0D_4D9A_B4F2_1EE447EA95E9__HEAD__)
#define INC_H___CC04FAD7_7E0D_4D9A_B4F2_1EE447EA95E9__HEAD__

namespace local {

 class Win final : public IWin {
  /*std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();*/
 public:
  Win();
  ~Win();
 protected:
  bool IsX64(const std::string&) const override final;
  bool IsPEDLL(const std::string&) const override final;
  bool IsPEEXE(const std::string&) const override final;
  bool CreateDirectoryA(const std::string&) const override final;
  void GetModulePathnameA(const tf_api_result_std_string_cb&, const HINSTANCE& hModule = nullptr) const override final;
  void GetModulePathA(const tf_api_result_std_string_cb&, const HINSTANCE& hModule = nullptr) const override final;
  void GetNameByPathnameA(const tf_api_result_std_string_cb&, const std::string& pathname) const override final;
  void GetPathByPathnameA(const tf_api_result_std_string_cb&, const std::string& pathname) const override final;
  void PathFixedA(const tf_api_result_std_string_cb&, const std::string& PathOrPathname) const override final;
  void GetSpecialFolderLocationA(const tf_api_result_std_string_cb&, const int& csidl) const override final;

  void RealtimeSpeed(const tf_api_result_std_string_cb&, const long long& speed_bype_size, const bool& divide = true) const override final;
  void TimePeriodUnMade(const tf_api_result_std_string_cb&, const UINT& TimePeriod) const override final;
  void ReadFile(const tf_api_result_std_string_cb&, const std::string& FilePathname, const int& OpenMode = std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary) const override final;
  bool WriteFile(const std::string& FilePathname, const std::string& WriteData, const int& OpenMode = std::ios::binary | std::ios::out | std::ios::trunc) const override final;
  bool AccessA(const std::string&) const override final;
  bool GetFileNameAndFormat(const std::string& pathname, std::string& out_name, std::string& out_format) const override final;
  void ReadAssignSize(const tf_api_result_std_string_cb&, const std::string& FilePathname, const size_t& assign_size, const int& OpenMode = std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary) const override final;

  bool ProcessCreateA(const std::string& exePathname,
   const std::string& commandline,
   const std::function<void(const HANDLE&, const DWORD&)> create_process_cb,
   const bool& Inheriting_parent_process = false,
   const bool& isShow = false,
   const DWORD& wait_time = 0) const override final;

  void ParseCommandLineParameters(const std::string& commandline, const std::function<void(const std::map<std::string, std::string>&)>&) const override final;

  void FindFileAssignPath(
   const std::string& path,
   const std::vector<std::string>& ffname_s,
   tfEnumFolderNode& found_s) const override final;

  void FindFileAssignPathOnce(
   const std::string& path,
   const std::vector<std::string>& ffname_s,
   tfEnumFolderNode& found_s) const override final;

  void EnumFolder(const std::string& Path,
   tfEnumFolderNode& Folders,
   tfEnumFolderNode& Files,
   const char* FileFilter = "*.*",
   bool bSleepDirect = false,
   const tfEnumFolderCb& enumcb = nullptr) const override final;
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_10_24T01:03:44.6365900Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___CC04FAD7_7E0D_4D9A_B4F2_1EE447EA95E9__HEAD__


