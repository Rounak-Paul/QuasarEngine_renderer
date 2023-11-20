#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quasar::Application* Quasar::CreateApplication();

/// <summary>
/// Init method for Core Engine
/// </summary>
void init() {
	Quasar::Log::Init();
	Quasar::Event::Init();
}

int main(int argc, char** argv)
{
	init();

	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}

#endif