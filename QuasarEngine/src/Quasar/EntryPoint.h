/*
-------------------------------------------------------------------------------
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Vector4 Studios <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Application	:		Quasar Engine

Author		:		Rounak Paul
Email		:		paulrounak1999@gmail.com
Date		:		4th Dec 2023

Description	:		Entry Point for the User Application. Contains main() 
					function. Execution stats here.
-------------------------------------------------------------------------------
*/

#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quasar::Application* Quasar::CreateApplication();

/// <summary>
/// Init methods for Core Engine
/// </summary>
void init() {
	Quasar::Log::Init();
	QS_CORE_INFO("Initiating Quasar Engine...");
}

int main(int argc, char** argv)
{
	init();

	auto app = Quasar::CreateApplication();
	app->Run();
	delete app;
}

#endif
