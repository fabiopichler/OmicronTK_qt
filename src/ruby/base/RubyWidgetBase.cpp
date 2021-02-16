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

#include "OmicronTK/Qt/ruby/base/RubyWidgetBase.hpp"
#include "OmicronTK/Qt/ruby/base/RubyObjectBase.hpp"

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <iostream>

#include <QWidget>
#include <QBoxLayout>

namespace OmicronTK {
namespace QT {

static mrb_value setLayout(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_value layout;
    mrb_get_args(mrb, "o", &layout);

    _this->setLayout(static_cast<QBoxLayout *>(DATA_PTR(layout)));

    return mrb_nil_value();
}

static mrb_value windowTitle(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    std::string title = _this->windowTitle().toStdString();

    return mrb_str_new(mrb, title.c_str(), title.size());
}

static mrb_value setStyleSheet(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_value text;
    mrb_get_args(mrb, "S", &text);

    _this->setStyleSheet(RSTRING_PTR(text));

    return mrb_nil_value();
}

static mrb_value setToolTip(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_value text;
    mrb_get_args(mrb, "S", &text);

    _this->setToolTip(RSTRING_PTR(text));

    return mrb_nil_value();
}

static mrb_value setEnabled(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_bool enabled;
    mrb_get_args(mrb, "b", &enabled);

    _this->setEnabled(enabled);

    return mrb_nil_value();
}

static mrb_value setMaximumHeight(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_value height;
    mrb_get_args(mrb, "i", &height);

    _this->setMaximumHeight(mrb_fixnum(height));

    return mrb_nil_value();
}

static mrb_value setMinimumWidth(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QWidget *>(DATA_PTR(self));

    mrb_value width;
    mrb_get_args(mrb, "i", &width);

    _this->setMinimumWidth(mrb_fixnum(width));

    return mrb_nil_value();
}

void RubyWidgetBase_Init(mrb_state *mrb, RClass *rclass)
{
    RubyObjectBase_Init(mrb, rclass);

    mrb_define_method(mrb, rclass, "setLayout", setLayout, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "windowTitle", windowTitle, MRB_ARGS_NONE());
    mrb_define_method(mrb, rclass, "setStyleSheet", setStyleSheet, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setToolTip", setToolTip, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setEnabled", setEnabled, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setMaximumHeight", setMaximumHeight, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "setMinimumWidth", setMinimumWidth, MRB_ARGS_REQ(1));
}

}
}
