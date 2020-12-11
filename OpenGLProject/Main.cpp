#include "pch.h"
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexArray.h"
#include "Engine/Graphics/VertexIndexArray.h"
#include "Engine/Objects/Model.h"

int main(int argc, char** argv) {

	nc::Engine engine;
	engine.Startup();

	nc::Scene scene{ &engine };

	nc::Program program;
	program.CreateShaderFromFile("shaders\\phong.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("shaders\\phong.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	nc::VertexArray vertexArray = nc::Model::Load("models/ogre.obj");


	nc::Texture texture;
	texture.CreateTexture("textures\\ogre_diffuse_flip.bmp");

	nc::Material material{ glm::vec3{1}, glm::vec3{1}, glm::vec3{1}, 32.0f };
	material.AddTexture(texture);
	material.SetProgram(program);

	glm::mat4 model1 = glm::mat4(1.0f);
	nc::Model model{ "model", nc::Transform{}, vertexArray, program, material };
	scene.Add(&model);

	nc::Camera camera{ "camera" };
	scene.Add(&camera);
	glm::vec3 eye{ 0, 0, 5 };
	camera.SetProjection(45.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
	camera.SetLookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	nc::Light light{ "light",
		nc::Transform{ glm::vec3{5, 2, 5} },
		glm::vec3{ 0.1f },
		glm::vec3{ 1 },
		glm::vec3{ 1 } };
	scene.Add(&light);

	scene.Add(&light);

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

		scene.Update(engine.GetTimer().DeltaTime());

		float angle = 0;

		model1 = glm::rotate(model1, angle * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));

		std::vector<nc::Light*> lights = scene.Get<nc::Light>();
		for (auto light : lights) {
			light->SetProgram(program);
		}

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}