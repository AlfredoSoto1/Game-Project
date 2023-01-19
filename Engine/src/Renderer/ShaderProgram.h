#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "UraniumApi.h"

namespace Uranium {

	struct vec2;
	struct vec3;
	struct vec4;

	struct mat2;
	struct mat3;
	struct mat4;

	class Camera;

	class ShaderProgram {
	public:
		ShaderProgram(const char* _vertexPath, const char* _fragmentPath);
		virtual ~ShaderProgram();

		operator unsigned int() const;

		void bind() const;
		void unbind() const;

		std::vector<int> getSamplers();
		std::vector<int> getMatrices();
		std::vector<int> getVectors();

		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformFlags();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformSamplers();

		void setAlbedoSampler(int _albedoSampler);
		void setNormalSampler(int _normalSampler);
		void setSpecularSampler(int _specularSampler);

		void setSampler(const Sampler& _sampler, unsigned int _samplerId) const;

		void setMat2(Uniform _uniform, mat2& _mat2) const;
		void setMat3(Uniform _uniform, mat3& _mat3) const;
		void setMat4(Uniform _uniform, mat4& _mat4) const;

		void setVec2(Uniform _uniform, const vec2& _vec2) const;
		void setVec3(Uniform _uniform, const vec3& _vec3) const;
		void setVec4(Uniform _uniform, const vec4& _vec4) const;

	protected:
		//void dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const;

	private:
		unsigned int program;
		unsigned int compShader;
		unsigned int vertShader;
		unsigned int fragShader;

		std::unordered_map<std::string, std::pair<int, unsigned int>> uniformFlags;
		std::unordered_map<std::string, std::pair<int, unsigned int>> uniformSamplers;

		int workGroupInvocations;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

		void sourceToString(const char* _path, std::string* shaderSource);

		unsigned int compile(unsigned int _shaderType, std::string& _shaderSource);
		unsigned int createShader(unsigned int _shaderType, const char* _path);

		void retrieveUniforms();

	};
}