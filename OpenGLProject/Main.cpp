#include "pch.h"
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexArray.h"
#include "Engine/Graphics/VertexIndexArray.h"

int main(int argc, char** argv) {

	nc::Engine engine;
	engine.Startup();

	/*nc::Renderer renderer;
	renderer.Startup();
	renderer.Create("OpenGL", 800, 600);*/

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
	//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
	//};

	static float vertices[] = {
		//font
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		//back
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
	};

	static GLushort indices[] = {
		//front
		0, 1, 2,
		2, 3, 0,
		//right
		1, 5, 6,
		6, 2, 1,
		//back
		7, 6, 5,
		5, 4, 7,
		//left
		4, 0, 3,
		3, 7, 4,
		//bottom
		4, 5, 1,
		1, 0, 4,
		//top
		3, 2, 6,
		6, 7, 3
	};

	nc::Program program;
	program.CreateShaderFromFile("shaders\\basic.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("shaders\\basic.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	nc::VertexIndexArray vertexIndexArray;
	vertexIndexArray.Create("vertex");
	vertexIndexArray.CreateBuffer(sizeof(vertices), sizeof(vertices) / (sizeof(float) * 5), vertices);
	vertexIndexArray.SetAttribute(0, 3, 5 * sizeof(float) , 0);
	vertexIndexArray.SetAttribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));
	vertexIndexArray.CreateIndexBuffer(GL_UNSIGNED_SHORT, sizeof(indices) / sizeof(GLushort), indices);


	glm::mat4 transform = glm::mat4(1.0f);
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800 / 600.0f, 0.01f, 1000.0f);

	glm::vec3 eye{ 0, 0, 5 };
	glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	nc::Texture texture;
	texture.CreateTexture("textures\\llama.jpg");

	bool quit = false;
	while (!quit) {
		SDL_Event event;

		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:quit = true;
			break;
		case SDL_KEYDOWN:if (event.key.keysym.sym == SDLK_ESCAPE) {
			quit = true;
		}

		}
		SDL_PumpEvents();
		engine.Update();

		float angle = 0;
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_E) == nc::InputSystem::eButtonState::HELD) {
			angle = 2;
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_Q) == nc::InputSystem::eButtonState::HELD) {
			angle = -2;
		}

		transform = glm::rotate(transform, angle * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));
		
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD) {
			eye.x -= 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			eye.x += 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD) {
			eye.z -= 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD) {
			eye.z += 4 * engine.GetTimer().DeltaTime();
		}

		view = glm::lookAt(eye, eye + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		glm::mat4 mvp = projection * view * transform;

		program.SetUniform("transform", mvp);

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		vertexIndexArray.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}