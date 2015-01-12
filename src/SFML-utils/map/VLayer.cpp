#include <SFML-utils/map/VLayer.hpp>

namespace sfutils
{
    namespace map
    {
        VLayer::VLayer(int z) : _z(z)
        {
        }

        VLayer::~VLayer()
        {
        }

        int VLayer::z()const
        {
            return _z;
        }
    }
}
