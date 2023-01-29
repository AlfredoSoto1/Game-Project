#pragma once

#include "UraniumApi.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Uranium {

	struct mat2;
	struct mat3;
	struct mat4;

	struct vec2;
	struct vec3;
	struct vec4;

	class Shader;
	class Texture;

	class ShaderProgram {
	public:
		ShaderProgram(std::shared_ptr<Shader> _computeShader);
		ShaderProgram(std::shared_ptr<Shader> _vertexShader, std::shared_ptr<Shader> _fragmentShader);
		virtual ~ShaderProgram();
		
		// getters
		operator unsigned int() const;

		std::unordered_map<std::string, std::pair<int, unsigned int>>& getVec2_fs();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getVec3_fs();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getVec4_fs();

		std::unordered_map<std::string, std::pair<int, unsigned int>>& getMat2_fs();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getMat3_fs();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getMat4_fs();

		std::unordered_map<std::string, std::pair<int, unsigned int>>& getSampler_2ds();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getSampler_3ds();

		bool hasViewMatrix();
		bool hasProjectionMatrix();
		bool hasTransformationMatrix();

		bool hasColor();
		bool hasAlbedoSampler();
		bool hasNormalSampler();
		bool hasSpecularSampler();

		// setters
		void setViewMatrix(mat4& _mat4) const;
		void setProjectionMatrix(mat4& _mat4) const;
		void setTransformationMatrix(mat4& _mat4) const;
		
		void setColor(const vec4& _color);
		void setAlbedoSampler(std::shared_ptr<Texture> _albedo, int _bindingId);
		void setNormalSampler(std::shared_ptr<Texture> _normal, int _bindingId);
		void setSpecularSampler(std::shared_ptr<Texture> _specular, int _bindingId);

		void setSampler(const Sampler& _sampler, unsigned int _samplerId) const;

		void setMat2(Uniform _uniform, mat2& _mat2) const;
		void setMat3(Uniform _uniform, mat3& _mat3) const;
		void setMat4(Uniform _uniform, mat4& _mat4) const;

		void setVec2(Uniform _uniform, const vec2& _vec2) const;
		void setVec3(Uniform _uniform, const vec3& _vec3) const;
		void setVec4(Uniform _uniform, const vec4& _vec4) const;

		// methods
		void bind() const;
		void unbind() const;

	protected:
		//void dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const;

	private:
		unsigned int program;
		unsigned int compShader;
		unsigned int vertShader;
		unsigned int fragShader;

		unsigned int maxCharUniform;
		unsigned int availableUniformCount;

		int workGroupInvocations;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

		Uniform viewMatrix;
		Uniform projectionMatrix;
		Uniform transformationMatrix;

		Uniform color;

		Sampler albedoSampler;
		Sampler normalSampler;
		Sampler specularSampler;

		bool containsViewMatrix;
		bool containsProjectionMatrix;
		bool containsTransformationMatrix;
		bool constainsColor;
		bool containsAlbedoSampler;
		bool containsNormalSampler;
		bool containsSpecularSampler;

		std::unordered_map<std::string, std::pair<int, unsigned int>> vec2_f;
		std::unordered_map<std::string, std::pair<int, unsigned int>> vec3_f;
		std::unordered_map<std::string, std::pair<int, unsigned int>> vec4_f;

		std::unordered_map<std::string, std::pair<int, unsigned int>> mat2_f;
		std::unordered_map<std::string, std::pair<int, unsigned int>> mat3_f;
		std::unordered_map<std::string, std::pair<int, unsigned int>> mat4_f;
		
		std::unordered_map<std::string, std::pair<int, unsigned int>> sampler_2d;
		std::unordered_map<std::string, std::pair<int, unsigned int>> sampler_3d;

		void readAvailableUniforms();

	};
}