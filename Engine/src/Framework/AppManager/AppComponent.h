#pragma once

namespace FrameworkEngine {
	
	class Application;

	class AppComponent {
	private:
		friend class Application;

		Application* reference;

	protected:
		AppComponent(Application* _reference);

		Application* getAppRef();

	};
}