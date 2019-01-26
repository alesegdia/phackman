# Phack Man

*Game design document.*

# 1. Brief

Tower defense roguelike with pacman design elements about a maintenance guy on a ship trying to clean up the lower cargo bays with the help of a gun, a few gadgets and some placeable machines.

# 2. Summary

The **INV4D-312** is a transport spaceship carrying The Crucible, an unknown alien device. The spaceship was just intercepted by an alien race classified as the **Zenytp-3D3**. Take control of **Phack Man**, a janitor and the only survivor in the **INV4D-312** in his mission to clear all the floors of the cargo bay from these little bastards.

Phack Man's gameplay resembles in some ways to the good ol’ Pacman mechanics, but using cargo bays of a ship infected by aliens as the playground where you can place gadgets at the walls and the floor to be able to transport **The Crucible** through the cargo bays safely.

# 3. Game flow

The player has to move an alien device, The Crucible, among floors to the last one to secure it. **The Crucible** always start with zero energy, so you have to fill using power nodes in order to be able to move it. Once **the crucible** is filled, hordes of enemies will start to come from the spawners directly towards the player and the energy will start to deplete over time, and when the energy level reaches zero, the player loses. The player has to find where the **gate** to the next floor is. Once it's found, fill **the crucible** with energy and start moving it to the gate to the next floor. The player speed will decrease when carrying The Crucible.

Normally, the game flow for a level starts with the player near **the crucible** and with the nodes kept in the previous floor. Then the player will start to investigate the maze to find the gate to the next floor. The player will encounter enemies that will need to overcome by building turrets. Once the gate is found, the player ideally will build a secure path from **the crucible** to the gate. When the player is confident that the path is safe, then the player will power the crucible and carry it with **Lock&Stock**, and hence won't be able to use it during the transport. The crucible's energy will start to deplete and if the player reaches the gate with the crucible

# 4. Gameplay mechanics

## Spawners

Each spawner has a fixed number of enemies and type of it assigned and will respawn them continually when they die. *TBD*: maybe could have a bar of spawns so when the bar is empty it can't spawn anymore until the bar is refilled in time again, or maybe we could just set a very high spawn rate, gameplay wise.

At first some enemies will follow the players and others don't, depending on the kind of enemy, but when **The Crucible** is powered and the player starts to carry it to the gate, the spawners capacity and rate will increase enormously, and all the enemies will chase the player.

Enemies could be spawned all at the start, and/or from spawning buildings. This way, the player might need to inhibit these spawners, via destroying them or via another gadget (the inhibitor).

## Infection system

Floor and wall tiles can be infected, normal or powered. When an alien enemy steps over a tile, it gets infected over time, unless the tile is secured. When a tile is infected, you can not use the floor or walls to place gadgets because of the infection. If there was a previously placed gadget when a normal tile turns to infected, the gadget will just be destroyed.

## Enemies

There will be different enemy behaviours defined, but this is still in development many of them can suffer changes or be removed.

1. **Infected walker**. Wanders the maze randomly infecting everything at
2. **Curious Chaser**. Wanders the maze randomly until the distance to the player is less than a threshold distance. Then it chases the player until the threshold distance is surpassed.
3. **Speedy**. Wanders the maze chasing the player. Movement is quick from node to node, but there is a resting time in each node.
4. **Insatiable Chaser**. Wanders the maze chasing the player independently from the distance to it.
5. **Unpleasant Snitch**. Wanders the maze randomly and if it detects the player in its range of vision, chases it. Each snitch also notifies other snitches about the player position. This could be improved by notifying infected walkers too.

Enemies can shoot, or might be buildings too, this is to be defined better.

## Lock&Stock

Phack Man can shoot with his two miniguns Lock & Stock (L&S from now on), but only when the battery is charged. In order to charge the battery, the player needs to collect power nodes (like Pacman power pills). Battery charge will decrease over time even if the player is not using them. These guns have several parameters like rate, power or bullet speed, but can be also raycasted. TBD.

## Nodes

There are nodes used as resources in the game. In each level there will be a fixed number of nodes that can be obtained, or maybe a probability, and when each enemy drop a type of node, the number of nodes spawned increases or the probability decreases. The types of nodes are the following:

| Name | Usage | Obtainability |
|:---:|:---:|:---:|
| IndustryNode | **Build** constructions and place gadgets | Spread around the map |
| ScienceNode | **Enhance** gadgets and constructions | Dropped by enemies |
| PowerNode | **Recharge** L&S batteries | Rarely spread around the map |

## Gadgets

The player will acquire construction nodes in the stage and can spend them in using gadgets. Some of them can be upgraded in the midstage so that parameters like power, rate, strike, time-to-live can change. Gadgets fall in these categories:

* Buildings
* Consumable
* Drones (not clear if it'll be in)

### Buildings

You can place those and repair them with construction nodes.

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| Laser | Countdown explosion and branches explosion like in bomberman | Power |
| FixedTurret | Cheap but can shoot in one direction | Advance, SimultaneosulyPlaced |
| OmniTurret | Not so cheap but can shoot at every direction | Advance, SimultaneosulyPlaced |
| (?) MovableTurret | Deals damage to enemies passing over it | TimeToLive, SimultaneosulyPlaced |
| SnailDevice | Slows nearby enemies | SlowPower |

### Consumable

like mines or bombs in a bomberman way

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| Spread Bomb | Countdown explosion and branches explosion like in bomberman | Advance |
| Spread Mine | Explodes on contact | Advance, SimultaneosulyPlaced |
| Electric field | Deals damage to enemies passing over it | TimeToLive, SimultaneosulyPlaced |
| Remote Bomb | Explodes on detonation, deals high damage in single block | Power |

## Drones (not clear if it'll be in)

Follows player and provides enhancements. When the player is reached by an enemy, a drone explodes instead of dying the player. The enemy or enemy bullet would explode as well as the enemy. The number of drones is TBD, but the decision ranges from 1 to 3.

| Name | Description | Upgrades |
|:---:|:---:|:---:|
| BarrierDrone | Deploys a barrier which explodes on enemy contact. | RegenTime, Capacity |
| PulseDrone | Shoots pulse bullets to enemies in front | ShootBack, DualShoot |

# 5. Interface

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

# 6. Map

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

# A.1. Possible upgrades

These upgrades won't probably be implemented, but they will be kept here for the record.

* **Lock&Stock mods**. These mods can change the rate, speed, or damage of L&S shoots.
* **Weaknesses and resistances** so that a certain mod can be strong against certain type of enemies and weak against others.
* **Vary enemy colors** to determine its toughness or Weakness&Resistances.
* Bosses

# A.2. Map generation

After doing a little of research, I found a really interesting [pacman-like maze generator idea](http://pacman.shaunew.com/play/mapgen/) by Shaun Williams, part of his [Pac-Man tribute project](http://pacman.shaunew.com/). As the author says, the doc is incomplete in details, but the base is **use tetromino shapes to aid on map generation**. The map will be generated following this very principle.

## Method overview
**Rectangle-made shapes** will be used to build a layout so that we can use the connected edges of those shapes to build the path. Later, this will be rendered into a tile map for its direct use in the game.

A **shape** model will be represented as a 2D matrix of integers. The generation will be supplied with a list of models in order to place them randomly in a blank layout. This way, we are shaping different distributions of the same shapes. Relating this to game progress, a different set of shapes can be used in each floor of the spaceship.

A resume of the needed steps (prone to changes):

* **Generate** a layout from a list of *connected shapes*.
* **Mirror** the resulting layout horizontally.
* **Trace** the path given the layout using shape edges.
* **Render** the path to a tile map and use in the game!

## Generate layout

Having a list with the wanted shapes, those can be placed in a blank canvas using different strategies. The one I will use is fairly simple: pick a random shape and place it to the left, as in tetris but shapes going left instead of down. The row will be selected randomly.

Currently, if no more pieces fit the blank canvas, an error is thrown and the app is stopped, but we could resolve this by making the map wider and/or trying to use other random row.

## Extract path

To extract the path, the matrix needs to be scaled x3, so that we can thick the shapes by one tile and get our needed walkable path of 2 tiles wide. Finally, a border will be added and filled with walls, so that we can use the more external paths that are only 1 tile wide.
