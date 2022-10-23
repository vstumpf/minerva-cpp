#include "files/Resource.hpp"

namespace minerva::files {

const std::string& Resource::getName() const {
  return fileName_;
}

void Resource::updateInfo(const std::string& filename) {
  fileName_ = filename;
}

}  // namespace minerva::files