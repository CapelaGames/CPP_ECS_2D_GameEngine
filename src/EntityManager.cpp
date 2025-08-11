#include "EntityManager.h"
#include "Entity.hpp"

EntityManager::EntityManager() = default;

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_toAdd.push_back(entity);

    if (m_entityMap.find(tag) == m_entityMap.end())
    {
        m_entityMap[tag] = EntityVec();
    }
    m_entityMap[tag].push_back(entity);

    return entity;
}

EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return m_entities;
}

void EntityManager::update()
{
    for (auto &e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    // Remove dead entities from the main vector
    removeDeadEntites(m_entities);

    // Remove dead entities from each tag vector in the map
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntites(entityVec);
    }
}

void EntityManager::removeDeadEntites(EntityVec &vec)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const std::shared_ptr<Entity> &e)
                             {
                                 return !e->isAlive();
                             }),
              vec.end());
}
