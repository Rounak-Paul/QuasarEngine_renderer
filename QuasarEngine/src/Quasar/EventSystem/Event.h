#pragma once
#include "qspch.h"

#include "Quasar/Core.h"

#define QS_EVENT_P1 1
#define QS_EVENT_P0 0

namespace Quasar
{
	class QUASAR_API Event
	{
	public:
		using RoutineType = void (*)(uint32_t);

		Event(uint8_t priority);
		~Event();

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		void Add(RoutineType routine);

		void Remove(RoutineType routine);

		void Invoke(uint32_t i);

	private:

		constexpr void EventDispatcher(uint32_t& input);

		std::vector<RoutineType> routines;
		uint8_t _priority;
	};
}


