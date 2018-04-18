//
// Created by matt on 4/12/18.
//

#ifndef GALAGA_OBJECTPOOL_H
#define GALAGA_OBJECTPOOL_H


#include <utility>
#include <vector>
#include <cassert>
#include <algorithm>
#include "../Interface/LifeCycle.h"

// TODO: Move this to Pure2D library (along with LifeCycle interface)

template <typename T>
class ObjectPool : private pure::NonCopyable
{
    static_assert(std::is_base_of<LifeCycle, T>::value);
private:
    template<typename P>
    class Poolable : public P
    {
        friend ObjectPool<P>;

        Poolable<P>* next;
    };

public:

    explicit ObjectPool(size_t size) : m_maxSize(size)
    {
        m_objects.resize(m_maxSize);
        // NOTE: Maybe this is getting invalidated somehow?
        m_firstAvailable = &m_objects[0];

        for (size_t i = 0; i < m_objects.size() - 1; i++)
        {
            m_objects[i].next = &m_objects[i + 1];
        }

        m_objects.back().next = nullptr;

        m_liveObjects.reserve(m_maxSize);
    }

    ObjectPool(ObjectPool<T> &&other) noexcept:
        m_maxSize(other.m_maxSize),
        m_objects(std::move(other.m_objects)),
        m_liveObjects(std::move(other.m_liveObjects))
    {
        m_firstAvailable = other.m_firstAvailable;
        other.m_firstAvailable = nullptr;
    }

    T* create()
    {
        assert(m_firstAvailable);

        Poolable<T>* obj = m_firstAvailable;
        obj->activate();

        m_firstAvailable = obj->next;

        m_liveObjects.push_back(obj);

        return obj;
    }

    void destroy(T* object)
    {
        static_assert(std::is_base_of<T, Poolable<T>>::value);

        auto* destroyTarget = static_cast<Poolable<T>*>(object);

        destroyTarget->deactivate();
        destroyTarget->next = m_firstAvailable;

        m_firstAvailable = destroyTarget;

        auto removeItr = std::remove_if(m_liveObjects.begin(), m_liveObjects.end(),
           [object](T* o) { return o == object; });

        m_liveObjects.erase(removeItr, m_liveObjects.end());
    }

    void destroy(int objectIndx)
    {
        T* obj = m_liveObjects[objectIndx];

        obj->deactivate();
        obj->next = m_firstAvailable;
        m_firstAvailable = obj;

        m_liveObjects.erase(m_liveObjects.begin() + objectIndx);
    }

    /**
     * Gets objects all objects that have been created
     * NOTE: This will still return potentially deactivated objects if object was not destroyed
     * @return all objects that have been created
     */
    const std::vector<T*>& getLiveObjects() const
    {
        return m_liveObjects;
    }

    // Destroy and set all active objects to not active state
    void reset()
    {
        auto objSize = static_cast<int>(m_liveObjects.size());
        for (int i = objSize - 1; i >= 0; i--)
            destroy(i);
    }


private:

    std::vector<Poolable<T>> m_objects;
    std::vector<T*> m_liveObjects;
    Poolable<T>* m_firstAvailable;
    const size_t m_maxSize;
};


#endif //GALAGA_OBJECTPOOL_H
