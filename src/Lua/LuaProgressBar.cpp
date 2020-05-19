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

#include "OmicronTK/Qt/Lua/LuaProgressBar.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QProgressBar>

namespace OmicronTK {
namespace QT {

static const char *const tableName = "ProgressBar";

int ProgressBar_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 1);

    if (!userdata)
        userdata = new QProgressBar;

    Lua::LuaBase::newUserData<QProgressBar>(L, tableName, userdata);

    return 1;
}

int ProgressBar_setOrientation(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *userdata = Lua::LuaBase::checkUserData<QProgressBar>(L, 1, tableName);
    int orientation = static_cast<int>(lua_tointegerx(L, 2, nullptr));

    userdata->setOrientation(static_cast<Qt::Orientation>(orientation));

    return 0;
}

int ProgressBar_setInvertedAppearance(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *userdata = Lua::LuaBase::checkUserData<QProgressBar>(L, 1, tableName);
    userdata->setInvertedAppearance(lua_toboolean(L, 2));

    return 0;
}

int ProgressBar_setTextVisible(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QProgressBar *userdata = Lua::LuaBase::checkUserData<QProgressBar>(L, 1, tableName);
    userdata->setTextVisible(lua_toboolean(L, 2));

    return 0;
}

void LuaProgressBar::requiref(Lua::LuaState *state)
{
    Lua::LuaRegVector functions;
    functions.push_back({ "new", ProgressBar_new });

    Lua::LuaRegVector methods = LuaWidgetBase::methods();
    methods.push_back({ "setOrientation", ProgressBar_setOrientation });
    methods.push_back({ "setInvertedAppearance", ProgressBar_setInvertedAppearance });
    methods.push_back({ "setTextVisible", ProgressBar_setTextVisible });

    state->reg(tableName, functions, methods);
}

}
}
