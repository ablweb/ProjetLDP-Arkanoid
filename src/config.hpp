#ifndef CONFIG_H
#define CONFIG_H

#include <sys/types.h>

constexpr int DISPLAY_WIDTH = 672;
constexpr int DISPLAY_HEIGHT = 896;
constexpr float SIDE_MARGIN = 24.0;
constexpr float TOP_MARGIN = 120.0;
constexpr float GAME_SIDE_MARGIN = 14.0;
constexpr float GAME_TOP_MARGIN = TOP_MARGIN*2;
constexpr int FONT_SIZE = 15;
constexpr const char* FONT_PATH = "resources/fonts/SourceCodePro-ExtraBold.ttf";
constexpr const char* LEVELS_DIR = "resources/levels/";
constexpr double FRAME_RATE = 1.0 / 60;

extern bool LOG;
extern uint LOG_LEVEL;

extern bool MOUSE;

#endif
