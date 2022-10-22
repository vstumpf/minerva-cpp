#ifndef MINERVA_FILES_BMPRESOURCE_HPP_
#define MINERVA_FILES_BMPRESOURCE_HPP_

#include <stb_image.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "files/Resource.hpp"

namespace minerva::files {

class BmpResource : public Resource {
 public:
  BmpResource() = default;
  ~BmpResource() override;

  bool load(const std::string&) override;

  uint32_t getWidth() const;
  uint32_t getHeight() const;
  const char* getData() const;
  uint32_t getColor(uint32_t x, uint32_t y) const;

 protected:
  void reset() override;

 private:
  int isAlpha_{};
  uint32_t width_{};
  uint32_t height_{};
  std::vector<char> data_{};
};

}  // namespace minerva::files

#endif  // MINERVA_FILES_BMPRESOURCE_HPP_
