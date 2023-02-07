#pragma once

#include <string>
#include <memory>
#include "UraniumApi.h"

#include "RigidBody.h"
#include "Renderer/Runnable.h"
#include "Renderer/Renderable.h"
#include "Renderer/AccesibleShader.h"

namespace Uranium {

	class Asset;

	class Entity : implements AccesibleShader, implements Renderable, implements Runnable {
	public:
		Entity(Entity&& _move) noexcept;
		Entity(const Entity& _copy);

		Entity(const std::shared_ptr<Asset>& _asset, const std::string& _name);
		virtual ~Entity();
		
		unsigned int getId() const;

		std::string getName() const;

		RigidBody& getRigidBody();
		std::shared_ptr<Asset>& getAsset();

		void setAsset(const std::shared_ptr<Asset>& _asset);

		void bindUniforms(std::shared_ptr<ShaderProgram> _shader);
		void preBindUniforms(std::shared_ptr<ShaderProgram> _shader);

		void run();
		void update();
		void render();
		void dispose();

	private:
		static unsigned int universal_entity_id_counter;

		unsigned int id;

		std::string name;

		RigidBody rigidBody;

		std::shared_ptr<Asset> asset;

	};
}