#ifndef SFUTILS_ES_ENTITY_HPP
#define SFUTILS_ES_ENTITY_HPP

#include <cstdint>

namespace sfutils
{
    namespace es
    {
        class EntityManager;
        class Entity
        {
            public:
                Entity(const Entity&) = default;
                Entity& operator=(const Entity&) = default;

                Entity(EntityManager* manager,std::uint64_t id);

                bool operator==(const Entity& other)const;
                bool operator!=(const Entity& other)const;

                void remove();
                bool isValid()const;

                const static std::uint64_t invalidId;
                
            private:
                std::uint64_t _id;
                
                EntityManager* _manager;
        };
    }
}
#endif
