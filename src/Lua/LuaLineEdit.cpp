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

#include "OmicronTK/Qt/Lua/LuaLineEdit.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <iostream>

#include <QLineEdit>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char tableName[] = "LineEdit";

int LineEdit_new(lua_State *L)
{
    if (lua_gettop(L) > 2)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 2);

    if (!userdata)
        userdata = new QLineEdit(lua_tolstring(L, 2, nullptr));

    ObjectUtil<QLineEdit, tableName>::newUserData(L, 1, (QLineEdit *)userdata);

    return 0;
}

int LineEdit_setPlaceholderText(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QLineEdit *userdata = ObjectUtil<QLineEdit, tableName>::checkUserData(L, 1);
    userdata->setPlaceholderText(luaL_checklstring(L, 2, nullptr));

    return 0;
}

int LineEdit_setClearButtonEnabled(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QLineEdit *userdata = ObjectUtil<QLineEdit, tableName>::checkUserData(L, 1);
    userdata->setClearButtonEnabled(lua_toboolean(L, 2));

    return 0;
}

void LuaLineEdit::requiref(lua::Lua *state)
{
    lua::Class luaClass(tableName);

    luaClass.addConstructor(LineEdit_new);

    luaClass.setMembers(LuaWidgetBase::methods());
    luaClass.addMember("setPlaceholderText", LineEdit_setPlaceholderText);
    luaClass.addMember("setClearButtonEnabled", LineEdit_setClearButtonEnabled);

    state->createClass(luaClass);
}

}
}
