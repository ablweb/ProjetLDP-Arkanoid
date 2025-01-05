# ProjetLDP-Arkanoid
Famous Arkanoid game written in c++ using the Allegro library

# Installation

To build and start game:

    make
    ./arkanoid


# Option
- -l --log | Enable Logging
- -m --mouse | Enable Mouse

# How to play

Break all bricks to win, don't let the ball fall, you have 3 lives, each time the ball falls you lose a life.
Silver bricks need to be hit 2 times to break.
Gold bricks are unbreakable.

## Controls
    D / P      - Move paddle right  |  R           - Reload level files
    A / Q      -  Move paddle left  |  RIGHT ARROW -     Previous level
    SPACE      -   Launch the ball  |  LEFT ARROW  -         Next level
    ESCAPE     -     Quit the game  |

# Custom Level Formating

The custom levels are stored in resources/levels/
In resources you can find a "levelTemplate.json", this can help create custom levels.

The level JSON format should be an array of objects, each representing a brick in the level. Each tile must contain the following fields
   - 'row' (integer): The row number of the tile (0 <= row <= 7).
   - 'col' (integer): The column number of the tile (0 <= col <= 13).
   - 'color' (string): The color of the tile. Allowed values: 'white', 'orange', 'cyan', 'green', 'red', 'blue', 'magenta', 'yellow', 'silver', 'gold'.
   - 'bonus' (string): The bonus on the tile. Allowed values: 'none', 'laser', 'bigger', 'capture', 'slow', 'interruption', 'player'.
Example:

    [
        {"row": 0, "col": 0, "color": "cyan", "bonus": "none"},
        {"row": 1, "col": 1, "color": "green", "bonus": "laser"}
    ]

Make sure all values are within the allowed ranges and use valid strings for color and bonus.

# Dependencies

This project requires the following dependencies:

 - Allegro 5: A cross-platform game programming library.

# Libraries

This project usses the JSON For Modern C++ library 
[JSON](https://github.com/nlohmann/json)
