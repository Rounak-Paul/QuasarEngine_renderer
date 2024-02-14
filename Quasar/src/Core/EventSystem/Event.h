/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Event class, create, subscribe to, unsubscribe to, and 
					execute Quasar events 
-------------------------------------------------------------------------------
*/

#pragma once
#include "qspch.h"

#include "Core/Core.h"

namespace Quasar
{
	class QUASAR_API Event
	{
	public:
		using RoutineType = void (*)(uint32_t);

		Event();
		~Event();

		static Event& getInstance()
		{
			static Event instance;
			return instance;
		}

		// deleted copy constructor and copy assignment to prevent copy
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		void Add(RoutineType routine);

		void Remove(RoutineType routine);

		void Invoke(uint32_t i);

	private:

		constexpr void EventDispatcher(uint32_t& input);

		std::vector<RoutineType> routines;
	};
}


