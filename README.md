# Janus
A 2D game inspired by Minecraft and RimWorld that I am working on over summer break as a college student.
Janus is the Roman god of beginnings, transitions, duality, doorways, and endings.
I wish to create a game where the player is placed in a world with nothing to defend for themselves, trying to build
and craft items and structures to survive while also slowly uncovering the deep history of the past generations who
crossed dimensional barriers discovering multiple other worlds.
## Features
As the game is currently in its very early stages, there is not much yet.
Here are some features that I have implemented so far.
All the graphics currently in the game are temporary.

- Chunk-based procedurally generated worlds (of infinite size!)
- Multiple different types of tiles (grass, stone, water, sand)
- Separated game update and rendering systems
- ~~Random ticks and scheduled ticks (much like Minecraft)~~
  - Removed this feature while refactoring to ecs
- Breaking and placing blocks

## Features  Planned
Although I am unsure whether I will reach the stage of actually creating a full game, here are my
plans on this game.

- Greater variety of blocks
- Player inventory system
- Crafting
- Greater building system
- Enemies and turrets
- Randomly generated structures
- Biomes

## Dependencies
This project uses [Raylib](https://github.com/raysan5/raylib) 
for most of the graphics handling, and [EnTT](https://github.com/skypjack/entt)
for the ECS system. This project also uses the [GLM](https://github.com/g-truc/glm) 
library for certain math-related calculations.