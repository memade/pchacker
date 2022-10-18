#if !defined(INC_H___BA3AFCDF_4BA0_4A75_8F77_DDACFD343CA5__HEAD__)
#define INC_H___BA3AFCDF_4BA0_4A75_8F77_DDACFD343CA5__HEAD__

namespace local {

 class Core final {
 public:
  Core();
  ~Core();
 private:
  void Init();
  void UnInit();
 public:
  bool Open();
  void Close();
 private:
  std::vector<std::thread> m_Threads;
  std::atomic_bool m_IsOpen = false;
  void Process();
  void Extract(pchacker::PTASKMANMSG);
 };



}///namespace lcoal

/// /*新生®（上海）**/
/// /*2022_10_17T03:53:08.3517015Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___BA3AFCDF_4BA0_4A75_8F77_DDACFD343CA5__HEAD__