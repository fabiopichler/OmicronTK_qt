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

#pragma once

#include "global.h"

#include <QDialog>

class QVBoxLayout;

namespace OmicronTK {
namespace OTKQT {

class TitleBar;

enum
{
    DIALOG
};

enum TitleBarPolicy
{
    NormalBar,
    CustomBar,
    HideBar
};

class OTKQT_CORE_EXPORT Dialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int marginLayout READ marginLayout WRITE setMarginLayout)
    Q_PROPERTY(int spacingLayout READ spacingLayout WRITE setSpacingLayout)

public:

    Dialog(QWidget *parent, TitleBarPolicy policy = TitleBarPolicy::CustomBar);
    ~Dialog() override;

    void setWindowTitle(const QString &title);
    void setLayout(QLayout *layout);

    int marginLayout() const;
    int spacingLayout() const;
    void setMarginLayout(int margin);
    void setSpacingLayout(int spacing);

public slots:
    virtual void close();

private:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    TitleBar *m_titleBar;
    QVBoxLayout *m_mainLayout;
};

}
}
