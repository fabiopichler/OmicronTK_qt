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

#include "OmicronTK/Qt/Dialog.hpp"
#include "OmicronTK/Qt/TitleBar.hpp"
#include "OmicronTK/Qt/AppInfo.hpp"

#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>

namespace OmicronTK {
namespace QT {

Dialog::Dialog(QWidget *parent, TitleBarPolicy policy)
    : QDialog(parent)
{
    m_titleBar = nullptr;

    switch (policy)
    {
    case TitleBarPolicy::NormalBar:
        setWindowFlags(Qt::Dialog);
        break;

    case TitleBarPolicy::CustomBar:
        setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        m_titleBar = new TitleBar(this, DIALOG);
        break;

    case TitleBarPolicy::HideBar:
        setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        break;
    }

    m_mainLayout = new QVBoxLayout;

    setObjectName("dialog");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle(AppInfo::appName());
}

Dialog::~Dialog()
{
}

void Dialog::setWindowTitle(const QString &title)
{
    if (m_titleBar && m_titleBar->m_label)
        m_titleBar->m_label->setText(title);

    QDialog::setWindowTitle(title);
}

void Dialog::setLayout(QLayout *layout)
{
    Widget *mainWidget = new Widget(this);
    mainWidget->setLayout(layout);

    if (m_titleBar)
        m_mainLayout->addWidget(m_titleBar);

    m_mainLayout->addWidget(mainWidget, 1);

    QDialog::setLayout(m_mainLayout);
}

int Dialog::marginLayout() const
{
    return m_mainLayout->margin();
}

int Dialog::spacingLayout() const
{
    return m_mainLayout->spacing();
}

void Dialog::setMarginLayout(int margin)
{
    m_mainLayout->setMargin(margin);
}

void Dialog::setSpacingLayout(int spacing)
{
    m_mainLayout->setSpacing(spacing);
}

//================================================================================================================
// public slots
//================================================================================================================

void Dialog::close()
{
    QDialog::close();
}

//================================================================================================================
// private
//================================================================================================================

void Dialog::paintEvent(QPaintEvent *)
{
    QStyleOption o;
    QPainter p(this);

    o.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

}
}
