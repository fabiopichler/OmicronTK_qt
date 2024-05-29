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

#include "OmicronTK/qt/Dialog.hpp"
#include "omicrontk_qt_global.hpp"

class QLabel;
class QTextEdit;

namespace OmicronTK {
namespace qt {

class OTK_QT_EXPORT ErrorWindow : public Dialog
{
    Q_OBJECT

public:
    ErrorWindow(QWidget *parent);
    ~ErrorWindow();
    void addError(QString msg);

private:
    void createWidgets();
    void createLayouts();
    void createEvents();

signals:
    void stopStream();

private:
    QLabel *m_infoLabel;
    QPushButton *m_stopButton, *m_clearButton, *m_closeButton;
    QTextEdit *m_contentTextEdit;
};

}
}
