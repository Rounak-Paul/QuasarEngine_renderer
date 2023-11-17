#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quasar::Application* Quasar::CreateApplication();

int main(int argc, char** argv)
{
	Quasar::Log::Init();
	QS_CORE_WARN("Initilized Log!");
	QS_INFO("Hello!");


	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}

#endif