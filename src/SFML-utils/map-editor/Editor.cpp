#include <SFML-utils/map-editor/Editor.hpp>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

//https://bitbucket.org/lucebac/cegui/src/ea8f8c814a4d5dbaa56344218659eb68ce173961/application_templates/SDL2.cpp?at=application-templates-devel


namespace sfutils
{
    namespace editor
    {
        Editor::Editor(const sf::VideoMode& mode):
            _window(mode,"SFML-utils map editor"),
            _renderer(nullptr),
            _system(nullptr)
        {
            _window.setFramerateLimit(65);
            //_window.setMouseCursorVisible(false);

            _renderer = &CEGUI::OpenGLRenderer::create(CEGUI::Sizef(_window.getSize().x,_window.getSize().y));
            _renderer->enableExtraStateSettings(true);
            _system = &CEGUI::System::create(*_renderer);

            
            CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

            rp->setResourceGroupDirectory("fonts", "media/datafiles/fonts/");
            rp->setResourceGroupDirectory("imagesets", "media/datafiles/imagesets/");
            rp->setResourceGroupDirectory("layouts", "media/datafiles/layouts/");
            rp->setResourceGroupDirectory("looknfeels", "media/datafiles/looknfeel/");
            rp->setResourceGroupDirectory("schemes", "media/datafiles/schemes/");
            //rp->setResourceGroupDirectory("lua_scripts", "media/datafiles/lua_scripts/");
            // set the default resource groups to be used
            CEGUI::Font::setDefaultResourceGroup("fonts");
            CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
            CEGUI::WindowManager::setDefaultResourceGroup("layouts");
            CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
            CEGUI::Scheme::setDefaultResourceGroup("schemes");
            //CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
            
            CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
            if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
                parser->setProperty("SchemaDefaultResourceGroup", "schemas");

            
            // create (load) the TaharezLook scheme file
            // (this auto-loads the TaharezLook looknfeel and imageset files)
            CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme", "schemes");
            CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");


            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
            CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");


            CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("TabControlDemo.layout");
            CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
            
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(_window.getSize().x,_window.getSize().y));

        }

        Editor::~Editor()
        {
            CEGUI::System::destroy();
            CEGUI::OpenGLRenderer::destroy(*_renderer);
        }

        void Editor::run()
        {
            /***************** Create our dialog **********************/
            /*
            ftry
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
            */

            while(_window.isOpen())
            {
                _processEvents();
                _update();
                _render();

            }
        }

        void Editor::_processEvents()
        {
            sf::Event event;
            while(_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed ) 
                    _window.close();
                
            }
        }

        void Editor::_update()
        {
            sf::Time deltaTime = _clock.restart();
            CEGUI::System::getSingleton().injectTimePulse(deltaTime.asSeconds());
            CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(deltaTime.asSeconds());
        }

        void Editor::_render()
        {
            _window.setActive(true);

            _window.clear();

            _renderer->beginRendering();
            CEGUI::System::getSingleton().renderAllGUIContexts();
            _renderer->endRendering();

            
            _window.display();
        }

    }
}
