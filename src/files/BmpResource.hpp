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

  bool load(const std::string&);

  uint32_t getWidth() const;
  uint32_t getHeight() const;
  const char* getData() const;
  uint32_t getColor(uint32_t x, uint32_t y) const;
  bool LoadFromBuffer(const std::string&, const uint8_t*, size_t);
  bool LoadBMPData(const uint8_t*, size_t);

 protected:
  void reset();

 private:
  bool LoadImageData(const uint8_t*, size_t);

 private:
  int isAlpha_;
  uint32_t width_;
  uint32_t height_;
  std::vector<char> data_;
};

#endif  // MINERVA_FILES_BMPRESOURCE_HPP_
