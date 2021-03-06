/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <frontier/frontier.h>
#include <frontier/widgets/button.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Button::Button(FrontierApp* ui, wstring text, ButtonType type) : Label(ui, L"Button", text)
{
    m_type = type;
}

Button::Button(FrontierApp* ui, wstring widgetType, wstring text, ButtonType type) : Label(ui, widgetType, text)
{
    m_type = type;
}

Button::~Button()
{
}

Widget* Button::handleEvent(Event* event)
{
    switch (event->eventType)
    {
        case FRONTIER_EVENT_MOUSE_BUTTON:
        {
            MouseButtonEvent* mouseButtonEvent = (MouseButtonEvent*)event;
            log(DEBUG, "handleEvent: Message! text=%ls", getText().c_str());
            switch (m_type)
            {
                case BUTTON_NORMAL:
                    if (m_selected != mouseButtonEvent->direction)
                    {
                        setDirty(DIRTY_CONTENT | DIRTY_STYLE);

                        m_selected = mouseButtonEvent->direction;

                        if (!m_selected)
                        {
                            clickSignal().emit(this);
                        }
                    }
                    break;

                case BUTTON_TOGGLE:
                    if (!mouseButtonEvent->direction)
                    {
                        m_selected = !m_selected;
                        setDirty(DIRTY_CONTENT | DIRTY_STYLE);
                        clickSignal().emit(this);
                    }
                    break;
            }
        } break;

        case FRONTIER_EVENT_KEY:
        {
            KeyEvent* keyEvent = (KeyEvent*)event;
            if (keyEvent->direction && keyEvent->key == KC_TAB)
            {
                if (m_parent != NULL)
                {
                    m_parent->activateNext(this);
                }
            }
            else if (keyEvent->key == KC_SPACE)
            {
                switch (m_type)
                {
                    case BUTTON_NORMAL:
                        if (m_selected != keyEvent->direction)
                        {
                            setDirty(DIRTY_CONTENT | DIRTY_STYLE);

                            m_selected = keyEvent->direction;
                            if (!m_selected)
                            {
                                clickSignal().emit(this);
                            }
                        }
                        break;
                    case BUTTON_TOGGLE:
                        if (!keyEvent->direction)
                        {
                            m_selected = !m_selected;
                            setDirty(DIRTY_CONTENT | DIRTY_STYLE);
                            clickSignal().emit(this);
                        }
                        break;
                }
            }
        } break;

        default:
            break;
    }
    return this;
}

void Button::activateNext(Widget* activeChild)
{
    if (activeChild == NULL)
    {
        setActive();
    }
}

