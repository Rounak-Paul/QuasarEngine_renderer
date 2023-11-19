#include <Quasar.h>

class Sandbox : public Quasar::Application
{
public:
	Sandbox()
	{
		QS_TRACE("Test from client");
	}
	~Sandbox()
	{

	}
};

Quasar::Application* Quasar::CreateApplication()
{
	return new Sandbox();
};