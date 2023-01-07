#pragma once

namespace Uranium {

	class ApplicationRunner {
	private:

	public:
		virtual void init()    = 0;
		virtual void run()     = 0;
		virtual void dispose() = 0;
	};
}