#pragma once

// C++ Headers
#include <string>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <fstream>

// Third-party
#include <yaml-cpp/yaml.h>

namespace Kvant {

  struct BaseConfig {};
  struct WindowConfig : public BaseConfig {
    static const std::string get_yaml_id () { return "window"; }

    unsigned int width, height;
    std::string title;
    bool fullscreen;
  };

  struct ResourcesConfig : public BaseConfig {
    static const std::string get_yaml_id () { return "resources"; }
    
    std::string textures_path, shaders_path;
  };

  class GameConfig {
  public:
    GameConfig (const std::string& config_path) : m_config_path (config_path) {
      load_config ();
    }

    void load_config () {
      auto root_node = YAML::LoadFile (m_config_path);
      get<WindowConfig> (&root_node);
      get<ResourcesConfig> (&root_node);
    }

    void load_new_config (const std::string& config_path) {
      m_config_path = config_path;
      load_config();
    }

    void save_config () {
      YAML::Node root_node;

      root_node[WindowConfig::get_yaml_id()] = *get<WindowConfig>();

      std::ofstream fout(m_config_path);
      fout << root_node;
    }

    template <typename T>
    const T* get (YAML::Node* root_node = nullptr) {
      static_assert(std::is_base_of<BaseConfig, T>::value, "T must inherit from BaseConfig");

      // Cache config if not previously parsed
      std::string key = T::get_yaml_id();
      if (m_config.count(key) < 1) {
        if (root_node == nullptr) {
          std::cout << "Error, key " + key +
                         " not previously read and root_node not passed"
                         << std::endl;
          return nullptr;
        }

        auto ptr = std::make_unique<T>( (*root_node)[key].as<T>() );
        m_config[key] = std::move(ptr);
      }

      auto ptr = m_config[key].get();
      return reinterpret_cast<T*>( ptr );
    }

    template <typename T>
    void set (std::unique_ptr<BaseConfig> config) {
      static_assert(std::is_base_of<BaseConfig, T>::value, "T must inherit from BaseConfig");
      m_config[T::get_yaml_id()] = std::move( config );
    }

  private:
    std::string m_config_path;
    std::unordered_map< std::string, std::unique_ptr<BaseConfig> > m_config;
  };
}

namespace YAML {
    template<> struct convert<Kvant::WindowConfig> {
      static Node encode (const Kvant::WindowConfig& config) {
        Node node;
        node["title"] = config.title;
        node["width"] = config.width;
        node["height"] = config.height;
        node["fullscreen"] = config.fullscreen;
        return node;
      }

      static bool decode (const Node& node, Kvant::WindowConfig& config) {
        config.title = node["title"].as<std::string>();
        config.width = node["width"].as<int>();
        config.height = node["height"].as<int>();
        config.fullscreen = node["fullscreen"].as<bool>();
        return true;
      }
    };

    template<> struct convert<Kvant::ResourcesConfig> {
      static bool decode (const Node& node, Kvant::ResourcesConfig& config) {
        config.textures_path = node["textures"].as<std::string>();
        config.shaders_path = node["shaders"].as<std::string>();
        return true;
      }
    };
  }
