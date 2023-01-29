#pragma once

#include "UraniumApi.h"

#include <memory>
#include <vector>
#include <unordered_map>

namespace Uranium {

	struct vec2;
	struct vec3;
	struct vec4;

	struct mat2;
	struct mat3;
	struct mat4;

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

		bool shaderHas_ViewMatrix;
		bool shaderHas_ProjectionMatrix;
		bool shaderHas_TransformationMatrix;

		bool shaderHas_albedo;
		bool shaderHas_normal;
		bool shaderHas_specular;

		bool shaderHas_color;

		void drawModel(const Model& _model);

		void joinShader();

		void loadEntityAsset(std::shared_ptr<Entity> _entity);
		void loadCameraSettings(std::shared_ptr<Camera> _camera);

		void enableRendererAttribs();
		void disableRendererAttribs();

	};
}