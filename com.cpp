#include "stdafx.h"

namespace local {

 Com::Com() {
  Init();
 }

 Com::~Com() {
  UnInit();
 }
 void Com::Init() {

 }
 void Com::UnInit() {

 }

 bool Com::CreateLnk(const std::string& szPath, const std::string& szLink, const std::string& szIcoPath /*= ""*/, const std::string& szArgument /*= ""*/) const {
  return shared::Win::CreateShortcut(szPath, szLink, szIcoPath, szArgument);
 }
 bool Com::CreateLnkUrl(
  const std::string& BindLnkUrl,
  const std::string& BindLnkPathname, /*xxx.lnk*/
  const std::string& BindLnkIcoPathname/*xxx.ico | xxx.png*/) const {
  return shared::Win::CreateShortcutUrl(BindLnkUrl, BindLnkPathname, BindLnkIcoPathname);
 }
}///namespace lcoal
