/*******************************************************************************
  OmicronTK_qt

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: MIT License

  Copyright 2018-2025, Fábio Pichler

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

#include "OmicronTK/qt_network/LocalServer.hpp"

#include <iostream>

#include <QLocalServer>
#include <QLocalSocket>
#include <QSharedMemory>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace OmicronTK {
namespace qt {

static bool createSharedMemory(QSharedMemory &sharedMemory)
{
    if (!sharedMemory.create(1, QSharedMemory::ReadOnly))
    {
        sharedMemory.attach();
        sharedMemory.detach();

        if (!sharedMemory.create(1, QSharedMemory::ReadOnly))
            return false;
    }

    return true;
}

std::unique_ptr<LocalServer> LocalServer::create(const QString &appKey, int timeout)
{
    return std::unique_ptr<LocalServer>(new LocalServer(appKey, timeout));
}

LocalServer::LocalServer(const QString &appKey, int timeout)
    : m_appKey(appKey)
    , m_timeout(timeout)
    , m_running(false)
    , m_sharedMemory(std::make_unique<QSharedMemory>(appKey))
{
    if (createSharedMemory(*m_sharedMemory))
    {
        listen();
        return;
    }

    if (m_sharedMemory->attach(QSharedMemory::ReadOnly))
    {
        m_running = true;
        m_sharedMemory->detach();
        m_sharedMemory.reset();
    }
}

LocalServer::~LocalServer()
{
}

bool LocalServer::listen()
{
    QLocalServer::removeServer(m_appKey);

    m_localServer = std::make_unique<QLocalServer>(this);
    connect(m_localServer.get(), &QLocalServer::newConnection, this, &LocalServer::newConnection);

    if (!m_localServer->listen(m_appKey))
    {
        std::cerr << "LocalServer::listen() listen error" << std::endl;
        return false;
    }

    return true;
}

void LocalServer::newConnection()
{
    QLocalSocket *qLocalSocket = m_localServer->nextPendingConnection();

    if (!qLocalSocket->waitForReadyRead(m_timeout))
    {
        if (qLocalSocket->error() != QLocalSocket::PeerClosedError)
            qWarning() << qLocalSocket->errorString();

        return;
    }

    QByteArray data = qLocalSocket->readAll().trimmed();

    if (data.isEmpty())
    {
        qLocalSocket->disconnectFromServer();
        return;
    }

    qsizetype index = data.indexOf(';');
    QByteArray left = data.left(index);
    qsizetype length = left.right(left.length()-7).toLongLong();
    QByteArray body = data.right(length);

    if (body.length() != length)
    {
        qLocalSocket->disconnectFromServer();
        qWarning() << "LocalServer::newConnection: The message body is the wrong size";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(body);

    if (doc.isArray())
    {
        const QJsonArray array = doc.array();
        QVector<QString> vector;

        for (const QJsonValue &value : array)
            vector.push_back(value.toString().trimmed());

        Q_EMIT clientDataAvailable(vector);
    }

    qLocalSocket->disconnectFromServer();
}

}
}
