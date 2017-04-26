#pragma once

// C++ Headers
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include <boost/filesystem.hpp>


// Third-party
#include <spdlog/spdlog.h>
#include <FileWatcher.hpp>

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
    virtual ~Resource() {
    }

    const fs::path& get_filepath () { return m_filepath; }
    const ResourceHandle& get_handle () { return m_handle; }

  protected:
    fs::path m_filepath;
    ResourceHandle m_handle;
  };


  /// Processes a file action
  class UpdateListener
  {
  public:
  	UpdateListener() {}
  	void handleFileAction(FW::WatchId, const FW::String& dir, const FW::String& filename,
  		FW::Action action)
  	{
  		std::cout << "DIR (" << dir + ") FILE (" + filename + ") has event " << (int)action << std::endl;
  	}
  };

  template <class T>
  class ResourceManager {
  public:
    ResourceManager () {
    }
    virtual ~ResourceManager () {
    }

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
        m_watch_id = m_filewatcher.add_watch(m_base_path.string(), std::bind(&ResourceManager::handle_file_update, this, _1, _2, _3, _4));
      }
    }

    std::shared_ptr<T> operator [](ResourceHandle handle) {
      return get(handle);
    }

    void update () {
      if (m_watch_id != INVALID)
        m_filewatcher.update();
    }

    void handle_file_update(FW::WatchId, const std::string& dir, const std::string& filename,
               FW::Action action) {
        switch(action) {
        case FW::Action::Add:
           std::cout << "File (" << dir + "\\" + filename << ") Added! " <<  std::endl;
           break;
        case FW::Action::Delete:
           std::cout << "File (" << dir + "\\" + filename << ") Deleted! " << std::endl;
           break;
        case FW::Action::Modified:
           std::cout << "File (" << dir + "\\" + filename << ") Modified! " << std::endl;
           break;
        default:
           std::cout << "Should never happen!" << std::endl;
     }
   }

  private:
    std::unordered_map<ResourceHandle, std::shared_ptr<T>> m_resources;

    FW::FileWatcher m_filewatcher;
    const FW::WatchId INVALID{99999};
    FW::WatchId m_watch_id{INVALID};
    fs::path m_base_path{"./"};
  };
}
