#pragma once
#include <functional>
#include <map>

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

    void unsubscribe(uint32_t id) {
      auto loc = subscribers.find(id);
      if (loc == subscribers.end()) return;
      subscribers.erase(loc);
    } 
};
