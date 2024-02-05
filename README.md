# ChamberCrawler3000

ChamberCrawler3000 is a rogue-like console game that is playable on linux. The player can select the playerrace of their character along with the difficulty level, before heading to a dungeon of 5 floors. 

<img src="https://github.com/abc1203/ChamberCrawler3000/blob/main/img/cc3k_demo.png">

The player's objective is to escape floor 5 of the dungeon while collecting as much gold as possible. The exit of each floor is invisible and inaccessible initially, and will only appear and become visible when the player acquires the compass. The compass is hidden inside a random enemy, meaning that the player needs to eliminate the enemies to acquire the compass.

## Playable Actions
The player can reach/move to one tile of their vicinity. The directions are no, so, we, ea, nw, ne, sw, se._
To **Move**:           '{direction}'_
To **Attack**:         'a {directioin}'_
To **Drink Potion**:   'u {direction}' (player can see the type of potion they have already drank)_
To **Re-select player race or difficulty level**: 'r'_
To **quit the game**:  'q'_

## In-game Objects
**@**: Player (Green)_
**W/V/N/M/D/X/T**: Enemies (Red)_
**G**: Treasure (Gold)_
**P**: Potion (Purple)_
**B & C**: Barriersuit & Compass (Blue)_

## How to Set up
1. In a Linux environment, go to ```ChamberCrawler3000/src```
2. Update & generate the exe file using ```make```
3. Start the game using ```./cc3k```
4. Good luck and have fun on your journey!
