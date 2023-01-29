#include "Material.h"
#include "Texture.h"
#include "ShaderProgram.h"

using namespace Uranium;

void Material::setAlbedo(std::shared_ptr<Texture> _albedoTexture) {
	albedo = _albedoTexture;
}
void Material::setNormal(std::shared_ptr<Texture> _normalTexture) {
	normal = _normalTexture;
}
void Material::setSpecular(std::shared_ptr<Texture> _specularTexture) {
	specular = _specularTexture;
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

void Material::setColor(const vec4& _color) {
	color = _color;
}

vec4& Material::getColor() {
	return color;
}

void Material::bind(std::shared_ptr<ShaderProgram> _shader) const {

	// load color to shader
	if (_shader->hasColor()) { // check if shader has color support
		_shader->setColor(color);
	}

	// load texture to shader
	if (albedo != nullptr && _shader->hasAlbedoSampler()) {
		albedo->bind(0);
		_shader->setAlbedoSampler(albedo, 0);
	}
	if (normal != nullptr && _shader->hasNormalSampler()) {
		normal->bind(1);
		_shader->setNormalSampler(normal, 1);
	}
	if (specular != nullptr && _shader->hasSpecularSampler()) {
		specular->bind(2);
		_shader->setSpecularSampler(specular, 2);
	}
}

void Material::unbind() const {
	// unbind all material textures
	if (albedo != nullptr) {
		albedo->unbind();
	}
	if (normal != nullptr) {
		normal->unbind();
	}
	if (specular != nullptr) {
		specular->unbind();
	}
}
