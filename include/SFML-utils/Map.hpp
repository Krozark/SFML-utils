#include <SFML-utils/map/es/Components.hpp>
#include <SFML-utils/map/es/Entity.hpp>
#include <SFML-utils/map/es/Systems.hpp>

#include <SFML-utils/map/geometry/Geometry.hpp>
#include <SFML-utils/map/geometry/GeometryHexa.hpp>
#include <SFML-utils/map/geometry/GeometryHexaIso.hpp>
#include <SFML-utils/map/geometry/GeometrySquare.hpp>
#include <SFML-utils/map/geometry/GeometrySquareIso.hpp>
#include <SFML-utils/map/geometry/GeometrySquareIsoStaggered.hpp>
#include <SFML-utils/map/geometry/GeometrySquareStaggered.hpp>

#include <SFML-utils/map/Configuration.hpp>

#ifdef SFML_UTILS_BUILD_MODULE_MAP_DATABASE
#include <SFML-utils/map/DatabaseMapLoader.hpp>
#endif

#include <SFML-utils/map/JsonMapLoader.hpp>
#include <SFML-utils/map/JsonSpriteLoader.hpp>
#include <SFML-utils/map/Layer.hpp>
#include <SFML-utils/map/Map.hpp>
#include <SFML-utils/map/MapManager.hpp>
#include <SFML-utils/map/MapMetaData.hpp>
#include <SFML-utils/map/MapViewer.hpp>
#include <SFML-utils/map/Tile.hpp>
#include <SFML-utils/map/VLayer.hpp>
#include <SFML-utils/map/VMapLoader.hpp>

