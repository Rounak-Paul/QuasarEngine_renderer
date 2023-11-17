#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quasar::Application* Quasar::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}

#endif