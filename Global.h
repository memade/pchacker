#if !defined(INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__)
#define INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__

namespace local {

	class Global final {
	public:
		Global();
		~Global();
	public:
		bool Init();
	private:
		void UnInit();
	public:
		static PCHacker* PCHackerGet();
		static libcurlpp::IHttpApi* HttpGet();
	private:
		PCHacker* m_pPCHacker = nullptr;
		libcurlpp::IHttpApi* m_pHttpObj = nullptr;
		std::atomic_bool m_Ready = false;

#if ENABLE_MODULE_CEF3
	public:
		static shared::cef3::ICef3Api* Cef3Get();
	private:
		shared::cef3::ICef3Api* m_pCef3Obj = nullptr;
#endif
	};


	extern Global* __gpGlobal;
	extern Global* GlobalGet();
	extern HINSTANCE __gpHinstance;
}///namespace local

/// /*新生®（上海）**/
/// /*2022_09_21T01:22:05.6053548Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___4A6B3036_6348_477A_960D_AFAB295FE18F__HEAD__



