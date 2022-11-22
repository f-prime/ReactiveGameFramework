#pragma once

#include "SignalBus.h"
#include <iostream>
#include <map>
#include <string>

typedef uint32_t EntityUID;
typedef uint32_t EntityID;

static EntityUID entity_uid = 0;

class Entity {
  public:
    std::map<std::string, EventBusUID> subscriptions;
    EntityID eid;
    EntityUID ueid;
};
