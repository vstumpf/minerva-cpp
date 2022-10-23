#include "files/BmpResource.hpp"

#ifndef WIN32
#include <string.h>
#define _strcmpi strcasecmp
#endif

#include "common/debug.hpp"

namespace minerva::files {

BmpResource::~BmpResource() {
  reset();
}

uint32_t BmpResource::getWidth() const {
  return width_;
}

uint32_t BmpResource::getHeight() const {
  return height_;
}

const char* BmpResource::getData() const {
  return data_.data();
}

void BmpResource::reset() {
  data_.clear();
  width_ = 0;
  height_ = 0;
}

uint32_t BmpResource::getColor(uint32_t x, uint32_t y) const {
  uint32_t result;

  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    result = 0x00FF0000;
  } else {
    auto idx = static_cast<size_t>(x) + static_cast<size_t>(y) * width_;
    LOG(info, "idx is {}", idx);
    result = data_[idx];
  }

  return result;
}

bool BmpResource::load(const std::string& filename) {
  reset();

  int width, height, channels;
  char* data = reinterpret_cast<char*>(
      stbi_load(filename.c_str(), &width, &height, &channels, 4));

  if (!data) {
    LOG(error, "Failed to load image data for {}", filename);
    return false;
  }

  LOG(debug, "STBI: File {} | Width {} | Height {} | Channels {}", filename,
      width, height, channels);

  width_ = width;
  height_ = height;

  size_t size = width * height * 4 * sizeof(char);

  data_.reserve(size);

  memmove(data_.data(), data, size);

  stbi_image_free(data);

  updateInfo(filename);
  return true;
}

}  // namespace minerva::files
