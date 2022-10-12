#include "stdafx.h"

namespace local {

 void PCHacker::Process() {
  /*Loading a Local Task*/

  std::vector<TaskNode*> RemoveTasks;
  do {
   m_TaskPool.iterate_clear(
    [&](const TypeID& task_id, TaskNode* pTaskNode, bool& itbreak, bool& itclear) {
     switch (pTaskNode->Status()) {
     case EnDownActionType::Normal: {

     }break;
     case EnDownActionType::Append: {
      pTaskNode->Action(EnDownActionType::Preparation);
     }break;
     case EnDownActionType::Preparation: {
      if (pTaskNode->Status() == EnActionType::InPreparation)
       break;
      pTaskNode->Action(EnActionType::InPreparation);
      do {
       if (!pTaskNode->Preparation())
        break;
       pTaskNode->Action(EnDownActionType::Ready);
       if (m_TaskResultStatusCb)
        m_TaskResultStatusCb(pTaskNode->TaskResultGet());
      } while (0);
     }break;
     case EnDownActionType::Ready: {
      pTaskNode->Action(EnDownActionType::Start);
     }break;
     case EnDownActionType::Pause: {



     }break;
     case EnDownActionType::Remove: {
      itclear = true;
      RemoveTasks.emplace_back(pTaskNode);
     }break;
     case EnDownActionType::Start: {
      if (pTaskNode->Status() == EnDownActionType::Beworking)
       break;
      pTaskNode->Action(EnDownActionType::Beworking);
      if (!pTaskNode->Perform())
       break;
     }break;
     case EnDownActionType::Beworking: {
      if (m_TaskResultStatusCb)
       m_TaskResultStatusCb(pTaskNode->TaskResultGet());
     }break;
     case EnDownActionType::Stop: {
      auto sk = 0;
     }break;
     case EnDownActionType::Waitinline: {
      auto sk = 0;
     }break;
     default:
      break;
     }

    });

   if (!m_IsOpen.load()) {


    break;
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
 }

}///namespace lcoal
