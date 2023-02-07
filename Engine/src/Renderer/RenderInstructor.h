#pragma once

#include "UraniumApi.h"

namespace Uranium {
	
	interface RenderInstructor {
	public:
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
	};
}