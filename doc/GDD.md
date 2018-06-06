# Phack Man


# 1. Brief

Tower defense roguelike with pacman design elements about a maintenance guy on a ship trying to clean up the lower cargo bays with the help of a gun, a few gadgets and some placeable machines.

# 2. Summary

## 2.1. Plot
The **INV4D-312** is a transport spaceship that was just intercepted by an alien race classified as the **Zenytp-3D3**. Take control of **Phack Man** in his mission to clear all the floors of the cargo bay from these little bastards.

## 2.2. Basic gameplay

Phack Man's gameplay resembles the good ol’ Pacman mechanics. The map is a generated maze and entities can move freely through it. The objective is to find the key node to open the stairs for the next floor and proceed to go to the next floor. There will be infinite floors.

Floor and wall tiles can be infected, normal or secured. When an alien enemy steps over a tile, it gets automatically infected, unless the tile is secured. When a tile is infected, you can not use the floor or walls to place gadgets because of the infection. If there was a previously placed gadget, this will just be destroyed.

Phack Man can shoot with his two miniguns Lock & Stock (L&S from now on), but only when the battery is charged. In order to charge the battery, the player needs to collect power nodes (like Pacman power pills). Battery charge will decrease over time even if the player is not using them. These guns have several parameters like rate, power or bullet speed, but can be also raycasted. TBD.

There are a few nodes that can be found in the game:

| Name | Usage | Obtainability |
|:---:|:---:|:---:|
| IndustryNode | **Build** constructions and place gadgets | Spread around the map |
| ScienceNode | **Enhance** gadgets and constructions | Dropped by spawners |
| PowerNode | **Recharge** L&S batteries | Rarely spread around the map |
| CleanseNode | **Clean** infection | Dropped by enemies |
| KeyNode | **Open** stairs to the next floor | One per floor |

## 2.3. Gadgets

The player will acquire construction nodes in the stage and can spend them in using gadgets. Some of them can be upgraded in the midstage so that parameters like power, rate, strike, time-to-live can change. Gadgets fall in these categories:

### 2.3.1. Buildings

You can place those and repair them with construction nodes.

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| Laser | Countdown explosion and branches explosion like in bomberman | Power |
| FixedTurret | Cheap but can shoot in one direction | Advance, SimultaneosulyPlaced |
| MovableTurret | Deals damage to enemies passing over it | TimeToLive, SimultaneosulyPlaced |
| SnailDevice | Slows nearby enemies | SlowPower |

### 2.3.2. Consumable

like mines or bombs in a bomberman way

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| Spread Bomb | Countdown explosion and branches explosion like in bomberman | Advance |
| Spread Mine | Explodes on contact | Advance, SimultaneosulyPlaced |
| Electric field | Deals damage to enemies passing over it | TimeToLive, SimultaneosulyPlaced |
| Remote Bomb | Explodes on detonation, deals high damage in single block | Power |

### 2.3.3. Drones

Follows player and provides enhancements. When the player is reached by an enemy, a drone explodes instead of dying the player. The enemy or enemy bullet would explode as well as the enemy. The number of drones is TBD, but the decision ranges from 1 to 3.

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| BarrierDrone | Deploys a barrier which explodes on enemy contact. | RegenTime, Capacity |
| PulseDrone | Shoots pulse bullets to enemies in front | ShootBack, DualShoot |

## 3. Interface

* The player will have an active gadget/building shown in the UI that can be changed by cycling.
* The player control consists of the following input:
* The player can advance the path by pressing the arrow keys.
* If the pressed key direction is not allowed in the current position, the player will advance following its current facing when pressing this key until it is possible to turn.

| Action | Keyboard | Gamepad |
|:---:|:---:|:---:|
| Movement | Arrows | D-Pad |
| Shoot L&S | Space | B |
| Use gadget | C | Y |
| Gadget menu | V | X |
| Cycle gadget | Z/X | L/R |

When the player presses the 'Use gadget' button, time will stop and you'll be able to mount gadgets in nearby floor or wall tiles.

## 4. Map

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

## 5. Enemies

There will be defined a few behaviors, but probably **only one will be implemented** (the easiest) for time economy reasons.

1. **Boring Walker**. Wanders the maze randomly with no meaning of life.  
2. **Curious Chaser**. Wanders the maze randomly until the distance to the player is less than a threshold distance. Then it chases the player until the threshold distance is surpassed.
3. **Speedy**. Wanders the maze chasing the player. Movement is quick from node to node, but there is a resting time in each node.
4. **Insatiable Chaser**. Wanders the maze chasing the player independently from the distance to it.
5. **Unpleasant Snitch**. Wanders the maze randomly and if it detects the player in its range of vision, chases it. Each snitch also notifies other snitches about the player position. This could be improved by notifying boring walkers too.

Enemies can shoot, or might be buildings too, this is to be defined better.

#### Spawning

Enemies could be spawned all at the start, and/or from spawning buildings. This way, the player might need to inhibit these spawners, via destroying them or via another gadget (the inhibitor).

Spawners could spawn enemies near it or just anywhere, and is the player objective to inhibit all the spawners in order to get the key to travel to the next floor.

## A.1. Possible upgrades

These upgrades won't probably be implemented, but they will be kept here for the record.

* **Lock&Stock mods**. These mods can change the rate, speed, or damage of L&S shoots.
* **Weaknesses and resistances** so that a certain mod can be strong against certain type of enemies and weak against others.
* **Vary enemy colors** to determine its toughness or Weakness&Resistances.
* Bosses

## A.2. Map generation

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
