
#include <frontier/frontier.h>
#include <frontier/config.h>

#ifdef FRONTIER_ENGINE_SDL
#   include "engines/sdl/sdl_engine.h"
#elif FRONTIER_ENGINE_COCOA
#   include "engines/cocoa/cocoa_engine.h"
#else
#   error No engine defined
#endif

using namespace std;
using namespace Frontier;

FrontierApp::FrontierApp()
{
}

FrontierApp::~FrontierApp()
{
}

bool FrontierApp::init()
{
    bool res;

#ifdef FRONTIER_ENGINE_SDL
    m_engine = new FrontierEngineSDL(this);
#elif FRONTIER_ENGINE_COCOA
    m_engine = new CocoaEngine(this);
#else
#error No engine defined
#endif

    res = m_engine->init();
    if (!res)
    {
return false;
    }

    m_fontManager = new FontManager("/Library/Fonts");
    res = m_fontManager->init();
    if (!res)
    {
        return false;
    }

    m_fontManager->scan("/System/Library/Fonts");
    m_fontManager->scan("/Users/ian/Library/Fonts");
    m_fontManager->scan("fonts");

    m_theme = new UITheme(this);
    res = m_theme->init();
    if (!res)
    {
        return false;
    }

    return true;
}

bool FrontierApp::main()
{
    while (true)
    {
        bool res;
        res = m_engine->checkEvents();
        if (!res)
        {
            return false;
        }
    }

    return true;
}

void FrontierApp::postMessage(Message* message)
{
    handleMessage(message);
}

void FrontierApp::handleMessage(Message* message)
{
}

string FrontierApp::chooseFile()
{
    return m_engine->chooseFile();
}

