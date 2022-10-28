#include "stdafx.h"

namespace pchacker {
 namespace libuvpp {

  class Libuv final : public ILibuv {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Libuv();
   virtual ~Libuv();
  protected:
   IServer* CreateServer() override final;
   IClient* CreateClient() override final;
  public:
   void Release() const override final;
  private:
   Server* m_pServer = nullptr;
   shared::container::map<TypeIdentify, Client*> m_ClientQ;
  public:
   static bool ParseIPAddr(const std::string&, std::string&, std::uint16_t&);
  };

 }///namespace libuvpp
}