#ifndef __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_
#define __LIBFRONTIER_ENGINES_COCOA_ENGINE_H_

#include <frontier/engine.h>
#include <frontier/windows/colourpicker.h>

namespace Frontier {

class CocoaEngine : public FrontierEngine
{
 private:
    void* m_application;
    void* m_appDelegate;
    void* m_windowMenu;

    Menu* m_currentMenu;

    bool createApplication();
    bool run();

    void updateMenu(Menu* menu);
    void addAppMenu(void* menu);

    void onActiveWindowChanged(FrontierWindow* window);

 public:
    CocoaEngine(FrontierApp* app);
    virtual ~CocoaEngine();

    virtual bool init();

    virtual bool initWindow(FrontierWindow* window);

    virtual bool checkEvents();

    virtual bool quit();

    virtual std::string getConfigDir();

    virtual void message(std::string title, std::string message);
    virtual bool confirmBox(std::string title, std::string message);
    virtual std::string chooseFile(int flags, std::string path, std::string pattern);
    virtual ColourPickerWindow* openColourPickerWindow(Geek::Gfx::Colour colour);

    bool providesMenus() { return true; }

    void updateMenu(FrontierWindow* window);

    void* getApplication() { return m_application; }
};

class CocoaColourPickerWindow : public ColourPickerWindow
{
 private:

 public:
    CocoaColourPickerWindow(Geek::Gfx::Colour colour);
    virtual ~CocoaColourPickerWindow();
};

}

#endif

