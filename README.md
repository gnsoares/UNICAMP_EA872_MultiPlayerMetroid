# Building

To build just run `mkdir build && cd build`, then `cmake ../` and, finally, `make`. Note that you need to have `SDL`, `boost`  and `g++` installed in your system.

# Playing

**Singleplayer** just run `./metroid`.

**Multiplayer (as host)**: to create a room, just run `./metroid -g multi -i (your IPv4 adress) -p host -nY` (Y = number of players that will join the game)

**Multiplayer (as client)**: to join a room, just run `./metroid -g multi -i (your IPv4 adress) -p client -h (host's IPv4 adress)`

**Commands**: Use space to jump and and left and right arrows to move Samus across the room. To shoot, press `1` and the arrow pointing to the direction you wish to shoot at. To change rooms, shoot the door and walk across it.

# Documentation

To see the code structure just run `doxygen Doxyfile`, then go to `/doc/html` and there, run `(your browser name, eg. firefox) index.html`. Not that you need to have `doxygen` installed in yout system.
