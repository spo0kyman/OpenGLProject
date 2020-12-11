#include "pch.h"
#include "Engine/Engine.h"
#include "Engine/Graphics/VertexArray.h"
#include "Engine/Graphics/VertexIndexArray.h"
#include "Engine/Graphics/Model.h"

int main(int argc, char** argv) {

	nc::Engine engine;
	engine.Startup();

	nc::Scene scene{ &engine };

	nc::Program program;
	program.CreateShaderFromFile("shaders\\phong.vert", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("shaders\\phong.frag", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	nc::VertexArray vertexArray;
	vertexArray.Create("vertex");

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	nc::Model::Load("models/cube.obj", positions, normals, texcoords);

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

	nc::Camera camera{ "camera" };
	scene.Add(&camera);
	glm::vec3 eye{ 0, 0, 5 };
	camera.SetProjection(45.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
	camera.SetLookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800 / 600.0f, 0.01f, 1000.0f);
	//glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	nc::Texture texture;
	texture.CreateTexture("textures\\ogre_diffuse_flip.bmp");

	nc::Material material{ glm::vec3{1}, glm::vec3{1}, glm::vec3{1}, 32.0f };
	material.AddTexture(texture);
	material.SetProgram(program);

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

		model = glm::rotate(model, angle * engine.GetTimer().DeltaTime(), glm::vec3(0, 1, 0));
		
		/*view = glm::lookAt(eye, eye + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));*/

		glm::mat4 mvp = camera.projection() * camera.view() * model;
		program.SetUniform("mvp", mvp);

		glm::mat4 model_view = camera.view() * model;
		program.SetUniform("model_view", model_view);

		std::vector<nc::Light*> lights = scene.Get<nc::Light>();
		for (auto light : lights) {
			light->SetProgram(program);
		}

		/*glm::vec4 position = camera.view() * light;
		program.SetUniform("light.position", position);*/

		engine.GetSystem<nc::Renderer>()->BeginFrame();

		vertexArray.Draw();
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}