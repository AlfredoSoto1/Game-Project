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
		Renderer(ShaderProgram* _shader);
		virtual ~Renderer();

		void push(std::shared_ptr<Entity> _entity);

		void render(std::shared_ptr<Camera> _camera);

	protected:
		void setMat2(Uniform _uniform, mat2& _mat2) const;
		void setMat3(Uniform _uniform, mat3& _mat3) const;
		void setMat4(Uniform _uniform, mat4& _mat4) const;

		void setVec2(Uniform _uniform, const vec2& _vec2) const;
		void setVec3(Uniform _uniform, const vec3& _vec3) const;
		void setVec4(Uniform _uniform, const vec4& _vec4) const;

		void setSampler(const Sampler& _sampler, unsigned int _samplerId) const;

	private:
		bool isWireframe;

		ShaderProgram* shader;

		std::unordered_map<std::shared_ptr<Asset>, std::vector<std::shared_ptr<Entity>>> mappedEntities;

		bool shaderHas_ViewMatrix;
		bool shaderHas_ProjectionMatrix;
		bool shaderHas_TransformationMatrix;

		bool shaderHas_albedo;
		bool shaderHas_normal;
		bool shaderHas_specular;

		bool shaderHas_color;

		void drawModel(const Model& _model);

		void bindModel();
		void unbindModel();

		void bindMaterial();
		void unbindMaterial();

		void joinShader();

		void loadAssets(std::shared_ptr<Asset> _asset);
		void flushAssets(std::shared_ptr<Asset> _asset);

		void loadEntityAsset(std::shared_ptr<Entity> _entity);
		void loadCameraSettings(std::shared_ptr<Camera> _camera);

		void enableRendererAttribs();
		void disableRendererAttribs();

	};
}