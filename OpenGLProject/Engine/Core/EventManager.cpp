#include "pch.h"
#include "EventManager.h"

namespace nc {

	void EventManager::Subscribe(const std::string& type, function_t function, Object* owner)
	{
		Observer observer;
		observer.function = function;
		observer.owner = owner;

		m_observers[type].push_back(observer);
	}

	void EventManager::Notify(const Event& event)
	{
		auto observers = m_observers[event.type];
		for (Observer& observer : observers) {
			if (event.receiver == nullptr || event.receiver == observer.owner) {
				observer.function(event);
			}
		}
	}
}
