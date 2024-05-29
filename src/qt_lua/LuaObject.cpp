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

#include "OmicronTK/qt_lua/LuaObject.hpp"
#include "OmicronTK/qt_lua/base/LuaWidgetBase.hpp"

#include <OmicronTK/lua/CallbackInfo.hpp>
#include <OmicronTK/lua/NativeClass.hpp>

#include <QObject>

using namespace OmicronTK::lua;

namespace OmicronTK {
namespace qt {

static const char className[] = "QObject";

static void connect(CallbackInfo &info)
{
    info.required(4);

    QObject *sender = info.getUserData<QObject>(1);
    const char *signal = info.getCString(2);
    QObject *receiver = info.getUserData<QObject>(3);
    const char *member = info.getCString(4);

    if (!sender || !signal || !receiver || !member)
        throw std::runtime_error("QObject::connect error");

#ifndef QLOCATION
# define QLOCATION "\0" __FILE__ ":" QT_STRINGIFY(__LINE__)
#endif

    QObject::connect(sender,
                     qFlagLocation(QString("2").append(signal).append(QLOCATION).toUtf8().constData()),
                     receiver,
                     qFlagLocation(QString("1").append(member).append(QLOCATION).toUtf8().constData()));
}

void LuaObject::init(Lua &lua)
{
    NativeClass nClass(lua, className);

    nClass.addStatic<connect>("connect");

    nClass.create();
}

}
}
