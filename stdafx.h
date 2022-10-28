#if !defined(INC_H___6CDDAE11_F6FE_44AD_A8A4_451272E21572__HEAD__)
#define INC_H___6CDDAE11_F6FE_44AD_A8A4_451272E21572__HEAD__

#include <win.h>
#include <command.h>
#include <spdlog.hpp>
#include <zip++.h>
#include <rapidjson.h>
#include <rapidxml.h>
#include <openssl.hpp>
#include <encryption.hpp>
#include <container.hpp>

#include <pchacker.hpp>
using namespace pchacker;

//!@ libuvpp
#include <uvpp.hpp>
#include <libuvpp/session.h>
#include <libuvpp/client.h>
#include <libuvpp/server.h>
#include <libuvpp/libuv.h>

//!@ libcurlpp 
#define ENABLE_OPENSSL_3 1
#define CURL_STATICLIB
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"crypt32.lib")
#pragma comment(lib,"normaliz.lib")
#if ENABLE_OPENSSL_3
//!@ Openssl 3.0
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"libssl.lib")
#if 0
#pragma comment(lib,"libfips.lib")
#pragma comment(lib,"fips.lib")
#pragma comment(lib,"legacy.lib")
#pragma comment(lib,"libapps.lib")
#pragma comment(lib,"libcommon.lib")
#pragma comment(lib,"libdefault.lib")
#pragma comment(lib,"liblegacy.lib")
#pragma comment(lib,"libtestutil.lib")
#endif
#else
//!@ Openssl 1.0.2
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")
#endif
//!@ Curlpp 0.8.1
#define CURLPP_STATICLIB
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#pragma comment(lib,"curlpp-0.8.1.lib")
//!@ Libcurl 7.85.0
#define CURL_STATICLIB
#pragma comment(lib,"libcurl_zlib_ssl3-7.85.0.lib")
#include <libcurlpp/cache.h>
#include <libcurlpp/base.h>
#include <libcurlpp/response.h>
#include <libcurlpp/request.h>
#include <libcurlpp/http.h>


//!@ local
#include "local.h"
#include "configure.h"
#include "downtask.h"
#include "Setup.h"
#include "taskman.h"
#include "encryption.h"
#include "com.h"
#include "win.h"
#include "zip.h"
#include "pchacker.h"
#include "Global.h"
#include "export.h"


#include<res\setup.xml.res.h>
#include <res\skin.zip.res.h>
#include <components/Taskman/Declspec.h>
/// /*新生®（上海）**/
/// /*2022_09_07T01:06:39.5877592Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___6CDDAE11_F6FE_44AD_A8A4_451272E21572__HEAD__

