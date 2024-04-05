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

#include "../../include/OmicronTK/qt/Label.hpp"
#include "LabelPlugin.hpp"

#include <QtPlugin>

namespace OmicronTK {
namespace qt {

LabelPlugin::LabelPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void LabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool LabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LabelPlugin::createWidget(QWidget *parent)
{
    return new Label(parent);
}

QString LabelPlugin::name() const
{
    return QLatin1String("MyLabel");
}

QString LabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon LabelPlugin::icon() const
{
    return QIcon();
}

QString LabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LabelPlugin::isContainer() const
{
    return false;
}

QString LabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MyLabel\" name=\"myLabel\">\n</widget>\n");
}

QString LabelPlugin::includeFile() const
{
    return QLatin1String("mylabel.h");
}

}
}
