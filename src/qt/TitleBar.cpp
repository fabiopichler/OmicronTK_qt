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

#include "OmicronTK/qt/TitleBar.hpp"
#include "OmicronTK/qt/AppInfo.hpp"
#include "OmicronTK/qt/Dialog.hpp"
#include "OmicronTK/qt/Theme.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QApplication>

namespace OmicronTK {
namespace qt {

TitleBar::TitleBar(QWidget *parent, int flags, QWidget *uiWidget)
    : QObject(parent)
{
    if (uiWidget)
    {
        m_widget = uiWidget;
        m_titleIcon = uiWidget->findChild<QLabel *>("windowIconLabel");
        m_titleLabel = uiWidget->findChild<QLabel *>("windowTitleLabel");
        m_buttonMinimize = uiWidget->findChild<QPushButton *>("minimizeButton");
        m_buttonMinimizeTray = uiWidget->findChild<QPushButton *>("minimizeTrayButton");
        m_buttonClose = uiWidget->findChild<QPushButton *>("closeButton");
    }
    else
    {
        m_widget = new Widget(parent);
        m_titleIcon = new QLabel;
        m_titleLabel = new QLabel;
        m_buttonMinimize = new QPushButton;
        m_buttonMinimizeTray = new QPushButton;
        m_buttonClose = new QPushButton;

        m_titleIcon->setObjectName("windowIconLabel");
        m_titleLabel->setObjectName("windowTitleLabel");
        m_buttonMinimize->setObjectName("minimizeButton");
        m_buttonMinimizeTray->setObjectName("minimizeTrayButton");
        m_buttonClose->setObjectName("closeButton");

        m_widget->setProperty("class", "titleBar");
        m_titleIcon->setProperty("class", "windowIconLabel");
        m_titleLabel->setProperty("class", "windowTitleLabel");
        m_buttonMinimize->setProperty("class", "titleBarButtons minimizeButton");
        m_buttonMinimizeTray->setProperty("class", "titleBarButtons minimizeTrayButton");
        m_buttonClose->setProperty("class", "titleBarButtons closeButton");

        auto layout = new QHBoxLayout;
        layout->addWidget(m_titleIcon);
        layout->addWidget(m_titleLabel);
        layout->addStretch(1);
        layout->addWidget(m_buttonMinimize);
        layout->addWidget(m_buttonMinimizeTray);
        layout->addWidget(m_buttonClose);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        m_widget->setLayout(layout);
    }

    m_titleIcon->setPixmap(QPixmap(QString(AppInfo::sharePath()).append("/icon.png")));
    m_titleLabel->setText(parent->windowTitle());
    m_buttonMinimize->setToolTip("Minimizar");
    m_buttonMinimizeTray->setToolTip("Minimizar para a Bandeja");
    m_buttonClose->setToolTip("Fechar");

    m_widget->installEventFilter(this);

    if (flags & DIALOG)
    {
        m_buttonMinimize->hide();
        m_buttonMinimizeTray->hide();

        connect(m_buttonClose, SIGNAL(clicked()), parent, SLOT(close()));
    }
    else
    {
        connect(m_buttonMinimize, SIGNAL(clicked()), parent, SLOT(showMinimized()));
        connect(m_buttonMinimizeTray, SIGNAL(clicked()), parent, SLOT(hide()));
        connect(m_buttonClose, SIGNAL(clicked()), this, SLOT(quitApp()));
    }
}

void TitleBar::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

//================================================================================================================
// private
//================================================================================================================

bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != m_widget)
        return false;

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->button() == Qt::LeftButton)
            m_cursor = m_widget->mapToParent(mouseEvent->pos());
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->buttons() == Qt::LeftButton)
            static_cast<QWidget *>(parent())->move(mouseEvent->globalPosition().toPoint() - m_cursor);
    }

    return false;
}

//================================================================================================================
// private Q_SLOTS
//================================================================================================================

void TitleBar::quitApp()
{
    static_cast<QWidget *>(parent())->hide();
    qApp->quit();
}

}
}
