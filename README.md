SimpleGame
==========

A simple PSP game using OSLib, made for a class project.

Building
--------
Set up a PSP Toolchain on a Linux machine or VM using [pspdev/psptoolchain](https://github.com/pspdev/psptoolchain), then just run `make` in your local copy of this repository.

Usage
-----
Copy `img` and `EBOOT.PBP` to `/PSP/GAME/SimpleGame`. Activate your CFW and fire up the game from the Game menu.

Playing the game
----------------
Move with the **D-Pad** or **Thumbstick**, firing at ghosts with **Square**.  
Switch to the utterly broken secondary weapon with **Triangle**.  
Use **L** or **R** to enter Strafe mode, where you move slower and your hitbox is shown.

Shoot evil, trigger-happy space ghosts for points. Pick up cinnamon rolls for bonus points.

You only die if your hitbox (the area highlighted with white when you Strafe) is hit, so as long as you can squeeze that tiny area past any obstacles, you're fine. Use this and the slowed movement from Strafe mode to your advantage to dodge bullets, Matrix-style!

Planned Features (maybe)
------------------------
* Graze Score - get points for /barely/ squeezing past enemies
* More interesting enemy attack patterns
* Highscore List
* Sound Effects
* Music (maybe)

Credits
-------
* Programming, Art, Idea - uppfinnarn
* QA, Most of the actual game design - lissilingon

My sister walked in on me working on the prototype for this, so I showed her an alpha build of the game (from before I even had collission checking). I expected her to just put it down and walk away immediately, but instead, she sat down next to me, occupying half of my chair, and started coming with ideas and finding things that didn't work. And it all actually made the game WAY better than it'd ended up otherwise.
