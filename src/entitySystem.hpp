#pragma once

// C++ Headers
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

namespace Kvant {
  // Namespaces
  using namespace std;

  // Forward declarations
  struct Component;
  struct Entity;
  struct Manager;

  // Implementation
  using ComponentID = std::size_t;
  using Group = std::size_t;

  namespace Internal {
    inline ComponentID getUniqueComponentID() noexcept {
      static ComponentID last_id{0u};
      return last_id++;
    }
  }

  template <typename T>
  inline ComponentID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<Component, T>::value,
        "T must inherit from Component");

    static ComponentID typeID{Internal::getUniqueComponentID()};
    return typeID;
  }

  constexpr size_t max_components{32};
  using ComponentBitset = bitset<max_components>;
  using ComponentArray = array<Component*, max_components>;

  constexpr size_t max_groups{32};
  using GroupBitset = bitset<max_groups>;

  struct Component {
    Entity* entity;

    virtual void init() {}
    virtual void update(float) {}
    virtual void draw() {}

    virtual ~Component() {}
  };

  struct Entity {
    Entity(Manager& _manager) : m_manager(_manager) {}

    // Update entity's components update phase
    void update(float ft) {
      for(auto& c : components) c->update(ft);
    }
    // Update entity's components draw call
    void draw() {
      for(auto& c : components) c->draw();
    }

    const bool& is_alive() const {
      return m_alive;
    }

    void destroy() { m_alive = false; }

    template <typename T>
    bool has_component() const {
      return m_component_bitset[getComponentTypeID<T>()];
    }

    bool has_group(Group group) const noexcept {
      return m_group_bitset[group];
    }

    void add_group(Group _group) noexcept;
    void delete_group(Group _group) noexcept {
      m_group_bitset[_group] = false;
    }

    template <typename T, typename... TArgs>
    T& add_component(TArgs&&... _args) {
      assert(!has_component<T>());

      T* c(new T(forward<TArgs>(_args)...));
      c->entity = this;
      unique_ptr<Component> uPtr{c};
      components.emplace_back(std::move(uPtr));

      m_component_array[getComponentTypeID<T>()] = c;
      m_component_bitset[getComponentTypeID<T>()] = true;

      c->init();
      return *c;
    }

    template <typename T>
    T& get_component() const {
      assert(has_component<T>());
      auto ptr(m_component_array[getComponentTypeID<T>()]);
      return *reinterpret_cast<T*>(ptr);
    }

  private:
    // Reference to it's manager
    Manager& m_manager;
    bool m_alive{true};

    // Store entitie's components
    vector<unique_ptr<Component>> components;

    //
    ComponentArray m_component_array;

    // used for ensuring one type of component
    ComponentBitset m_component_bitset;

    //
    GroupBitset m_group_bitset;
  };

  struct Manager {
    void update(float ft) {
      for(auto& e : entities) e->update(ft);
    }
    void draw() {
      for(auto& e : entities) e->draw();
    }

    void add_to_group(Entity* _entity, Group _group) {
      m_grouped_entities[_group].emplace_back(_entity);
    }
    vector<Entity*>& get_entities_by_group(Group _group) {
      return m_grouped_entities[_group];
    }

    void refresh() {
      for(size_t i{0u}; i< max_groups; ++i) {
        auto& v(m_grouped_entities[i]);

        v.erase(remove_if(begin(v), end(v),
                [i](Entity* _entity) {
                  return !_entity->is_alive() || !_entity->has_group(i);
                }),
              end(v));
      }

      entities.erase(remove_if(begin(entities), end(entities),
              [](const unique_ptr<Entity>& _entity) {
                return !_entity->is_alive();
              }),
              end(entities));
    }

    Entity& add_entity() {
      Entity* e(new Entity(*this));
      unique_ptr<Entity> uPtr{e};
      entities.emplace_back(move(uPtr));
      return *e;
    }

  private:
    vector<unique_ptr<Entity>> entities;
    array<vector<Entity*>, max_groups> m_grouped_entities;
  };

  void Entity::add_group(Group _group) noexcept {
    m_group_bitset[_group] = true;
    m_manager.add_to_group(this, _group);
  } 
}
