#include "stdafx.h"

namespace pchacker {
 namespace libuvpp {

  Libuv::Libuv() {

  }

  Libuv::~Libuv() {
   m_ClientQ.iterate_clear(
    [](const auto&, Client* pClient, auto&, auto& itclear) {
     pClient->Stop();
     pClient->Release();
     itclear = true;
    });
   if (m_pServer) {
    m_pServer->Stop();
    m_pServer->Release();
   }
  }
  void Libuv::Release() const {
   delete this;
  }
  IServer* Libuv::CreateServer() {
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   if (!m_pServer)
    m_pServer = new Server();
   return dynamic_cast<IServer*>(m_pServer);
  }

  IClient* Libuv::CreateClient() {
   std::lock_guard<std::mutex> lock{ *m_Mutex };
   IClient* pClient = new Client(shared::Win::Time::TimeStamp<std::chrono::microseconds>());
   m_ClientQ.push(pClient->Identify(), dynamic_cast<Client*>(pClient));
   return pClient;
  }

  bool Libuv::ParseIPAddr(const std::string& ipaddr, std::string& ip, std::uint16_t& port) {
   bool result = false;
   ip.clear();
   port = 0;
   do {
    if (ipaddr.empty())
     break;
    std::vector<std::string> parses;
    shared::Win::File::ParseA(ipaddr, ':', parses);
    if (parses.size() < 2)
     break;
    ip = parses[0];
    port = ::atoi(parses[1].c_str());
    if (port <= 0)
     break;
    if (ip.empty())
     break;
    result = true;
   } while (0);
   if (!result) {
    port = 0;
    ip.clear();
   }
   return result;
  }
 }///namespace libuvpp
}
