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

#include "OmicronTK/Qt/Lua/LuaLayout.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QBoxLayout>
#include <QWidget>
#include <QMenuBar>

#include <QDebug>

namespace OmicronTK {
namespace QT {

static const char *const tableName = "BoxLayout";

int BoxLayout_new(lua_State *L)
{
    if (lua_gettop(L) != 1)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 1);

    if (!userdata)
    {
        double direction = lua_tointegerx(L, 1, nullptr);
        userdata = new QBoxLayout(static_cast<QBoxLayout::Direction>(static_cast<int>(direction)));
    }

    OTKLUA::LuaBase::newUserData<QBoxLayout>(L, tableName, userdata);

    return 1;
}

int BoxLayout_addWidget(lua_State *L)
{
    if (lua_gettop(L) < 2)
        return luaL_error(L, "expecting 1, 2 or 3 arguments");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    QWidget *widget = *static_cast<QWidget **>(lua_touserdata(L, 2));

    if (!widget)
        return luaL_error(L, "widget error");

    int stretch = static_cast<int>(lua_tointegerx(L, 3, nullptr));
    int alignment = static_cast<int>(lua_tointegerx(L, 4, nullptr));

    userdata->addWidget(widget, stretch, static_cast<Qt::AlignmentFlag>(alignment));

    return 0;
}

int BoxLayout_addLayout(lua_State *L)
{
    if (lua_gettop(L) < 2)
        return luaL_error(L, "expecting 0 or 1 arguments");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    QBoxLayout *layout = *static_cast<QBoxLayout **>(luaL_checkudata(L, 2, tableName));
    int stretch = static_cast<int>(lua_tointegerx(L, 3, nullptr));

    userdata->addLayout(layout, stretch);

    return 0;
}

int BoxLayout_setAlignment(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    userdata->setAlignment(static_cast<Qt::AlignmentFlag>(static_cast<int>(luaL_checknumber(L, 2))));

    return 0;
}

int BoxLayout_setSpacing(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    userdata->setSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_setMargin(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    userdata->setMargin(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_addStretch(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    userdata->addStretch(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_addSpacing(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);
    userdata->addSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_setContentsMargins(lua_State *L)
{
    if (lua_gettop(L) != 5)
        return luaL_error(L, "expecting exactly 4 arguments");

    QBoxLayout *userdata = OTKLUA::LuaBase::checkUserData<QBoxLayout>(L, 1, tableName);

    int left = static_cast<int>(luaL_checknumber(L, 2));
    int top = static_cast<int>(luaL_checknumber(L, 3));
    int right = static_cast<int>(luaL_checknumber(L, 4));
    int bottom = static_cast<int>(luaL_checknumber(L, 5));

    userdata->setContentsMargins(left, top, right, bottom);

    return 0;
}

void LuaLayout::requiref(OTKLUA::LuaState *state)
{
    OTKLUA::LuaRegVector functions;
    functions.push_back({ "new", BoxLayout_new });

    OTKLUA::LuaRegVector methods = LuaWidgetBase::methods();
    methods.push_back({ "addLayout", BoxLayout_addLayout });
    methods.push_back({ "addWidget", BoxLayout_addWidget });
    methods.push_back({ "setAlignment", BoxLayout_setAlignment });
    methods.push_back({ "setSpacing", BoxLayout_setSpacing });
    methods.push_back({ "setMargin", BoxLayout_setMargin });
    methods.push_back({ "addStretch", BoxLayout_addStretch });
    methods.push_back({ "addSpacing", BoxLayout_addSpacing });
    methods.push_back({ "setContentsMargins", BoxLayout_setContentsMargins });

    state->reg(tableName, functions, methods);
}

}
}
