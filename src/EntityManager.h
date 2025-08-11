#pragma once

#include "Entity.hpp"
#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager
{
    EntityVec m_entities;
    EntityVec m_toAdd;
    std::map<std::string, EntityVec> m_entityMap;
    size_t m_totalEntities = 0;

    void removeDeadEntites(EntityVec &vec);

  public:
    EntityManager();
    void init();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVec &getEntities();
    EntityVec &getEntities(const std::string &tag);
};
