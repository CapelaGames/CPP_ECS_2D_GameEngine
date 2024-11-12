#include "EntityManager.hpp"
#include <memory>

EntityManager::EntityManager() {}

// std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
//{
//     auto e = std::make_shared<Entity>(tag, m_totalEntities++);
//     m_toAdd.push_back(e);
//     return e;
// }
EntityVec &getEntities();
EntityVec &getEntities(const std::string &tag);

void EntityManager::update()
{
    //  for (auto e : m_toAdd)
    //  {
    //      m_entities.push_back(e);
    //      m_entityMap[e->tag()].push_back(e);
    //  }
    //  for (auto e : m_entities)
    //  {
    //  }
    //  m_toAdd.clear();
}
