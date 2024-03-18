#include "files/FlrResource.hpp"

#ifndef WIN32
#include <string.h>
#define _strcmpi strcasecmp
#endif

#include "common/debug.hpp"

namespace minerva::files {

FlrResource::~FlrResource() {
  reset();
}

uint32_t FlrResource::getWidth() const {
  return width_;
}

uint32_t FlrResource::getLength() const {
  return length_;
}

const char* FlrResource::getData() const {
  return data_.data();
}

void FlrResource::reset() {
  data_.clear();
  width_ = 0;
  length_ = 0;
}

bool FlrResource::load(const std::string& filename) {
  reset();

  int width, height, channels;
  char* data = reinterpret_cast<char*>(
      stbi_load(filename.c_str(), &width, &height, &channels, 4));

  if (!data) {
    LOG(error, "Failed to load image data for {}", filename);
    return false;
  }

  width_ = width;
  length_ = height;

  size_t size = width * height * 4 * sizeof(char);

  data_.resize(size);

  memmove(data_.data(), data, size);

  stbi_image_free(data);

  updateInfo(filename);

  LOG(debug, "STBI: File {} | Width {} | Height {} | Size {} | Channels {}",
      filename, width, height, data_.size(), channels);

  return true;
}

}  // namespace minerva::files
