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
