//
// Created by matt on 3/31/18.
//

#ifndef GALAGA_ENTITYMANAGER_H
#define GALAGA_ENTITYMANAGER_H

#include <tuple>
#include <vector>
#include <algorithm>
#include <Pure2D/Util/Constants.h>
#include <iostream>

template<typename T>
using EArr = std::vector<T>;

template<pure::uint32 poolsize, typename ...Args>
class EntityManager
{
public:
    EntityManager()
    {
        m_entities = std::make_tuple(EArr<Args>()...);
        ( std::get<EArr<Args>>(m_entities).reserve(poolsize), ... );
    }

    /**
     * Cleans up any queued entities in deletion queue to be deleted
     */
    void update()
    {
        ( deleteQueue<Args>(std::get<EArr<Args*>>(m_deletionQueue)), ... );
    }

    template<typename T, typename ...CtorParams>
    T& create(CtorParams&&... ctorParams)
    {
        EArr<T>& entities = std::get<EArr<T>>(m_entities);

        assert(entities.size() <= poolsize);

        entities.emplace_back(std::forward<CtorParams>(ctorParams)...);
        return entities.back();
    };

    /**
     * Requests for an entity to be deleted
     * @tparam T Type of entity to be deleted
     * @param entity
     */
    template<typename T>
    void destroy(T* entity)
    {
        EArr<T*>& queue = std::get<EArr<T*>>(m_deletionQueue);
        queue.push_back(entity);
    }

    template<typename T>
    const EArr<T>& get()
    {
        return std::get<EArr<T>>(m_entities);
    }


private:
    std::tuple<EArr<Args>...> m_entities;
    std::tuple<EArr<Args*>...> m_deletionQueue;

    // TODO: This can be refactored to a true 'Pool' of entities where
    // entities aren't deleted, just deactivated.
    template<typename T>
    void deleteQueue(EArr<T*>& deleteQueue)
    {
        EArr<T>& entities = std::get<EArr<T>>(m_entities);

        if (deleteQueue.empty()) return;

        for (auto de : deleteQueue)
        {
            auto itr = std::find_if(entities.begin(), entities.end(), [de](T& e) {
                return &e == de;
            });

            if (itr != entities.end())
                entities.erase(itr);

        }

        deleteQueue.clear();
    }
};

#endif //GALAGA_ENTITYMANAGER_H
