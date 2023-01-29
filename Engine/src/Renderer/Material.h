#pragma once

#include <memory>

#include "Utils/Maths/vec4.h"

namespace Uranium {

	class Texture;
	class ShaderProgram;

	class Material {
	public:
		void setAlbedo(std::shared_ptr<Texture> _albedoTexture);
		void setNormal(std::shared_ptr<Texture> _normalTexture);
		void setSpecular(std::shared_ptr<Texture> _specularTexture);


		const std::shared_ptr<Texture>& getAlbedo() const;
		const std::shared_ptr<Texture>& getNormal() const;
		const std::shared_ptr<Texture>& getSpecular() const;

		void setColor(const vec4& _color);

		vec4& getColor();

		void bind(std::shared_ptr<ShaderProgram> _shader) const;
		void unbind() const;

	private:
		std::shared_ptr<Texture> albedo;
		std::shared_ptr<Texture> normal;
		std::shared_ptr<Texture> specular;

		vec4 color;

	};

}