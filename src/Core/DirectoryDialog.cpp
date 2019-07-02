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

#include "OmicronTK/Qt/DirectoryDialog.hpp"
#include "OmicronTK/Qt/Dialog.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDirIterator>

namespace OmicronTK {
namespace OTKQT {

DirectoryDialog::DirectoryDialog(QWidget *parent)
    : m_parent(parent),
      m_dialog(nullptr),
      m_label(nullptr),
      m_countFiles(0),
      m_stop(false)
{
    connect(this, &DirectoryDialog::finished, this, &DirectoryDialog::deleteLater);
    connect(this, &DirectoryDialog::updateFiles, this, &DirectoryDialog::update);
}

DirectoryDialog::~DirectoryDialog()
{
    if (m_execLater)
        m_execLater();

    delete m_dialog;
}

void DirectoryDialog::getAllFiles(QString &dirName, std::function<void(QFileInfo &)> func)
{
    m_dirName = dirName;
    m_func = std::move(func);

    m_dialog = new Dialog(m_parent, TitleBarPolicy::HideBar);
    m_dialog->setFixedWidth(400);

    m_label = new QLabel("---");

    QPushButton *button = new QPushButton("Cancelar");
    connect(button, &QPushButton::clicked, [=]() { m_stop = true; });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("<strong>Procurado por arquivos. Aguarde...</strong>"));
    layout->addWidget(m_label);
    layout->addWidget(button, 0, Qt::AlignRight);

    m_dialog->setLayout(layout);
    m_dialog->show();
}

void DirectoryDialog::executeLater(std::function<void(void)> func)
{
    m_execLater = std::move(func);
}

void DirectoryDialog::setFileNameFilter(const QString &filter)
{
    m_fileNameFilter = filter;
}

//================================================================================================================
// public slots
//================================================================================================================

void DirectoryDialog::update(QFileInfo fileInfo)
{
    if (m_countFiles > 9)
    {
        m_label->setText(fileInfo.completeBaseName());
        m_countFiles = 0;
    }
    else
    {
        m_countFiles++;
    }
}

//================================================================================================================
// private
//================================================================================================================

void DirectoryDialog::run()
{
    QDirIterator dirIt(m_dirName, QDirIterator::Subdirectories);
    QRegExp filter(QString(m_fileNameFilter).replace(" ", "|").remove("*."), Qt::CaseInsensitive);

    while (dirIt.hasNext())
    {
        if (m_stop)
            break;

        QFileInfo fileInfo(dirIt.next());

        if (fileInfo.isFile() && fileInfo.suffix().contains(filter))
        {
            emit updateFiles(fileInfo);

            if (m_func)
                m_func(fileInfo);
        }
    }
}

}
}
