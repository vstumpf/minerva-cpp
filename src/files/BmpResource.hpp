#ifndef MINERVA_FILES_BMPRESOURCE_HPP_
#define MINERVA_FILES_BMPRESOURCE_HPP_

#include <stdint.h>

#include <string>
#include <vector>

#include <stb_image.h>

class BmpResource {
 public:
  BmpResource();
  ~BmpResource();

  bool Load(const std::string &);

  uint32_t GetWidth() const;
  uint32_t GetHeight() const;
  const char *GetData() const;
  uint32_t GetColor(uint32_t x, uint32_t y) const;
  bool LoadFromBuffer(const std::string &, const uint8_t *, size_t);
  bool LoadBMPData(const uint8_t *, size_t);

 protected:
  void Reset();

 private:
  bool LoadImageData(const uint8_t *, size_t);

 private:
  int m_isAlpha;
  uint32_t m_width;
  uint32_t m_height;
  std::vector<char> m_data;
};


#endif // MINERVA_FILES_BMPRESOURCE_HPP_
