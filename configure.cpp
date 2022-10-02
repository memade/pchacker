#include "stdafx.h"

namespace local {

 Configure::Configure(const std::string& config_file) : m_ConfigureFilePathname(config_file) {
  Init();
 }

 Configure::~Configure() {
  UnInit();
 }
 void Configure::Finish() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
#if 0
  if (!m_ConfigureDataCache.empty())
   shared::Win::File::Write(m_ConfigureFilePathname, m_ConfigureDataCache);
#endif
 }
 void Configure::operator>>(std::string& output) const {
#if 0
  output.clear();
  do {
   rapidjson::Document doc{ rapidjson::Type::kObjectType };
   doc.AddMember(
    rapidjson::Value().SetString("StartupPowerOn", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_StartupPowerOn).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("AutoInstalledAfterDownload", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_AutoInstalledAfterDownload).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("HideAdsAfterOpened", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_HideAdsAfterOpened).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("OnCloseBtnToExit", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_OnCloseBtnToExit).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("OnCloseBtnToTaskbar", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_OnCloseBtnToTaskbar).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("ShutdownAfterDownload", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_ShutdownAfterDownload).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("DownloadSpeedLimit", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(m_DownloadSpeedLimit).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("DownloadSpeedThresholdValue", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint(m_DownloadSpeedThresholdValue).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("DownloadConfigKeepDays", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint(m_DownloadConfigKeepDays).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("InstallpakSavePath", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(m_InstallpakSavePath.c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator());
   doc.AddMember(
    rapidjson::Value().SetString("InstallBasePath", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(m_InstallBasePath.c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator());
   output = shared::Json::toString(doc);
  } while (0);
#endif
 }

 bool Configure::operator<<(const std::string& input) {
  bool result = false;
  do {
   if (input.empty())
    break;
#if 0
   rapidjson::Document doc;
   if (doc.Parse(input.data(), input.size()).HasParseError())
    break;
   if (doc.HasMember("StartupPowerOn") && doc["StartupPowerOn"].IsBool())
    m_StartupPowerOn = doc["StartupPowerOn"].GetBool();
   if (doc.HasMember("AutoInstalledAfterDownload") && doc["AutoInstalledAfterDownload"].IsBool())
    m_AutoInstalledAfterDownload = doc["AutoInstalledAfterDownload"].GetBool();
   if (doc.HasMember("HideAdsAfterOpened") && doc["HideAdsAfterOpened"].IsBool())
    m_HideAdsAfterOpened = doc["HideAdsAfterOpened"].GetBool();
   if (doc.HasMember("OnCloseBtnToExit") && doc["OnCloseBtnToExit"].IsBool())
    m_OnCloseBtnToExit = doc["OnCloseBtnToExit"].GetBool();
   if (doc.HasMember("m_OnCloseBtnToTaskbar") && doc["OnCloseBtnToTaskbar"].IsBool())
    m_OnCloseBtnToTaskbar = doc["OnCloseBtnToTaskbar"].GetBool();
   if (doc.HasMember("InstallpakSavePath") && doc["InstallpakSavePath"].IsString())
    m_InstallpakSavePath = doc["InstallpakSavePath"].GetString();
   if (doc.HasMember("InstallBasePath") && doc["InstallBasePath"].IsString())
    m_InstallBasePath = doc["InstallBasePath"].GetString();
   if (doc.HasMember("ShutdownAfterDownload") && doc["ShutdownAfterDownload"].IsBool())
    m_ShutdownAfterDownload = doc["ShutdownAfterDownload"].GetBool();
   if (doc.HasMember("DownloadSpeedLimit") && doc["DownloadSpeedLimit"].IsBool())
    m_DownloadSpeedLimit = doc["DownloadSpeedLimit"].GetBool();
   if (doc.HasMember("DownloadSpeedThresholdValue") && doc["DownloadSpeedThresholdValue"].IsNumber())
    m_DownloadSpeedThresholdValue = doc["DownloadSpeedThresholdValue"].GetUint();
   if (doc.HasMember("DownloadConfigKeepDays") && doc["DownloadConfigKeepDays"].IsNumber())
    m_DownloadConfigKeepDays = doc["DownloadConfigKeepDays"].GetUint();
#endif
   result = true;
  } while (0);
  return result;
 }
 void Configure::Init() {
  bool file_init_flag = false;

  m_PathForStoringTheInstallationPackage = Global::PCHacherGet()->SystemDirectoryA();

  m_ProgramInstallationPath = Global::PCHacherGet()->SystemDirectoryA();
#if 0
  m_InstallpakSavePath = "c:\\games\\";
  m_InstallBasePath = "c:\\games\\";

  do {
   if (m_ConfigureFilePathname.empty())
    break;
   if (!shared::Win::AccessA(m_ConfigureFilePathname)) {
    reset_config = true;
    break;
   }
   m_ConfigureDataCache = shared::Win::File::Read(m_ConfigureFilePathname);
   if (!(*this << m_ConfigureDataCache)) {
    reset_config = true;
    break;
   }

  } while (0);

  do {
   if (!reset_config)
    break;
   *this >> m_ConfigureDataCache;
   Finish();
  } while (0);

  do {

  } while (0);
#endif
 }
 void Configure::UnInit() {

 }



 bool Configure::StartsAutomaticallyWhenStarts() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_StartsAutomaticallyWhenStarts;
 }
 bool Configure::LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup;
 }
 bool Configure::AutomaticallyInstalledAfterDownloading() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_AutomaticallyInstalledAfterDownloading;
 }
 bool Configure::NoPromotionalAdsAreDisplayedWhenOpened() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NoPromotionalAdsAreDisplayedWhenOpened;
 }
 bool Configure::NoMoreRemindersEverytimeItClosesInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NoMoreRemindersEverytimeItClosesInClickCloseBtn;
 }
 bool Configure::MinimizeToSystemTrayInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MinimizeToSystemTrayInClickCloseBtn;
 }
 bool Configure::ExitImmediatelyInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ExitImmediatelyInClickCloseBtn;
 }
 const std::string& Configure::PathForStoringTheInstallationPackage() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_PathForStoringTheInstallationPackage;
 }
 const std::string& Configure::ProgramInstallationPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProgramInstallationPath;
 }
 bool Configure::NolimitOnDownloadSpeed() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NolimitOnDownloadSpeed;
 }
 const unsigned int& Configure::DownloadSpeedThreshold() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DownloadSpeedThreshold;
 }
 bool Configure::InstallationPackageAutomaticallyDownloadedToDefaultPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_InstallationPackageAutomaticallyDownloadedToDefaultPath;
 }
 const unsigned int& Configure::TheInstallationPackageIsReservedDays() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_TheInstallationPackageIsReservedDays;
 }
 bool Configure::ShutDownAfterDownloading() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ShutDownAfterDownloading;
 }
 const unsigned int& Configure::DisableDelayInMinutes() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DisableDelayInMinutes;
 }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 bool PCHacher::StartsAutomaticallyWhenStarts() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_StartsAutomaticallyWhenStarts;
 }
 bool PCHacher::LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_LastIncompleteDownloadIsDownloadedAutomaticallyAtStartup;
 }
 bool PCHacher::AutomaticallyInstalledAfterDownloading() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_AutomaticallyInstalledAfterDownloading;
 }
 bool PCHacher::NoPromotionalAdsAreDisplayedWhenOpened() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NoPromotionalAdsAreDisplayedWhenOpened;
 }
 bool PCHacher::NoMoreRemindersEverytimeItClosesInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NoMoreRemindersEverytimeItClosesInClickCloseBtn;
 }
 bool PCHacher::MinimizeToSystemTrayInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MinimizeToSystemTrayInClickCloseBtn;
 }
 bool PCHacher::ExitImmediatelyInClickCloseBtn() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ExitImmediatelyInClickCloseBtn;
 }
 const std::string& PCHacher::PathForStoringTheInstallationPackage() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_PathForStoringTheInstallationPackage;
 }
 const std::string& PCHacher::ProgramInstallationPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProgramInstallationPath;
 }
 bool PCHacher::NolimitOnDownloadSpeed() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_NolimitOnDownloadSpeed;
 }
 const unsigned int& PCHacher::DownloadSpeedThreshold() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DownloadSpeedThreshold;
 }
 bool PCHacher::InstallationPackageAutomaticallyDownloadedToDefaultPath() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_InstallationPackageAutomaticallyDownloadedToDefaultPath;
 }
 const unsigned int& PCHacher::TheInstallationPackageIsReservedDays() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_TheInstallationPackageIsReservedDays;
 }
 bool PCHacher::ShutDownAfterDownloading() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ShutDownAfterDownloading;
 }
 const unsigned int& PCHacher::DisableDelayInMinutes() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_DisableDelayInMinutes;
 }
}///namespace lcoal
