#include <SFML-utils/es/Component.hpp>

namespace sfutils
{
    namespace es
    {
        template<class ENTITY>
        EntityManager<ENTITY>::EntityManager()
        {
        }

        template<class ENTITY>
        EntityManager<ENTITY>::~EntityManager()
        {
            reset();
        }

        template<class ENTITY>
        template<typename ... Args>
        std::uint32_t EntityManager<ENTITY>::create(Args&& ... args)
        {
            std::uint32_t index = 0;
            if(not _entities_index_free.empty())
            {
                //reuse existing entity
                index = _entities_index_free.front();
                _entities_index_free.pop_front();
                _entities_allocated[index] = new ENTITY(this,index,std::forward<Args>(args)...);
            }
            else
            {
                _entities_components_mask.emplace_back();

                index = _entities_allocated.size();
                _entities_allocated.emplace_back(nullptr);

                //resize components
                auto comp_size = _components_entities.size();
                for(std::size_t i=0;i<comp_size;++i)
                {
                    if(_components_entities[i] != nullptr)
                        _components_entities[i]->resize(index+1);
                }

                //create new entity
                _entities_allocated[index] = new ENTITY(this,index,std::forward<Args>(args)...);

            }
            _entities_index.emplace_back(index);

            return index;

        }

        template<class ENTITY>
        template<typename ... Args>
        void EntityManager<ENTITY>::emplace(std::uint32_t id,Args&& ... args)
        {
            //container to small
            std::size_t size = _entities_allocated.size();
            if(size <= id) //resize it
            {
                _entities_allocated.resize(id+1,nullptr);
                for(size_t i = size;i<id;++i)
                    _entities_index_free.emplace_back(i);


            }
            else if(_entities_allocated[id] != nullptr) //if already in use
            {
                _entities_index_to_destroy.remove(id);
                _entities_index.remove(id);
                delete _entities_allocated[id];
            }
            else //already free
            {
                _entities_index_free.remove(id);
            }
            
            _entities_allocated[id] = new ENTITY(this,id,std::forward<Args>(args)...);
            _entities_index.emplace_back(id);

            return id;
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::remove(std::size_t id)
        {
            _entities_index_to_destroy.emplace_back(id);
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::update()
        {
            if(_entities_index_to_destroy.size() > 0)
            {
                auto end = _entities_index_to_destroy.end();
                for(auto it = _entities_index_to_destroy.begin();it!=end;++it)
                {
                    std::uint32_t id = *it;
                    ENTITY* e = _entities_allocated.at(id);
                    if(e != nullptr)
                    {
                        auto comp_size = _components_entities.size();
                        for(std::size_t i=0;i<comp_size;++i)
                        {
                            if(_components_entities[i] != nullptr)
                                _components_entities[i]->erase<VComponent<ENTITY>>(id);
                        }
                        _entities_components_mask.at(id) = 0;

                        delete e;
                        _entities_allocated[id] = nullptr;

                        _entities_index.erase(std::find(_entities_index.begin(),_entities_index.end(),id));
                        _entities_index_free.emplace_back(id);
                    }
                }
                _entities_index_to_destroy.clear();
            }
        }

        template<class ENTITY>
        void EntityManager<ENTITY>::reset()
        {
            _entities_index_free.clear();
            _entities_index.clear();

            auto comp_size = _components_entities.size();
            for(std::size_t i=0;i<comp_size;++i)
            {
                if(_components_entities[i] != nullptr)
                {
                    for(size_t i = 0;i<_entities_index.size();++i)
                        _components_entities[i]->erase<VComponent<ENTITY>>(i);
                    delete _components_entities[i];
                }
            }
            _components_entities.clear();

            _entities_components_mask.clear();

            size_t size = _entities_allocated.size();
            for(size_t i=0;i<size;++i)
                delete _entities_allocated[i];

            _entities_allocated.clear();
        }

        template<class ENTITY>
        std::size_t EntityManager<ENTITY>::size()const
        {
            return _entities_allocated.size() - _entities_index_free.size();
        }

        template<class ENTITY>
        bool EntityManager<ENTITY>::isValid(std::uint32_t id)const
        {
            return id < _entities_allocated.size() and _entities_allocated[id] != nullptr;
        }


        template<class ENTITY>
        const ENTITY& EntityManager<ENTITY>::get(std::size_t id) const
        {
            return *_entities_allocated.at(id);
        }

        template<class ENTITY>
        ENTITY& EntityManager<ENTITY>::get(std::size_t id)
        {
            return *_entities_allocated.at(id);
        }

        template<class ENTITY>
        const ENTITY* EntityManager<ENTITY>::getPtr(std::size_t id)const
        {
            return _entities_allocated.at(id);
        }

        template<class ENTITY>
        ENTITY* EntityManager<ENTITY>::getPtr(std::size_t id)
        {
            return _entities_allocated.at(id);
        }

        template<class ENTITY>
        EntityManager<ENTITY>::container::const_iterator EntityManager<ENTITY>::begin()const
        {
            return _entities_index.cbegin();
        }

        template<class ENTITY>
        EntityManager<ENTITY>::container::const_iterator EntityManager<ENTITY>::end()const
        {
            return _entities_index.cend();
        }


        template<class ENTITY>
        template<typename COMPONENT,typename ... Args>
        void EntityManager<ENTITY>::addComponent(std::uint32_t id,Args&& ... args)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(not _entities_components_mask.at(id).test(family));

            auto pool = static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family]);
            pool->emplace(id,std::forward<Args>(args)...);

            pool->at(id)._owner_id = id;
            pool->at(id)._manager = this;

            _entities_components_mask.at(id).set(family);
        }
        
        template<class ENTITY>
        template<typename COMPONENT>
        void EntityManager<ENTITY>::removeComponent(std::uint32_t id)
        {
            checkComponent<COMPONENT>();
            Family family = COMPONENT::family();

            assert(_entities_components_mask.at(id).test(family));

            static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->erase(id);

            _entities_components_mask[id].reset(family);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline bool EntityManager<ENTITY>::hasComponent(std::uint32_t id)const
        {
            //checkComponent<COMPONENT>();
            Family family = COMPONENT::family();
            return _entities_components_mask.at(id).test(family);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline ComponentHandle<COMPONENT,ENTITY> EntityManager<ENTITY>::getComponent(std::uint32_t id)const
        {
            if(hasComponent<COMPONENT>(id))
                return ComponentHandle<COMPONENT,ENTITY>(this,id);
            return ComponentHandle<COMPONENT,ENTITY>();
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline std::tuple<ComponentHandle<COMPONENT,ENTITY>...> EntityManager<ENTITY>::getComponents(std::uint32_t id)const
        {
            return std::make_tuple(getComponent<COMPONENT>(id)...);
        }

        template<class ENTITY>
        template<typename COMPONENT>
        inline COMPONENT* EntityManager<ENTITY>::getComponentPtr(std::uint32_t id)const
        {
            Family family = COMPONENT::family();
            return &static_cast<utils::memory::Pool<COMPONENT>*>(_components_entities[family])->at(id);
        }

        template<typename COMPONENT>
        inline void getMask(std::bitset<MAX_COMPONENTS>& mask)
        {
            mask.set(COMPONENT::family());
        }

        template<typename C1, typename C2, typename ... COMPONENT>
        inline void getMask(std::bitset<MAX_COMPONENTS>& mask)
        {
            mask.set(C1::family());
            getMask<C2,COMPONENT...>(mask);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT ...> EntityManager<ENTITY>::getByComponents(ComponentHandle<COMPONENT,ENTITY>& ... components)
        {
            std::bitset<MAX_COMPONENTS> mask;
            getMask<COMPONENT ...>(mask);
            return View<COMPONENT...>(*this,mask,components ...);
        }


        template<class ENTITY>
        template<typename COMPONENT>
        inline void EntityManager<ENTITY>::checkComponent()
        {
            Family family = COMPONENT::family();
            //resize
            if( _components_entities.size() <= family)
                _components_entities.resize(family+1,nullptr);
            //check Pool validity
            if(_components_entities[family] == nullptr)
            {
                auto pool = new utils::memory::Pool<COMPONENT>;
                pool->resize(_entities_allocated.size());
                _components_entities[family] = pool;
            }
        }

        /////////////////////// VIEW ///////////////////

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT...>::View(EntityManager<ENTITY>& manager,const std::bitset<MAX_COMPONENTS>& mask,ComponentHandle<COMPONENT,ENTITY>& ... components) : _manager(manager), _mask(mask), _handles(std::tuple<ComponentHandle<COMPONENT,ENTITY>&...>(components ...))
        {
            unpack_manager<0,COMPONENT ...>();
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline typename EntityManager<ENTITY>::template View<COMPONENT ...>::iterator EntityManager<ENTITY>::View<COMPONENT ...>::begin()
        {
            auto begin = _manager._entities_index.begin();
            auto end = _manager._entities_index.end();

            while(begin != end)
            {
                std::uint32_t index = *begin;    
                if((_manager._entities_components_mask[index] & _mask) == _mask)
                {
                    unpack_id<0,COMPONENT...>(index);
                    break;
                }
                ++begin;
            }

            return iterator(*this,begin,end);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline typename EntityManager<ENTITY>::template View<COMPONENT ...>::iterator EntityManager<ENTITY>::View<COMPONENT ...>::end()
        {
            return iterator(*this,_manager._entities_index.end(),_manager._entities_index.end());
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpack_id(std::uint32_t id)
        {
            std::get<N>(_handles)._entity_id = id;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C0,typename C1,typename ... Cx>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpack_id(std::uint32_t id)
        {
            unpack_id<N,C0>(id);
            unpack_id<N+1,C1,Cx ...>(id);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpack_manager()
        {
            std::get<N>(_handles)._manager = &_manager;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        template<int N,typename C0,typename C1,typename ... Cx>
        inline void EntityManager<ENTITY>::View<COMPONENT...>::unpack_manager()
        {
            unpack_manager<N,C0>();
            unpack_manager<N+1,C1,Cx ...>();
        }

        ////////////////// VIEW ITERATOR /////////////////////////

        template<class ENTITY>
        template<typename ... COMPONENT>
        EntityManager<ENTITY>::View<COMPONENT ...>::iterator::iterator(View& view,EntityManager<ENTITY>::container::iterator it,EntityManager<ENTITY>::container::iterator it_end) : _view(view), _it(it), _it_end(it_end)
        {
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        typename EntityManager<ENTITY>::template View<COMPONENT...>::iterator& EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator++()
        {
            ++_it;
            while(_it != _it_end)
            {
                std::uint32_t index = *_it;    
                if(_view._manager._entities_allocated.at(index) != nullptr and (_view._manager._entities_components_mask.at(index) & _view._mask) == _view._mask)
                {
                    _view.unpack_id<0,COMPONENT...>(index);
                    break;
                }
                ++_it;
            }
            return *this;
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline ENTITY* EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator*()const
        {
            if(_it == _it_end)
                return nullptr;
            return _view._manager._entities_allocated.at(*_it);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        inline ENTITY* EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator->()const
        {
            if(_it == _it_end)
                return nullptr;
            return _view._manager._entities_allocated.at(*_it);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        bool EntityManager<ENTITY>::View<COMPONENT ...>::iterator::operator==(const EntityManager<ENTITY>::View<COMPONENT...>::iterator& other)
        {
            return _it == other._it and _view._mask == other._view._mask and &(_view._manager) == &(other._view._manager);
        }

        template<class ENTITY>
        template<typename ... COMPONENT>
        bool EntityManager<ENTITY>::View<COMPONENT...>::iterator::operator!=(const EntityManager<ENTITY>::View<COMPONENT...>::iterator& other)
        {
            return _it != other._it or _view._mask != other._view._mask or &(_view._manager) != &(other._view._manager);
        }

    }
}
