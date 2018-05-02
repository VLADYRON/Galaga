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
#include "ObjectPool.h"
#include "../Entities/Entity.h"

template<typename T>
using EArr = std::vector<T>;

template<typename ...Args>
class EntityManager
{
private:
    template<class T>
    using GetPoolType = typename decltype(typename std::remove_reference<T>::type())::type;

public:
    EntityManager():
        m_entities(std::make_tuple(ObjectPool<Args>()...))
    {
    }


    template<typename T>
    T& create()
    {
        ObjectPool<T>& pool = std::get<ObjectPool<T>>(m_entities);
        return *pool.create();
    };

    template<typename T>
    void resize(uint32_t newSize)
    {
        ObjectPool<T>& pool = std::get<ObjectPool<T>>(m_entities);
        pool.resize(newSize);
    }

    /**
     * Searches in all pools of given base type for given entity
     * and then destroys it
     *
     * -- Use this for polymorphic types when exact type is not known --
     *
     * @tparam T Base class
     * @param entity entity to be destroyed
     */
    template<typename T>
    void destroyBySuper(T* entity)
    {
        std::apply([this, entity](auto&... x) {
            bool done = false;
            ( searchDestroyEntity<GetPoolType<decltype(x)>>(entity, x, done), ...);
        }, m_entities);
    }

    /**
     * Requests for an entity to be deleted
     * @tparam T Type of entity to be deleted
     * @param entity
     */
    template<typename T>
    void destroy(T* entity)
    {
        ObjectPool<T>& pool = std::get<ObjectPool<T>>(m_entities);
        pool.destroy(entity);
    }

    template<typename T>
    const ObjectPool<T>& get()
    {
        return std::get<ObjectPool<T>>(m_entities);
    }

    template<typename T>
    EArr<T*> getAllOfType()
    {
        EArr<T*> result;

        std::apply([this, &result](auto&... x) {
           ( addQueryType<T, GetPoolType<decltype(x)>>(x, result), ...);
        }, m_entities);

        return result;
    }


private:
    std::tuple<ObjectPool<Args>...> m_entities;

    template<typename Base, typename Derived, typename Ret = void>
    using EnableIfBaseOf = typename std::enable_if_t<std::is_base_of_v<Base, Derived>, Ret>;
    template<typename Base, typename Derived, typename Ret = void>
    using DisableIfBaseOf = typename std::enable_if_t<!std::is_base_of_v<Base, Derived>, Ret>;

    template<typename Derived, typename Base, typename Pool>
    auto searchDestroyEntity(Base* obj, Pool& pool, bool& done) -> DisableIfBaseOf<Base, Derived> { };

    template<typename Derived, typename Base, typename Pool>
    auto searchDestroyEntity(Base* obj, Pool& pool, bool& done) -> EnableIfBaseOf <Base, Derived>
    {
        if (done) return;
        const EArr<Derived*>& entities = pool.getLiveObjects();
        for (auto e : entities)
        {
            if (e == obj)
            {
                pool.destroy(static_cast<Derived*>(obj));
                done = true;
                return;
            }
        }
    };

    template<typename Base, typename Derived, typename Pool>
    auto addQueryType(Pool& obj, EArr<Base*>& arr) -> DisableIfBaseOf<Base, Derived> { }

    template<typename Base, typename Derived, typename Pool>
    auto addQueryType(Pool& pool, EArr<Base*>& arr) -> EnableIfBaseOf<Base, Derived>
    {
        const EArr<Derived*>& entities = pool.getLiveObjects();
        arr.insert(arr.end(), entities.begin(), entities.end());
    }
};


#endif //GALAGA_ENTITYMANAGER_H
