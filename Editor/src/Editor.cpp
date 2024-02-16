#include <Quasar.h>

class Editor : public Quasar::Application
{
public:
	

	Editor()
	{
		
	}
	~Editor()
	{

	}
};

Quasar::Application* Quasar::CreateApplication()
{
	return new Editor();
};
