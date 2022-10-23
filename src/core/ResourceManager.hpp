#ifndef MINERVA_CORE_RESOURCEMANAGER_HPP_
#define MINERVA_CORE_RESOURCEMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include "files/Resource.hpp"

namespace minerva::core {

using minerva::files::Resource;

/**
 * This is the global resource manager for the game
 *
 */
class ResourceManager {
 public:
  ResourceManager() = default;

  /**
   * Fetches a resource from the internal storage
   * If the resource doesn't exist, or if forceRefresh is set, it will load it
   * from disk
   */
  template <class T>
  std::shared_ptr<T> getResource(const std::string& filename,
                                 bool forceRefresh = false) {
    if (!forceRefresh) {
      auto it = resourceList_.find(filename);
      if (it != resourceList_.end()) {
        auto res = std::static_pointer_cast<T>(it->second);
        if (res) {
          return res;
        }
      }
    }

    auto resource = std::make_shared<T>();
    if (!resource->load(filename)) {
      return nullptr;
    }

    resourceList_[filename] = resource;
    return resource;
  }

 private:
  std::unordered_map<std::string, std::shared_ptr<Resource>> resourceList_{};
};

}  // namespace minerva::core

#endif