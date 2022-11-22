#pragma once
#include <functional>
#include <map>

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

    void unsubscribe(uint32_t id) {
      auto loc = subscribers.find(id);
      if (loc == subscribers.end()) return;
      subscribers.erase(loc);
    } 
};
