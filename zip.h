#if !defined(INC_H___44DFEC92_91FF_4EF8_9FE1_7C6BDD35966E__HEAD__)
#define INC_H___44DFEC92_91FF_4EF8_9FE1_7C6BDD35966E__HEAD__

namespace local {

 class Zip final : public IZip {
  /*std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();*/
 public:
  Zip();
  virtual ~Zip();
 protected:
  bool UncompressBuffer(const std::string& zbuffer, std::string& outbuffer) const override final;
  bool UncompressBuffer(const std::string& zbuffer, \
   const std::function<bool(const std::string&, const std::string&, bool&)>& uncompress_cb, const std::string& outpath = "") const override final;
#if 0
  static bool IsZipCompress(const std::string& buffer);
  static int zipCompress(__in const std::string& src, __out std::string& dest) noexcept;
  static int zipUnCompress(__in const std::string& src, __in const size_t& nraw, __out std::string& dest) noexcept;
 public:
  static bool gzipCompress(const std::string& src, std::string& dest, int level = -1);
  static bool gzipUnCompress(const std::string& src, std::string& dest);
  static bool zipFileUnCompress(const std::string& buffer, const std::string& out_path);
  static bool zipPakUnCompress(const std::string& zipBuffer, const std::string& out_pathname);
  static bool zipPakUnCompressFirstToBuffer(const std::string& zipBuffer, std::string& out_buffer);
  static bool zipPakUnCompressToBuffer(const std::string& zipBuffer, const std::string& identify, std::string& out_buffer);
  static bool zipBufferCompress(const std::string& zipBuffer, std::string& zipFinish);
  static bool zipBufferUnCompress(const std::string& zipBuffer, const std::function<bool(const std::string&, const std::string&, bool&)>& uncompress_cb, const std::string& outputDir = "");
 private://!@ GZip
  static size_t GZGetBound(const size_t& sourceLen);
  static int GZCompress(unsigned char* pSrc, unsigned long nSrc, unsigned char* pDest, unsigned long* nDest);
  static int GZUnCompress(unsigned char* pSrc, unsigned long nSrc, unsigned char* pDest, unsigned long* nDest);
#endif
 };

}///namespace local 

/// /*新生®（上海）**/
/// /*2022_10_26T00:37:11.1978538Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___44DFEC92_91FF_4EF8_9FE1_7C6BDD35966E__HEAD__




