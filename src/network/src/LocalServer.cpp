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

#include "OmicronTK/qt/network/LocalServer.hpp"

#include <QLocalServer>
#include <QLocalSocket>

namespace OmicronTK {
namespace QT {

LocalServer::LocalServer(int timeout, const QString &appKey) : timeout(timeout), appKey(appKey)
{
    qLocalServer = nullptr;

    QLocalSocket localSocket(this);
    localSocket.connectToServer(appKey, QIODevice::NotOpen);

    if (localSocket.waitForConnected(timeout))
    {
        running = true;
        localSocket.disconnectFromServer();
    }
    else
    {
        running = false;
        createServer();
    }
}

LocalServer::~LocalServer()
{
    delete qLocalServer;
}

bool LocalServer::createServer()
{
    QLocalServer::removeServer(appKey);

    if ((qLocalServer = new QLocalServer(this)))
    {
        connect(qLocalServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

        if (qLocalServer->listen(appKey))
            return true;
    }

    return false;
}

//================================================================================================================
// public slots
//================================================================================================================

void LocalServer::newConnection()
{
    QLocalSocket *qLocalSocket = qLocalServer->nextPendingConnection();

    if (!qLocalSocket->waitForReadyRead(timeout))
    {
        if (qLocalSocket->error() != QLocalSocket::PeerClosedError)
            qWarning() << qLocalSocket->errorString();

        return;
    }

    QString data = QString::fromUtf8(qLocalSocket->readAll());
    QStringList list = data.split(":!#!:");
    list.removeAll("");

    emit messageAvailable(QVector<QString>::fromList(list));

    qLocalSocket->disconnectFromServer();
}

}
}
