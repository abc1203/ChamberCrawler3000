# ChamberCrawler3000

ChamberCrawler3000 is a rogue-like console game that is playable on linux. The player can select the playerrace of their character along with the difficulty level, before heading to a dungeon of 5 floors. 

<img src="https://github.com/abc1203/ChamberCrawler3000/blob/main/img/cc3k_demo.png">

The player's objective is to escape floor 5 of the dungeon while collecting as much gold as possible. The exit of each floor is invisible and inaccessible initially, and will only appear and become visible when the player acquires the compass. The compass is hidden inside a random enemy, meaning that the player needs to eliminate the enemies to acquire the compass.

## Playable Actions
The player can reach/move to one tile of their vicinity. The directions are no, so, we, ea, nw, ne, sw, se.  
To **Move**:           '{direction}'  
To **Attack**:         'a {directioin}'  
To **Drink Potion**:   'u {direction}' (player can see the type of potion they have already drank)  
To **Re-select player race or difficulty level**: 'r'  
To **Quit the game**:  'q'  

## In-game Objects
**@**: Player (Green)  
**W/V/N/M/D/X/T**: Enemies (Red)  
**G**: Treasure (Gold)  
**P**: Potion (Purple)  
**B & C**: Barriersuit & Compass (Blue)  

## How to Set up
1. In a Linux environment, go to ```ChamberCrawler3000/src```
2. Update & generate the exe file using ```make```
3. Start the game using ```./cc3k```
4. Good luck and have fun on your journey!
