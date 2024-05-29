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

#include "OmicronTK/qt/ruby/base/RubyObjectBase.hpp"

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <QObject>

#include <iostream>

namespace OmicronTK {
namespace qt {

static const char className[] = "QObjectBase";
static RClass *rclass = nullptr;

static mrb_value setObjectName(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QObject *>(DATA_PTR(self));

    mrb_value text;
    mrb_get_args(mrb, "S", &text);

    _this->setObjectName(RSTRING_PTR(text));

    return mrb_nil_value();
}

static mrb_value deleteLater(mrb_state *, mrb_value self)
{
    auto _this = static_cast<QObject *>(DATA_PTR(self));

    _this->deleteLater();

    return mrb_nil_value();
}

RClass *RubyObjectBase_Init(mrb_state *mrb)
{
    if (rclass)
        return rclass;

    rclass = mrb_define_class(mrb, className, mrb->object_class);

    mrb_define_method(mrb, rclass, "setObjectName", setObjectName, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rclass, "deleteLater", deleteLater, MRB_ARGS_NONE());

    return rclass;
}

}
}
