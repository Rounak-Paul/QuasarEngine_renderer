#include <Quasar.h>

class Sandbox : public Quasar::Application
{
public:
	Sandbox()
	{
		
	}
	~Sandbox()
	{

	}
};

Quasar::Application* Quasar::CreateApplication()
{
	return new Sandbox();
};