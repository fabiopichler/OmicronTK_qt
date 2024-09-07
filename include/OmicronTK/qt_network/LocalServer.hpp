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

#pragma once

#include "omicrontk_qt_network_global.hpp"

#include <memory>
#include <QObject>
#include <QVector>

class QLocalServer;
class QSharedMemory;

namespace OmicronTK {
namespace qt {

class LocalSocket;

class OTKQT_NETWORK_EXPORT LocalServer : public QObject
{
    Q_OBJECT

    LocalServer(const QString &appKey, int timeout);

public:
    static std::unique_ptr<LocalServer> create(const QString &appKey, int timeout = 1000);

    ~LocalServer();

    bool listen();
    inline bool isRunning() const;

public Q_SLOTS:
    void newConnection();

Q_SIGNALS:
    void messageAvailable(QVector<QString>);

private:
    friend class LocalSocket;

    const QString m_appKey;
    const int m_timeout;

    bool m_running;

    std::unique_ptr<QLocalServer> m_localServer;
    std::unique_ptr<QSharedMemory> m_sharedMemory;
};

inline bool LocalServer::isRunning() const { return m_running; }

}
}
