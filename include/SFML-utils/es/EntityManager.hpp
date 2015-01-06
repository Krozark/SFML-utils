#ifndef SFUTILS_ES_ENTITYMANAGER_HPP
#define SFUTILS_ES_ENTITYMANAGER_HPP

#include <forward_list>
#include <vector>
#include <bitset>
#include <cstdint>
#include <tuple>
#include <utils/memory.hpp>

#include <SFML-utils/es/defines.hpp>

namespace sfutils
{
    namespace es
    {
        class Entity;
        template<typename T> class ComponentHandle;
        class EntityManager
        {
            template<typename ...> class View;
            public:
                EntityManager(const EntityManager&) = delete;
                EntityManager& operator=(const EntityManager&) = delete;

                EntityManager();
                ~EntityManager();

                std::uint32_t create();
                void remove(std::size_t id);

                void reset();
                void reset(std::uint32_t id);

                bool isValid(std::uint32_t id);

                const Entity& get(std::size_t id)const;
                Entity& get(std::size_t id);

                std::forward_list<std::uint32_t>::const_iterator begin()const;
                std::forward_list<std::uint32_t>::const_iterator end()const;

                template<typename COMPONENT,typename ... Args>
                void addComponent(std::uint32_t id,Args&& ... args);
                
                template<typename COMPONENT>
                void removeComponent(std::uint32_t id);

                template<typename COMPONENT>
                bool hasComponent(std::uint32_t id)const;

                template<typename COMPONENT>
                ComponentHandle<COMPONENT> getComponent(std::uint32_t id);

                template<typename ... COMPONENT>
                std::tuple<ComponentHandle<COMPONENT>...> getComponents(std::uint32_t id);
                

                template<typename ... COMPONENT>
                View<COMPONENT ...> getByComponents(ComponentHandle<COMPONENT>& ... components);

            private:
                std::vector<Entity> _entities_allocated;
                std::vector<std::bitset<MAX_COMPONENTS>> _entities_components_mask;
                std::vector<utils::memory::VPool*> _components_entities;

                std::forward_list<std::uint32_t> _entities_index;
                std::forward_list<std::uint32_t> _entities_index_free;

                template<typename COMPONENT>
                void checkComponent();

                template<typename> friend class ComponentHandle;

                template<typename COMPONENT>
                COMPONENT* getComponentPtr(std::uint32_t id);

                template<typename ... COMPONENT>
                class View
                {
                    class iterator;
                    public:
                        View(EntityManager& manager,const std::bitset<MAX_COMPONENTS>& mask,ComponentHandle<COMPONENT>& ... components);

                        iterator begin();
                        iterator end();

                    private:
                        class iterator
                        {
                            public:
                                iterator(View& view,std::forward_list<std::uint32_t>::iterator it,std::forward_list<std::uint32_t>::iterator it_end);
                                iterator& operator++(); //prefix increment
                                Entity* operator*() const;
                                Entity* operator->() const;
                                bool operator==(const iterator& other);
                                bool operator!=(const iterator& other);
                            private:
                                View& _view;
                                std::forward_list<std::uint32_t>::iterator _it;
                                std::forward_list<std::uint32_t>::iterator _it_end;
                        };

                        template<int N,typename C>
                        void unpack_id(std::uint32_t id);

                        template<int N,typename C0,typename C1,typename ... Cx>
                        void unpack_id(std::uint32_t id);

                        template<int N,typename C>
                        void unpack_manager();

                        template<int N,typename C0,typename C1,typename ... Cx>
                        void unpack_manager();

                        EntityManager& _manager;
                        const std::bitset<MAX_COMPONENTS> _mask;
                        std::tuple<ComponentHandle<COMPONENT>& ...> _handles;
                };
        };
    }
}
#include <SFML-utils/es/EntityManager.tpl>
#endif
