#pragma once

#include <memory>

namespace Uranium {

	class Model;
	class Material;

	class Asset {
	public:
		Asset(std::shared_ptr<Model> _model, std::shared_ptr<Material> _material);

		const std::shared_ptr<Model>& getModel() const;
		const std::shared_ptr<Material>& getMaterial() const;

	private:
		std::shared_ptr<Model> model;
		std::shared_ptr<Material> material;
	};
}