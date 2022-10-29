#if !defined(INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__)
#define INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__

namespace componects_taskman {

 static const char STARUP_VERIFY[] = R"(3B0443FC_1E37_4CA9_9CA3_DBCA2A6D6AE0)";

 static const char LIB7Z_DEPENDENCY_IDENTIFY[] = R"(7z.dll)";

 static const char MODULE_NAME[] = R"(Taskman)";

 enum class EnTaskType {
  Unknow = 0,
  Extractor = 1,
  Download = 2,
  Guard = 3,
 };

 enum class EnCmdType {
  Verify = 0,
  TaskId = 1,
  IPAddr = 2,
 };

 static const std::map<EnCmdType, std::string> mapCommandLineIdentify = {
  {EnCmdType::Verify,R"(--verify)"},
  {EnCmdType::TaskId,R"(--taskid)"},
  {EnCmdType::IPAddr,R"(--ipaddr)"},
 };

}///componects_taskman

/// /*新生®（上海）**/
/// /*2022_09_30T01:57:35.9702567Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__



