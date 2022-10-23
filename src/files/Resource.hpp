#ifndef MINERVA_FILES_RESOURCE_HPP_
#define MINERVA_FILES_RESOURCE_HPP_

#include <string>

namespace minerva::files {

class Resource {
 public:
  Resource() = default;
  virtual ~Resource() = default;

  virtual bool load(const std::string&) = 0;
  const std::string& getName() const;

 protected:
  virtual void reset() = 0;
  void updateInfo(const std::string&);

 private:
  std::string fileName_{};
};

}  // namespace minerva::files

#endif  // MINERVA_FILES_RESOURCE_HPP_