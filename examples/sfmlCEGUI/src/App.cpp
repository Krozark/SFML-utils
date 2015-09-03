#include "App.h"
#include <CEGUI.h>

using namespace CEGUI;

App::App() : mDone(false)
{
}

bool App::Initialize()
{
	sf::VideoMode Mode(Width, Height, 32);

	mWindow.Create(Mode, "sfmlCEGUI", sf::Style::Close);
	mWindow.ShowMouseCursor(false);
	if (!mGUIManager.Initialize(&mWindow))
		return false;

	mString.SetPosition(300.0f, 400.0f);
	/***************** Create our dialog **********************/
	try
	{
		CEGUI::WindowManager* WindowMgr = mGUIManager.getWindowManager();
		CEGUI::Window* Dialog = WindowMgr->createWindow("WindowsLook/FrameWindow", "OurDialog");
		Dialog->setMinSize(UVector2(UDim(0.0f, 200),UDim(0.0f, 150)));
		Dialog->setSize(UVector2(UDim(0.0f, 400),UDim(0.0f, 300)));
		Dialog->setPosition(UVector2(UDim(0.25f, 0), UDim(0.1f, 0)));
		Dialog->setText("Window");
		Dialog->subscribeEvent(FrameWindow::EventCloseClicked, Event::Subscriber(&App::onDialog_Closed, this));
		CEGUI::Window* EditBox = WindowMgr->createWindow("WindowsLook/Editbox", "OurDialog_Editbox");
		EditBox->setMinSize(UVector2(UDim(0.0f, 100), UDim(0.0f, 20)));
		EditBox->setSize(UVector2(UDim(0.5f, 0), UDim(0.1f, 0)));
		EditBox->setPosition(UVector2(UDim(0.25f, 0), UDim(0.4f, 0)));
		EditBox->subscribeEvent(CEGUI::Window::EventTextChanged, Event::Subscriber(&App::onEditbox_TextChanged, this));
		Dialog->addChildWindow(EditBox);
		mGUIManager.setRootWindow(Dialog);
	}
	catch (CEGUI::Exception& e)
	{
		printf("CEGUI Exception: %s\n", e.getMessage().c_str());
		return false;
	}
	return true;
}

void App::Run()
{
	sf::Event Event;

	while (!mDone)
	{
		while (mWindow.GetEvent(Event))
		{
			//See if CEGUI should handle it
			if (mGUIManager.handleEvent(Event))
				continue;

			switch (Event.Type)
			{
			case sf::Event::Closed:
				Stop();
				break;
			case sf::Event::KeyPressed:
				if (Event.Key.Code == sf::Key::Escape)
					Stop();

				break;
			}
		}
		mWindow.Draw(mString);
		mGUIManager.Draw();
		mWindow.Display();
	}
}

/************************************************************************/
/*                            Private                                   */
/************************************************************************/

bool App::onDialog_Closed(const CEGUI::EventArgs& e)
{
	Stop();
	return true;
}

bool App::onEditbox_TextChanged(const CEGUI::EventArgs& e)
{
	CEGUI::WindowManager* WindowMgr = mGUIManager.getWindowManager();

	CEGUI::Window* Edit = WindowMgr->getWindow("OurDialog_Editbox");
	mString.SetText(Edit->getText().c_str());
	return true;
}
