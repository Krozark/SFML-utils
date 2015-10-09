#ifndef SFUTILS_GEOMETRY_BASETILE_HPP
#define SFUTILS_GEOMETRY_BASETILE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace sfutils
{
    namespace map
    {
        class Tile;
        class VLayer;
    }

    namespace geometry
    {
        /**
         * \brief base class for all geometry
         * */
        class Geometry
        {
            public:
                Geometry(float scale,float width, float height);
                virtual ~Geometry();

                const sf::ConvexShape& getShape() const;
                float getScale()const;

                virtual sf::Vector2f mapCoordsToPixel(const sf::Vector2i& coord) const = 0;
                virtual sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const = 0;

                virtual sf::IntRect getTextureRect(const sf::Vector2i& pos) const = 0;

                virtual sf::Vector2i round(const sf::Vector2f& pos) const = 0;
                virtual int distance(const sf::Vector2i& p1, const sf::Vector2i& p2) const = 0;

            protected:
                const float _scale;
                const float _width;
                const float _height;
                sf::ConvexShape _shape; //< need to be initialized by child class
        };

        /**
         * \brief Base Geometry for all Square shape (should not be used)
         * */
        class _GeometrySquareBase_helper : public Geometry
        {
            public:
                _GeometrySquareBase_helper(float scale,float width, float height);
                virtual ~_GeometrySquareBase_helper();

                virtual sf::IntRect getTextureRect(const sf::Vector2i& pos) const override final;

                virtual sf::Vector2i round(const sf::Vector2f& pos) const override final;

                virtual int distance(const sf::Vector2i& p1, const sf::Vector2i& p2) const override final;
                
            protected:
        };

        /**
         * \breif base class for Square tile
         * */
        class GeometrySquareBase : public _GeometrySquareBase_helper
        {
            public:
                GeometrySquareBase(float scale);
                virtual ~GeometrySquareBase();
        };

        /**
         * \breif base class for Square Iso tile
         * */
        class GeometrySquareIsoBase : public _GeometrySquareBase_helper
        {
            public:
                GeometrySquareIsoBase(float scale);
                virtual ~GeometrySquareIsoBase();
        };


        class GeometryHexaBase: public Geometry
        {
            public:
                GeometryHexaBase(float scale,float width, float height);
                virtual ~GeometryHexaBase();

                virtual sf::IntRect getTextureRect(const sf::Vector2i& pos) const override final;

                virtual sf::Vector2i round(const sf::Vector2f& pos) const override final;
                virtual int distance(const sf::Vector2i& p1, const sf::Vector2i& p2) const override final;

        };

    }
}
#endif
