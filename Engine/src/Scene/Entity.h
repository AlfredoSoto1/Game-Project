#pragma once

#include <string>
#include <memory>
#include "UraniumApi.h"

#include "RigidBody.h"
#include "Renderer/AccesibleShader.h"

namespace Uranium {

	class Asset;

	class Entity {
	public:
		Entity(Entity&& _move) noexcept;
		Entity(const Entity& _copy);

		Entity(const std::shared_ptr<Asset>& _asset, const std::string& _name);
		virtual ~Entity();
		
		unsigned int getId() const;

		std::string getName() const;

		RigidBody& getRigidBody();
		std::shared_ptr<Asset>& getAsset();

		void setName(const std::string& _name);
		void setRigidBody(const RigidBody& _rigidBody);
		void setAsset(const std::shared_ptr<Asset>& _asset);

	private:
		static unsigned int universal_entity_id_counter;

		unsigned int id;

		std::string name;

		RigidBody rigidBody;

		std::shared_ptr<Asset> asset;

	};
}