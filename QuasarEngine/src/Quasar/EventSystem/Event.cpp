/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Camera class, contains methods related to various
					transformations responsible for projection to camera space
-------------------------------------------------------------------------------
*/

#include "qspch.h"
#include "Event.h"

namespace Quasar
{
	Event::Event()
	{
		QS_CORE_TRACE("Event created");
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
		for (const RoutineType routine : routines) {
			routine(input);
		}
	}
}
