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

#include "OmicronTK/Qt/ruby/RubyLayout.hpp"
#include "OmicronTK/Qt/ruby/base/RubyWidgetBase.hpp"

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <iostream>

#include <QBoxLayout>
#include <QWidget>
#include <QMenuBar>

namespace OmicronTK {
namespace QT {

static const char className[] = "BoxLayout";

static mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    // expecting 0 or 1 arguments

    mrb_value direction;
    mrb_get_args(mrb, "i", &direction);

    DATA_PTR(self) = new QBoxLayout(static_cast<QBoxLayout::Direction>(mrb_fixnum(direction)));

    return self;
}

static mrb_value addWidget(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    QWidget *widget = toUserData<QWidget>(L, 2);

//    if (!widget)
//        return luaL_error(L, "widget error");

//    int stretch = static_cast<int>(lua_tointegerx(L, 3, nullptr));
//    int alignment = static_cast<int>(lua_tointegerx(L, 4, nullptr));

//    _this->addWidget(widget, stretch, static_cast<Qt::AlignmentFlag>(alignment));

    return mrb_nil_value();
}

static mrb_value addLayout(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    QBoxLayout *layout = ObjectUtil<QBoxLayout, tableName>::checkUserData(L, 2);
//    int stretch = static_cast<int>(lua_tointegerx(L, 3, nullptr));

//    _this->addLayout(layout, stretch);

    return mrb_nil_value();
}

static mrb_value setAlignment(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    _this->setAlignment(static_cast<Qt::AlignmentFlag>(static_cast<int>(luaL_checknumber(L, 2))));

    return mrb_nil_value();
}

static mrb_value setSpacing(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    _this->setSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return mrb_nil_value();
}

static mrb_value setMargin(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    _this->setMargin(static_cast<int>(luaL_checknumber(L, 2)));

    return mrb_nil_value();
}

static mrb_value addStretch(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    _this->addStretch(static_cast<int>(luaL_checknumber(L, 2)));

    return mrb_nil_value();
}

static mrb_value addSpacing(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    _this->addSpacing(static_cast<int>(luaL_checknumber(L, 2)));

    return mrb_nil_value();
}

static mrb_value setContentsMargins(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

//    int left = static_cast<int>(luaL_checknumber(L, 2));
//    int top = static_cast<int>(luaL_checknumber(L, 3));
//    int right = static_cast<int>(luaL_checknumber(L, 4));
//    int bottom = static_cast<int>(luaL_checknumber(L, 5));

//    _this->setContentsMargins(left, top, right, bottom);

    return mrb_nil_value();
}

void RubyLayout_Init(mrb_state *mrb)
{
    struct RClass *rclass = mrb_define_class(mrb, className, mrb->object_class);

    RubyWidgetBase_Init(mrb, rclass);

    mrb_define_method(mrb, rclass, "initialize", initialize, MRB_ARGS_REQ(1));// 0 or 1 arguments
    mrb_define_method(mrb, rclass, "addLayout", addLayout, MRB_ARGS_REQ(1));// 0 or 1 arguments
    mrb_define_method(mrb, rclass, "addWidget", addWidget, MRB_ARGS_REQ(1));// expecting 1, 2 or 3 arguments
    mrb_define_method(mrb, rclass, "setAlignment", setAlignment, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setSpacing", setSpacing, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setMargin", setMargin, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "addStretch", addStretch, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "addSpacing", addSpacing, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setContentsMargins", setContentsMargins, MRB_ARGS_REQ(4));
}

}
}
