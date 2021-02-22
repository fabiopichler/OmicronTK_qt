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

#include "OmicronTK/qt/ruby/RubyPushButton.hpp"
#include "OmicronTK/qt/ruby/base/RubyWidgetBase.hpp"

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <iostream>

#include <QPushButton>

namespace OmicronTK {
namespace QT {

static const char className[] = "PushButton";

static mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    if (mrb_get_argc(mrb) == 0)
    {
        DATA_PTR(self) = new QPushButton;
    }
    else
    {
        mrb_value text;
        mrb_get_args(mrb, "S", &text);

        DATA_PTR(self) = new QPushButton(RSTRING_PTR(text));
    }

    return self;
}

static mrb_value setText(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QPushButton *>(DATA_PTR(self));

    mrb_value text;
    mrb_get_args(mrb, "S", &text);

    _this->setText(RSTRING_PTR(text));

    return mrb_nil_value();
}

void RubyPushButton_Init(mrb_state *mrb)
{
    struct RClass *rclass = mrb_define_class(mrb, className, RubyWidgetBase_Init(mrb));

    mrb_define_method(mrb, rclass, "initialize", initialize, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, rclass, "setText", setText, MRB_ARGS_REQ(1));
}

}
}
