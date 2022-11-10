#if !defined(INC_H___20F97F29_22A2_4375_9F7B_44AB07EE54EB__HEAD__)
#define INC_H___20F97F29_22A2_4375_9F7B_44AB07EE54EB__HEAD__

namespace pchacker {
 namespace libuvpp {
  class Server final : public IServer {
   std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
  public:
   Server();
   virtual ~Server();
  private:
   void Init();
   void UnInit();
  public:
   const std::string& Addr() const override final;
   const EnIPV& Ipv() const override final;
   const EnSocketType& SocketType() const override final;
   bool Start(const EnSocketType&, const EnIPV&, const std::string&) override final;
   bool Ready() const override final;
   void MessageCb(const tfOnServerMessage&) override final;
   void Write(const unsigned long long&, const std::string&) override final;
   void SessionCreateAfterCb(const tfOnSessionCreateAfterCb&) override final;
   void SessionDestoryAfterCb(const tfOnSessionDestoryAfterCb&) override final;
   void SessionDestoryBeforeCb(const tfOnSessionDestoryBeforeCb&) override final;
  public:
   void Stop() override final;
  private:
   shared::container::buffer m_BufferWrite;
   tfOnServerMessage m_MessageCb = nullptr;
   std::atomic_bool m_IsOpen = false;
   std::vector<std::thread> m_Threads;
   std::thread m_ServerThread;
   void Process();
   std::string m_Addr;
   EnIPV m_Ipv = EnIPV::IPV4;
   EnSocketType m_SocketType = EnSocketType::TCP;
   shared::container::map<std::string, Session*> m_SessionQ;
   tfOnSessionCreateAfterCb m_OnSessionCreateAfterCb = nullptr;
   tfOnSessionDestoryAfterCb m_OnSessionDestoryAfterCb = nullptr;
   tfOnSessionDestoryBeforeCb m_OnSessionDestoryBeforeCb = nullptr;
  private:
   uv::TcpServer* m_pUVServer = nullptr;
   uv::EventLoop* m_loop_ = nullptr;
  };

 }///namespace libuvpp
}

/// /*新生®（上海）**/
/// /*2022_10_14T22:04:54.7963906Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___20F97F29_22A2_4375_9F7B_44AB07EE54EB__HEAD__