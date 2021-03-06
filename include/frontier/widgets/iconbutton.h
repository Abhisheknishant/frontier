#ifndef __FRONTIER_WIDGETS_ICON_BUTTON_H_
#define __FRONTIER_WIDGETS_ICON_BUTTON_H_

#include <frontier/widgets/button.h>
#include <frontier/fontawesome.h>
#include <frontier/icon.h>

namespace Frontier
{

/**
 * \brief A simple Button widget that displays an Icon
 *
 * \ingroup widgets
 */
class IconButton : public Button
{
 private:
    Icon* m_icon;

 public:
    IconButton(FrontierApp* ui, Icon* icon);
    IconButton(FrontierApp* ui, uint32_t icon);
    virtual ~IconButton();

    void setIcon(Icon* icon);
    Icon* getIcon() { return m_icon; }

    virtual void calculateSize();
    virtual bool draw(Geek::Gfx::Surface* surface);
};

};

#endif
