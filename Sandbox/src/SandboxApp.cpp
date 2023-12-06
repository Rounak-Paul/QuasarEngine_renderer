#include <Quasar.h>

void TestEvent1(uint32_t i)
{
	std::cout << "Event1 passed: " << i << std::endl;
}void TestEvent2(uint32_t i)
{
	std::cout << "Event2 passed: " << i << std::endl;
}

class Sandbox : public Quasar::Application
{
public:
	Quasar::Event event;

	Sandbox()
	{
		event.Add(TestEvent1);
		event.Add(TestEvent1);
		event.Add(TestEvent2);
		//event.Remove(TestEvent1);
		event.Invoke(1);
	}
	~Sandbox()
	{

	}
};

Quasar::Application* Quasar::CreateApplication()
{
	return new Sandbox();
};
