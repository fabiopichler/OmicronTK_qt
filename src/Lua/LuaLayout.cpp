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

#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <iostream>

#include <QBoxLayout>
#include <QWidget>
#include <QMenuBar>

#include <QDebug>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char tableName[] = "BoxLayout";

int BoxLayout_new(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 2);

    if (!userdata)
    {
        double direction = lua_tointegerx(L, 2, nullptr);
        userdata = new QBoxLayout(static_cast<QBoxLayout::Direction>(static_cast<int>(direction)));
    }

    ObjectUtil<QBoxLayout, tableName>::newUserData(L, 1, (QBoxLayout *)userdata);

    return 0;
}

int BoxLayout_addWidget(lua_State *L)
{
    if (lua_gettop(L) < 2)
        return luaL_error(L, "expecting 1, 2 or 3 arguments");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
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

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    QBoxLayout *layout = *static_cast<QBoxLayout **>(luaL_checkudata(L, 2, tableName));
    int stretch = static_cast<int>(lua_tointegerx(L, 3, nullptr));

    userdata->addLayout(layout, stretch);

    return 0;
}

int BoxLayout_setAlignment(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    userdata->setAlignment(static_cast<Qt::AlignmentFlag>(static_cast<int>(luaL_checknumber(L, 2))));

    return 0;
}

int BoxLayout_setSpacing(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    userdata->setSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_setMargin(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    userdata->setMargin(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_addStretch(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    userdata->addStretch(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_addSpacing(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);
    userdata->addSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return 0;
}

int BoxLayout_setContentsMargins(lua_State *L)
{
    if (lua_gettop(L) != 5)
        return luaL_error(L, "expecting exactly 4 arguments");

    QBoxLayout *userdata = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 1);

    int left = static_cast<int>(luaL_checknumber(L, 2));
    int top = static_cast<int>(luaL_checknumber(L, 3));
    int right = static_cast<int>(luaL_checknumber(L, 4));
    int bottom = static_cast<int>(luaL_checknumber(L, 5));

    userdata->setContentsMargins(left, top, right, bottom);

    return 0;
}

void LuaLayout::requiref(lua::Lua *state)
{
    lua::Class luaClass(tableName);

    luaClass.addConstructor(BoxLayout_new);

    luaClass.setMembers(LuaWidgetBase::methods());
    luaClass.addMember("addLayout", BoxLayout_addLayout);
    luaClass.addMember("addWidget", BoxLayout_addWidget);
    luaClass.addMember("setAlignment", BoxLayout_setAlignment);
    luaClass.addMember("setSpacing", BoxLayout_setSpacing);
    luaClass.addMember("setMargin", BoxLayout_setMargin);
    luaClass.addMember("addStretch", BoxLayout_addStretch);
    luaClass.addMember("addSpacing", BoxLayout_addSpacing);
    luaClass.addMember("setContentsMargins", BoxLayout_setContentsMargins);

    state->createClass(luaClass);
}

}
}
