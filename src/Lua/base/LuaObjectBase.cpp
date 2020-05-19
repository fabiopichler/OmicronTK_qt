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

#include "LuaObjectBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QObject>

namespace OmicronTK {
namespace QT {

int Object_setObjectName(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    QObject *userdata = *static_cast<QObject **>(lua_touserdata(L, 1));
    userdata->setObjectName(luaL_checklstring(L, 2, nullptr));

    return 0;
}

int Object_deleteLater(lua_State *L)
{
    if (lua_gettop(L) != 1)
        return luaL_error(L, "expecting 0 arguments");

    QObject *userdata = *static_cast<QObject **>(lua_touserdata(L, 1));
    userdata->deleteLater();

    return 0;
}

OTKLUA::LuaRegVector LuaObjectBase::s_methods;

const OTKLUA::LuaRegVector &LuaObjectBase::methods()
{
    if (!s_methods.empty())
        return s_methods;

    s_methods.push_back({ "setObjectName", Object_setObjectName });
    s_methods.push_back({ "deleteLater", Object_deleteLater });

    return s_methods;
}

}
}
