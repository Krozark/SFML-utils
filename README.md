SFML Utils
==========

It provide some adds to the SFML library including:

* Resource manager
* Event manager with callback
* A Gui
  * Container
    * Frame
  * Button
    * Text Button
    * Sprite Button
  * Sprite
  * Label
  * Layout
    * Vertical
    * Horizontal
* 2D tile map framwork
  * Tile Hexa [Iso], Square [Iso], Staggered [Iso]
  * loading from json file
  * possibility to make your own mapLoader
* 2D Map Editor
  * Saved in database
* Entity system
  * Customisable Components
  * Customisable Systems
  * Customisable Entity
  * Entity manager
  * Application
* Box2D debugDraw (optional)
* CEGUI GuiManager (optional)
  * convert events from SFML to cegui


Requirements
------------

* SFML 2.0 +
* Box2D 2.3 + (optional)
* cpp-utils : json parser (for map framwork, https://github.com/Krozark/cpp-utils)
* C++11 compiler


Map
===

<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/V0.3.png" alt="Hexagonal grid" width="350px">

Hexagonal grid
---------
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/Hexa.png" alt="Hexagonal grid" width="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/HexaIso.png" alt="Hexagonal isomitric grid" width="350px">

Square grid
-----------

<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/Square.png" alt="Square grid" width="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/SquareIso.png" alt="Square isomitric grid" width="350px">


Square Staggered grid
----------------------
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/SquareStaggered.png" alt="Square Staggered grid" width="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/SquareIsoStaggered.png" alt="Square Iso Staggered grid" width="350px">


Map Editor (optional)
======

Requirement:
-----------
* all the previous depndencies
* map framwork
* CEGUI 0.8.x (Editor optional)
* cpp-ORM : Cpp ORM (https://github.com/Krozark/cpp-ORM)
* lua 5.1
* luabind (https://github.com/Krozark/luabind-deboostified)




<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/Editor.png" alt="Editor" width="850px">
