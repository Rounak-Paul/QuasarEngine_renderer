#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quasar::Application* Quasar::CreateApplication();

void init() {
	Quasar::Log::Init();
	Quasar::Event::Init();
}

int main(int argc, char** argv)
{
	init();

	QS_CORE_WARN("Initilized Log!");
	QS_INFO("Hello!");


	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}

#endif