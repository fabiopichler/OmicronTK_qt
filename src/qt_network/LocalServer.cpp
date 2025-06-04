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
