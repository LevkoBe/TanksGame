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
- Class diagram
- Activity diagram

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







