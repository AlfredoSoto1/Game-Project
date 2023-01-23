#pragma once

#include "UraniumApi.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Uranium {

	class Shader;

	class ShaderProgram {
	public:
		ShaderProgram(std::shared_ptr<Shader> _computeShader);
		ShaderProgram(std::shared_ptr<Shader> _vertexShader, std::shared_ptr<Shader> _fragmentShader);
		virtual ~ShaderProgram();

		operator unsigned int() const;

		void bind() const;
		void unbind() const;

		unsigned int getMaxCharUniform();
		unsigned int getAvailableUniformCount();

		Uniform getViewU();
		Uniform getProjectionU();
		Uniform getTransformationU();

		Uniform getColorU();
		Uniform getAlbedoU();
		Uniform getNormalU();
		Uniform getSpecularU();

		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformFlags();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformSamplers();
	
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformVectors();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformMatrices();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformSamplers2D();
		std::unordered_map<std::string, std::pair<int, unsigned int>>& getUniformSamplers3D();

	protected:
		//void dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const;

	private:
		unsigned int program;
		unsigned int compShader;
		unsigned int vertShader;
		unsigned int fragShader;

		unsigned int maxCharUniform;
		unsigned int availableUniformCount;

		std::unordered_map<std::string, std::pair<int, unsigned int>> uniformFlags;
		std::unordered_map<std::string, std::pair<int, unsigned int>> uniformSamplers;

		int workGroupInvocations;

		int workGroupMaxSize[3];
		int workGroupMaxCount[3];

		void readAvailableUniforms();

	};
}