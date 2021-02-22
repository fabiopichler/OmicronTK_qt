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

#include "OmicronTK/qt/lua/base/LuaWidgetBase.hpp"
#include "OmicronTK/qt/lua/base/LuaObjectBase.hpp"

#include <OmicronTK/lua/CallbackInfo.hpp>

#include <QWidget>
#include <QBoxLayout>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char boxLayoutName[] = "BoxLayout";

static void setLayout(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    QBoxLayout *layout = info.checkUserData<QBoxLayout>(2, boxLayoutName);

    self->setLayout(layout);
}

static void windowTitle(CallbackInfo &info)
{
    info.required(1);

    QWidget *self = info.getUserData<QWidget>(1);

    info.getReturnValue().add(self->windowTitle().toUtf8().constData());
}

static void setStyleSheet(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    self->setStyleSheet(info.getCString(2));
}

static void setToolTip(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    self->setToolTip(info.getCString(2));
}

static void setEnabled(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    self->setEnabled(info.getBoolean(2));
}

static void setMaximumHeight(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    self->setMaximumHeight(info.getInteger(2));
}

static void setMinimumWidth(CallbackInfo &info)
{
    info.required(2);

    QWidget *self = info.getUserData<QWidget>(1);
    self->setMinimumWidth(info.getInteger(2));
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
