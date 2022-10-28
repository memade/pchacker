#include "stdafx.h"

namespace local {

 Zip::Zip() {
 }

 Zip::~Zip() {
 }

 bool Zip::UncompressBuffer(const std::string& zbuffer, \
  const std::function<bool(const std::string&, const std::string&, bool&)>& uncompress_cb, const std::string& outpath /*= ""*/) const {
  return shared::Zip::zipBufferUnCompress(zbuffer, uncompress_cb, outpath);
 }

 bool Zip::UncompressBuffer(const std::string& zbuffer, std::string& outbuffer) const {
  return shared::Zip::zipPakUnCompressFirstToBuffer(zbuffer, outbuffer);
 }
}///namespace lcoal
