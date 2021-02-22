/*******************************************************************************
  OmicronTK_qt

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

#include "OmicronTK/qt/lua/LuaLineEdit.hpp"
#include "OmicronTK/qt/lua/base/LuaWidgetBase.hpp"

#include <QLineEdit>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace qt {

static const char className[] = "LineEdit";

static void constructor(CallbackInfo &info)
{
    info.required(1, 2);

    QLineEdit *self = info.length() == 1 ? new QLineEdit : new QLineEdit(info.getCString(2));

    info.newUserData(1, className, self);
}

static void setPlaceholderText(CallbackInfo &info)
{
    info.required(2);

    QLineEdit *self = info.checkUserData<QLineEdit>(1, className);
    self->setPlaceholderText(info.getCString(2));
}

static void setClearButtonEnabled(CallbackInfo &info)
{
    info.required(2);

    QLineEdit *self = info.checkUserData<QLineEdit>(1, className);
    self->setClearButtonEnabled(info.getBoolean(2));
}

void LuaLineEdit::require(lua::Lua *state)
{
    lua::Class luaClass(className);

    LuaWidgetBase::methods(luaClass);

    luaClass.addConstructor<constructor>();

    luaClass.addMember<setPlaceholderText>("setPlaceholderText");
    luaClass.addMember<setClearButtonEnabled>("setClearButtonEnabled");

    state->createClass(luaClass);
}

}
}
