#include "stdafx.h"

namespace local {
 UIBase::UIBase(const UIType& uitype, const bool& show) : m_Type(uitype) {
  m_Show.store(show);
  Init();
 }
 UIBase::~UIBase() {
  UnInit();
 }
 void UIBase::Init() {
 }
 void UIBase::UnInit() {
 }
 const HWND& UIBase::Hwnd() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_hWnd;
 }
 bool UIBase::IsOpen() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_IsOpen.load();
 }
 bool UIBase::Show() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Show.load();
 }
 void UIBase::Show(const bool& show) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Show.store(show);
 }
 const UIType& UIBase::Type() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Type;
 }
#if 0
 void UIBase::Open() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return;
 }
 void UIBase::Close() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpen.load())
    break;
   for (auto& it : m_Threads)
    it.join();
   m_Threads.clear();
   UIFrame::Close(IDOK);
   m_IsOpen.store(false);
  } while (0);
 }
#endif
 void UIBase::ParentSet(const HWND& parent) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_hWnd || !parent)
    break;
   auto Style = ::GetWindowLongW(m_hWnd, GWL_STYLE);
   if (!(Style & WS_CHILD)) {
    Style |= WS_CHILD;
    ::SetWindowLongW(m_hWnd, GWL_STYLE, Style);
   }
   ::SetParent(m_hWnd, parent);
   m_Parent = parent;
  } while (0);
 }
 void UIBase::OnShowMininized() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
 }
 bool UIBase::AppendDownTaskNode(TaskNode*) {
  return false;
 }
 bool UIBase::RemoveDownTaskNode(TaskNode*) {
  return false;
 }
 void UIBase::Refresh() const {
  return;
 }
 const HWND& UIBase::GetParent() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Parent;
 }
 void UIBase::SetPosition(const ::tagPOINT& inPoint, const ::tagSIZE& inSize) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  ::memcpy(&m_tagSize, &inSize, sizeof(::tagSIZE));
  ::memcpy(&m_tagPoint, &inPoint, sizeof(::tagPOINT));
 }
 unsigned int UIBase::UIListDownTaskCount() const {
  return 0;
 }
 bool UIBase::SwitchPage(const EnChildPageType&) {
  return false;
 }
 void UIBase::DownStatusTotalCount(const size_t&) {
  return;
 }
 size_t UIBase::DownStatusTotoalCount() const {
  return 0;
 }
 void UIBase::StatusbarProgressCtrl(const bool&) {
  return;
 }
}///namespace local
