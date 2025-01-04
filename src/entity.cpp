#include "entity.hpp"

#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <allegro5/drawing.h>
#include <cmath>

#include "config.hpp"
#include "utils.hpp"

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
  _pos.x+=dx;_pos.y+=dy;
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
  // Code generere par GPT-3.5 : 
  // write a methode for a object CollisionRect that detects collision with
  // another object CollisionCircle. Using distance based detection
  float oX=other->colX(), oY=other->colY(), oRad=other->colRadius(),
        halfWidth=colHeight()/2, halfHeight=colHeight()/2,
        thisX=colX(), thisY=colY();
  float closestX = std::max(oX-halfWidth,std::min(thisX, oX+halfWidth));
  float closestY = std::max(oY-halfHeight,std::min(thisY, oY+halfHeight));
  colPoint.x = closestX; colPoint.y = closestY;

  double distance = std::sqrt(std::pow((closestX-thisX),2)+std::pow((closestY-thisY),2));

  return distance<=oRad;
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
  // Code generere par GPT-3.5 : 
  // write a methode for a object CollisionCircle that detects collision with
  // another object CollisionRect. Using distance based detection
  float oX=other->colX(), oY=other->colY(),
        halfWidth=other->colWidth()/2, halfHeight=other->colHeight()/2,
        thisX=colX(), thisY=colY(), thisRad=colRadius();
  float closestX = std::max(oX-halfWidth,std::min(thisX, oX+halfWidth));
  float closestY = std::max(oY-halfHeight,std::min(thisY, oY+halfHeight));
  colPoint.x = closestX;colPoint.y = closestY;

  double distance = std::sqrt(std::pow((closestX-thisX),2)+std::pow((closestY-thisY),2));

  return distance<=thisRad;
}

// -------------------------------------------------------------------------
// Brick
// -------------------------------------------------------------------------
Brick::Brick(tpl position,
             BRICK_CONST::colorType brickType,
             BRICK_CONST::bonusType bonusType,
             BrickHolder* holder)
  : Entity(position),
    CollisionRect(&this->_pos,&_w,&_h),
    _type(brickType),_bonus(bonusType),_holder(holder) {
  _col = BRICK_CONST::typeToColor.at(_type);
  switch (brickType) {
    case BRICK_CONST::silver:
      _life = 2;
      break;
    case BRICK_CONST::gold:
      _life = -1;
      break;
    default: _life = 1;
      break;
  }
}
Brick::~Brick() {
}

void Brick::destroy() {
  if (_holder != nullptr) {
    _holder->removeBrick(this);
  } else {
    delete this;
  }
}

float Brick::width() const { return _w; }
float Brick::height() const { return _h; }
BRICK_CONST::colorType Brick::getType() const { return _type; }
ALLEGRO_COLOR Brick::color() const { return _col; }

void Brick::collisionDetected(Entity*,tpl) {
  if (_life!=-1) {
    _life -= 1;
  }
  if (_life==0) {
    destroy();
  }
}
// -------------------------------------------------------------------------
// BrickHolder
// -------------------------------------------------------------------------
BrickHolder::BrickHolder(std::vector<BRICK_CONST::Param> bricksData) {
  for (const auto& b:bricksData) {
    addBrick(b);
  }
}
BrickHolder::BrickHolder() {}
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
    this));
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
void Paddle::collisionDetected(Entity*,tpl) {}

// -------------------------------------------------------------------------
// Ball
// -------------------------------------------------------------------------
Ball::Ball(tpl position, float speed, float radius, ALLEGRO_COLOR color)
  : DynamiqueEntity(position),
    CollisionCircle(&this->_pos,&_rad),
    _dx(0),_dy(0),_spd(speed),_rad(radius),_col(color),isAttached(true) {} 
Ball::~Ball() {}

void Ball::move(float dx, float dy ) {
  _pos.x+=dx;_pos.y+=dy;
  // check if collision with left or right walls
  if ((_pos.x-_rad)<(SIDE_MARGIN)) {
    // Move the ball inside the game area
    float overLap = (float)SIDE_MARGIN-(_pos.x-_rad);
    move(overLap, 0);
    bounceHorizontal();
  } else if ((_pos.x+_rad)>(DISPLAY_WIDTH-SIDE_MARGIN)) {
    // Move the ball inside the game area
    float overLap = (_pos.x+_rad)-(float)(DISPLAY_WIDTH-SIDE_MARGIN);
    move(-overLap, 0);
    bounceHorizontal();
  }
  // check if collision with top or bottom walls
  if ((_pos.y-_rad)<(TOP_MARGIN) ) {
    // Move the ball inside the game area
    float overLap = (float)TOP_MARGIN-(_pos.y-_rad);
    move(0, overLap);
    bounceVertical();
  } else if ((_pos.y+_rad)>(DISPLAY_HEIGHT-TOP_MARGIN)) {
    // Move the ball inside the game area
    float overLap = (_pos.y+_rad)-(float)(DISPLAY_HEIGHT-TOP_MARGIN);
    move(0, -overLap);
    bounceVertical();
  }
}
void Ball::bounceHorizontal() { _dx = -_dx; }
void Ball::bounceVertical() { _dy = -_dy; }
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
void Ball::handleCollision(Paddle* paddle, tpl p) {
  // Calcul de la position relative de l'impact
  float impactX = p.x - (paddle->x()-paddle->width()/2);
  // Calcul de l'angle alpha (en degrés) en fonction de l'impact
  float alpha = 30 + 120 * (1 - impactX / paddle->width());
  // Conversion de l'angle en radians
  float alphaRadians = alpha * M_PIf / 180.0f;

  // Calcul du vecteur direction
  float dx = std::cos(alphaRadians);
  float dy = -std::sin(alphaRadians);
  float length = std::sqrt(dx * dx + dy * dy);
  setDirection(dx / length, dy / length);
}
void Ball::handleCollision(Brick* brick, tpl p) {
  // float bx = brick->x(), by = brick->y(),
  //      hw = brick->width()/2, hh = brick->height()/2;
  std::cerr<<"|COL:\n";
  std::cerr<<p.x<<"|"<<p.y<<"\n";
  std::cerr<<x()<<"|"<<y()<<"\n";
  std::cerr<<brick->x()<<"|"<<brick->y()<<"\n";
  float distX = p.x-brick->x();
  float distY = p.y-brick->y();
  std::cerr<<"|Dist:\n";
  std::cerr<<distX<<"|"<<distY<<"\n";
  if (std::abs(distX) > std::abs(distY)) {
    std::cerr<<"   Horizontal side\n";
    bounceHorizontal();
  } else {
    std::cerr<<"   Vertical side\n";
    bounceVertical();
  }
}
void Ball::collisionDetected(Entity* other, tpl p) {
  if (const auto paddle = dynamic_cast<Paddle*>(other)) {
    handleCollision(paddle, p);
  } else if (const auto brick = dynamic_cast<Brick*>(other)) {
    handleCollision(brick, p);
  }
};
