#pragma once

#include "UraniumApi.h"

namespace Uranium {
	interface Updatable {
	public:
		virtual void update() = 0;
	};
}