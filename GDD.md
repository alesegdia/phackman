# Phack Man

## Table of Contents

0. [Disclaimer](#disclaimer)
1. [Plot](#plot)
2. [Gameplay](#gameplay)
3. [Objectives](#objectives)
4. [Input](#input)
5. [Gadgets](#gadgets)
6. [Map](#map)
7. [Enemy behaviors](#enemy-behaviors)
8. [Possible upgrades](#possible-upgrades)

### Appendix
1. [Map generation](#map-generation)

---

## 0. Disclaimer

This document is prone to modifications and will probably be changed during development.

## 1. Plot
The **INV4D-312** is a transport spaceship that was just intercepted by an alien race classified as the **Zenytp-3D3**. Take control of **Phack Man** in his mission to clear all the floors of the cargo bay from these little bastards.

## 2. Gameplay
Phack Man's gameplay resembles the good ol’ Pacman mechanics. The map is a generated maze and entities can move freely through it. Phack Man can shoot with Lock & Stock, his loyal twin miniguns, among other gadgets he will find in his path.

## 3. Objectives

The main and needed-to-advance objective is to collect the key and open the stairs to the next floor. Some secondary objectives for the player are:

* Clear the floor from aliens.
* Collect all nodes scattered around the map in the same way as Pac-Man has to collect all balls.

The completion of these secondary objectives are rewarded with points, that could be used later to buy and enhance gadgets in the next level.

## 4. Input
The player control consists of the following input:
<center>

| Key        | Action           |
|:----------:|:----------------:|
| ←↑→↓       | Movement         |
| z/x        | Cycle gadget     |
| 1-9        | Gadget shortcut  |
| Space      | Use gadget       |

</center>
The player can advance the path by pressing the arrow keys. If the pressed key direction is not allowed in the current position, the player will advance following its current facing when pressing this key until it is possible to turn.

## 5. Gadgets

The way to obtain gadgets is still to be polished. The player needs credits in order to buy and enhance gadgets. They could be extracted from a vending machine present in the map, or maybe in each mid-level stage. Gadgets fall in the following categories:

* Buildings (turrets, lasers).
* Placeable items (mines).
* Allied AI-controlled actors (drones, robots).
* Guns (Lock&Stock basically).
* Utility gadgets (running shoes, invisibility, repair tool, hook).

The enhancement of gadgets could impact the number of placed objects at the same time, the power, the time-to-live or the cooldown.

#### Lock&Stock

Can shoot

#### Mines

Upgradable:

* Number of simultaneously placed mines.
* Power.
* Cooldown.

#### Lasers

* Number of simultaneously placed lasers.
* Power.

#### Drones

Can set N wandering nodes?

#### Static turrets

Can be placed in walls.

#### Hook

Lets you quickly travel by launching the hook to the front-facing wall and getting you quickly to it.

## 6. Map
The map is a generated maze with progressive size depending on the floor. We can think of the map like a node graph where nodes are placed at maze positions where the player can turn 90 degrees.

```
# # # # # # # #
# o         o #     # - solid block
#   # # # #   #     o - map node
# o     o #   #
#   # #   #   #
# o     o   o #
# # # # # # # #
```

The walkable path will be 2 tiles width, instead of 1 like in Pac-Man. The walls of the map can have a minimum of 1 tile width. The generation will be defined later.

## 7. Enemy behaviors

There will be defined a few behaviors, but probably **only one will be implemented** (the easiest) for time economy reasons.

1. **Boring Walker**. Wanders the maze randomly with no meaning of life.  
2. **Curious Chaser**. Wanders the maze randomly until the distance to the player is less than a threshold distance. Then it chases the player until the threshold distance is surpassed.
3. **Speedy**. Wanders the maze chasing the player. Movement is quick from node to node, but there is a resting time in each node.
4. **Insatiable Chaser**. Wanders the maze chasing the player independently from the distance to it.
5. **Unpleasant Snitch**. Wanders the maze randomly and if it detects the player in its range of vision, chases it. Each snitch also notifies other snitches about the player position. This could be improved by notifying boring walkers too.

Enemies can shoot, or might be buildings too, this is to be defined better.

## 8. Possible upgrades

These upgrades won't probably be implemented, but they will be kept here for the record.

* **Lock&Stock mods**. These mods can change the rate, speed, or damage of L&S shoots.
* **Weaknesses and resistances** so that a certain mod can be strong against certain type of enemies and weak against others.
* **Vary enemy colors** to determine its toughness or Weakness&Resistances.

### A.1. Map generation

After doing a little of research, I found a really interesting [pacman-like maze generator idea](http://pacman.shaunew.com/play/mapgen/) by Shaun Williams, part of his [Pac-Man tribute project](http://pacman.shaunew.com/). As the author says, the doc is incomplete in details, but the base is **use tetromino shapes to aid on map generation**. The map will be generated following this very principle.

#### Method overview
**Rectangle-made shapes** will be used to build a layout so that we can use the connected edges of those shapes to build the path. Later, this will be rendered into a tile map for its direct use in the game.

A **shape** model will be represented as a 2D matrix of integers. The generation will be supplied with a list of models in order to place them randomly in a blank layout. This way, we are shaping different distributions of the same shapes. Relating this to game progress, a different set of shapes can be used in each floor of the spaceship.

A resume of the needed steps (prone to changes):

* **Generate** a layout from a list of *connected shapes*.
* **Mirror** the resulting layout horizontally.
* **Trace** the path given the layout using shape edges.
* **Render** the path to a tile map and use in the game!

#### Generate layout

Having a list with the wanted shapes, those can be placed in a blank canvas using different strategies. The one I will use is fairly simple: pick a random shape and place it to the left, as in tetris but shapes going left instead of down. The row will be selected randomly.

Currently, if no more pieces fit the blank canvas, an error is thrown and the app is stopped, but we could resolve this by making the map wider and/or trying to use other random row.

#### Extract path

To extract the path, the matrix needs to be scaled x3, so that we can thick the shapes by one tile and get our needed walkable path of 2 tiles wide. Finally, a border will be added and filled with walls, so that we can use the more external paths that are only 1 tile wide.
