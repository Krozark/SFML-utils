#ifndef SMFL_UTILS_RESOURCEMANAGER_HPP
#define SMFL_UTILS_RESOURCEMANAGER_HPP

#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr

#include <SFML/Audio.hpp> //sf::Music

namespace sfutils
{
    template<typename RESOURCE,typename IDENTIFIER = int>
    class ResourceManager
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id,Args&& ... args);

            RESOURCE& get(const IDENTIFIER& id)const;

            template<typename ... Args>
            RESOURCE& getOrLoad(const IDENTIFIER& id,Args&& ... args);

        private:
            std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;
    };

    template<typename IDENTIFIER>
    class ResourceManager<sf::Music,IDENTIFIER>
    {
        public:
            ResourceManager(const ResourceManager&) = delete;
            ResourceManager& operator=(const ResourceManager&) = delete;

            ResourceManager() = default;

            template<typename ... Args>
            void load(const IDENTIFIER& id,Args&& ... args);

            sf::Music& get(const IDENTIFIER& id)const;

            template<typename ... Args>
            sf::Music& getOrLoad(const IDENTIFIER& id,Args&& ... args);

        private:
            std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;
    };


}
#include <SFML-utils/core/ResourceManager.tpl>

#endif
