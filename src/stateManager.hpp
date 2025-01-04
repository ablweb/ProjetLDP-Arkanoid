#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>

class Entity;
struct Level;
struct CollisionGroup;
class CollisionRect;
class CollisionCircle;

typedef std::shared_ptr<Level> LevelSPtr;

/*
 * class StateManager
 * 
 * Manages the game's state, including paddle movements, ball interactions, 
 * and collision detection. This class is based on the MVC design pattern 
 * and acts as a facade to the model. It is a component of the controller 
 * that enables the translation of user input into game logic.
 *
 * - The `update` method is called each frame in the game loop to handle
 *   automatic updates such as ball movement and collision detection.
 * - Method like `movePaddleRight` and `lauchBall` are triggered 
 *   by user inputs to change the game state.
 */
class StateManager {
 private:
  LevelSPtr lvl;

 public:
  StateManager(LevelSPtr);
  ~StateManager();

  // Here add all methods to change state of game entities
  void movePaddleRight();
  void movePaddleLeft();
  void launchBall();
  void update();

 private:
  /*
   * Checks for collisions between game entities.
   * Called within the update function.
   */
  void checkAllCollision();
};

#endif
