#pragma once
#include <functional>
#include <map>
#include "SignalBus.h"

typedef uint32_t EventBusUID;

template<typename... CallbackParams>
class EventBus {
  private:
    EventBusUID id = 0;
    std::map<EventBusUID, std::function<void(CallbackParams...)>> subscribers; 
  
  public:
    void broadcast(CallbackParams... args) {
      for (auto& sub : subscribers) {
        auto callback = sub.second;
        callback(args...);
      }
    }

    EventBusUID subscribe(std::function<void(CallbackParams...)> callback) {
      id++;
      subscribers[id] = callback;
      return id;
    }

    EventBusUID idOfNextSubscription() {
      return id + 1;
    }

    EventBusUID subscribeUntil(std::function<void(CallbackParams...)> callback, SignalBus* deleteWhenEmits) {
      auto subId  = this->subscribe(callback);
      auto delId = this->idOfNextSubscription(); 
      deleteWhenEmits->subscribe([this, subId, deleteWhenEmits, delId]() {
        this->unsubscribe(subId); 
        deleteWhenEmits->unsubscribe(delId);
      });
      return subId;
    }

    void unsubscribe(uint32_t id) {
      auto loc = subscribers.find(id);
      if (loc == subscribers.end()) return;
      subscribers.erase(loc);
    } 
};
