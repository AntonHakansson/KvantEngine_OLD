#pragma once

// C++ Headers
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>


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
}