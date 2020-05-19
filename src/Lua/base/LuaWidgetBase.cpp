/*******************************************************************************
  OmicronTK+Qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2019, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "LuaWidgetBase.hpp"
#include "LuaObjectBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QWidget>
#include <QBoxLayout>

namespace OmicronTK {
namespace QT {

int Widget_setLayout(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    QBoxLayout *layout = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 2, "BoxLayout");

    userdata->setLayout(layout);

    return 0;
}

int Widget_windowTitle(lua_State *L)
{
    if (lua_gettop(L) != 1)
        return luaL_error(L, "expecting exactly 0 arguments");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    lua_pushstring(L, userdata->windowTitle().toUtf8().constData());

    return 1;
}

int Widget_setStyleSheet(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    userdata->setStyleSheet(luaL_checklstring(L, 2, nullptr));

    return 0;
}

int Widget_setToolTip(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    userdata->setToolTip(luaL_checklstring(L, 2, nullptr));

    return 0;
}

int Widget_setEnabled(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    userdata->setEnabled(lua_toboolean(L, 2));

    return 0;
}

int Widget_setMaximumHeight(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    userdata->setMaximumHeight(lua_tonumber(L, 2));

    return 0;
}

int Widget_setMinimumWidth(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QWidget *userdata = *static_cast<QWidget **>(lua_touserdata(L, 1));
    userdata->setMinimumWidth(lua_tonumber(L, 2));

    return 0;
}

OTKLUA::LuaRegVector LuaWidgetBase::s_methods;

const OTKLUA::LuaRegVector &LuaWidgetBase::methods()
{
    if (!s_methods.empty())
        return s_methods;

    s_methods = LuaObjectBase::methods();
    s_methods.push_back({ "setLayout", Widget_setLayout });
    s_methods.push_back({ "windowTitle", Widget_windowTitle });
    s_methods.push_back({ "setStyleSheet", Widget_setStyleSheet });
    s_methods.push_back({ "setToolTip", Widget_setToolTip });
    s_methods.push_back({ "setEnabled", Widget_setEnabled });
    s_methods.push_back({ "setMaximumHeight", Widget_setMaximumHeight });
    s_methods.push_back({ "setMinimumWidth", Widget_setMinimumWidth });

    return s_methods;
}

}
}
