#pragma once

#include "UraniumApi.h"

namespace Uranium {

	interface Runnable {
	public:
		virtual void run() = 0;
		virtual void update() = 0;
		virtual void dispose() = 0;
	};
}