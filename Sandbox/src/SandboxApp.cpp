#include <Engine.h>

class Sandbox : public Engine::Application {

public:
	Sandbox() {

	}

	~Sandbox() {
			
	}

};

Engine::Application* Engine::CreateApplication() {
	printf("Application Created");
	return new Sandbox();
}