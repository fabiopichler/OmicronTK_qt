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

    mrb_value widget, stretch, alignment;
    mrb_get_args(mrb, "oii", &widget, &stretch, &alignment);

    _this->addWidget(
                static_cast<QWidget *>(DATA_PTR(widget)),
                mrb_fixnum(stretch),
                static_cast<Qt::AlignmentFlag>(mrb_fixnum(alignment))
                );

    return mrb_nil_value();
}

static mrb_value addLayout(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value layout, stretch;
    mrb_get_args(mrb, "oi", &layout, &stretch);

    _this->addLayout(static_cast<QBoxLayout *>(DATA_PTR(layout)), mrb_fixnum(stretch));

    return mrb_nil_value();
}

static mrb_value setAlignment(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value alignment;
    mrb_get_args(mrb, "i", &alignment);

    _this->setAlignment(static_cast<Qt::AlignmentFlag>(mrb_fixnum(alignment)));

    return mrb_nil_value();
}

static mrb_value setSpacing(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value spacing;
    mrb_get_args(mrb, "i", &spacing);

    _this->setSpacing(mrb_fixnum(spacing));

    return mrb_nil_value();
}

static mrb_value setMargin(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value margin;
    mrb_get_args(mrb, "i", &margin);

    _this->setMargin(mrb_fixnum(margin));

    return mrb_nil_value();
}

static mrb_value addStretch(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value stretch;
    mrb_get_args(mrb, "i", &stretch);

    _this->addStretch(mrb_fixnum(stretch));

    return mrb_nil_value();
}

static mrb_value addSpacing(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value spacing;
    mrb_get_args(mrb, "i", &spacing);

    _this->addSpacing(mrb_fixnum(spacing));

    return mrb_nil_value();
}

static mrb_value setContentsMargins(mrb_state *mrb, mrb_value self)
{
    auto _this = static_cast<QBoxLayout *>(DATA_PTR(self));

    mrb_value left, top, right, bottom;
    mrb_get_args(mrb, "iiii", &left, &top, &right, &bottom);

    _this->setContentsMargins(mrb_fixnum(left), mrb_fixnum(top), mrb_fixnum(right), mrb_fixnum(bottom));

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
