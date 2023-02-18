# Alien vs. Zombie

# Sample Output
![Screenshot_23](https://user-images.githubusercontent.com/123613860/218414554-cf010b02-75ad-461f-ba4a-a2daf7fe4288.png)

![Screenshot_25](https://user-images.githubusercontent.com/123613860/218422820-84a232c1-67b9-4e93-b88d-e8c9c3c28b84.png)


# Introduction of this game


Alien vs. Zombie is basically a role-play game that needs the path-planning and strategy of the players. In this game, players must defeat all the zombies that are hunting for the alien itself in order to achieve victory for this game. Therefore, set a trail and prepare the way to protect the alien from those zombies as every way matters!


There are some mysterious game objects such as rocks, arrow power, pod attack power and others that can help the alien become stronger in order to attack the zombies. 


YouTube link to our [Video Demo_Part 1](https://www.youtube.com/watch?v=klaqKXWuF1o) and [Video Demo_Part 2](https://youtu.be/kB-EhNpGuqU).


## Compilation Instructions

## For First Part
g++ firstPart.cpp -o firstPart

## For main.cpp (Second Part)
g++ main.cpp -o main -lwinmm


## User Manual
### Introduction of Game Objects and Zombies
- Alien (A) was initialized to 100 life and 0 attack. 
- Health pack (h) can help to add 20 life to alien.
- Pod attack (p) will attack the nearest zombie with 10 damage.
- Bomb attack (B) will deduct 20 life to alien / zombie if either of them step on it.
- Rock (r) will hide any power object / empty space beneath it.
- Arrow power [^v<>] will change the direction of alien movement and add 20 attack to the alien.
- Zombies' life and attack [Maximum number is 9] will be set to randomized.

### Game Guide
1. Users need to choose 'y' -YES / 'n'-NO For edit the settings of the game.
2. If users press 'n', then the setting of game will remain as default.
3. If users press 'y', then user need to input number of zombie which does not more than 9 zombies.
4. Users need to input the row and column of the game map with specific rules such as only odd number accepted / minimum number for row and column is 5 / Maximum number of row and column is due to users' Windows display size.
5. Game Map will auto generated with an alien at center of game map randomly placement of game objects / zombies.
6. The maxmimum life for the alien will be always initialized 100 and 0 attack. The zombies' life / health / attack range will be randomize.
7. Users can using [WASD] key on keyboard to control the movement of the alien.
8. Users can press [P] key to change the direction of game object: [Arrow] to change the next movement of the alien. 
9. Users can press [F1] key to call out help function if users face any doubts.
10. Users can press [F2] key to save the progress of current game by key in prefer filename with filename extension [.txt].
11. Users can press [F3] key to load the saved game progress by key in the filename without filename extension [.txt].
12. Users can press [F4] key to refresh the screen when users face any game map layout problem.
13. Users can press [F5] key to restart the game with current settings of the game which is same number of row / column / quantity zombies.
14. Users can press [F6] key to exit the game.
15. If users accidentally exit the game, this game will also autosave your latest progress of your game.
16. Users can press 'y' in the start page of this game when AutoSync dialog box pop out. 



## Progress Log


- [Part 1](PART1.md)
- [Part 2](PART2.md)


## Contributors


- Low Kai Yan 1211101699
- Nicholas Tiow Kai Bo 1211102398







