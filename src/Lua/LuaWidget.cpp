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

#include "OmicronTK/Qt/Lua/LuaWidget.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <iostream>

#include <QWidget>

#include <QDebug>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char tableName[] = "Widget";

int Widget_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
        return luaL_error(L, "expecting 0 arguments");

    ObjectUtil<QWidget, tableName>::newUserData(L, 1, new QWidget);

    return 0;
}

void LuaWidget::require(lua::Lua *state)
{
    lua::Class luaClass(tableName);

    luaClass.setMembers(LuaWidgetBase::methods());

    luaClass.addConstructor(Widget_new);

    state->createClass(luaClass);
}

}
}
