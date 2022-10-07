#if !defined(INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__)
#define INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__

namespace local {

 enum class EnMainPageType : int {
  Downing = 0,
  Success = 1,
 };

 enum class EnChildPageType : int {
  Empty = 0,
  Normal = 1,
 };

 class UIBase {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  UIBase(const UIType&, const bool& init_show);
  ~UIBase();
 public:
  virtual void Create() = 0;
  virtual void Destory() = 0;
  virtual const HWND& Hwnd() const;
  virtual bool IsOpen() const;
  virtual const UIType& Type() const;
  virtual bool Show() const;
  virtual void Show(const bool&);
  virtual bool AppendDownTaskNode(TaskNode*);
  virtual bool RemoveDownTaskNode(TaskNode*);
  virtual unsigned int UIListDownTaskCount() const;
  virtual bool SwitchPage(const EnChildPageType&);
  virtual void DownStatusTotalCount(const size_t&);
  virtual size_t DownStatusTotoalCount() const;
  virtual void StatusbarProgressCtrl(const bool&);
  virtual void Refresh() const;
  virtual const HWND& GetParent() const;
  virtual void SetPosition(const ::tagPOINT&,const ::tagSIZE&);
 protected:
  virtual void Init();
  virtual void UnInit();
 protected:
  const UIType& m_Type;
  HWND m_hWnd = nullptr;
  HWND m_Parent = nullptr;
  std::atomic_bool m_IsOpen = false;
  std::vector<std::thread> m_Threads;
  std::atomic_bool m_Show = false;
  // position form ui.
  ::tagSIZE m_tagSize = { 0 };
  ::tagPOINT m_tagPoint = { 0 };
  HANDLE m_UIMainThread = nullptr;
 protected:
  virtual void OnShowMininized() const;
 public:
  virtual void ParentSet(const HWND&);
 };


}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_09T23:53:43.1131556Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___D185A4AC_40F5_4798_8E7D_F285AD5F40A9__HEAD__
