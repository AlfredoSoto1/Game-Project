#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

namespace MathsUtils {
	struct vec2; 
	struct vec3;
	struct vec4;
	struct mat2;
	struct mat3;
	struct mat4;
}

namespace Render {
	class Renderer;
}

namespace Graphics {

	class Shader;

	class ShaderProgram { 
	private:
		friend class Render::Renderer;

		uint32_t program;
		uint32_t compShader;
		uint32_t vertShader;
		uint32_t fragShader;
		uint32_t geomShader;

		int32_t workGroupInvocations;

		int32_t workGroupMaxSize[3];
		int32_t workGroupMaxCount[3];

		mutable std::unordered_map<std::string, int32_t> uniformLocations;

		void source_toString(const char* _path, std::string* shaderSource);

		uint32_t createShader(uint32_t _shaderType, const char* _path);
		uint32_t compile(uint32_t _shaderType, std::string& _shaderSource);

	protected:
		virtual void load() const = 0;
		virtual void update() const = 0;
		virtual void unload() const = 0;

		void dispatchCompute(uint32_t groupX, uint32_t groupY, uint32_t groupZ, uint32_t barrier) const;

		int32_t getUniformLocation(const std::string& _name) const;

		void setFloat(const char* _name, const float& _v) const;
		void setVec2(const char* _name, const MathsUtils::vec2& _vec2) const;
		void setVec3(const char* _name, const MathsUtils::vec3& _vec3) const;
		void setVec4(const char* _name, const MathsUtils::vec4& _vec4) const;

		void setInt1(const char* _name, const int32_t& x) const;
		void setInt2(const char* _name, const int32_t& x, const int32_t& y) const;
		void setInt3(const char* _name, const int32_t& x, const int32_t& y, const uint32_t& z) const;
		void setInt4(const char* _name, const int32_t& x, const int32_t& y, const uint32_t& z, const uint32_t& w) const;
		
		void setMat2(const char* _name, MathsUtils::mat2& _mat2) const;
		void setMat3(const char* _name, MathsUtils::mat3& _mat3) const;
		void setMat4(const char* _name, MathsUtils::mat4& _mat4) const;

		void setFloat(int32_t _location, const float& _v) const;
		void setVec2(int32_t _location, const MathsUtils::vec2& _vec2) const;
		void setVec3(int32_t _location, const MathsUtils::vec3& _vec3) const;
		void setVec4(int32_t _location, const MathsUtils::vec4& _vec4) const;

		void setInt1(int32_t _location, const int32_t& x) const;
		void setInt2(int32_t _location, const int32_t& x, const int32_t& y) const;
		void setInt3(int32_t _location, const int32_t& x, const int32_t& y, const uint32_t& z) const;
		void setInt4(int32_t _location, const int32_t& x, const int32_t& y, const uint32_t& z, const uint32_t& w) const;

		void setMat2(int32_t _location, MathsUtils::mat2& _mat2) const;
		void setMat3(int32_t _location, MathsUtils::mat3& _mat3) const;
		void setMat4(int32_t _location, MathsUtils::mat4& _mat4) const;

	public:
		ShaderProgram(const char* _computeShader_path);
		ShaderProgram(const char* _vertexShader_path, const char* _fragmentShader_path);
		ShaderProgram(const char* _geometryShader_path, const char* _vertexShader_path, const char* _fragmentShader_path);

		virtual ~ShaderProgram();

		operator uint32_t() const;

		void bind() const;
		void unbind() const;
	};
}