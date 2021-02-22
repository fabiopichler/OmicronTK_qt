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

#include "OmicronTK/qt/DropArea.hpp"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QString>

namespace OmicronTK {
namespace QT {

DropArea::DropArea(QWidget *parent)
    : Widget(parent),
      m_allowAnyFile(false)
{
}

void DropArea::setFileNameFilter(const QString &filter)
{
    m_fileNameFilter = filter;
}

void DropArea::setPlaylistExt(const QString &ext)
{
    m_playlistExt = ext;
}

void DropArea::setAllowAnyFile(bool anyFile)
{
    m_allowAnyFile = anyFile;
}

//================================================================================================================
// protected
//================================================================================================================

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    emit dragAndDrop(true);
    event->acceptProposedAction();
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QVector<QString> list;
        QString filter = QString(m_fileNameFilter).replace(" ", "|").remove("*");
        QList<QUrl> urls = mimeData->urls();

#ifdef Q_OS_UNIX
        QString prefix = "file://";
#elif defined(Q_OS_WIN)
        QString prefix = "file:///";
#endif

        for (int i = 0; i < urls.length(); i++)
            list << urls[i].toString();

        if (list.length() == 1 && list[0].contains(QRegExp(QString(".").append(m_playlistExt).append("$"), Qt::CaseInsensitive)))
        {
            list[0].remove(prefix);
        }
        else if (m_allowAnyFile)
        {
            for (int i = list.length()-1; i > -1; i--)
                list[i].remove(prefix);
        }
        else
        {
            for (int i = list.length() - 1; i > -1; i--)
            {
                if (list[i].contains(QRegExp(QString("^").append(prefix).append("(.*)(").append(filter).append(")$"), Qt::CaseInsensitive)))
                    list[i].remove(prefix);
                else
                    list.removeAt(i);
            }
        }

        if (!list.isEmpty())
        {
            list.push_front(QString("--nohide"));
            emit filesFromDropArea(list);
        }
    }

    emit dragAndDrop(false);
    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    emit dragAndDrop(false);
    event->accept();
}

}
}
