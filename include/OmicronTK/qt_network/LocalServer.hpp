#pragma once

#include <memory>

#include <QObject>
#include <QVector>

class QLocalServer;
class QSharedMemory;

namespace OmicronTK {
namespace qt {

class LocalClient;

class LocalServer : public QObject
{
    Q_OBJECT

    LocalServer(const QString &appKey, int timeout);

public:
    static std::unique_ptr<LocalServer> create(const QString &appKey, int timeout = 1000);

    ~LocalServer() override;

    inline bool isRunning() const;
    inline const QString &appKey() const;
    inline int timeout() const;

Q_SIGNALS:
    void clientDataAvailable(QVector<QString> dataList);

private:
    bool listen();
    void newConnection();

    const QString m_appKey;
    const int m_timeout;

    bool m_running;

    std::unique_ptr<QLocalServer> m_localServer;
    std::unique_ptr<QSharedMemory> m_sharedMemory;
};

inline bool LocalServer::isRunning() const
{
    return m_running;
}

inline const QString &LocalServer::appKey() const
{
    return m_appKey;
}

inline int LocalServer::timeout() const
{
    return m_timeout;
}

}
}
