#pragma once

#include <memory>

namespace Uranium {

	class Model;
	class Material;
	class ShaderProgram;

	class Asset	{
	public:
		std::shared_ptr<Model>& getModel();
		std::shared_ptr<Material>& getMaterial();
		std::shared_ptr<ShaderProgram>& getShader();

		void setModel(std::shared_ptr<Model> _model);
		void setMaterial(std::shared_ptr<Material> _material);
		void setShader(std::shared_ptr<ShaderProgram> _shader);

	private:
		std::shared_ptr<Model> model;
		std::shared_ptr<Material> material;
		std::shared_ptr<ShaderProgram> shaderProgram;

	};
}