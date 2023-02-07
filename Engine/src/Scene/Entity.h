#pragma once

#include <string>
#include <memory>
#include "UraniumApi.h"

#include "RigidBody.h"
#include "Scene/Updatable.h"
#include "Renderer/ShaderProcessor.h"

namespace Uranium {

	class Asset;

	class Entity : implements ShaderProcessor, implements Updatable {
	public:
		// copy constructor
		Entity(const Entity& _copy);
		// move constructor
		Entity(Entity&& _move) noexcept;
		// default entity constructor
		Entity(const std::shared_ptr<Asset>& _asset, const std::string& _name);
		virtual ~Entity();
		
		unsigned int getId() const;

		std::string getName() const;

		RigidBody& getRigidBody();
		std::shared_ptr<Asset>& getAsset();

		void setAsset(const std::shared_ptr<Asset>& _asset);

		// TODO temp: remove when abstraction is used
		void update();
		void processShaderInstructions(std::shared_ptr<ShaderProgram> _shader);

	private:
		static unsigned int universal_entity_id_counter;

		unsigned int id;

		std::string name;

		RigidBody rigidBody;

		std::shared_ptr<Asset> asset;

	};
}