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

        std::apply([this, &result](auto&... x)
           {
               ( addQueryType<T, typename decltype(typename std::remove_reference<decltype(x)>::type())::type>(x, result), ...);
           }, m_entities);

        return result;
    }


private:
    std::tuple<ObjectPool<Args>...> m_entities;

    template<typename B, typename D, typename T>
    auto addQueryType(T& obj, EArr<B*>& arr) -> typename std::enable_if<!std::is_base_of<B, D>::value>::type
    {}

    template<typename B, typename D, typename T>
    auto addQueryType(T& obj, EArr<B*>& arr) -> typename std::enable_if<std::is_base_of<B, D>::value>::type
    {
        const EArr<D*>& entities = obj.getLiveObjects();
        arr.insert(arr.end(), entities.begin(), entities.end());
    }
};


#endif //GALAGA_ENTITYMANAGER_H
