#ifndef SFUTILS_MAP_VLAYER_HPP
#define SFUTILS_MAP_VLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace sfutils
{
    namespace map
    {
        class Map;

        class VLayer
        {
            public:
                VLayer(const VLayer&) = delete;
                VLayer& operator=(const VLayer&) = delete;

                VLayer(const std::string& type,int z,bool isStatic,bool isVisible);
                virtual ~VLayer();

                virtual void sort() = 0;

                int getZ()const;
                void setZ(int z);

                const std::string& getType()const;

                virtual void remove(void* data,bool del = true) = 0;

                bool isStatic()const;
                bool isVisible() const;
                void setVisible(bool visibility);

                static VLayer* create(const std::string& type, int z, bool isStatic, bool isVisible = true);

            protected:
                const bool _isStatic;

                sf::RenderTexture _renderTexture;
                sf::Sprite _sprite;
                sf::FloatRect _lastViewport;

            private:
                friend class Map;
                virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states,const sf::FloatRect& viewport) = 0;

                const std::string _type;
                bool _visibility;
                int _z;
        };
    }
}
#endif
