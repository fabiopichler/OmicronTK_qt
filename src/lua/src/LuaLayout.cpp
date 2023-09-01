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

#include "OmicronTK/qt/lua/LuaLayout.hpp"
#include "OmicronTK/qt/lua/base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/CallbackInfo.hpp>
#include <OmicronTK/lua/NativeClass.hpp>

#include <QBoxLayout>
#include <QWidget>
#include <QMenuBar>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace qt {

static const char className[] = "BoxLayout";

static void constructor(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout::Direction direction = static_cast<QBoxLayout::Direction>(info.getInteger(2));

    info.newUserData(1, new QBoxLayout(direction));
}

static void addWidget(CallbackInfo &info)
{
    info.required(2, 4);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    QWidget *widget = info.getUserData<QWidget>(2);

    if (!widget)
        throw std::runtime_error("widget error");

    int stretch = info.getInteger(3);
    int alignment = info.getInteger(4);

    self->addWidget(widget, stretch, static_cast<Qt::AlignmentFlag>(alignment));
}

static void addLayout(CallbackInfo &info)
{
    info.required(2, 3);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    QBoxLayout *layout = info.checkUserData<QBoxLayout>(2, className);
    int stretch = info.getInteger(3);

    self->addLayout(layout, stretch);
}

static void setAlignment(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->setAlignment(static_cast<Qt::AlignmentFlag>(info.getInteger(2)));
}

static void setSpacing(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->setSpacing(info.getInteger(2));
}

// Obsoleto: Alterar para setContentsMargins
static void setMargin(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);

    int _margin = info.getInteger(2);
    self->setContentsMargins(_margin, _margin, _margin, _margin);
}

static void addStretch(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->addStretch(info.getInteger(2));
}

static void addSpacing(CallbackInfo &info)
{
    info.required(2);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);
    self->addSpacing(info.getInteger(2));
}

static void setContentsMargins(CallbackInfo &info)
{
    info.required(5);

    QBoxLayout *self = info.checkUserData<QBoxLayout>(1, className);

    int left = info.getInteger(2);
    int top = info.getInteger(3);
    int right = info.getInteger(4);
    int bottom = info.getInteger(5);

    self->setContentsMargins(left, top, right, bottom);
}

void LuaLayout::init(Lua &lua)
{
    NativeClass nClass(lua, className);

    LuaWidgetBase::methods(nClass);

    nClass.setConstructor<constructor>();

    nClass.addMember<addWidget>("addWidget");
    nClass.addMember<addLayout>("addLayout");
    nClass.addMember<setAlignment>("setAlignment");
    nClass.addMember<setSpacing>("setSpacing");
    nClass.addMember<setMargin>("setMargin");
    nClass.addMember<addStretch>("addStretch");
    nClass.addMember<addSpacing>("addSpacing");
    nClass.addMember<setContentsMargins>("setContentsMargins");

    nClass.create();
}

}
}
