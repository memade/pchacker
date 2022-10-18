#include "stdafx.h"

namespace local {

 void PCHacker::ResponseResult() {
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
 }

 void PCHacker::Process() {
  do {
   m_TaskPool.iterate_clear(
    [&](const TypeID& task_id, TaskNode* pTask, bool& itbreak, bool& itclear) {
     if (pTask->Status() == EnActionType::DownRemove) {
      pTask->Release();
      itclear = true;
     }
     else {
      if (pTask->IsPost()) {
       auto view = pTask->Status();

       m_ResponseResultQ.push(pTask);

       LOGERROR("{:x} {}", reinterpret_cast<std::uint64_t>(pTask),std::uint64_t(view));
       auto sk = 0;
      }

     }
#if 0
     switch (pTaskNode->Status()) {
     case EnActionType::Normal: {
     }break;
     case EnActionType::DownAppend: {
      pTaskNode->Action(EnActionType::DownPreparation);
     }break;
     case EnActionType::DownPreparation: {
      if (pTaskNode->Status() == EnActionType::DownInPreparation)
       break;
      pTaskNode->Action(EnActionType::DownInPreparation);

      bool preparation_result = pTaskNode->Preparation();
      pTaskNode->Action(preparation_result ? EnActionType::DownReady : EnActionType::DownFailed);
      m_ResponseResultQ.push(pTaskNode);
      if (!preparation_result)
       pTaskNode->Action(EnActionType::DownRemove);
     }break;
     case EnActionType::DownReady: {
      pTaskNode->Action(EnActionType::DownStart);
     }break;
     case EnActionType::DownFinish: {
      m_ResponseResultQ.push(pTaskNode);

      //!@ 下载任务完成后
      //!@ 如果对接方没有指定安装流程那么该任务将从任务队列移除 
      if (pTaskNode->Status() != EnActionType::InstallAppend) {
       pTaskNode->Action(EnActionType::DownRemove);
      }
     }break;
     case EnActionType::DownRemove: {
      itclear = true;
      RemoveTasks.emplace_back(pTaskNode);
      LOGINFO("task({}) status({}) and remove by work queue.", pTaskNode->ID(), (std::uint64_t)pTaskNode->Status());
     }break;
     case EnActionType::DownStart: {
      if (pTaskNode->Status() == EnActionType::DownBeworking)
       break;
      pTaskNode->Action(EnActionType::DownBeworking);
      if (!pTaskNode->Perform())
       break;
     }break;
     case EnActionType::DownBeworking: {
      m_ResponseResultQ.push(pTaskNode);
     }break;
     case EnActionType::DownPause:
      [[fallthrough]];
     case EnActionType::DownStop: {
      if (EnStatusType::DownBeworking == pTaskNode->Status())
       break;
      pTaskNode->Action(EnStatusType::DownStopd);
     }break;
     case EnActionType::DownStopd: {
      pTaskNode->Action(EnActionType::DownRemove);
     }break;

     case EnActionType::InstallAppend: {


      auto sk = 0;
     }break;
     case EnActionType::InstallPreparation: {


      auto sk = 0;
     }break;
     case EnActionType::InstallInPreparation: {

      auto sk = 0;
     }break;
     case EnActionType::InstallReady: {

      auto sk = 0;
     }break;

     case EnActionType::InstallStop: {

      auto sk = 0;
     }break;
     case EnActionType::InstallStoping: {

      auto sk = 0;
     }break;
     case EnActionType::InstallStopd: {

      auto sk = 0;
     }break;

     case EnActionType::InstallStart: {

      auto sk = 0;
     }break;
     case EnActionType::InstallBeworking: {

      auto sk = 0;
     }break;

     case EnActionType::InstallFinish: {

      auto sk = 0;
      }break;

     default:
      break;
     }
#endif


     std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });

   if (!m_IsOpen.load()) {
    if (m_TaskPool.empty())
     break;
    else {
     m_TaskPool.iterate(
      [&](const auto&, TaskNode* pTaskNode, auto&) {
       const auto current_status = pTaskNode->Status();
       if (current_status != EnActionType::DownStop && current_status != EnActionType::DownRemove && current_status != EnActionType::DownStopd)
        pTaskNode->Action(EnActionType::DownStop);
      });
    }
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
 }


}///namespace lcoal
