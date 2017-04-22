#pragma once

// C++ Headers
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include <boost/filesystem.hpp>


// Third-party
#include <spdlog/spdlog.h>

namespace Kvant {

  namespace fs = boost::filesystem;

  using ResourceHandle = std::string;

  class Resource {
  public:
    Resource(const ResourceHandle handle, const fs::path& filepath) {

      if (!fs::exists(filepath))
        std::cout <<  "File \"" << filepath <<"\" doesn't exist" << std::endl;

      m_filepath = filepath;
      m_handle = handle;
    }
    virtual ~Resource() {}

    const fs::path& get_filepath () { return m_filepath; }
    const ResourceHandle& get_handle () { return m_handle; }

  protected:
    fs::path m_filepath;
    ResourceHandle m_handle;
  };


  template <class T>
  class ResourceManager {
  public:
    ResourceManager () { }

    std::shared_ptr<T> get (const ResourceHandle handle) {
      auto found_it = m_resources.find(handle);
      if (found_it != m_resources.end()) {
        return m_resources[handle];
      }
      return nullptr;
    }

    ResourceHandle add (const std::string& file) {
      ResourceHandle handle = file;
      // If resource already exists, return it
      auto element = get(handle);
      if (element) {
        return handle;
      }

      m_resources[handle] = std::make_shared<T>( handle, m_base_path / fs::path(file) );
      return handle;
    }

    bool try_remove (const ResourceHandle handle) {
      auto resource = get (handle);

      // if resource is not being referenced by reource in stack and this, destroy it.
      if (resource.use_count() <= 2) {
        m_resources.erase (handle);
        return true;
      }
      return false;
    }

    void set_base_path (const std::string& base_filepath) {
      if (!fs::is_directory(base_filepath))
        std::cout << "Base directory \"" << base_filepath << "\" is not a directory" << std::endl;
      else
          m_base_path = base_filepath;
    }

    std::shared_ptr<T> operator [](ResourceHandle handle) {
      return get(handle);
    }

  private:
    std::unordered_map<ResourceHandle, std::shared_ptr<T>> m_resources;
    fs::path m_base_path{"./"};
  };
}
