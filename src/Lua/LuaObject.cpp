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

#include "OmicronTK/Qt/Lua/LuaObject.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/Lua/LuaBase.hpp>
#include <iostream>

#include <QObject>

namespace OmicronTK {
namespace QT {

static const char *const tableName = "Object";

int Object_connect(lua_State *L)
{
    void *sender = lua_touserdata(L, 1);
    const char *signal = lua_tolstring(L, 2, nullptr);
    void *receiver = lua_touserdata(L, 3);
    const char *member = lua_tolstring(L, 4, nullptr);

    if (!sender || !signal || !receiver || !member)
    {
        std::cerr << "ERRO connect" << std::endl;
        return 0;
    }
#ifndef QLOCATION
# define QLOCATION "\0" __FILE__ ":" QT_STRINGIFY(__LINE__)
#endif
    QObject::connect(*static_cast<QObject **>(sender),
                     qFlagLocation(QString("2").append(signal).append(QLOCATION).toUtf8().constData()),
                     *static_cast<QObject **>(receiver),
                     qFlagLocation(QString("1").append(member).append(QLOCATION).toUtf8().constData()));

    return 0;
}

void LuaObject::requiref(OTKLUA::LuaState *state)
{
    OTKLUA::LuaRegVector functions;
    functions.push_back({ "connect", Object_connect });

    state->reg(tableName, functions);
}

}
}
