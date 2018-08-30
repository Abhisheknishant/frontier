
#include <frontier/frontier.h>
#include <frontier/widgets.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

List::List(FrontierApp* ui) : Widget(ui)
{
    m_selected = -1;
}

List::~List()
{
}

void List::calculateSize()
{
    vector<ListItem*>::iterator it;

    m_minSize.set(0, 0);
    m_maxSize.set(WIDGET_SIZE_UNLIMITED, WIDGET_SIZE_UNLIMITED);

    for (it = m_list.begin(); it != m_list.end(); it++)
    {
        ListItem* item = *it;
        int w = m_ui->getTheme()->getTextWidth(item->getText()) + (5 * 2);
        if (w > m_minSize.width)
        {
            m_minSize.width = w;
        }
    }

    m_itemHeight = m_ui->getTheme()->getTextHeight();
    m_minSize.height = m_itemHeight * m_list.size();

    m_minSize.width += 2 * 2;
    m_minSize.height += 2 * 2;

    m_dirty = false;
}

bool List::draw(Surface* surface)
{
    //surface->drawRect(0, 0, m_setSize.width, m_setSize.height, 0xffffffff);
    m_ui->getTheme()->drawBackground(surface);

    int x = 2;
    int y = 2;
    int idx;
    vector<ListItem*>::iterator it;
    for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
    {
        ListItem* item = *it;
        uint32_t c = 0xffffffff;
bool isSelected = m_selected == idx;
UIState state = STATE_NONE;
if (isSelected)
{
state = STATE_SELECTED;
}
UIBorderType border;
if ((idx % 2) == 0)
{
border = BORDER_LIST_ITEM_1;
}
else
{
border = BORDER_LIST_ITEM_2;
}
m_ui->getTheme()->drawBorder(surface, border, state, 0, y, m_setSize.width, m_itemHeight);

        m_ui->getTheme()->drawText(surface, x, y, item->getText(), m_selected == idx);

        y += m_itemHeight;
    }
    return true;
}

Widget* List::handleMessage(Message* msg)
{
    if (msg->messageType == FRONTIER_MSG_INPUT)
    {
        InputMessage* imsg = (InputMessage*)msg;
        if (imsg->inputMessageType == FRONTIER_MSG_INPUT_MOUSE_BUTTON)
        {
            Vector2D pos = getAbsolutePosition();
            int ey = imsg->event.button.y - pos.y;
            int selected = -1;
            bool hasSelected = false;
            int y = 2;

            int idx;
            vector<ListItem*>::iterator it;
            for (it = m_list.begin(), idx = 0; it != m_list.end(); it++, idx++)
            {
                ListItem* item = *it;
                if (ey >= y && ey < y + m_itemHeight)
                {
                    selected = idx;
                    hasSelected = true;
                    break;
                }
                y += m_itemHeight;
            }

            if (hasSelected && (m_selected != selected || imsg->event.button.doubleClick || imsg->event.button.button == 3))
            {
                printf("List::handleMessage: Selected item %d, doubleClick=%d\n", m_selected, imsg->event.button.doubleClick);

                setDirty();

                m_selected = selected;

                UIMessage* buttonMessage = new UIMessage();
                buttonMessage->messageType = FRONTIER_MSG_UI;
                buttonMessage->uiMessageType = FRONTIER_MSG_UI_LIST_SELECTED;
                buttonMessage->widget = this;
                buttonMessage->source = msg;
                buttonMessage->list.selected = m_selected;
                buttonMessage->list.itemY = y;
                m_ui->postMessage(buttonMessage);
            }
        }
    }

    return this;
}

void List::clearItems()
{
    m_list.clear();
    setDirty();
}

void List::addItem(ListItem* item)
{
    m_list.push_back(item);
    setDirty();
}

