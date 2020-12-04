#include "pch.h"
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexArray.h"
#include "Engine/Graphics/VertexIndexArray.h"
#include "Engine/Graphics/Model.h"

int main(int argc, char** argv) {

	nc::Engine engine;
	engine.Startup();

	/*nc::Renderer renderer;
	renderer.Startup();
	renderer.Create("OpenGL", 800, 600);*/

	static float vertices[] =
	{
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,



		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,



		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,



		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,



		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,



		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
	};

	nc::Program program;
	program.CreateShaderFromFile("shaders\\gouraud.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("shaders\\gouraud.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	nc::VertexArray vertexArray;
	vertexArray.Create("vertex");
	//vertexArray.CreateBuffer(sizeof(vertices), sizeof(vertices) / (sizeof(float) * 6), vertices);
	//vertexArray.SetAttribute(0, 3, 6 * sizeof(float) , 0);
	//vertexArray.SetAttribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	nc::Model::Load("models/ogre.obj", positions, normals, texcoords);

	if (!positions.empty()) {
		vertexArray.CreateBuffer(positions.size() * sizeof(glm::vec3), positions.size(), positions.data());
		vertexArray.SetAttribute(0, 3, 0, 0);
	}
	if (!normals.empty()) {
		vertexArray.CreateBuffer(normals.size() * sizeof(glm::vec3), normals.size(), normals.data());
		vertexArray.SetAttribute(1, 3, 0, 0);
	}
	if (!texcoords.empty()) {
		vertexArray.CreateBuffer(texcoords.size() * sizeof(glm::vec2), texcoords.size(), texcoords.data());
		vertexArray.SetAttribute(2, 2, 0, 0);
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800 / 600.0f, 0.01f, 1000.0f);

	glm::vec3 eye{ 0, 0, 5 };
	glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	nc::Texture texture;
	texture.CreateTexture("textures\\llama.jpg");

	program.SetUniform("material.ambient", glm::vec3{ 1, 1, 1 });
	program.SetUniform("material.diffuse", glm::vec3{ 1, 1, 1 });
	program.SetUniform("material.specular", glm::vec3{ 1, 1, 1 });
	program.SetUniform("material.shininess", 32.0f);

	program.SetUniform("light.ambient", glm::vec3{ 0.1f, 0.8f, 0.1f });
	program.SetUniform("light.diffuse", glm::vec3{ 0, 0, 1 });
	program.SetUniform("light.specular", glm::vec3{ 0, 0, 1 });
	glm::vec4 light{ 5, 2, 5, 1 };

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

		model = glm::rotate(model, angle * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));
		
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD) {
			eye.x -= 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD) {
			eye.x += 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD) {
			eye.y += 4 * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == nc::InputSystem::eButtonState::HELD) {
			eye.y -= 4 * engine.GetTimer().DeltaTime();
		}

		view = glm::lookAt(eye, eye + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		glm::mat4 mvp = projection * view * model;
		program.SetUniform("mvp", mvp);

		glm::mat4 model_view = view * model;
		program.SetUniform("model_view", model_view);

		glm::vec4 position = view * light;
		program.SetUniform("light.position", position);

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		vertexArray.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}