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
* Box2D debugDraw (optional)
* 2D tile map framwork
  * Tile Hexa, Hexa iso, Square, Square Iso
  * loading from json file/stream/object
* Entity system
  * Customisable Components
  * Customisable Systems
  * Customisable Entity
  * Entity manager
  * Application


Requirements
------------

* SFML 2.0 +
* Box2D 2.3 + (optional)
* cpp-utils : json parser (for map framwork, https://github.com/Krozark/cpp-utils)
* C++11 compiler


Map
===

Only one parameter as been change in the json file :

```
{
    "name" : "test",
    "geometry" :
    {
        "name" : "Hexa/HexIso/Square/SquareIso",    //here is the change
        "size" : 50.0
    },
    "layers" :
    [
      {
            "content" : "tile", //type of the layer (grid here)
            "z" : 1, //zbuffer (default is 0)
            "static" : true, //default is false
            "datas" :  //texture informations
            [
                {
                    "img" :"media/img/ground2.png", //texture to apply
                    "x" : 0, //start point x
                    "y" : 0, //start point y
                    "width" : 100, //number of lines
                    "height" : 100 //number of collumns
                }
                //... other textures can be specify if needed
            ]
        }

    ]
}
```

Then another file is use for the trees:

```
{
    "layers" : 
    [
        {
            "content" : "sprite", //type of the layer
            "z" : 3, //z buffer
            "datas" : 
            [
                {
                    "x" : 2, // line emplacement
                    "y" : 4, // row emplacement 
                    "ox" : 0.5, //center point (default is 0.5) relative to the image size
                    "oy" : 1.0, //center point (default is 1) relative to image size
                    "img" : "media/img/tree/tree1.png" //skin file
                },
                //.... other trees
            ]
        }
    ]
}
```


Hexagonal grid
---------
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/Hexa.png" alt="Hexagonal grid" width="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/HexaIso.png" alt="Hexagonal isomitric grid" width="350px">

Square grid
-----------

<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/Square.png" alt="Square grid" width="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-utils/master/screen/SquareIso.png" alt="Square isomitric grid" width="350px">
