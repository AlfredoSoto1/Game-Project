#include "Material.h"

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
