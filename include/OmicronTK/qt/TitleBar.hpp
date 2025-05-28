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

#pragma once

#include "OmicronTK/qt/Widget.hpp"
#include "omicrontk_qt_global.hpp"

class QLabel;
class QPushButton;

namespace OmicronTK {
namespace qt {

class OTK_QT_EXPORT TitleBar : public QObject
{
    Q_OBJECT

public:
    TitleBar(QWidget *parent, int flags = 0, QWidget *uiWidget = nullptr);
    inline QWidget *widget();

public Q_SLOTS:
    void setTitle(const QString &title);

private:
    bool eventFilter(QObject *watched, QEvent *event) override;

private Q_SLOTS:
    void quitApp();

public:
    QLabel *m_titleLabel;

private:
    QWidget *m_parent;
    QWidget *m_widget;
    QLabel *m_titleIcon;
    QPushButton *m_buttonMinimize, *m_buttonMinimizeTray, *m_buttonClose;
    // QPoint m_cursor;
};

inline QWidget *TitleBar::widget() { return m_widget; }

}
}
