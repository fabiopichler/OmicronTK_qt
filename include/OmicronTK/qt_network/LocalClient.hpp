#pragma once

#include <QObject>
#include <QVector>

namespace OmicronTK {
namespace qt {

class LocalServer;

class LocalClient : public QObject
{
    Q_OBJECT

public:
    LocalClient(const QString &appKey, int timeout = 1000);
    LocalClient(const LocalServer &localServer);

    bool sendDataToServer(const QVector<QString> &dataList);

private:
    const QString m_appKey;
    const int m_timeout;
};

}
}
