#include <SFML-utils/cegui/GuiManager.hpp>

#include <CEGUI/RendererModules/OpenGL/ViewportTarget.h>

namespace sfutils
{
    namespace cegui
    {
        void GuiManager::init(const std::string& mediDirectory,const std::string& defaultFont)
        {
            _initMaps();
            _initRenderer();
            _initResources(mediDirectory);

            CEGUI::FontManager::getSingleton().createFromFile(defaultFont + ".font");
            CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(defaultFont);
        }

        bool GuiManager::processEvent(const sf::Event& event,CEGUI::GUIContext& context)
        {
            switch(event.type)
            {
                case sf::Event::Resized :
                {
                    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(event.size.width,event.size.height));
                }
                case sf::Event::KeyPressed:
                {
                    return context.injectKeyDown(_keyMap[event.key.code]);
                }
                case sf::Event::KeyReleased:
                {
                    return context.injectKeyUp(_keyMap[event.key.code]);
                }
                case sf::Event::TextEntered:
                {
                    return context.injectChar(event.text.unicode);
                }
                case sf::Event::MouseMoved:
                {
                    return context.injectMousePosition(static_cast<float>(event.mouseMove.x),
                                                        static_cast<float>(event.mouseMove.y));
                }
                case sf::Event::MouseButtonPressed:
                {
                    return context.injectMouseButtonDown(_mouseButtonMap[event.mouseButton.button]);
                }
                case sf::Event::MouseButtonReleased:
                {
                    return context.injectMouseButtonUp(_mouseButtonMap[event.mouseButton.button]);
                }
                case sf::Event::MouseWheelMoved:
                {
                    return context.injectMouseWheelChange(static_cast<float>(event.mouseWheel.delta));
                }
                default : 
                {
                    return false;
                }
            }
        }

        bool GuiManager::processEvent(const sf::Event& event)
        {
            return processEvent(event,
                               CEGUI::System::getSingleton().getDefaultGUIContext());
        }

        void GuiManager::update(const sf::Time& deltaTime)
        {
            float sec = deltaTime.asSeconds();
            CEGUI::System::getSingleton().injectTimePulse(sec);
            update(deltaTime,
                   CEGUI::System::getSingleton().getDefaultGUIContext());
        }

        void GuiManager::update(const sf::Time& deltaTime,CEGUI::GUIContext& context)
        {
            float sec = deltaTime.asSeconds();
            context.injectTimePulse(sec);
        }

        void GuiManager::render()
        {
            render(CEGUI::System::getSingleton().getDefaultGUIContext());

        }

        void GuiManager::render(CEGUI::GUIContext& context)
        {
            _renderer->beginRendering();
            context.draw();
            _renderer->endRendering();
        }

        CEGUI::OpenGLRenderer& GuiManager::getRenderer()
        {
            return *_renderer;
        }

        CEGUI::GUIContext& GuiManager::createGUIContext()
        {
            CEGUI::RenderTarget* target = new CEGUI::OpenGLViewportTarget(getRenderer());
            CEGUI::GUIContext* context = &CEGUI::System::getSingleton().createGUIContext(*target);

            _guiContexts.emplace_back(std::make_pair(target,context));

            return *context;
            
        }

        bool GuiManager::destroyGUIContext(CEGUI::GUIContext& context)
        {
            for(auto it = _guiContexts.begin(); it != _guiContexts.end(); ++it)
            {
                if( it->second == &context)
                {
                    CEGUI::System::getSingleton().destroyGUIContext(context);
                    delete it->first;
                    _guiContexts.erase(it);
                    return true;
                }
            }
            return false;
        }

        ///////////////// PRIVATE //////////////////

        GuiManager::KeyMap GuiManager::_keyMap;
        GuiManager::MouseButtonMap GuiManager::_mouseButtonMap;
        CEGUI::OpenGLRenderer* GuiManager::_renderer = nullptr;
        std::list<std::pair<CEGUI::RenderTarget*,CEGUI::GUIContext*>> GuiManager::_guiContexts;
        
        GuiManager::GuiManager()
        {
        }

        void GuiManager::_initMaps()
        {
            _keyMap[sf::Keyboard::Key::A]               = CEGUI::Key::A            ;
            _keyMap[sf::Keyboard::Key::B]               = CEGUI::Key::B            ;
            _keyMap[sf::Keyboard::Key::C]               = CEGUI::Key::C            ;
            _keyMap[sf::Keyboard::Key::D]               = CEGUI::Key::D            ;
            _keyMap[sf::Keyboard::Key::E]               = CEGUI::Key::E            ;
            _keyMap[sf::Keyboard::Key::F]               = CEGUI::Key::F            ;
            _keyMap[sf::Keyboard::Key::G]               = CEGUI::Key::G            ;
            _keyMap[sf::Keyboard::Key::H]               = CEGUI::Key::H            ;
            _keyMap[sf::Keyboard::Key::I]               = CEGUI::Key::I            ;
            _keyMap[sf::Keyboard::Key::J]               = CEGUI::Key::J            ;
            _keyMap[sf::Keyboard::Key::K]               = CEGUI::Key::K            ;
            _keyMap[sf::Keyboard::Key::L]               = CEGUI::Key::L            ;
            _keyMap[sf::Keyboard::Key::M]               = CEGUI::Key::M            ;
            _keyMap[sf::Keyboard::Key::N]               = CEGUI::Key::N            ;
            _keyMap[sf::Keyboard::Key::O]               = CEGUI::Key::O            ;
            _keyMap[sf::Keyboard::Key::P]               = CEGUI::Key::P            ;
            _keyMap[sf::Keyboard::Key::Q]               = CEGUI::Key::Q            ;
            _keyMap[sf::Keyboard::Key::R]               = CEGUI::Key::R            ;
            _keyMap[sf::Keyboard::Key::S]               = CEGUI::Key::S            ;
            _keyMap[sf::Keyboard::Key::T]               = CEGUI::Key::T            ;
            _keyMap[sf::Keyboard::Key::U]               = CEGUI::Key::U            ;
            _keyMap[sf::Keyboard::Key::V]               = CEGUI::Key::V            ;
            _keyMap[sf::Keyboard::Key::W]               = CEGUI::Key::W            ;
            _keyMap[sf::Keyboard::Key::X]               = CEGUI::Key::X            ;
            _keyMap[sf::Keyboard::Key::Y]               = CEGUI::Key::Y            ;
            _keyMap[sf::Keyboard::Key::Z]               = CEGUI::Key::Z            ;
            _keyMap[sf::Keyboard::Key::Num0]            = CEGUI::Key::Zero         ;
            _keyMap[sf::Keyboard::Key::Num1]            = CEGUI::Key::One          ;
            _keyMap[sf::Keyboard::Key::Num2]            = CEGUI::Key::Two          ;
            _keyMap[sf::Keyboard::Key::Num3]            = CEGUI::Key::Three        ;
            _keyMap[sf::Keyboard::Key::Num4]            = CEGUI::Key::Four         ;
            _keyMap[sf::Keyboard::Key::Num5]            = CEGUI::Key::Five         ;
            _keyMap[sf::Keyboard::Key::Num6]            = CEGUI::Key::Six          ;
            _keyMap[sf::Keyboard::Key::Num7]            = CEGUI::Key::Seven        ;
            _keyMap[sf::Keyboard::Key::Num8]            = CEGUI::Key::Eight        ;
            _keyMap[sf::Keyboard::Key::Num9]            = CEGUI::Key::Nine         ;
            _keyMap[sf::Keyboard::Key::Escape]          = CEGUI::Key::Escape       ;
            _keyMap[sf::Keyboard::Key::LControl]        = CEGUI::Key::LeftControl  ;
            _keyMap[sf::Keyboard::Key::LShift]          = CEGUI::Key::LeftShift    ;
            _keyMap[sf::Keyboard::Key::LAlt]            = CEGUI::Key::LeftAlt      ;
            _keyMap[sf::Keyboard::LSystem]		        = CEGUI::Key::LeftWindows;
            _keyMap[sf::Keyboard::Key::RControl]        = CEGUI::Key::RightControl ;
            _keyMap[sf::Keyboard::Key::RShift]          = CEGUI::Key::RightShift   ;
            _keyMap[sf::Keyboard::Key::RAlt]            = CEGUI::Key::RightAlt     ;
            _keyMap[sf::Keyboard::RSystem]		        = CEGUI::Key::RightWindows;
            //_keyMap[sf::Keyboard::Menu]		            = CEGUI::Key: //TODO Dunno what this is
            _keyMap[sf::Keyboard::Key::LBracket]        = CEGUI::Key::LeftBracket  ;
            _keyMap[sf::Keyboard::Key::RBracket]        = CEGUI::Key::RightBracket ;
            _keyMap[sf::Keyboard::Key::SemiColon]       = CEGUI::Key::Semicolon    ;
            _keyMap[sf::Keyboard::Key::Comma]           = CEGUI::Key::Comma        ;
            _keyMap[sf::Keyboard::Key::Period]          = CEGUI::Key::Period       ;
            _keyMap[sf::Keyboard::Quote]		        = CEGUI::Key::Apostrophe;
            _keyMap[sf::Keyboard::Key::Slash]           = CEGUI::Key::Slash        ;
            _keyMap[sf::Keyboard::Key::BackSlash]       = CEGUI::Key::Backslash    ;
            _keyMap[sf::Keyboard::Tilde]		        = CEGUI::Key::Grave;
            _keyMap[sf::Keyboard::Key::Equal]           = CEGUI::Key::Equals       ;
            _keyMap[sf::Keyboard::Key::Dash]            = CEGUI::Key::Minus        ;
            _keyMap[sf::Keyboard::Key::Space]           = CEGUI::Key::Space        ;
            _keyMap[sf::Keyboard::Key::Return]          = CEGUI::Key::Return       ;
            _keyMap[sf::Keyboard::BackSpace]	        = CEGUI::Key::Backspace;
            _keyMap[sf::Keyboard::Key::Tab]             = CEGUI::Key::Tab          ;
            _keyMap[sf::Keyboard::Key::PageUp]          = CEGUI::Key::PageUp       ;
            _keyMap[sf::Keyboard::Key::PageDown]        = CEGUI::Key::PageDown     ;
            _keyMap[sf::Keyboard::Key::End]             = CEGUI::Key::End          ;
            _keyMap[sf::Keyboard::Key::Home]            = CEGUI::Key::Home         ;
            _keyMap[sf::Keyboard::Key::Insert]          = CEGUI::Key::Insert       ;
            _keyMap[sf::Keyboard::Key::Delete]          = CEGUI::Key::Delete       ;
            _keyMap[sf::Keyboard::Key::Add]             = CEGUI::Key::Add          ;
            _keyMap[sf::Keyboard::Key::Subtract]        = CEGUI::Key::Subtract     ;
            _keyMap[sf::Keyboard::Key::Multiply]        = CEGUI::Key::Multiply     ;
            _keyMap[sf::Keyboard::Key::Divide]          = CEGUI::Key::Divide       ;
            _keyMap[sf::Keyboard::Key::Left]            = CEGUI::Key::ArrowLeft    ;
            _keyMap[sf::Keyboard::Key::Right]           = CEGUI::Key::ArrowRight   ;
            _keyMap[sf::Keyboard::Key::Up]              = CEGUI::Key::ArrowUp      ;
            _keyMap[sf::Keyboard::Key::Down]            = CEGUI::Key::ArrowDown    ;
            _keyMap[sf::Keyboard::Key::Numpad0]         = CEGUI::Key::Numpad0      ;
            _keyMap[sf::Keyboard::Key::Numpad1]         = CEGUI::Key::Numpad1      ;
            _keyMap[sf::Keyboard::Key::Numpad2]         = CEGUI::Key::Numpad2      ;
            _keyMap[sf::Keyboard::Key::Numpad3]         = CEGUI::Key::Numpad3      ;
            _keyMap[sf::Keyboard::Key::Numpad4]         = CEGUI::Key::Numpad4      ;
            _keyMap[sf::Keyboard::Key::Numpad5]         = CEGUI::Key::Numpad5      ;
            _keyMap[sf::Keyboard::Key::Numpad6]         = CEGUI::Key::Numpad6      ;
            _keyMap[sf::Keyboard::Key::Numpad7]         = CEGUI::Key::Numpad7      ;
            _keyMap[sf::Keyboard::Key::Numpad8]         = CEGUI::Key::Numpad8      ;
            _keyMap[sf::Keyboard::Key::Numpad9]         = CEGUI::Key::Numpad9      ;
            _keyMap[sf::Keyboard::Key::F1]              = CEGUI::Key::F1           ;
            _keyMap[sf::Keyboard::Key::F2]              = CEGUI::Key::F2           ;
            _keyMap[sf::Keyboard::Key::F3]              = CEGUI::Key::F3           ;
            _keyMap[sf::Keyboard::Key::F4]              = CEGUI::Key::F4           ;
            _keyMap[sf::Keyboard::Key::F5]              = CEGUI::Key::F5           ;
            _keyMap[sf::Keyboard::Key::F6]              = CEGUI::Key::F6           ;
            _keyMap[sf::Keyboard::Key::F7]              = CEGUI::Key::F7           ;
            _keyMap[sf::Keyboard::Key::F8]              = CEGUI::Key::F8           ;
            _keyMap[sf::Keyboard::Key::F9]              = CEGUI::Key::F9           ;
            _keyMap[sf::Keyboard::Key::F10]             = CEGUI::Key::F10          ;
            _keyMap[sf::Keyboard::Key::F11]             = CEGUI::Key::F11          ;
            _keyMap[sf::Keyboard::Key::F12]             = CEGUI::Key::F12          ;
            _keyMap[sf::Keyboard::Key::F13]             = CEGUI::Key::F13          ;
            _keyMap[sf::Keyboard::Key::F14]             = CEGUI::Key::F14          ;
            _keyMap[sf::Keyboard::Key::F15]             = CEGUI::Key::F15          ;
            _keyMap[sf::Keyboard::Key::Pause]           = CEGUI::Key::Pause        ;

            _mouseButtonMap[sf::Mouse::Button::Left]		= CEGUI::LeftButton;
            _mouseButtonMap[sf::Mouse::Button::Right]		= CEGUI::RightButton;
            _mouseButtonMap[sf::Mouse::Button::Middle]		= CEGUI::MiddleButton;
            _mouseButtonMap[sf::Mouse::Button::XButton1]	= CEGUI::X1Button;
            _mouseButtonMap[sf::Mouse::Button::XButton2]	= CEGUI::X2Button;

        }

        void GuiManager::_initRenderer()
        {
            _renderer = &CEGUI::OpenGLRenderer::bootstrapSystem();
        }

        void GuiManager::_initResources(const std::string& rootDir)
        {
            CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

            rp->setResourceGroupDirectory("fonts", rootDir + "fonts/");
            rp->setResourceGroupDirectory("imagesets", rootDir +"imagesets/");
            rp->setResourceGroupDirectory("layouts",  rootDir + "layouts/");
            rp->setResourceGroupDirectory("looknfeels", rootDir + "looknfeel/");
            rp->setResourceGroupDirectory("schemes", rootDir + "schemes/");
            rp->setResourceGroupDirectory("lua_scripts", rootDir + "lua_scripts/");

            // set the default resource groups to be used
            CEGUI::Font::setDefaultResourceGroup("fonts");
            CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
            CEGUI::WindowManager::setDefaultResourceGroup("layouts");
            CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
            CEGUI::Scheme::setDefaultResourceGroup("schemes");
            CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
            
            CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
            if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
                parser->setProperty("SchemaDefaultResourceGroup", "schemas");
        }
    }
}
