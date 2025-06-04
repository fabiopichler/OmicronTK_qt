#include "OmicronTK/qt_network/LocalClient.hpp"
#include "OmicronTK/qt_network/LocalServer.hpp"

#include <QLocalServer>
#include <QLocalSocket>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace OmicronTK {
namespace qt {
    
LocalClient::LocalClient(const QString &appKey, int timeout)
    : m_appKey(appKey)
    , m_timeout(timeout)
{
}

LocalClient::LocalClient(const LocalServer &localServer)
    : m_appKey(localServer.appKey())
    , m_timeout(localServer.timeout())
{
}

bool LocalClient::sendDataToServer(const QVector<QString> &dataList)
{
    QLocalSocket localSocket(this);
    localSocket.connectToServer(m_appKey, QIODevice::WriteOnly);

    if (!localSocket.waitForConnected(m_timeout))
    {
        qWarning() << localSocket.errorString();
        return false;
    }

    QJsonArray array;

    for (const QString &message : dataList)
        array.append(message.trimmed());

    QByteArray body = QJsonDocument(array).toJson(QJsonDocument::Compact);

    QByteArray data;
    data.append(QString(QStringLiteral("length:%1;")).arg(body.size()).toUtf8());
    data.append(body);

    localSocket.write(data);

    if (!localSocket.waitForBytesWritten(m_timeout))
    {
        qWarning() << localSocket.errorString();
        return false;
    }

    localSocket.disconnectFromServer();

    return true;
}

}
}
