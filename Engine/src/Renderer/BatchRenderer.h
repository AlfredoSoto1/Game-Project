#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium {

	class Model;
	class Camera;
	class Entity;
	class ShaderProgram;

	class BatchRenderer {
	public:
		BatchRenderer(ShaderProgram* _shader);
		virtual ~BatchRenderer();

		void submit(const Entity&& _entity);

		void render(Camera* _camera);

	private:
		bool isWireframe;

		ShaderProgram* shader;

		std::unordered_map<std::shared_ptr<Model>, std::vector<Entity>> entityBatch;

		void renderCallstack();

	};
}