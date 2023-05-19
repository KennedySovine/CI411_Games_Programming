**University of Brighton 
Computer Games**

# **CI411 - Introduction to Game Programming 2022-23**
 Coursework 2: C++ SDL Game

Module Leader: David Dorrington

Student: Kennedy Sovine <br>
 Date: May 14, 2023

#

Table of Contents

[Table of Contents](#_Toc134962498)

[Introduction](#_Toc134962499)

[Game Design](#_Toc134962500)

[Type and Style of Game / Genre](#_Toc134962501)

[Screen Layout and Format](#_Toc134962502)

[Control System](#_Toc134962503)

[Gameplay & Core Rules](#_Toc134962504)

[Level Designs](#_Toc134962505)

[Implementation](#_Toc134962506)

[Game Objects Diagram](#_Toc134962507)

[Program Structure](#_Toc134962508)

[Player Controlled Objects / Character](#_Toc134962509)

[NPCs](#_Toc134962510)

[Objects](#_Toc134962511)

[Interface](#_Toc134962512)

[Game Management](#_Toc134962513)

[Testing, Problems & Solutions](#_Toc134962514)

[Critical Review](#_Toc134962515)

[Conclusion](#_Toc134962516)

[Bibliography](#_Toc134962517)

[Graphical Assets](#_Toc134962518)

[Audio Assets](#_Toc134962519)

[Appendices](#_Toc134962520)

[How to play / game Walkthrough](#_Toc134962521)

# Introduction

This document is a detailed overview of the development of my SDL game. This document covers the design decisions for the game, how ideas and techniques were implemented, testing, and a review of my own work.

The 'Game Design' section covers the design of the game. This includes the inspiration for the game and every design choice that went into it. It is essentially the idea behind the game.

The 'Implementation' section covers the parts of the game. This includes the NPCs, the PC, the game's management, and the program's structure. The implementation is the next stage of the game's development as the idea discussed in 'Game Design' is realized and put into a physical form.

In 'Testing, Problems, and Solutions,' the document details any issues that occurred during development. This will also include solutions that were or were not implemented and solutions that may or may not have been found.

Lastly, the end of the document contains the bibliography and appendices, which includes a walkthrough and gameplay description for the game.

# Game Design

This section details the design decisions made for the game. The game is an arcade-style shooter inspired by the mechanics of classics such as _'Space Invaders.'_ This game is called '_Prism of Lights.'_

## Type and Style of Game / Genre

The genre of the game is an arcade-style shooter. The conventions of these types of games are low-res sprites, along with simple mechanics of 'point-and-shoot'. Since these games were first created for arcades, they are meant simply for entertainment and quick play. There is no story nor deeper meaning behind them like modern video games. Center of the pa

 The game's visual style is pixelated and inspired by contemporary fantasy. The world and scene are visually basic, not having any complex colors or details that would be hard to see in a low-resolution setting. The theme of the levels are bushy grass lands.

## Screen Layout and Format

The game's resolution is 1920 x 1080, which is standard 1080 resolution. The entire screen is the play area, and the view is top-down. The game is fixed, and the level itself not moving around. The entire left-to-right part of the screen is in use.

In the bottom left of the screen, there is a points display. Next to it is the current level and how many NPCs are left for the player to kill.

## Control System

The methods of control are WASD and the mouse. WASD is used for movement controls, whereas the mouse is used for aiming to shoot.

| Control | W | A | S | D | First Mouse Button/Space Bar |
| --- | --- | --- | --- | --- | --- |
| Action | Move Forward | Move to the Left | Move Backwards | Move to the Right | Shoot |

## Gameplay & Core Rules

The intended gameplay style is a simple point-and-shoot, where the player shoots the enemies and can earn power-ups by moving around the map.

The goal is to get through 10 waves of enemies. A congratulatory message will appear if the player wins, and the game will end. The player can only win if they destroy all the enemies without losing all their health. The player loses if the enemies can attack them and reduce their health to 0. The enemies can only attack if they get too close, meaning the player needs to kill the closest enemies first to ensure their safety. This introduces an element of strategy.

The player must shoot and kill all enemies to proceed to the next wave. In every wave, there is a chance that a power-up will spawn. The powerups are blue, yellow, red, and white prisms, all with their own special ability.

## Level Designs

The intended method of where the items would spawn in was meant to be random, but that could not be implemented within the timescale. Therefore, though not depicted in the screen plans, the 4 items are randomly placed around the dark orange area of the map.

![](RackMultipart20230519-1-inoot7_html_c4e1e2973dfdabca.png)

**Screen plan of Level 1**

![](RackMultipart20230519-1-inoot7_html_7c2ed06614b5aa57.png)

**Screen plan of Level 2**

![](RackMultipart20230519-1-inoot7_html_591db26696905621.png)

**Screen plan of Level 3**

![](RackMultipart20230519-1-inoot7_html_5a1872e258f9e1eb.png)

**Screen plan of Level 4**

![](RackMultipart20230519-1-inoot7_html_b9206679a31a048f.png)

**Screen plan of Level 5**

![](RackMultipart20230519-1-inoot7_html_64a3eaa23bad10b.png)

**Figure 3: Screenshot of the GUI in the bottom left-hand corner**

# Implementation

The implementation section is all about how the ideas and concepts behind the game were implemented through code inside the program. Using techniques that were learned in class, the ideas were efficiently added to the program.

The program's codebase is the code provided during class. This was an efficient choice due to the code base already having many of the functions and features desired for the game.

## Game Objects Diagram

![](RackMultipart20230519-1-inoot7_html_2313815ef77f58a0.png)

**Figure 4: Screenshot of 'GameObject.h' Class Diagram**

## Program Structure

The program is structured in the basic C++ way. There are 'cpp' files, which are the main substance of the program. There is a Main.cpp file that is the executor of the program. It makes the program run. For every '.cpp' file, except for Main.cpp, there is an equivalent '.h' file. These files are header files which contain the function declarations. They allow the '.cpp' files to only contain the actual code of the programs.

The files inside the program are: Game.cpp, Game.h, GameObjects.cpp, GameObjects.h, Main.cpp, Level.cpp, and Level.h.

Some of the key functions of the program are the main function, which runs the game, the function that checks the game states, and the function that updates the GUI. All of those are the bones of the game: without any of those, there would be no game.

Figure 6 shows the core game loop of the game. Essentially, the game is a loop of player input, updating the game based on those inputs, updating information given to the user through the display, and checking the game states to see if the game is over. The program flows though this loop consistently until the game is over, either by being quit or the player winning/losing.

| ![](RackMultipart20230519-1-inoot7_html_2645f67d7296292c.png) **Figure 5: Screenshot of the main function in 'Main.cpp'**
 | ![](RackMultipart20230519-1-inoot7_html_7872381003a98850.png) **Figure 6: Core game loop of the game**
 |
| --- | --- |

## Player Controlled Objects / Character

- Player is controlled by the WASD keys.
- Key states are alive and dead, with some variables being its health and shot power.
- PC can shoot, obtain power-ups (prisms), and gain points.

![](RackMultipart20230519-1-inoot7_html_bac495b03ee62c3.png)

**Figure 7: Screenshot of the PlayerCharacter functions**

## NPCs

- There are 3 kinds of NPCs: Regular, Tank, and Fast
- Regular NPCs move at a standard speed, Tank NPCs have more health, and Fast NPCs move quicker and can often take the player by surprise.
- They move in a screen-crawl fashion, moving from one side of the screen to the other. They shoot downwards towards the player, but never directly at them.

![](RackMultipart20230519-1-inoot7_html_b9e0773dd3809507.png)

**Figure 8: Screen crawl method for the NPCs**

## Objects

- The only objects in the game are the prisms.
- The red prism gives the player health, the blue prism gives the player extra damage, the yellow prism gives the player the ability to instantly kill any enemy, and the white prism gives the player 1000 points.

![](RackMultipart20230519-1-inoot7_html_57e07d40facfa3c7.png)

**Figure 9: Collision code for if the player interacts with an object. Each case specifies which type of item it is.**

## Interface

- The purpose of the interface is to let the player know what level they're on, how many NPCs are left, and how many points they have.

![](RackMultipart20230519-1-inoot7_html_64a3eaa23bad10b.png)

**Figure 10: Screenshot of the Interface on the bottom left-hand corner of the screen.**

![](RackMultipart20230519-1-inoot7_html_a575aa70e38f3323.png)

**Figure 11: Screenshot of the updateGUI method in 'Game.cpp'**

## Game Management

- The player wins when they defeat all the enemies in the level without dying. The player loses when their health reaches 0.
- The player earns points by defeating enemies and their objective is to defeat all the enemies as quick as possible.
- The items, player, NPCs, and levels are all being managed. The code is constantly checking for if an item needs to be spawned and if the ability granted by the item needs to go away; if the player is losing health or is dead; if the NPCs are dead and staying within bounds.
- The replay-ability of the game comes from the randomness of the spawning of the items.

![](RackMultipart20230519-1-inoot7_html_8b8478ab85de2275.png)

**Figure 12: Screenshot of the function 'resetAllObjects'. This resets all objects, including NPCs whenever a level is won/lost**

# Testing, Problems & Solutions

| **Priority** | **Problem** | **Solution** | **Implemented** |
| --- | --- | --- | --- |
| High | Enemies not properly advancing to the next line. Instead, they are going to the first line and proceeding onwards. | Remove the first enemy on each line and increase the LHS barrier so they properly advance. | Solution has been implemented within timescale. |
| Med | Prisms (items) are not spawning properly. ---Prisms spawn properly, but some issues still arise. If there is an object where the prism is meant to spawn (Bullet, pc, etc.), the prism will spawn in the top left corner in the walls. | Don't make the item's location random. Make a random one spawn in every 15s in render.Solution for the inaccessible items is to have items respawn after a fixed amount of time not being collected. | Solution has been implemented within timescale / Need to research problem. ---Solution has been implemented within timescale. |
| High | Fast NPCS are not spawning in. Their health-bars are visible but the textures aren't loading in, even though they are supposed to. Tank NPCs are not spawning in at all with no health bars nor visual of them at all. | Change the texture file (DID NOT WORK). I have no idea how to fix this issue. | Need to further research problem. Solution could not be found within the timescale. |
| Medium | On loading of a level after the first time, the NPCs don't move from left to right. Instead, some move right to left. | Resetting the NPCs' xVelocity to 0 when calling "resetobjects" | Solution has been implemented within timescale. |
| High | Some terrain blocks on the right-hand side are not properly spawning in. | Add more terrain blocks to the array (DID NOT WORK) I have no idea how to fix this issue. By all intents and purposes, this shouldn't be happening. | Need further research into the problem |

#

# Critical Review

The design and implementation of the game are well done because it is an original idea. It was successfully converted into a simpler idea that would better fulfill the assessment criteria. The first level of the game is playable and winnable. It is simple to comprehend and easy to pick up for a first-time player.

Implementation could've been improved by figuring out why some assets weren't loading in properly. Due to this, the game after the first level is unplayable, but a solution could not be found within the timescale. Implementation could've also been improved through better references for ideas of the game being found. Lastly, it could've been improved through further knowledge of game mechanics and C++ techniques. If I knew more about SDL and could effectively read the documentation of it, I feel I could improve the game and figure out why some aspects are not working seemingly for no reason.

I could've made the idea more fleshed out. Originally, I wished to make a platformer, but that idea did not fit the brief appropriately, so I discarded the method of gameplay idea. If I were able to do a platformer-style retro game, and knew how to do vertical or horizontal scrolling, I would have implemented it to improve the gameplay.

Through this process, I have learned how to make a retro-style arcade shooter. With this, I have also learnt how to properly detect collision detection and how to do level maps effectively in C++.

# Conclusion

In development, I learned key concepts of difficulty scaling and proper gameplay experience. There is a fine line between making levels more difficult as you progress and making progress impossible. In the type of game I decided to make, there is no objective progress. Essentially, everything resets every level, making no progress to the character itself. The only thing that changes are the type of enemies you encounter and how many. This makes no scaling factor for the player. It is the type of game you play with a quarter in an arcade, which is the type of game we were tasked to create.

-
#

# Bibliography

## Graphical Assets

| **Image** | **name** | **Used for** | **Sourced from** |
| --- | --- | --- | --- |
| ![](RackMultipart20230519-1-inoot7_html_5c6afbc8e4b07d72.png) | Bush\_background.png | Background for all levels | Modification of bush image. (user17446225, n.d.) |
|
 ![](RackMultipart20230519-1-inoot7_html_b99831ea617bf2b7.jpg)
 | Bush.png | Tile for shrubbery border | Freepik (user17446225, n.d.) |
| ![](RackMultipart20230519-1-inoot7_html_8dd60edfa09b4aa0.png) | Blue\_prism.png | Blue prism item | Created by author in Procreate. |
| ![](RackMultipart20230519-1-inoot7_html_9b6645939f058b9f.png) | Red\_prism.png | Red prism item | Created by author in Procreate. |
| ![](RackMultipart20230519-1-inoot7_html_2a69a58321f0c7e8.png) | White\_prism.png | White prism item | Created by author in Procreate. |
| ![](RackMultipart20230519-1-inoot7_html_3d8f1c1aafbedf35.png) | Yellow\_prism.png | Yellow prism item | Created by author in Procreate. |
| ![](RackMultipart20230519-1-inoot7_html_310dbff9412627cc.png) | GameOverScreen.png | Game over screen | Given materials during classtime. |
| ![](RackMultipart20230519-1-inoot7_html_5cd1065ce4d072a5.png) | Pawn\_Purple.png | Player-Character | Given materials during classtime. |
| ![](RackMultipart20230519-1-inoot7_html_92a08acd1df33bef.png) | Circle\_Red.png | Normal NPCs | Given materials during classtime. |
| ![](RackMultipart20230519-1-inoot7_html_a794eedb6d0b8be2.png) | Circle\_Blue.png | Tank NPCs | Given materials during classtime. |
| ![](RackMultipart20230519-1-inoot7_html_6d8fbed4236babdd.png) | Circle\_Purple.png | Fast NPCs | Given materials during classtime. |

## Audio Assets

| **Sound** | **Used for** | **File & Source** |
| --- | --- | --- |
| Background Music | Background for all Levels (Renda, 2021) | levelMusic.mp3(Renda, 2021) |
| Player Attack | PC Attack | PCAttack.mp3 (Free Gun Sound Effects, n.d.) |
| Explosion | NPC hit | Explosion.wav Given material during classtime |

#

# Appendices

## How to play / game Walkthrough

Playing '_Prism of Lights_' is simple. Once you enter the level, you can click and point to shoot with your mouse or press space to shoot straight up. Use WASD to move. Pick up prisms as they spawn to get buffs. Destroy all of the enemies throughout 5 levels to beat the game.
