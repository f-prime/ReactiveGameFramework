#pragma once

#include <array>
#include <vector>
#include "Entity.h"

template<typename E, size_t NUM_ENTITIES>
class EntityManager {
  private:
    // Assume that these entities are heap allocated
    std::array<bool, NUM_ENTITIES> registry;
    std::vector<E*> toDelete;

  public:
    std::array<E*, NUM_ENTITIES> entities; 

    EntityManager() {
      for (auto i = 0; i < NUM_ENTITIES; i++)
        registry[i] = false;
    }

    EntityID add_entity(E* entity) {
      for (auto e = 0; e < NUM_ENTITIES; e++) {
        if (registry[e]) continue;
        registry[e] = true;
        entities[e] = entity;
        entity->eid = e;
        entity->ueid = entity_uid;
        entity_uid++;
        return e;
      }

      delete entity;
      return -1;
    }

    E* get_entity(EntityID eid) {
      return entities[eid];
    }

    void remove_entity(EntityID e) {
      registry[e] = false;
      toDelete.push_back(entities[e]);
    } 

    void clean() {
      for (auto e : toDelete) {
        delete e;
      }

      toDelete.clear();
    }

    void flush() {
      for (auto i = 0; i < NUM_ENTITIES; i++) {
        if (!registry[i]) continue;
        remove_entity(i);
        delete entities[i];
      }
    }
};
