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

#include "OmicronTK/Qt/Lua/LuaLayout.hpp"
#include "OmicronTK/Qt/Lua/base/LuaWidgetBase.hpp"

#include <iostream>

#include <QBoxLayout>
#include <QWidget>
#include <QMenuBar>

#include <QDebug>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace QT {

static const char className[] = "BoxLayout";

static int constructor(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("QBoxLayout: expecting 1 argument");

    QBoxLayout::Direction direction = static_cast<QBoxLayout::Direction>(info.getInteger(2));

    info.newUserData<QBoxLayout>(1, className, new QBoxLayout(direction));

    return 0;
}

static int addWidget(const CallbackInfo &info)
{
    const int length = info.length();

    if (length < 2)
        return info.error("expecting 1, 2 or 3 arguments");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    QWidget *widget = info.getUserData<QWidget>(2);

    if (!widget)
        return info.error("widget error");

    int stretch = length >= 3 ? info.getInteger(3) : 0;
    int alignment = length >= 4 ? info.getInteger(4) : 0;

    self->addWidget(widget, stretch, static_cast<Qt::AlignmentFlag>(alignment));

    return 0;
}

static int addLayout(const CallbackInfo &info)
{
    const int length = info.length();

    if (length < 2)
        return info.error("expecting 1 or 2 arguments");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    QBoxLayout *layout = info.checkUserData<QBoxLayout>(2, className);
    int stretch = length >= 3 ? info.getInteger(3) : 0;

    self->addLayout(layout, stretch);

    return 0;
}

static int setAlignment(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->setAlignment(static_cast<Qt::AlignmentFlag>(info.getInteger(2)));

    return 0;
}

static int setSpacing(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->setSpacing(info.getInteger(2));

    return 0;
}

static int setMargin(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->setMargin(info.getInteger(2));

    return 0;
}

static int addStretch(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->addStretch(info.getInteger(2));

    return 0;
}

static int addSpacing(const CallbackInfo &info)
{
    if (info.length() != 2)
        return info.error("expecting exactly 1 argument");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->addSpacing(info.getInteger(2));

    return 0;
}

static int setContentsMargins(const CallbackInfo &info)
{
    if (info.length() != 5)
        return info.error("expecting exactly 4 arguments");

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);

    int left = info.getInteger(2);
    int top = info.getInteger(3);
    int right = info.getInteger(4);
    int bottom = info.getInteger(5);

    self->setContentsMargins(left, top, right, bottom);

    return 0;
}

void LuaLayout::require(lua::Lua *state)
{
    lua::Class luaClass(className);

    LuaWidgetBase::methods(luaClass);

    luaClass.addConstructor<constructor>();

    luaClass.addMember<addWidget>("addWidget");
    luaClass.addMember<addLayout>("addLayout");
    luaClass.addMember<setAlignment>("setAlignment");
    luaClass.addMember<setSpacing>("setSpacing");
    luaClass.addMember<setMargin>("setMargin");
    luaClass.addMember<addStretch>("addStretch");
    luaClass.addMember<addSpacing>("addSpacing");
    luaClass.addMember<setContentsMargins>("setContentsMargins");

    state->createClass(luaClass);
}

}
}
