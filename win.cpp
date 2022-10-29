#include "stdafx.h"

namespace local {

 Win::Win() {

 }

 Win::~Win() {

 }

 bool Win::IsX64(const std::string& pebuffer) const {
  return shared::Win::PE::IsX64(pebuffer);
 }
 bool Win::IsPEDLL(const std::string& pebuffer) const {
  return shared::Win::PE::IsDLL(pebuffer);
 }
 bool Win::IsPEEXE(const std::string& pebuffer) const {
  return shared::Win::PE::IsEXE(pebuffer);
 }
 void Win::FindFileAssignPath(
  const std::string& path,
  const std::vector<std::string>& ffname_s,
  tfEnumFolderNode& found_s) const {
  return shared::Win::FindFileAssignPath(path, ffname_s, found_s);
 }

 void Win::FindFileAssignPathOnce(
  const std::string& path,
  const std::vector<std::string>& ffname_s,
  tfEnumFolderNode& found_s) const {
  return shared::Win::FindFileAssignPathOnce(path, ffname_s, found_s);
 }

 void Win::EnumFolder(const std::string& Path,
  tfEnumFolderNode& Folders,
  tfEnumFolderNode& Files,
  const char* FileFilter /*= "*.*"*/,
  bool bSleepDirect /*= false*/,
  const tfEnumFolderCb& enumcb /*= nullptr*/) const {
  return shared::Win::EnumFolder(Path, Folders, Files, FileFilter, bSleepDirect, enumcb);
 }

 void Win::ParseCommandLineParameters(const std::string& commandline, const std::function<void(const std::map<std::string, std::string>&)>& out_cb) const {
  std::map<std::string, std::string> outs;
  shared::Win::ParseCommandLineParameters(commandline, outs);
  if (out_cb)
   out_cb(outs);
 }
 bool Win::ProcessCreateA(const std::string& exePathname,
  const std::string& commandline,
  const std::function<void(const HANDLE&, const DWORD&)> create_process_cb,
  const bool& Inheriting_parent_process /*= false*/,
  const bool& isShow /*= false*/,
  const DWORD& wait_time /*= 0*/) const {
  return shared::Win::Process::CreateA(exePathname, commandline, create_process_cb, Inheriting_parent_process, isShow, wait_time);
 }
 bool Win::CreateDirectoryA(const std::string& path) const {
  return shared::Win::CreateDirectoryA(path);
 }
 void Win::GetSpecialFolderLocationA(const  tf_api_result_std_string_cb& rescb, const int& csidl) const {
  const std::string res = shared::Win::GetSpecialFolderLocationA(csidl);
  rescb(res);
 }
 void Win::GetModulePathnameA(const  tf_api_result_std_string_cb& rescb, const HINSTANCE& hModule /*= nullptr*/) const {
  const std::string res = shared::Win::GetModulePathnameA(hModule);
  rescb(res);
 }
 void Win::GetModulePathA(const  tf_api_result_std_string_cb& rescb, const HINSTANCE& hModule /*= nullptr*/) const {
  const auto res = shared::Win::GetModulePathA(hModule);
  rescb(res);
 }
 void Win::RealtimeSpeed(const  tf_api_result_std_string_cb& rescb, const long long& speed_bype_size, const bool& divide /*= true*/) const {
  const auto res = shared::Win::RealtimeSpeed(speed_bype_size, divide);
  rescb(res);
 }
 void Win::TimePeriodUnMade(const  tf_api_result_std_string_cb& rescb, const UINT& TimePeriod) const {
  const auto res = shared::Win::Time::TimePeriodUnMade(TimePeriod);
  rescb(res);
 }
 bool Win::AccessA(const std::string& path) const {
  return shared::Win::AccessA(path);
 }
 bool Win::GetFileNameAndFormat(const std::string& pathname, std::string& out_name, std::string& out_format) const {
  return shared::Win::GetFileNameAndFormat(pathname, out_name, out_format);
 }
 void Win::GetNameByPathnameA(const  tf_api_result_std_string_cb& rescb, const std::string& pathname) const {
  const auto res = shared::Win::GetNameByPathnameA(pathname);
  rescb(res);
 }
 void Win::GetPathByPathnameA(const  tf_api_result_std_string_cb& rescb, const std::string& pathname) const {
  const auto res = shared::Win::GetPathByPathnameA(pathname);
  rescb(res);
 }
 void Win::PathFixedA(const  tf_api_result_std_string_cb& rescb, const std::string& PathOrPathname) const {
  const auto res = shared::Win::PathFixedA(PathOrPathname);
  rescb(res);
 }

 void Win::ReadFile(const  tf_api_result_std_string_cb& rescb, const std::string& FilePathname, const int& OpenMode /*= std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/) const {
  const auto res = shared::Win::File::Read(FilePathname, OpenMode);
  rescb(res);
 }
 bool Win::WriteFile(const std::string& FilePathname, const std::string& WriteData, const int& OpenMode /*= std::ios::binary | std::ios::out | std::ios::trunc*/) const {
  return shared::Win::File::Write(FilePathname, WriteData, OpenMode);
 }
 void Win::ReadAssignSize(const  tf_api_result_std_string_cb& rescb, const std::string& FilePathname, const size_t& assign_size, const int& OpenMode /*= std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/) const {
  const auto res = shared::Win::File::ReadAssignSize(FilePathname, assign_size, OpenMode);
  rescb(res);
 }
}///namespace lcoal
