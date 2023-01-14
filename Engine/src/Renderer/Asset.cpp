#include "Asset.h"

using namespace Uranium;

void Asset::setModel(std::shared_ptr<Model> _model) {
	model = _model;
}

void Asset::setMaterial(std::shared_ptr<Material> _material) {
	material = _material;
}

void Asset::setShader(std::shared_ptr<ShaderProgram> _shader) {
	shaderProgram = _shader;
}

std::shared_ptr<Model>& Asset::getModel() {
	return model;
}

std::shared_ptr<Material>& Asset::getMaterial() {
	return material;
}

std::shared_ptr<ShaderProgram>& Asset::getShader() {
	return shaderProgram;
}
