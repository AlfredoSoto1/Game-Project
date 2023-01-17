#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium {

	class Asset;
	class Entity;
	class Camera;
	class ShaderProgram;

	class Renderer { 
	public:
		Renderer(ShaderProgram* _shader);
		virtual ~Renderer();

		void submit(std::shared_ptr<Entity> _entity);

		void render(Camera* _camera);

	private:
		bool isWireframe;

		ShaderProgram* defaultShader;

		std::unordered_map<std::shared_ptr<Asset>, std::vector<std::shared_ptr<Entity>>> mappedEntities;
	};
}