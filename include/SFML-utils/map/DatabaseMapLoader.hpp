#ifndef SFUTILS_MAP_DATABASEMAPLOADER_HPP
#define SFUTILS_MAP_DATABASEMAPLOADER_HPP

#include <SFML-utils/map/VMapLoader.hpp>

#include <SFML-utils/map/models/MapModel.hpp>

namespace sfutils
{
    namespace map
    {
        class DatabaseMapLoader : public VMapLoader
        {
            public:
                DatabaseMapLoader(MapModel::pointer& map);

                virtual ~DatabaseMapLoader();

            protected:

            private:
                MapModel::pointer _map;

                virtual std::unique_ptr<MetaArea> _loadArea(int x,int y,Map* const map) override;
                virtual Map* _loadMap() override;

        };
    }
}
#endif
