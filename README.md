# MultiPlayer Pong

The pong game, in multiplayer, using sfml

Dependencies
---
- SFML (2.5.0)
- Qmake
- QtCore
- Box2D

Compiling
---

To compile the server, execute `qmake server.pro` then `make`. The server is now accessible to `bin/server/pong`.

To compile the client, execute `qmake client.pro` then `make`. The client is now accessible to `bin/client/pong`. You might need to move the resources needed by the program (font and music) to the binary folder.
