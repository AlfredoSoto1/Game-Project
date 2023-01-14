#pragma once

#include <string>
#include <memory>

#include "Renderer/AccesibleShader.h"

namespace Uranium {

	class Texture;

	class Material : public AccesibleShader {
	public:
		Material();
		virtual ~Material();

		void setAlbedo(const std::string& _name, std::shared_ptr<Texture> _albedoTexture);
		void setNormal(const std::string& _name, std::shared_ptr<Texture> _normalTexture);
		void setSpecular(const std::string& _name, std::shared_ptr<Texture> _specularTexture);
	
		const std::string& getAlbedoName() const;
		const std::string& getNormalName() const;
		const std::string& getSpecularName() const;

		const std::shared_ptr<Texture>& getAlbedo() const;
		const std::shared_ptr<Texture>& getNormal() const;
		const std::shared_ptr<Texture>& getSpecular() const;

	protected:
		void bind() const;
		void unbind() const;

		virtual void staticUniforms(unsigned int _program);
		virtual void updateUniforms(unsigned int _program);

	private:
		friend class BatchRenderer;

		std::shared_ptr<Texture> albedo;
		std::shared_ptr<Texture> normal;
		std::shared_ptr<Texture> specular;

		std::string albedoName;
		std::string normalName;
		std::string specularName;

		int samplerCounter;
		mutable int currentSamplerCount;

		Sampler albedoSampler;
		Sampler normalSampler;
		Sampler specularSampler;
	};

}