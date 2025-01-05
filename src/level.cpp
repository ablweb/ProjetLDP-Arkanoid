#include "level.hpp"
#include "env.hpp"  // Ajouté pour connaître le type Env ( debugging)

#include <memory>
#include "entity.hpp"
#include "utils.hpp"
#include <cmath> 

LevelManager::LevelManager()
  : _palette(std::make_shared<TestRectangle>(tpl{250, 480}, 100, 20, COLORS::RED)), // Position et taille initiales 
    _ball(std::make_shared<Ball>(tpl{250, 250}, 10, 10, COLORS::WHITE, 5.0f)),      // Balle
    score(0),                                                                    // Score initial
    _lives(3) {} // Initialisation du score à 0
  
LevelManager::~LevelManager() {}

void LevelManager::addScore(int points) {
  _score += points;
}

int LevelManager::getScore() const {
  return _score;
}

void LevelManager::movePaletteRigth() {
if (_palette->x() + _palette->width() / 2 < 500) { // Vérifie les limites de l'écran
    _palette->move(10, 0);
  }}
void LevelManager::movePaletteLeft() {
  if (_palette->x() - _palette->width() / 2 > 0) { // Vérifie les limites de l'écran
    _palette->move(-10, 0);
  }}

void LevelManager::update() {

  // Collision entre la balle et la raquette
  auto ball = getBall();      // Supposez une méthode pour accéder à la balle
  auto paddle = getPalette(); // Supposez une méthode pour accéder à la raquette

  if (ball->y() + ball->height() / 2 >= paddle->y() - paddle->height() / 2 && ball->x() > paddle->x() - paddle->width() / 2 && ball->x() < paddle->x() + paddle->width() / 2) {

    // Calcul de la position relative de l'impact
    float impactX = ball->x() - (paddle->x() - paddle->width() / 2);

    // Calcul de l'angle alpha (en degrés) en fonction de l'impact
    float alpha = 30 + 120 * (1 - impactX / paddle->width());

    // Conversion de l'angle en radians
    float alphaRadians = alpha * M_PI / 180.0f;

   // Calcul du vecteur direction
    float dx = std::cos(alphaRadians);
    float dy = -std::sin(alphaRadians);
    float length = std::sqrt(dx * dx + dy * dy);
    ball->setDirection(dx / length, dy / length);
  }

  // Déplacer la balle
  ball->move();

  // Gestion des collisions avec les murs
  if (ball->x() - ball->width() / 2 <= 0 || ball->x() + ball->width() / 2 >= 500) {
    ball->bounceHorizontal();
  }
  if (ball->y() - ball->height() / 2 <= 0) {
    ball->bounceVertical();
  }

<<<<<<< Updated upstream
  // Si la balle tombe en bas de l'écran
  if (ball->y() > 500) {
    loseLife();
    if (_lives > 0) {
      // Réinitialise la balle si des vies restent
      ball->setPosition(tpl{250, 250});
      ball->setDirection(0, -1);
    } else {
      // Si plus de vies, arrêter le jeu  (encore a faire )
=======
// -------------------------------------------------------------------------
// Level Loader
// -------------------------------------------------------------------------
LevelLoader::LevelLoader(Env* environment) : env(environment) {
  registerLevelFiles();
}
LevelLoader::~LevelLoader() {}

size_t LevelLoader::levelCount() { return levelDatas.size(); }
bool LevelLoader::isEmpty() { return levelDatas.empty(); }

void LevelLoader::load(size_t levelIndex, Level* lvl) {
  if (levelIndex >= levelCount()){
    throw std::runtime_error("No level to load");
  }
  std::cerr<<"|Level::load -> Loading custom level {"<<levelNames[levelIndex]<<"}\n";
  lvl->bricks = std::make_unique<BrickHolder>(levelDatas[levelIndex]);
  lvl->paddle = std::make_unique<Paddle>(PADDLE_CONST::spawnPosition,PADDLE_CONST::normalColor);
  lvl->ball = std::make_unique<Ball>(BALL_CONST::spawnPosition,BALL_CONST::baseSpeed, BALL_CONST::baseRadius, BALL_CONST::normalColor);
  lvl->env = env; 

}

void LevelLoader::loadDefault(Level* lvl) {
  std::cerr<<"|Level::loadDefault -> Loading default level\n";
  lvl->bricks = std::make_unique<BrickHolder>();
  lvl->paddle = std::make_unique<Paddle>(PADDLE_CONST::spawnPosition,PADDLE_CONST::normalColor);
  lvl->ball = std::make_unique<Ball>(BALL_CONST::spawnPosition, BALL_CONST::baseSpeed, BALL_CONST::baseRadius, BALL_CONST::normalColor);
  lvl->env = env; 
                              
  // Generate default level (tringular shape)
  using namespace BRICK_CONST;
  for (uint col = 1;col <= 12;++col) {
    int colorIndex = 50;
    uint start = 7;
    uint end = start - (col <= (12+1)/2 ? col - 1 : 12 - col);
    for (uint row = start;row >= end;--row) {
      lvl->bricks->addBrick({row, col, (colorType)colorIndex, none});
      colorIndex += 10;
>>>>>>> Stashed changes
    }
  }
   // for score --------
  for (auto it = bricks.begin(); it != bricks.end();) {
    auto& brick = *it;
    if (ball->x() + ball->width() / 2 > brick->x() - brick->width() / 2 && ball->x() - ball->width() / 2 < brick->x() + brick->width() / 2 && ball->y() + ball->height() / 2 > brick->y() - brick->height() / 2 && ball->y() - ball->height() / 2 < brick->y() + brick->height() / 2) {
      // Détruire la brique
      it = bricks.erase(it); // Supprime la brique de la liste

      // Ajoute des points au score
      addScore(10);

      // Fait rebondir la balle
      ball->bounceVertical();
    }else {
      ++it; // Passe à la brique suivante
    }
  }

}

void LevelManager::loseLife() {
  _lives -= 1;
}

std::shared_ptr<TestRectangle> LevelManager::getPalette() const {
  return _palette;
}

std::shared_ptr<Ball> LevelManager::getBall() const {
  return _ball;
}

std::vector<std::shared_ptr<TestRectangle>> LevelManager::getBricks() const {
  return _bricks;
}