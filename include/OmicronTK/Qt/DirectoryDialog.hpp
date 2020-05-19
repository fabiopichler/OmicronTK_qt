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

#include <QThread>
#include <QFileInfo>

#include <functional>

class QLabel;

namespace OmicronTK {
namespace QT {

class Dialog;

class OTKQT_CORE_EXPORT DirectoryDialog : public QThread
{
    Q_OBJECT

public:
    explicit DirectoryDialog(QWidget *parent);
    ~DirectoryDialog();

    void getAllFiles(QString &dirName, std::function<void(QFileInfo &)> func);
    void executeLater(std::function<void(void)> func);

    void setFileNameFilter(const QString &filter);

public slots:
    void update(QFileInfo fileInfo);

private:
    void run();

signals:
    void updateFiles(QFileInfo);

private:
    QWidget *m_parent;
    Dialog *m_dialog;
    QLabel *m_label;

    QString m_dirName, m_fileNameFilter;
    int m_countFiles;
    bool m_stop;

    std::function<void(QFileInfo &)> m_func;
    std::function<void(void)> m_execLater;
};

}
}
