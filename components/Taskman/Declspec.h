#if !defined(INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__)
#define INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__

namespace componects_taskman {

 static const char LIB7Z_DEPENDENCY_IDENTIFY[] = R"(7z.dll)";

 static const char MODULE_NAME[] = R"(Taskman)";

 enum class EnTaskType {
  Unknow = 0,
  Extractor = 1,
  Download = 2,
  Guard = 3,
 };

 enum class EnCmdType {
  HostPID = 0,
  HostTID = 1,
  OutPath = 2,
  InPathname = 3,
  HostPort = 4,
  TaskType = 5,
 };

 static const std::map<EnCmdType, std::string> mapCommandLineIdentify = {
  {EnCmdType::HostPID,R"(--host-pid)"},
  {EnCmdType::HostTID,R"(--host-tid)"},
  {EnCmdType::OutPath,R"(--out-path)"},
  {EnCmdType::InPathname,R"(--in-pathname)"},
  {EnCmdType::HostPort,R"(--host-port)"},
  {EnCmdType::HostPort,R"(--task-type)"},
 };

}///componects_taskman

/// /*新生®（上海）**/
/// /*2022_09_30T01:57:35.9702567Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___841C9D93_7238_4A94_A514_8721CFDD0E7D__HEAD__



