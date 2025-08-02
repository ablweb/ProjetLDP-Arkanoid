#include "entity.hpp"

#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>         
#include <cmath>
#include <cstdlib>


#include "config.hpp"
#include "utils.hpp"
#include "env.hpp"
#include "level.hpp"

// -------------------------------------------------------------------------
// Entity
// -------------------------------------------------------------------------
Entity::Entity(tpl position) : _pos(position) {}
float Entity::x() const { return _pos.x; }
float Entity::y() const { return _pos.y; }

// -------------------------------------------------------------------------
// DynamiqueEntity
// -------------------------------------------------------------------------
DynamiqueEntity::DynamiqueEntity(tpl position) : Entity(position) {}
void DynamiqueEntity::move(float dx, float dy) {
  _pos.x+=dx;
  _pos.y+=dy;
}

// -------------------------------------------------------------------------
// CollisionRect
// -------------------------------------------------------------------------
CollisionRect::CollisionRect(tpl* position, float* width, float* height)
  : _c_pos(position),_c_w(width),_c_h(height) {}
CollisionRect::~CollisionRect() {}

float CollisionRect::colX() const { return _c_pos->x; }
float CollisionRect::colY() const { return _c_pos->y; }
float CollisionRect::colWidth() const { return *_c_w; }
float CollisionRect::colHeight() const { return *_c_h; }

bool CollisionRect::checkCollision(const CollisionRect* other) {
  if (colX()+colWidth()  < other->colX() ||
      colX()             > other->colX()+other->colWidth() ||
      colY()+colHeight() < other->colY() ||
      colY()             > other->colY()+other->colHeight() ) {
    return true;
  }
  return false;
}
bool CollisionRect::checkCollision(const CollisionCircle* other){
  // https://www.jeffreythompson.org/collision-detection/circle-rect.php
  float oX=other->colX(), oY=other->colY(), oRad=other->colRadius();
  float left = colX() - colWidth()/2;
  float right = colX() + colWidth()/2;
  float top = colY() - colHeight()/2;
  float bottom = colY() + colHeight()/2;
  
  // temporary variables to set edges for testing
  float testX = oX;
  float testY = oY;

  // which edge is closest?
  if (oX < left)        testX = left;     // test left edge
  else if (oX > right)  testX = right;    // right edge
  if (oY < top)         testY = top;      // top edge
  else if (oY > bottom) testY = bottom;   // bottom edge

  // get distance from closest edges
  float distX = oX-testX;
  float distY = oY-testY;
  colPoint.x = distX; colPoint.y = distY;
  float distance = std::sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance <= oRad) {
    return true;
  }
  return false;
}

void CollisionRect::updateWidthPointer(float* newWidth) {
  _c_w = newWidth;
}

// -------------------------------------------------------------------------
// CollisionCircle
// -------------------------------------------------------------------------
CollisionCircle::CollisionCircle(tpl* position, float* radius)
  : _c_pos(position),_c_rad(radius) {}
CollisionCircle::~CollisionCircle() {}

float CollisionCircle::colX() const { return _c_pos->x; }
float CollisionCircle::colY() const { return _c_pos->y; }
float CollisionCircle::colRadius() const { return *_c_rad; }

bool CollisionCircle::checkCollision(const CollisionRect* other){
  // https://www.jeffreythompson.org/collision-detection/circle-rect.php
  float thisX=colX(), thisY=colY(), thisRad=colRadius();
  float left = other->colX() - other->colWidth()/2;
  float right = other->colX() + other->colWidth()/2;
  float top = other->colY() - other->colHeight()/2;
  float bottom = other->colY() + other->colHeight()/2;
  
  // temporary variables to set edges for testing
  float testX = thisX;
  float testY = thisY;

  // which edge is closest?
  if (thisX < left)        testX = left;     // test left edge
  else if (thisX > right)  testX = right;    // right edge
  if (thisY < top)         testY = top;      // top edge
  else if (thisY > bottom) testY = bottom;   // bottom edge

  // get distance from closest edges
  float distX = thisX-testX;
  float distY = thisY-testY;
  colPoint.x = distX; colPoint.y = distY;
  float distance = std::sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance <= thisRad) {
    return true;
  }
  return false;
}

void CollisionCircle::fixOverlap(DynamiqueEntity* thisEntity) {
  if (std::abs(colPoint.x) >= std::abs(colPoint.y)) {
    if (colPoint.x>=0) {
      float overlap = 6;
      thisEntity->move(overlap, 0);
    } else {
      float overlap = 6;
      thisEntity->move(-overlap, 0);
    }
  } else {
    if (colPoint.y>=0) {
      float overlap = 6;
      thisEntity->move(0, overlap);
    } else {
      float overlap = 6;
      thisEntity->move(0, -overlap);
    }
  }
}

// -------------------------------------------------------------------------
// Brick
// -------------------------------------------------------------------------
Brick::Brick(tpl position, BRICK_CONST::colorType brickType, BRICK_CONST::bonusType bonusType, BrickHolder* holder,int& score):
  Entity(position),
  CollisionRect(&this->_pos,&_w,&_h),
  _type(brickType),_bonus(bonusType),_scoreRef(score),_holder(holder) {
  _col = BRICK_CONST::typeToColor.at(_type);
  switch (brickType) {
    case BRICK_CONST::silver:
      _lives = 2;
      break;
    case BRICK_CONST::gold:
      _lives = -1;
      break;
    default: _lives = 1;
      break;
  }
}
Brick::~Brick() {
}

void Brick::destroy() {
  if (_lives!=-1) {
    _scoreRef+=(int)_type; // Update the score if brick is not undestructable
  }
  // --- BONUS SPAWN ---
  if (_bonus != BRICK_CONST::none && _holder != nullptr) {
    // Récupère la lettre du bonus
    char bonusChar = bonusToChar(_bonus);

    // Crée un nouveau bonus à la position de la brique
    Bonus* newBonus = new Bonus(_pos.x, _pos.y, bonusChar, COLORS::WHITE);
    newBonus->activate(); // le fait tomber

    // Accède au niveau via le BrickHolder et ajoute le bonus
    if (_holder) {
    _holder->getLevel()->activeBonuses.push_back(newBonus);
}
  }

  if (_holder != nullptr) {
    _holder->removeBrick(this);
  } else {
    delete this;
  }
}

float Brick::width() const { return _w; }
float Brick::height() const { return _h; }
BRICK_CONST::colorType Brick::getType() const { return _type; }
BRICK_CONST::bonusType Brick::getBonus() const {return _bonus;}

ALLEGRO_COLOR Brick::color() const { return _col; }
bool Brick::isDestructable() const { return _lives!=-1; }

bool Brick::hasBonus() const {
  return _bonus != BRICK_CONST::none;
}
void Brick::collisionDetected(Entity*,tpl) {
  if (_lives!=-1) {
    _lives -= 1;
  }
  if (_lives==0) {
    destroy();
  }
}
// -------------------------------------------------------------------------
// BrickHolder
// -------------------------------------------------------------------------
BrickHolder::BrickHolder(Level* level, int& score, std::vector<BRICK_CONST::Param> bricksData) 
  :_level(level), _score(score) {
  for (const auto& b:bricksData) {
    addBrick(b);
  }
}
BrickHolder::BrickHolder(Level* level, int& score) 
  : _level(level), _score(score) {}
BrickHolder::~BrickHolder() {
  for (auto brick : brickContainer) {
    delete brick;
  }
  brickContainer.clear(); 
}

void BrickHolder::addBrick(BRICK_CONST::Param b) {
  if (b.row >= maxRow || b.col >= maxCol) {
    throw std::out_of_range("Brick position out of grid bounds");
  }
  using namespace BRICK_CONST;
  brickContainer.push_back(new Brick(
    tpl{((float)b.col+1) * (width + spacing) + GAME_SIDE_MARGIN,
        ((float)b.row+1) * (height + spacing) + GAME_TOP_MARGIN},
    b.color,
    b.bonus,
    this,
    _score));
}
std::vector<Brick*> BrickHolder::getContainer() const {
  return brickContainer;
}
void BrickHolder::removeBrick(Brick* brick) {
  brickContainer.erase(
    std::remove(brickContainer.begin(), brickContainer.end(), brick),
    brickContainer.end()
  );
  delete brick;
}

// -------------------------------------------------------------------------
// Paddle
// -------------------------------------------------------------------------
Paddle::Paddle(tpl position, ALLEGRO_COLOR color)
  : DynamiqueEntity(position),
    CollisionRect(&this->_pos,&_w,&_h),
    _w(PADDLE_CONST::spawnWidth),
    _h(PADDLE_CONST::spawnHeight),
    _spd(PADDLE_CONST::normalSpeed),
    _col(color) {}
Paddle::~Paddle() {}

void Paddle::move(float dx, [[maybe_unused]]float dy ) {
  if ((SIDE_MARGIN+_w/2)<(_pos.x+dx)&&(_pos.x+dx)<(DISPLAY_WIDTH-SIDE_MARGIN-_w/2)) {
    _pos.x+=dx;
  }
}

float Paddle::width() const { return _w; }
float Paddle::height() const { return _h; }
ALLEGRO_COLOR Paddle::color() const { return _col; }

void Paddle::move(bool direction) { move(direction?_spd:-_spd, 0); }
void Paddle::widen(float factor) {
  _w *= factor;
  updateWidthPointer(&_w); // On met à jour le pointeur privé via la méthode publique
}
  
void Paddle::collisionDetected(Entity*,tpl) {}
void Paddle::resetWidth() {
  _w = PADDLE_CONST::spawnWidth;
  updateWidthPointer(&_w); // Update CollisionRect's internal pointer
}


// -------------------------------------------------------------------------
// Ball
// -------------------------------------------------------------------------
Ball::Ball(tpl position, float speed, float radius, ALLEGRO_COLOR color, int& lives)
  : DynamiqueEntity(position),
    CollisionCircle(&this->_pos,&_rad),
    _dx(0),_dy(0),_spd(speed),_rad(radius),_col(color),_bounceCount(0),_livesRef(lives),isAttached(true) {} 
Ball::~Ball() {}

void Ball::move(float dx, float dy ) {
  _pos.x+=dx;_pos.y+=dy;
  // check if collision with left or right walls
  if ((_pos.x-_rad)<(SIDE_MARGIN)) {
    // Move the ball inside the game area
    float overlap = (float)SIDE_MARGIN-(_pos.x-_rad);
    move(overlap, 0);
    bounceHorizontal();
  } else if ((_pos.x+_rad)>(DISPLAY_WIDTH-SIDE_MARGIN)) {
    // Move the ball inside the game area
    float overlap = (_pos.x+_rad)-(float)(DISPLAY_WIDTH-SIDE_MARGIN);
    move(-overlap, 0);
    bounceHorizontal();
  }
  // check if collision with top or bottom walls
  if ((_pos.y-_rad)<(TOP_MARGIN) ) {
    // Move the ball inside the game area
    float overlap = (float)TOP_MARGIN-(_pos.y-_rad);
    move(0, overlap);
    bounceVertical();
  } else if ((_pos.y+_rad)>(DISPLAY_HEIGHT-TOP_MARGIN-20.0f)) {
    // reset the ball
    resetBall();
  }
}
void Ball::resetBall() {
  _livesRef--;
  _dx=0;_dy=0,_spd=BALL_CONST::baseSpeed;_bounceCount=0;isAttached=true;
  _pos=BALL_CONST::spawnPosition;
}
void Ball::bounceHorizontal() { _dx = -_dx; _bounceCount++; updateSpeed(); }
void Ball::bounceVertical() { _dy = -_dy; _bounceCount++;updateSpeed(); }
void Ball::updateSpeed() {
  if(LOG_LEVEL>=2)std::cerr<<"|Ball::speed -> "<<_spd<<"\n";
  if (_spd>=BALL_CONST::maxSpeed) return;
  if (_bounceCount!=0&&_bounceCount%BALL_CONST::bounceModulo==0) {
      _spd++;
    if(LOG)std::cerr<<"|Ball::updateSpeed() -> "<<_spd<<"\n";
  }
}

void Ball::setDirection(float dx, float dy) {
  _dx = dx;
  _dy = dy;

  // Normalise la direction pour conserver une vitesse constante
  float length = std::sqrt(_dx * _dx + _dy * _dy);
  if (length != 0) {
    _dx /= length;
    _dy /= length;
  }
}

float Ball::radius() const { return _rad; }
ALLEGRO_COLOR Ball::color() const { return _col; }

void Ball::go() { _dx = 0.1f; _dy = -1; isAttached=false; }
void Ball::setPos(float x) { _pos.x = x; }
void Ball::move() { move(_dx * _spd,_dy * _spd); }

float Ball::getSpeed() const {
  return _spd;
}

void Ball::setSpeed(float speed) {
  // Optionnel : Limiter la vitesse minimale et maximale
  if (speed < 1.0f) speed = 1.0f;
  if (speed > BALL_CONST::maxSpeed) speed = BALL_CONST::maxSpeed;
  _spd = speed;
}


void Ball::collisionDetected(Entity* other, tpl p) {
  if (const auto paddle = dynamic_cast<Paddle*>(other)) {
    if (LOG_LEVEL>=2)std::cerr<<"|Ball::collisionDetected() -> Ball against Paddle\n";
    handleCollision(paddle, p);
  } else if (const auto brick = dynamic_cast<Brick*>(other)) {
    if (LOG_LEVEL>=2)std::cerr<<"|Ball::collisionDetected() -> Ball against Brick\n";
    handleCollision(brick, p);
  }
};
void Ball::handleCollision(Paddle* paddle,[[maybe_unused]] tpl p) {
  if (LOG_LEVEL>=2)std::cerr<<" |Collision Details: \n"
    <<"  |Relative Collision Point : {"<<p.x<<","<<p.y<<"}\n"
    <<"  |Subjects Positions : Ball{"<<_pos.x<<","<<_pos.y<<"} ; Paddle{"
    <<paddle->x()<<","<<paddle->y()<<"}\n";
  // Calculate the relative impact  position 
  float impactX = _pos.x - (paddle->x()-paddle->width()/2);
  // Calculate angle alpha (in degrees) in fonction of impact
  float alpha = 30 + 120 * (1 - impactX / paddle->width());
  // Conversion of angle to  radians
  float alphaRadians = alpha * M_PI / 180.0f;

  // Calculate  direction vector
  float dx = std::cos(alphaRadians);
  float dy = -std::sin(alphaRadians);
  float length = std::sqrt(dx * dx + dy * dy);
  setDirection(dx / length, dy / length);
}
void Ball::handleCollision([[maybe_unused]]Brick* brick, tpl p) {
  if (LOG_LEVEL>=2)std::cerr<<" |Collision Details: \n"
    <<"  |Relative Collision Point : {"<<p.x<<","<<p.y<<"}\n"
    <<"  |Subjects Positions : Ball{"<<_pos.x<<","<<_pos.y<<"} ; Brick{"
    <<brick->x()<<","<<brick->y()<<"}\n";
  if (std::abs(p.x) > std::abs(p.y)) {
    bounceHorizontal();
    fixOverlap(this);
  } else {
    bounceVertical();
    fixOverlap(this);
  }
}


// -------------------------------------------------------------------------
// Bonus Implementation
// -------------------------------------------------------------------------
Bonus::Bonus(float x, float y, char letter, ALLEGRO_COLOR color)
  : DynamiqueEntity({x, y}),
    CollisionCircle(&this->_pos, &_radius),
    _velocityY(0.5f), // Initial vertical velocity
    _radius(10.0f),  
    _letter(letter),  // Letter representing the bonus
    _active(false),  // Initially inactive
    _color(color) {} 

Bonus::~Bonus() {}

void Bonus::activate() {
  _active = true;
}

void Bonus::update(float deltaTime) {
  if (!_active) return;

  // Simulate falling with gravity
  _pos.y += _velocityY * deltaTime;

  // Apply gravity
  _velocityY += 300.0f * deltaTime;

  // Check if it hits the ground
  if (_pos.y >= groundLevel()) {
    _pos.y = groundLevel(); // Clamp to ground level
    _active = false;
    onGroundCollision();
  }
}

void Bonus::render() const {
  if (!_active) return;

  // Render the capsule shape and letter
  al_draw_filled_circle(this->x(), this->y(), _radius, _color);
  al_draw_textf(al_create_builtin_font(), _color, this->x(), this->y(), ALLEGRO_ALIGN_CENTER, "%c", _letter);
}

float Bonus::groundLevel() const {
  return DISPLAY_HEIGHT - 5.0f; // tout en bas
}

void Bonus::onGroundCollision() {
  std::cout << "Bonus with letter " << _letter << " hit the ground.\n";
  // Handle ground collision logic (e.g., deactivate bonus)
}

char Bonus::getLetter() const {
  return _letter;
}

bool Bonus::isActive() const {
  return _active;
}

void Bonus::collisionDetected(Entity*, tpl) {
  // À remplir si tu veux une interaction avec paddle, sinon vide pour l’instant
}

void Bonus::deactivate() {
  _active = false;
}
