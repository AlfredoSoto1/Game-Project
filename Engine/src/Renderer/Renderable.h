#pragma once

#include "UraniumApi.h"

namespace Uranium {
	interface Renderable {
	public:
		virtual void render() = 0;
		virtual void dispose() = 0;

	};
}