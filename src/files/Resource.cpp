#include "files/Resource.hpp"

namespace minerva::files {

const std::string& Resource::getName() const {
  return resourceName_;
}

}  // namespace minerva::files