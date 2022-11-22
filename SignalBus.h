#pragma once
#include <functional>
#include <map>
#include <iostream>

typedef uint32_t EventBusUID;

class SignalBus {
  private:
    EventBusUID id = 0;
    std::map<EventBusUID, std::function<void()>> subscribers; 
  
  public:
    void broadcast() {
      for (auto& sub : subscribers) {
        auto callback = sub.second;
        callback();
      }
    }

    EventBusUID subscribe(std::function<void()> callback) {
      id++;
      subscribers[id] = callback;
      return id;
    }

    EventBusUID idOfNextSubscription() {
      return id + 1;
    }

    EventBusUID subscribeUntil(std::function<void()> callback, SignalBus* deleteWhenEmits) {
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
