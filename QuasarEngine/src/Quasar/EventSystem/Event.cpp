#include "qspch.h"
#include "Event.h"

namespace Quasar
{
	Event::Event(uint8_t priority) : _priority{ priority }
	{
		QS_CORE_TRACE("Event created with priority: {0}", _priority);
	}

	Event::~Event()
	{

	}

	void Event::Add(RoutineType routine)
	{
		routines.push_back(routine);
	}

	void Event::Remove(RoutineType routine)
	{
		auto it = std::remove(routines.begin(), routines.end(), routine);
		routines.erase(it, routines.end());
	}

	void Event::Invoke(uint32_t input)
	{
		EventDispatcher(input);



	}

	constexpr void Event::EventDispatcher(uint32_t& input)
	{
		switch (_priority)
		{
		case 0:

			return;

		default:

			for (const RoutineType routine : routines) {
				routine(input);
			}
			return;
		}
	}
}
