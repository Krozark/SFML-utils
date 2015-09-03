#ifndef App_h
#define App_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/String.hpp>
#include "GUIManager.h"

class App
{
public:
	static const unsigned int Width = 800, Height = 600;

	App();

	bool Initialize();
	void Run();
	void Stop() {mDone = true;}

	bool onDialog_Closed(const CEGUI::EventArgs& e);
	bool onEditbox_TextChanged(const CEGUI::EventArgs& e);

private:
	sf::RenderWindow mWindow;
	GUIManager mGUIManager;
	bool mDone;
	sf::String mString;
};

#endif
