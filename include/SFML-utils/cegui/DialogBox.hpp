#ifndef SFUTILS_CEGUI_DIALOGBOX_HPP
#define SFUTILS_CEGUI_DIALOGBOX_HPP

#include <SFML-utils/cegui/PopupBox.hpp>

#include <list>
#include <string>

namespace sfutils
{
    namespace cegui
    {
        class DialogBox : public PopupBox
        {
            public:
                static void getInt(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,
                                   const std::function<void(int)>& ok, const std::function<void()>& cancel = [](){},
                                   int defaultValue = 0);

                static void getInt(CEGUI::Window* parent,const std::string& title,const std::string& text,
                                   const std::function<void(int)>& ok, const std::function<void()>& cancel = [](){},
                                   int defaultValue = 0);

                static void getDouble(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,
                                      const std::function<void(double)>& ok, const std::function<void()>& cancel = [](){},
                                      double defaultValue = 0.0);

                static void getDouble(CEGUI::Window* parent,const std::string& title,const std::string& text,
                                      const std::function<void(double)>& ok, const std::function<void()>& cancel = [](){},
                                      double defaultValue = 0.0);

                static void getString(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,
                                      const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel = [](){},
                                      const std::string& defaultValue="", const std::string& regex=".*");

                static void getString(CEGUI::Window* parent,const std::string& title,const std::string& text,
                                      const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel = [](){},
                                      const std::string& defaultValue="", const std::string& regex=".*");

                static void getItem(CEGUI::GUIContext& parent,const std::string title,const std::string& text,const std::list<std::string>& choices,
                                    const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel = [](){});

                static void getItem(CEGUI::Window* parent,const std::string title,const std::string& text,const std::list<std::string>& choices,
                                    const std::function<void(const std::string&)>& ok, const std::function<void()>& cancel = [](){});

                static void message(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,
                                    const std::function<void()>& ok, const std::function<void()>& cancel = [](){});
                static void message(CEGUI::Window* parent,const std::string& title,const std::string& text,
                                    const std::function<void()>& ok, const std::function<void()>& cancel = [](){});

                static void getStringAndItem(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,const std::list<std::string>& choices,
                                             const std::function<void(const std::string& txt, const std::string& item)>& ok, const std::function<void()>& cancel = [](){});

                static void getStringAndItem(CEGUI::Window* parent,const std::string& title,const std::string& text,const std::list<std::string>& choices,
                                             const std::function<void(const std::string& txt,const std::string& item)>& ok, const std::function<void()>& cancel = [](){});



            private:
                DialogBox(CEGUI::GUIContext& parent,const std::string& title,const std::string& text,const std::list<CEGUI::Window*>& objects,const sf::Vector2u& size={300,200});

                CEGUI::Window* _layout;
                CEGUI::Window* _box;
        };
    }
}
#endif
