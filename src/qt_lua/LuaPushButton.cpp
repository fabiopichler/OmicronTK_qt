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

#include "OmicronTK/qt_lua/LuaPushButton.hpp"
#include "OmicronTK/qt_lua/base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/CallbackInfo.hpp>
#include <OmicronTK/lua/NativeClass.hpp>

#include <QPushButton>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace qt {

static const char className[] = "PushButton";

static void constructor(CallbackInfo &info)
{
    info.required(1, 2);

    QPushButton *self = info.length() == 1 ? new QPushButton : new QPushButton(info.getCString(2));

    info.newUserData(1, self);
}

static void setText(CallbackInfo &info)
{
    info.required(2);

    QPushButton *self = info.checkUserData<QPushButton>(1, className);
    self->setText(info.getCString(2));
}

void LuaPushButton::init(Lua &lua)
{
    NativeClass nClass(lua, className);

    LuaWidgetBase::methods(nClass);

    nClass.setConstructor<constructor>();

    nClass.addMember<setText>("setText");

    nClass.create();
}

}
}
