#include "stdafx.h"

#include "Engine.h"

int main(int argc, char** argv) {

	Engine* engine = new Engine();
	engine->loop();

	delete engine;

	return 0;
}
