# Hawaii Snake Project
![Project Icon](https://github.com/arturgesiarz/Snake_Hawaii/blob/master/public/photos/menu.png)

## About

This desktop game is similar to the top Snake game, in which we move with arrows and collect fruits just like in this one. The game is written entirely in C++ using the SFML library.

## How the Project Works

The game welcomes you with a welcome screen in which you have to press the START button to proceed, then the game starts.


During the game we eat fruit to collect as many points as possible. There is a special sound when we eat fruit (as well as when we fail).


The counter of the eaten fruit is located at the top.


When you lose, your score is displayed and you have the option to play again or to quit the game.

## Before Download

1.  Make sure you have downloaded the library SFML v2.5.1 library on your C drive, appropriately named C:SFML.
2.  Make sure you have environment variables to C:\SFML, C:\SFML\lib, C:\SFML\bin, C:\SFML\include.
3.  Ensure you have downloaded MinGW and added it to the environment variable

## Getting Started

To run the Hawaii Snake, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/arturgesiarz/Snake_Hawaii.git
  
2. **Go to directory**:
    ```bash
    cd Snake_Hawaii

3. **Run Application**:
   ```bash
    g++ -I C:\SFML\include src\Main.cpp src\Game.cpp src\Button.cpp src\Screen.cpp include\Button.h include\GameParametres.h include\Screen.h include\Snake.h -mwindows -o Main.exe -L C:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system
    ./Main.exe
