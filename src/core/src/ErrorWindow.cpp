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

#include "OmicronTK/qt/ErrorWindow.hpp"
#include "OmicronTK/qt/AppInfo.hpp"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>

namespace OmicronTK {
namespace QT {

ErrorWindow::ErrorWindow(QWidget *parent) : Dialog(parent)
{
    createWidgets();
    createLayouts();
    createEvents();

    setWindowTitle(QString("Erro » ").append(AppInfo::appName()));
    setMinimumSize(500, 300);
}

ErrorWindow::~ErrorWindow()
{
}

void ErrorWindow::addError(QString msg)
{
    if (!m_contentTextEdit->toPlainText().isEmpty())
        msg.push_front("<div>---------------------------------------------------</div>");

    m_contentTextEdit->append(msg);
}

//================================================================================================================
// private
//================================================================================================================

void ErrorWindow::createWidgets()
{
    m_infoLabel = new QLabel("Lista dos erros ocorridos:");

    m_stopButton = new QPushButton("Parar Reprodução");
    m_clearButton = new QPushButton("Limpar");
    m_closeButton = new QPushButton("Fechar");

    m_contentTextEdit = new QTextEdit;
    m_contentTextEdit->setReadOnly(true);
}

void ErrorWindow::createLayouts()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_stopButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(m_clearButton);
    buttonLayout->addWidget(m_closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_infoLabel);
    mainLayout->addWidget(m_contentTextEdit);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setMargin(8);
    mainLayout->setSpacing(8);

    setLayout(mainLayout);
}

void ErrorWindow::createEvents()
{
    connect(m_stopButton, SIGNAL(clicked()), this, SIGNAL(stopStream()));
    connect(m_clearButton, SIGNAL(clicked()), m_contentTextEdit, SLOT(clear()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

}
}
