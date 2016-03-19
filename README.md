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
* CEGUI 0.8.x (optional)
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


Load from file
---------------

Only one parameter as been change in the json file to change the grid geometry:

```
{
    "map" :
    {
        "name" : "test",
        "tile" :
        {
            "geometry" :"SquareIsoStaggered", //here is the change

            "size" : 50.0
        },
        "area" :
        {
            "width" : 10,
            "height" : 15
        },

        "layers" :
        [
            {
                "z-buffer" : 0,
                "content-type" : "tile",
                "static" : true
            },
            {
                "z-buffer" : 2,
                "content-type" : "sprite_ptr",
                "static" : false
            }

        ]
    }
}

```

Then another file is use for the trees:

```
{
    "areas" :
    [
        {
            "name" : "area fill-rect",
            "position-x" : 0,
            "position-y" : 0,
            "layers" :
            [
                {
                    "z-buffer" : 0,
                    "data" : 
                    [
                        {
                            "texture" : "media/img/ground3.png",
                            "position-x" : 0, //default is 0
                            "position-y" : 0, //default is 0
                            "width" : 5, //default is Areasize.width
                            "height" : 4 //default is Areasize.height
                        }
                    ]
                },
                {
                    "z-buffer" : 2,
                    "data" :
                    [
                        {
                            "position-x" : 4,
                            "position-y" : 1,
                            "texture" : "media/img/tree/tree1.png"
                        },
                        {
                            "position-x" : 3,
                            "position-y" : 3,
                            "texture" : "media/img/tree/trees.png",
                            "texture-rect" : //default is the entire texture (in pixel)
                            {
                                "left" : 311, 
                                "top" : 74,
                                "width" : 45,
                                "height" : 97
                            }
                        },
                        {
                            "position-x" : 1,
                            "position-y" : 1,
                            "texture" : "media/img/tree/tree3.png",
                            "texture-center" : //same as default values (relative to the subrect used)
                            {
                                "left" : 0.5,
                                "top" : 1.0
                            }
                        }
                    ]
                }
            ]
        }
    ]
}
```
