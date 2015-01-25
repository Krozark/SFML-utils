namespace sfutils
{
    namespace es
    {
        template<typename ENTITY>
        Application<ENTITY>::Application() : systems(entites)
        {
        }

        template<typename ENTITY>
        void Application<ENTITY>::update(sf::Time deltaTime)
        {
            systems.updateAll(deltaTime);
            entites.update();
        }
    }
}
