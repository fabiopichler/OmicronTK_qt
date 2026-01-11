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

#include "OmicronTK/qt/Slider.hpp"

#include <QMouseEvent>

namespace OmicronTK {
namespace qt {

Slider::Slider(QWidget *parent)
    : QSlider(parent)
{
    m_sendEvent = false;
    setPageStep(0);
}

//---------------------------------------------------------------------------------------------------------------
// private
//---------------------------------------------------------------------------------------------------------------

void Slider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_sendEvent = true;

    QSlider::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    //m_sendEvent = false;
    QSlider::mouseMoveEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_sendEvent)
    {
        m_sendEvent = false;

        double halfHandleWidth = (0.5 * 9) + 0.5;
        double adaptedPosX = event->position().x();

        if (adaptedPosX < halfHandleWidth)
            adaptedPosX = halfHandleWidth;

        if (adaptedPosX > width() - halfHandleWidth)
            adaptedPosX = width() - halfHandleWidth;

        double newWidth = (width() - halfHandleWidth) - halfHandleWidth;
        double normalizedPosition = (adaptedPosX - halfHandleWidth) / newWidth;
        double pos = minimum() + ((maximum() - minimum()) * normalizedPosition);

        setValue(static_cast<int>(pos));
        Q_EMIT sliderMoved(static_cast<int>(pos));
        event->accept();
    }

    QSlider::mouseReleaseEvent(event);
}

void Slider::enterEvent(QEnterEvent *event)
{
    Q_EMIT hover(true, event);

    QSlider::enterEvent(event);
}

void Slider::leaveEvent(QEvent *event)
{
    Q_EMIT hover(false, event);

    QSlider::leaveEvent(event);
}

}
}
