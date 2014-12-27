namespace sfutils
{
    template<typename T>
    ActionTarget<T>::ActionTarget(const ActionMap<T>& map) : _action_map(map)
    {
    }

    template<typename T>
    bool ActionTarget<T>::processEvent(const sf::Event& event)const
    {
        for(auto& pair : _events_poll_action)
        {
            if(pair.first == event)
            {
                pair.second(event);
                return true;
            }
        }

        for(auto& pair : _events_poll)
        {
            if(_action_map.get(pair.first) == event)
            {
                pair.second(event);
                return true;
            }
        }
        return false;
    }

    template<typename T>
    void ActionTarget<T>::processEvents()const
    {
        for(auto& pair : _events_real_time_action)
        {
            if(pair.first.test())
                pair.second(pair.first._event);
        }
        
        for(auto& pair : _events_real_time)
        {
            const Action& action = _action_map.get(pair.first);
            if(action.test())
                pair.second(action._event);
        }
    }

    template<typename T>
    void ActionTarget<T>::bind(const T& key,const FuncType& callback)
    {
        const Action& action = _action_map.get(key);
        bind(_action_map.get(key),callback);
        if(action._type & Action::Type::RealTime)
            _events_real_time.emplace_back(key,callback);
        else
            _events_poll.emplace_back(key,callback);
    }

    template<typename T>
    void ActionTarget<T>::bind(const Action& action,const FuncType& callback)
    {
        if(action._type & Action::Type::RealTime)
            _events_real_time_action.emplace_back(action,callback);
        else
            _events_poll_action.emplace_back(action,callback);
    }

    template<typename T>
    void ActionTarget<T>::bind(Action&& action,const FuncType& callback)
    {
        if(action._type & Action::Type::RealTime)
            _events_real_time_action.emplace_back(std::move(action),callback);
        else
            _events_poll_action.emplace_back(std::move(action),callback);
    }

    template<typename T>
    void ActionTarget<T>::unbind(const T& key)
    {
        auto remove_func = [&key](const std::pair<T,FuncType>& pair) -> bool
        {
            return pair.first == key;
        };

        const Action& action = _action_map.get(key);
        if(action._type & Action::Type::RealTime)
            _events_real_time.remove_if(remove_func);
        else
            _events_poll.remove_if(remove_func);
    }

}
