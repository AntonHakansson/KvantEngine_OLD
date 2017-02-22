#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>

#include <chrono>
#include <functional>

using namespace std;
using namespace sf;

using FrameTime = float;

constexpr unsigned int windowWidth{800}, windowHeight{600};
constexpr float ballRadius{10.f}, ballVelocity{0.8f};
constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{0.6f};
constexpr float blockWidth{60.f}, blockHeight{20.f};
constexpr int countBlocksX{11}, countBlocksY{4};
constexpr float ftStep{1.f}, ftSlice{1.f};

/*
// 21 -> 021
[0, 0, 0]

// digit=0
// 21/(10^0) % 10 => 1
// Int(21/(10^1)) & 10 => 2 => 2
// 2131451/10^3 % 10 => 2131 %10 => 1


(21/10^digit) % 10

['0', '2', '1']
*/

struct Game;
struct Component;
struct Entity;
struct Manager;

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
    for(auto i{0u}; i< maxGroups; ++i) {
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

// Entities can have a position in the game world.
// TODO: make tranform with matrices
struct CPosition : Component {
    Vector2f position;

    CPosition() = default;
    CPosition(const Vector2f& mPosition) : position{mPosition} {}

    float x() const noexcept { return position.x; }
    float y() const noexcept { return position.y; }
};

struct CCircle : Component {
  Game* game{nullptr};
  CPosition* cPosition{nullptr};
  CircleShape shape;
  float radius;

  CCircle(Game* mGame, float mRadius) : game{mGame}, radius{mRadius} {}

  void init() override {
    cPosition = &entity->getComponent<CPosition>();

    shape.setRadius(radius);
    shape.setFillColor(Color::Red);
    shape.setOrigin(radius, radius);
  }
  void update(float mFT) override {
    shape.setPosition(cPosition->position);
  }

  void draw() override;
};

struct CRectangle : Component {
  Game* game{nullptr};
  CPosition* cPosition{nullptr};
  RectangleShape shape;
  Vector2f size;

  CRectangle(Game* _game, Vector2f _size) : game{_game}, size{_size} {}

  void init() override {
    cPosition = &entity->getComponent<CPosition>();

    shape.setSize(size);
    shape.setFillColor(Color::Red);
    shape.setOrigin(size.x/2., size.y/2.);
  }
  void update(float mFT) override {
    shape.setPosition(cPosition->position);
  }

  void draw() override;
};


struct CPhysics : Component {
  CPosition* cPosition{nullptr};
  Vector2f velocity, halfSize;

  std::function<void(const Vector2f&)> onOutOfBounds;

  CPhysics(Vector2f _halfSize) : halfSize(_halfSize) {  }

  void init() override {
    cPosition = &entity->getComponent<CPosition>();
  }

  void update(float mFt) override {
    cPosition->position += velocity*mFt;

    if(left() < 0) {
      onOutOfBounds(Vector2f(1.0, 0.0));
    }
    if(right() > windowWidth) {
      onOutOfBounds(Vector2f(-1.0, 0.0));
    }
    if(top() < 0) {
      onOutOfBounds(Vector2f(0.0, 1.0));
    }
    if(bottom() > windowHeight) {
      onOutOfBounds(Vector2f(0.0, -1.0));
    }
  }

  float x() const noexcept { return cPosition->x(); }
  float y() const noexcept { return cPosition->y(); }
  float left() const noexcept { return x() - halfSize.x; }
  float right() const noexcept { return x() + halfSize.x; }
  float top() const noexcept { return y() - halfSize.y; }
  float bottom() const noexcept { return y() + halfSize.y; }
};

struct CPeddleControl : Component {
  CPhysics* cPhysics{nullptr};

  void init() override {
    cPhysics = &entity->getComponent<CPhysics>();
  }

  void update(float mFt) override {
    if(Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      cPhysics->velocity.x -= 0.08*mFt;
    }
    if(Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      cPhysics->velocity.x += 0.08*mFt;
    }

    cPhysics->velocity *= 0.93f*mFt;
  }
};


struct Game {
  RenderWindow window{{windowWidth, windowHeight}, "SFML works!"};
  Manager manager;
  bool running;
  FrameTime lastFt{0.f}, currentSlice{0.f};

  enum groups : std::size_t {
    peddles,
    balls,
    bricks
  };

  Entity& createBall() {
    auto& e(manager.addEntity());
    e.addComponent<CPosition>(Vector2f(400, 200));
    e.addComponent<CCircle>(this, ballRadius);
    e.addComponent<CPhysics>(Vector2f(ballRadius, ballRadius));
    e.addGroup(groups::balls);

    auto& cPhysics(e.getComponent<CPhysics>());
    cPhysics.velocity = Vector2f{-ballVelocity, -ballVelocity};
    cPhysics.onOutOfBounds = [&cPhysics](const Vector2f& side) {
     if(side.x != 0.f)
       cPhysics.velocity.x =
         std::abs(cPhysics.velocity.x) * side.x;

     if(side.y != 0.f)
       cPhysics.velocity.y =
         std::abs(cPhysics.velocity.y) * side.y;
    };

    return e;
  }

  Entity& createPeddle() {
    Vector2f paddleSize(paddleWidth, paddleHeight);

    auto& e(manager.addEntity());
    e.addComponent<CPosition>(Vector2f(100, windowHeight-(paddleHeight+5)));
    e.addComponent<CRectangle>(this, Vector2f(paddleWidth, paddleHeight));
    e.addComponent<CPhysics>(paddleSize*0.5f);
    e.addComponent<CPeddleControl>();
    e.addGroup(groups::peddles);

    auto& cPhysics(e.getComponent<CPhysics>());
    cPhysics.onOutOfBounds = [&cPhysics](const Vector2f& side) {
      if(side.x < 0) {
        cPhysics.velocity.x =
          std::abs(cPhysics.velocity.x) * side.x;
        cPhysics.cPosition->position.x += windowWidth-cPhysics.right();
      }
      else {
        cPhysics.velocity.x =
          std::abs(cPhysics.velocity.x) * side.x;
        cPhysics.cPosition->position.x -= cPhysics.left();
      }
    };

    return e;
  }

  Entity& createBrick(const Vector2f& _position) {
    Vector2f blockSize(50, 20);

    auto& e(manager.addEntity());
    e.addComponent<CPosition>(Vector2f(_position.x, _position.y));
    e.addComponent<CRectangle>(this, blockSize);
    e.addComponent<CPhysics>(blockSize*0.5f);

    e.addGroup(groups::bricks);

    auto& cPhysics(e.getComponent<CPhysics>());
    cPhysics.onOutOfBounds = [&cPhysics](const Vector2f& side) {
      if(side.x < 0) {
        cPhysics.velocity.x =
          std::abs(cPhysics.velocity.x) * side.x;
        cPhysics.cPosition->position.x += windowWidth-cPhysics.right();
      }
      else {
        cPhysics.velocity.x =
          std::abs(cPhysics.velocity.x) * side.x;
        cPhysics.cPosition->position.x -= cPhysics.left();
      }
    };

    return e;
  }

  Game() {
    window.setFramerateLimit(20);

    createBall();
    createPeddle();

    for(int iX{0}; iX < countBlocksX; ++iX)
      for(int iY{0}; iY < countBlocksY; ++iY)
        createBrick(Vector2f{(iX + 1) * (blockWidth + 3) + 22,
                    (iY + 2) * (blockHeight + 3)});
  }

  void run() {
    while(running = window.isOpen()) {
      auto timePoint1(chrono::high_resolution_clock::now());

      window.clear(Color::Black);

      inputPhase();
      updatePhase();
      drawPhase();

      auto timePoint2(chrono::high_resolution_clock::now());
      auto elapsedTime(timePoint2 - timePoint1);
      FrameTime ft{
          chrono::duration_cast<chrono::duration<float, milli>>(
              elapsedTime)
              .count()};

      lastFt = ft;

      auto ftSeconds(ft / 1000.f);
      auto fps(1.f / ftSeconds);

      window.setTitle(
          "FT: " + to_string(ft) + "\tFPS: " + to_string(fps));
    }
  }

  void inputPhase() {
    Event event;
    while(window.pollEvent(event)) {
      if(event.type == Event::Closed) {
        window.close();
        break;
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) running = false;
  }

  template <class T1, class T2>
  bool isIntersecting(T1& mA, T2& mB) noexcept {
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
  }

  void testCollisionPB(Entity& peddle, Entity& ball) {

    auto& cpPaddle(peddle.getComponent<CPhysics>());
    auto& cpBall(ball.getComponent<CPhysics>());

    if(!isIntersecting(cpPaddle, cpBall)) return;

    cpBall.velocity.y = -ballVelocity;
    if(cpBall.x() < cpPaddle.x())
        cpBall.velocity.x = -ballVelocity;
    else
        cpBall.velocity.x = ballVelocity;
  }

  void testCollisionBB(Entity& brick, Entity& ball) {
    auto& cpBrick(brick.getComponent<CPhysics>());
    auto& cpBall(ball.getComponent<CPhysics>());

    if(!isIntersecting(cpBrick, cpBall)) return;
    brick.destroy();

    float overlapLeft{cpBall.right() - cpBrick.left()};
    float overlapRight{cpBrick.right() - cpBall.left()};
    float overlapTop{cpBall.bottom() - cpBrick.top()};
    float overlapBottom{cpBrick.bottom() - cpBall.top()};

    bool ballFromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool ballFromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if(std::abs(minOverlapX) < std::abs(minOverlapY))
        cpBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        cpBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
  }

  void updatePhase() {
    currentSlice += lastFt;
    for(; currentSlice >= ftSlice; currentSlice -= ftSlice) {
      manager.refresh();
      manager.update(ftStep);

      // Get entities by group
      auto& paddles(manager.getEntitiesByGroup(groups::peddles));
      auto& bricks(manager.getEntitiesByGroup(groups::bricks));
      auto& balls(manager.getEntitiesByGroup(groups::balls));

      // perform collision tests on them.
      for(auto& b : balls) {
        for(auto& p : paddles) testCollisionPB(*p, *b);
        for(auto& br : bricks) testCollisionBB(*br, *b);
      }
    }
  }

  void drawPhase() {
    manager.draw();
    window.display();
  }

  void render(const Drawable& mDrawable) { window.draw(mDrawable); }
};

void CCircle::draw() { game->render(shape); }
void CRectangle::draw() { game->render(shape); }

int main() {
  Game{}.run();
  return 0;
}
