#include "stdafx.h"

namespace local {

 void PCHacker::Process() {
  auto pResultStatusCallbackThread = new std::thread(
   [&]() {

    do {
     do {
      if (m_ResponseResultQ.empty())
       break;
      auto tasks = m_ResponseResultQ.pops();
      for (const auto& task : tasks) {
       if (m_TaskResultStatusCb)
        m_TaskResultStatusCb(task);
      }
     } while (0);
     if (!m_IsOpen.load())
      break;
     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    } while (1);

   });

  do {
   m_TaskPool.iterate_clear(
    [&](const TypeID& task_id, TaskNode* pTask, bool& itbreak, bool& itclear) {
     if (pTask->Status() == EnActionType::DownRemove) {
      itclear = true;
     }
     else {
      if (pTask->IsPost())
       m_ResponseResultQ.push(pTask);
     }
    });

   if (!m_IsOpen.load()) {
    //!@ 停止回调线程
    m_ResponseResultQ.clear();
    if (pResultStatusCallbackThread) {
     pResultStatusCallbackThread->join();
     SK_DELETE_PTR(pResultStatusCallbackThread);
    }

    //!@ 回调线程停止以后 才可以安装的清除任务队列
    m_TaskPool.iterate_clear(
     [&](const auto&, TaskNode* pTask, auto&, auto& itclear) {
      pTask->Release();
      itclear = true;
     });
    break;
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
 }


}///namespace lcoal
