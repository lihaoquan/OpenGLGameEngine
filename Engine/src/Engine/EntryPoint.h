#pragma once

#ifdef EG_PLATFORM_WINDOWS

// Look for, within the Engine namespace, a function called CreateApplication that returns a pointer of Application class
extern Engine::Application* Engine::CreateApplication();

// Get number of command line arguments as well as the arguments themselves
int main(int argc, char** argv) {

	Engine::Log::Init();
	EG_CORE_WARN("Engine Logger Initialized!");
	int a = 5;
	EG_INFO("App Logger Initialized! Var={0}", a);

	// Heap allocation to manually control the lifetime of sandbox
	// Auto is used here to let allow the app class to be of any type
	// User might name their file x.cpp, or y.cpp, and have class X or Y, we do not know what class they are going to use,
	// we only know that they will have the CreateApplication function and therefore we use auto to "guess" the class and then
	// call the function that we know will definitely be there.
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif