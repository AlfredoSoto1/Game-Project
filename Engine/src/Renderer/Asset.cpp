#include "Asset.h"

using namespace std;
using namespace Uranium;

Asset::Asset(shared_ptr<Model> _model, shared_ptr<Material> _material)
	: model(_model), material(_material)
{

}

const shared_ptr<Model>& Asset::getModel() const {
	return model;
}

const shared_ptr<Material>& Asset::getMaterial() const {
	return material;
}
