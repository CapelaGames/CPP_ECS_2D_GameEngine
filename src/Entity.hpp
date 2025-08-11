#pragma once

#include "CCollision.hpp"
#include "CInput.hpp"
#include "CLifeSpan.hpp"
#include "CScore.hpp"
#include "CShape.hpp"
#include "CTransform.hpp"
#include "Component.hpp"
#include <string>

class EntityManager;

using ComponentTuple = std::tuple<
    CTransform,
    CShape,
    CCollision,
    CInput,
    CScore,
    CLifeSpan>;

class Entity
{
    friend class EntityManager;

    ComponentTuple m_components;
    bool m_alive = true;
    std::string m_tag = "default";
    size_t m_id = 0;

    Entity(const size_t &id, const std::string &tag)
        : m_tag(tag), m_id(id) {}

  public:
    size_t id() const
    {
        return m_id;
    }

    bool isAlive() const
    {
        return m_alive;
    }

    std::string tag() const
    {
        return m_tag;
    }

    void destroy()
    {
    }

    template <typename T>
    T &get()
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    const T &get() const
    {
        return std::get<T>(m_components);
    }

    template <typename T>
    bool has() const
    {
        return get<T>().exists;
    }

    template <typename T>
    bool remove()
    {
        get<T>() = T();
        return false;
    }

    template <typename T, typename... TArgs>
    T &add(TArgs &&...mArgs)
    {
        auto &component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.exists = true;
        return component;
    }
};
