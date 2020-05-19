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

#include "OmicronTK/Qt/Lua/LuaLabel.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>

#include <iostream>

#include <QLabel>

namespace OmicronTK {
namespace QT {

static const char *const tableName = "Label";

int Label_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 1);

    if (!userdata)
        userdata = new QLabel(lua_tolstring(L, 1, nullptr));

    Lua::LuaBase::newUserData<QLabel>(L, tableName, userdata);

    return 1;
}

int Label_setText(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QLabel *userdata = Lua::LuaBase::checkUserData<QLabel>(L, 1, tableName);
    userdata->setText(luaL_checklstring(L, 2, nullptr));

    return 0;
}

int Label_setAlignment(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QLabel *userdata = Lua::LuaBase::checkUserData<QLabel>(L, 1, tableName);
    int alignment = static_cast<int>(lua_tointegerx(L, 2, nullptr));

    userdata->setAlignment(static_cast<Qt::Alignment>(alignment));

    return 0;
}

void LuaLabel::requiref(Lua::LuaState *state)
{
    Lua::LuaRegVector functions;
    functions.push_back({ "new", Label_new });

    Lua::LuaRegVector methods = LuaWidgetBase::methods();
    methods.push_back({ "setText", Label_setText });
    methods.push_back({ "setAlignment", Label_setAlignment });

    state->reg(tableName, functions, methods);
}

}
}
