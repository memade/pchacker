#include "stdafx.h"

namespace pchacker {
 namespace libuvpp {

  class Libuv final : public ILibuv {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Libuv();
   virtual ~Libuv();
  private:
   void Init();
   void UnInit();
  public:
   IServer* CreateServer() override final;
   IClient* CreateClient() override final;
   void DestoryServer(IServer*&) override final;
  private:
   std::atomic_bool m_Ready = false;
   Server* m_pServer = nullptr;
   shared::container::map<TypeIdentify, Client*> m_ClientQ;
  public:
   static bool ParseIPAddr(const std::string&, std::string&, std::uint16_t&);
  };

 }///namespace libuvpp
}