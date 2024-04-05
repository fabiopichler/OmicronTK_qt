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

#include "../../include/OmicronTK/qt/Slider.hpp"
#include "SliderPlugin.hpp"

#include <QtPlugin>

namespace OmicronTK {
namespace qt {

SliderPlugin::SliderPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

void SliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool SliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SliderPlugin::createWidget(QWidget *parent)
{
    return new Slider(parent);
}

QString SliderPlugin::name() const
{
    return QLatin1String("MySlider");
}

QString SliderPlugin::group() const
{
    return QLatin1String("");
}

QIcon SliderPlugin::icon() const
{
    return QIcon();
}

QString SliderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SliderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SliderPlugin::isContainer() const
{
    return false;
}

QString SliderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MySlider\" name=\"mySlider\">\n</widget>\n");
}

QString SliderPlugin::includeFile() const
{
    return QLatin1String("myslider.h");
}

}
}
