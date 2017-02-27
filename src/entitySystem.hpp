#pragma once

// Includes
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

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
    static ComponentID lastID{0u};
    return lastID++;
  }
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
  static_assert(std::is_base_of<Component, T>::value,
      "T must inherit from Component");

  static ComponentID typeID{Internal::getUniqueComponentID()};
  return typeID;
}

constexpr size_t maxComponents{32};
using ComponentBitset = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

constexpr size_t maxGroups{32};
using GroupBitset = bitset<maxGroups>;

struct Component {
  Entity* entity;

  virtual void init() {}
  virtual void update(float mFT) {}
  virtual void draw() {}

  virtual ~Component() {}
};

struct Entity {
  Entity(Manager& _manager) : manager(_manager) {}

  // Update entity's components update phase
  void update(float ft) {
    for(auto& c : components) c->update(ft);
  }
  // Update entity's components draw call
  void draw() {
    for(auto& c : components) c->draw();
  }

  const bool& isAlive() const {
    return alive;
  }

  void destroy() { alive = false; }

  template <typename T>
  bool hasComponent() const {
    return componentBitset[getComponentTypeID<T>()];
  }

  bool hasGroup(Group group) const noexcept {
    return groupBitset[group];
  }

  void addGroup(Group _group) noexcept;
  void delGroup(Group _group) noexcept {
    groupBitset[_group] = false;
  }

  template <typename T, typename... TArgs>
  T& addComponent(TArgs&&... _args) {
    assert(!hasComponent<T>());

    T* c(new T(forward<TArgs>(_args)...));
    c->entity = this;
    unique_ptr<Component> uPtr{c};
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitset[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
  }

  template <typename T>
  T& getComponent() const {
    assert(hasComponent<T>());
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *reinterpret_cast<T*>(ptr);
  }

private:
  // Reference to it's manager
  Manager& manager;
  bool alive{true};

  // Store entitie's components
  vector<unique_ptr<Component>> components;

  //
  ComponentArray componentArray;

  // used for ensuring one type of component
  ComponentBitset componentBitset;

  //
  GroupBitset groupBitset;
};

struct Manager {
  void update(float ft) {
    for(auto& e : entities) e->update(ft);
  }
  void draw() {
    for(auto& e : entities) e->draw();
  }

  void addToGroup(Entity* _entity, Group _group) {
    groupedEntities[_group].emplace_back(_entity);
  }
  vector<Entity*>& getEntitiesByGroup(Group _group) {
    return groupedEntities[_group];
  }

  void refresh() {
    for(size_t i{0u}; i< maxGroups; ++i) {
      auto& v(groupedEntities[i]);

      v.erase(remove_if(begin(v), end(v),
              [i](Entity* _entity) {
                return !_entity->isAlive() || !_entity->hasGroup(i);
              }),
            end(v));
    }

    entities.erase(remove_if(begin(entities), end(entities),
            [](const unique_ptr<Entity>& _entity) {
              return !_entity->isAlive();
            }),
            end(entities));
  }

  Entity& addEntity() {
    Entity* e(new Entity(*this));
    unique_ptr<Entity> uPtr{e};
    entities.emplace_back(move(uPtr));
    return *e;
  }

private:
  vector<unique_ptr<Entity>> entities;
  array<vector<Entity*>, maxGroups> groupedEntities;
};

void Entity::addGroup(Group _group) noexcept {
  groupBitset[_group] = true;
  manager.addToGroup(this, _group);
}
