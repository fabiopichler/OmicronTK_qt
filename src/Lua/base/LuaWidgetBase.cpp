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

#include "OmicronTK/Qt/Lua/base/LuaWidgetBase.hpp"
#include "OmicronTK/Qt/Lua/base/LuaObjectBase.hpp"

#include <OmicronTK/lua/CallbackInfo.hpp>

#include <lua.hpp>
#include <iostream>

#include <QWidget>
#include <QBoxLayout>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char boxLayoutName[] = "BoxLayout";

static int setLayout(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    QBoxLayout *layout = info.checkUserData<QBoxLayout>(2, boxLayoutName);

    self->setLayout(layout);

    return 0;
}

static int windowTitle(const CallbackInfo &info)
{
    if (info.length() != 1)
        return info.error("expecting exactly 0 arguments");

    QWidget *self = info.getUserData<QWidget>(1);
    lua_pushstring(info.state(), self->windowTitle().toUtf8().constData());

    return 1;
}

static int setStyleSheet(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    self->setStyleSheet(info.getCString(2));

    return 0;
}

static int setToolTip(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    self->setToolTip(info.getCString(2));

    return 0;
}

static int setEnabled(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    self->setEnabled(info.getBoolean(2));

    return 0;
}

static int setMaximumHeight(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    self->setMaximumHeight(info.getInteger(2));

    return 0;
}

static int setMinimumWidth(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QWidget *self = info.getUserData<QWidget>(1);
    self->setMinimumWidth(info.getInteger(2));

    return 0;
}

void LuaWidgetBase::methods(lua::Class &luaClass)
{
    LuaObjectBase::methods(luaClass);

    luaClass.addMember<setLayout>("setLayout");
    luaClass.addMember<windowTitle>("windowTitle");
    luaClass.addMember<setStyleSheet>("setStyleSheet");
    luaClass.addMember<setToolTip>("setToolTip");
    luaClass.addMember<setEnabled>("setEnabled");
    luaClass.addMember<setMaximumHeight>("setMaximumHeight");
    luaClass.addMember<setMinimumWidth>("setMinimumWidth");
}

}
}
