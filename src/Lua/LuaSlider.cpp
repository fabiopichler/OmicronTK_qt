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

#include "OmicronTK/Qt/Lua/LuaSlider.hpp"
#include "base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <iostream>

#include "OmicronTK/Qt/Slider.hpp"

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char tableName[] = "Slider";

int Slider_new(lua_State *L)
{
    if (lua_gettop(L) > 2)
        return luaL_error(L, "expecting 0 or 1 arguments");

    void *userdata = lua_touserdata(L, 2);

    if (!userdata)
        userdata = new Slider;

    ObjectUtil<Slider, tableName>::newUserData(L, 1, (Slider *)userdata);

    return 0;
}

int Slider_setOrientation(lua_State *L)
{
    if (lua_gettop(L) != 2)
        return luaL_error(L, "expecting exactly 1 argument");

    Slider *userdata = ObjectUtil<Slider, tableName>::checkUserData(L, 1);
    int orientation = static_cast<int>(lua_tointegerx(L, 2, nullptr));

    userdata->setOrientation(static_cast<Qt::Orientation>(orientation));

    return 0;
}

void LuaSlider::requiref(lua::Lua *state)
{
    lua::Class luaClass(tableName);

    luaClass.addConstructor(Slider_new);

    luaClass.setMembers(LuaWidgetBase::methods());
    luaClass.addMember("setOrientation", Slider_setOrientation);

    state->createClass(luaClass);
}

}
}
