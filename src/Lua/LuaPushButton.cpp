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

#include "OmicronTK/Qt/Lua/LuaPushButton.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QPushButton>

namespace OmicronTK {
namespace QT {

static const char *const tableName = "PushButton";

int PushButton_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 1);

    if (!userdata)
        userdata = new QPushButton(lua_tolstring(L, 1, nullptr));

    OTKLUA::LuaBase::newUserData<QPushButton>(L, tableName, userdata);

    return 1;
}

int PushButton_setText(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QPushButton *userdata = OTKLUA::LuaBase::checkUserData<QPushButton>(L, 1, tableName);
    userdata->setText(luaL_checklstring(L, 2, nullptr));

    return 0;
}

void LuaPushButton::requiref(OTKLUA::LuaState *state)
{
    OTKLUA::LuaRegVector functions;
    functions.push_back({ "new", PushButton_new });

    OTKLUA::LuaRegVector methods = LuaWidgetBase::methods();
    methods.push_back({ "setText", PushButton_setText });

    state->reg(tableName, functions, methods);
}

}
}
