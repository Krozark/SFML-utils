namespace sfutils
{
    namespace es
    {
        template<typename COMPONENT,typename ... Args>
        void EntityManager::addComponent(Entity& e,Args&& ... args)
        {
        }
        
        template<typename COMPONENT>
        void EntityManager::removeComponent(Entity& e)
        {
        }
    }
}
