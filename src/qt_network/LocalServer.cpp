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

#include "OmicronTK/qt_network/LocalServer.hpp"

#include <QLocalServer>
#include <QLocalSocket>
#include <QSharedMemory>
#include <iostream>

namespace OmicronTK {
namespace qt {

std::unique_ptr<LocalServer> LocalServer::create(const QString &appKey, int timeout)
{
    std::unique_ptr<LocalServer> server(new LocalServer(appKey, timeout));

    //if (server->listen())
        return std::move(server);

    //return nullptr;
}

LocalServer::LocalServer(const QString &appKey, int timeout)
    : m_appKey(appKey)
    , m_timeout(timeout)
    , m_running(false)
    , m_sharedMemory(std::make_unique<QSharedMemory>(appKey))
{
    if (m_sharedMemory->attach())
    {
        m_running = true;
        m_sharedMemory.reset();

        return;
    }

    if (!m_sharedMemory->create(1))
    {
        std::cerr << "Unable to create single instance." << std::endl;
        return;
    }

    listen();
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
        std::cerr << "LocalServer::createServer() listen error" << std::endl;
        return false;
    }

    return true;
}

//================================================================================================================
// public slots
//================================================================================================================

void LocalServer::newConnection()
{
    QLocalSocket *qLocalSocket = m_localServer->nextPendingConnection();

    if (!qLocalSocket->waitForReadyRead(m_timeout))
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
