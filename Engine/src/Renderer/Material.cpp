#define GLEW_STATIC
#include <GL/glew.h>

#include "Texture.h"
#include "Material.h"
#include "Utils/Geometry/Model.h"
#include "Utils/Buffers/IndexBuffer.h"

using namespace Uranium;

Material::Material()
{

}

Material::~Material() {

}

void Material::bind() const {
	if (albedo != nullptr)
		albedo->bind(currentSamplerCount++);
	if (normal != nullptr)
		normal->bind(currentSamplerCount++);
	if (specular != nullptr)
		specular->bind(currentSamplerCount++);
}
void Material::unbind() const {
	if (albedo != nullptr)
		albedo->unbind();
	if (normal != nullptr)
		normal->unbind();
	if (specular != nullptr)
		specular->unbind();

	currentSamplerCount = 0;
}

void Material::setAlbedo(const std::string& _name, std::shared_ptr<Texture> _albedoTexture) {
	albedoName = _name;
	albedo = _albedoTexture;
}
void Material::setNormal(const std::string& _name, std::shared_ptr<Texture> _normalTexture) {
	normalName = _name;
	normal = _normalTexture;
}
void Material::setSpecular(const std::string& _name, std::shared_ptr<Texture> _specularTexture) {
	specularName = _name;
	specular = _specularTexture;
}

const std::string& Material::getAlbedoName() const {
	return albedoName;
}
const std::string& Material::getNormalName() const {
	return normalName;
}
const std::string& Material::getSpecularName() const {
	return specularName;
}

const std::shared_ptr<Texture>& Material::getAlbedo() const {
	return albedo;
}
const std::shared_ptr<Texture>& Material::getNormal() const {
	return normal;
}
const std::shared_ptr<Texture>& Material::getSpecular() const {
	return specular;
}

void Material::staticUniforms(unsigned int _program) {
	if (albedo != nullptr)
		albedoSampler = getUniform(_program, albedoName.c_str());
	if (normal != nullptr)
		normalSampler = getUniform(_program, normalName.c_str());
	if (specular != nullptr)
		specularSampler = getUniform(_program, specularName.c_str());
}

void Material::updateUniforms(unsigned int _program) {
	if (albedo != nullptr)
		setSampler(albedoSampler, samplerCounter++);
	if (normal != nullptr)
		setSampler(normalSampler, samplerCounter++);
	if (specular != nullptr)
		setSampler(specularSampler, samplerCounter++);

	// add more samplers here and increase sampler counter == binding ID
}
