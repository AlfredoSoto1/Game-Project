#pragma once

#include "UraniumApi.h"

#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium {

	class Asset;
	class Model;
	class Entity;
	class Camera;
	class Material;
	class ShaderProgram;

	class Renderer { 
	public:
		Renderer(std::shared_ptr<ShaderProgram> _shader);
		virtual ~Renderer();

		void push(std::shared_ptr<Entity> _entity);
		void render(std::shared_ptr<Camera> _camera);

	private:
		bool isWireframe;

		std::shared_ptr<ShaderProgram> shader;

		std::unordered_map<std::shared_ptr<Asset>, std::vector<std::shared_ptr<Entity>>> mappedEntities;

		void drawModel(const Model& _model);

		void joinShader();
	};
}