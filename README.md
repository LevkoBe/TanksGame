# TanksGame
Tanks
Main features:
1. The player starts on the empty square map.
2. The player controls the tank with a keyboard.
3. The tank can fire a projectile on a specific button pressed.
4. There is a second tank (or even several), which is controlled by the bot.
5. Bot shoots the player whenever he directly sees the player.
6. Bot randomly moves on the map (or some traveling logic can be applied).
7. On projectile hit both the bot and player take damage.
8. When the player or bot runs out of health points, they are destroyed. If the player tank is destroyed, the player loses.
9. The player wins if his tank is the last on a map.

As yet I'm new to UML diagrams, for this game I created the whole bunch of them:
- [Usecase diagram](https://github.com/LevkoBe/TanksGame/blob/master/README.md#usecase-diagram)
- [State diagram](https://github.com/LevkoBe/TanksGame/blob/master/README.md#state-diagram)
- [Class diagram](https://github.com/LevkoBe/TanksGame/blob/master/README.md#class-diagram)
- [Sequence diagram](https://github.com/LevkoBe/TanksGame/blob/master/README.md#sequence-diagram)
- [Activity diagram](https://github.com/LevkoBe/TanksGame/blob/master/README.md#activity-diagram)

and, maybe most importantly, -
- Sequence diagram

#### Let's start review of all the diagrams I created, and the first will be...
### Usecase diagram
Usecase diagrams are generally good to show who are actors in a program, which usecases we have, and which are available to each actor. And my diagram is not an exception:

![usecase diagram](https://res.cloudinary.com/dbkotg0js/image/upload/v1701681555/github/tank_games/UCD_2_rfmkwe.svg)

On the diagram we can see that the main actors are following:
- **User**: player that is able to set everything needed (level, mode, characteristics) before the tank battle begins, and then hit the button 'Play' to start the game itself
- **UserTank**: appears when the battle is started, is moving on the screen, can rotate and shoot
- **BotTank**: comes to destroy the UserTank, may have multiple instances. In standard mode it just moves up-down-left-right, and shoots
These are actors, and corresponding to them usecases. Also we can see on the diagram that tanks can explode, and we can guess that when the only tank that is left is UserTank, User wins.

#### The next will be...
### State diagram
#### that shows states the system can be in

![State diagram](https://res.cloudinary.com/dbkotg0js/image/upload/v1701681432/github/tank_games/StD_4_vnanvf.svg)

Here you can see that there're two main states:
- **Starting** - window, that'll have buttons
    - Play: for starting the game
    - choose level: to make the game harder or easier
    - set characteristics: to make the tanks stronger or weaker
    - choose mode: to make the game slower or faster
    - review achievements: to see what you've already got
    - exit: to close the game
- **GameRun** state, to which you can go with 'Continue', or 'Start' buttons on the starting window, in which you can:
    - rotate and move your tank
    - shoot missiles
    - pause the game that moves you to another substate:
- Paused game
    - allows you to take a rest
    - can be ended by clicking 'go to menu'
    - or continuing playing the game, that moves you back to
- GameRun state
    - when you win or lose you go to to the
- Finished game state
    - where you can go to menu, or,
    - depending on whether you won, or lose:
        - restart the current game, or
        - play the next level


#### The next comes...
### Class diagram
#### that represents the static structure of my system

![State diagram](https://res.cloudinary.com/dbkotg0js/image/upload/v1701687679/github/tank_games/CD_3_r5cohu.svg)

Here you can see that there're four main classes:
- **GameRun**, that has all the objects used in the games. It may include the tanks, their projectiles, walls etc.
  - keeps records of what objects are in the game and their positions
  - check on collisions and whether the game should be over
  - handle the commands from user, already processed by Renderer, speaking of which:
- **Renderer**, that is responsible for
  - showing messages on the starting window
  - processing user's commands (clicking keyboard and mouse buttons, maybe later also scrolling the wheel)
  - drawing Background of the game
  - showing GameObjects:
- **GameObject**, any object in the game
  - has its position to be renderable
  - may have velocity and acceleration
- **Tank**, GameObject with certain characteristics
  - also has health
  - also can shoot
 
separately from classes, I have enumerated type:
- ProjectileType, that represents possible projectile types


#### Prelast diagram will be...
### Sequence diagram
#### that depicts the interactions between program's components over time
![Sequence diagram](https://res.cloudinary.com/dbkotg0js/image/upload/v1701690137/github/tank_games/SeD_1_fbvewq.svg)
#### Here's a breakdown of the diagram:

1. **Initialization:**
   - Player chooses level, sets characteristics, and selects game mode.
   - Player hits "Play" button.

2. **Game Setup:**
   - GameRun initializes the map and instructs Renderer to draw walls.
   - UserTank and BotTank instances are created, and their visuals are rendered.

3. **Game Loop:**
   - **Player's Moves:**
     - Player can move the tank with buttons (</^/>)
     - Renderer conveys input to GameRun for tank movement and shooting (projectile creation).
         - When projectile is shot:
         - it moves, checks collisions, and applies damage.
         - Game state transitions based on win or lose conditions.

   - **Bot's Moves:**
     - BotTank autonomously moves and shoots projectiles.
     - Projectiles move, check collisions, and apply damage; game state is rechecked.

4. **Game States:**
   - System transitions between Running, Pause, Win, or Lose states during gameplay.
   - Renderer continuously renders game elements.

5. **Game Termination:**
   - Player can choose to exit the game.  

#### And the last one:
### Activity diagram
#### that represents the action flow in my program

![State diagram](https://res.cloudinary.com/dbkotg0js/image/upload/v1701693395/github/tank_games/ActivityD_1_tjlam0.svg)
Alternatively, you can review a little bit more detailed activity diagram at [the link](https://res.cloudinary.com/dbkotg0js/image/upload/v1701677750/github/tank_games/ActionD_1_wujkwv.svg)
Explanations to the diagram:

1. Starting Window:
    - The process begins with the starting window.
    - The player has options to set characteristics, choose the game mode, select a level, and review achievements.
2. Player Choices:
    - The player has the choice to play or exit the game.
    - If the player decides to play, the system enters the gameplay loop.
3. Gameplay Loop:
    - The game involves repeated actions until it's over:
        - Move: Tank movement during gameplay.
        - Shoot: Firing projectiles.
        - Rotate: Rotating the tank.
        - Pause: Option to pause the game.
4. Game Over:
    - If the game is won, the player progresses to the next level.
    - If the game is lost, the player has the option to play again.
5. Menu Options:
    - After completing a level or deciding not to continue, the player can access menu options.
    - The player may choose to exit the game or proceed to the next level.
6. Cycle Continuation:
    - The cycle continues, allowing the player to repeat the gameplay loop or exit the game.

  ### That's all about diagrams. Hope they help to understand the program! And the only part that is left after creating them is to implement everything!

