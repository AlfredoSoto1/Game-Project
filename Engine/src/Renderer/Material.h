#pragma once

#include <memory>

namespace Uranium {

	class Texture;

	class Material {
	public:
		void setAlbedo(std::shared_ptr<Texture> _albedoTexture);
		void setNormal(std::shared_ptr<Texture> _normalTexture);
		void setSpecular(std::shared_ptr<Texture> _specularTexture);

		const std::shared_ptr<Texture>& getAlbedo() const;
		const std::shared_ptr<Texture>& getNormal() const;
		const std::shared_ptr<Texture>& getSpecular() const;

	private:
		std::shared_ptr<Texture> albedo;
		std::shared_ptr<Texture> normal;
		std::shared_ptr<Texture> specular;

	};

}