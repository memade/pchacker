#include "stdafx.h"

std::atomic_bool system_exit_flag = true;
std::atomic_bool extract_execute_result = false;
shared::container::queue<std::string> ExtractNotifyWriteQ;
int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3869);
#endif
 
 do {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  if (local::Global::SystemExitFlag())
   break;
 } while (1);

 return 0;
}
