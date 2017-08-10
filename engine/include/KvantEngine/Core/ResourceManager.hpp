#pragma once

// C++ Headers
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <chrono>

#include <boost/filesystem.hpp>

// Third-party
#include <spdlog/spdlog.h>
#include <FileWatcher/FileWatcher.hpp>

// Kvant Headers
#include <KvantEngine/CoreTypes/Resource.hpp>
#include <KvantEngine/CoreTypes/Texture.hpp>


namespace Kvant {

  namespace fs = boost::filesystem;

  using ResourceHandle = std::string;

  template <class T>
  class ResourceManager {
  public:
    ResourceManager () {}
    virtual ~ResourceManager () {}

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
      else {
        if (m_watch_id != INVALID) m_filewatcher.remove_watch(m_watch_id);
        m_base_path = base_filepath;
        using namespace std::placeholders;
        m_watch_id = m_filewatcher.add_watch(base_filepath, true, std::bind(&ResourceManager::handle_file_update<T>, this, _1, _2, _3, _4));
      }
    }

    std::shared_ptr<T> operator [](ResourceHandle handle) {
      return get(handle);
    }

    void update () {
      if (m_watch_id != INVALID)
        m_filewatcher.update();
    }

    template<class Texture>
    void handle_file_update(FW::WatchId, const std::string& dir, const std::string& filename,
               FW::Action action) {
      // Return if texture is not an observed resource
      if (!m_resources[filename]) return;

      switch(action) {
        case FW::Action::Add:
          std::cout << "Texture (" << dir + filename << ") Reappeared! " <<  std::endl;
          break;
        case FW::Action::Delete:
          std::cout << "Texture (" << dir + filename << ") Deleted! " << std::endl;
          m_resources[filename]->load_image(m_base_path / fs::path("removed.png"));
          break;
        case FW::Action::Modified:
          std::cout << "Texture (" << dir + filename << ") Modified! " << std::endl;
          m_resources[filename]->load_image(dir + filename);
          break;
        default:
          std::cout << "Should never happen!" << std::endl;
     }
    }

  private:
    std::unordered_map<ResourceHandle, std::shared_ptr<T>> m_resources;

    FW::FileWatcher m_filewatcher;
    const FW::WatchId INVALID{std::numeric_limits<FW::WatchId>::max()};
    FW::WatchId m_watch_id{INVALID};
    fs::path m_base_path{"./"};
  };
}
