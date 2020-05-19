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

#pragma once

#include "global.h"

namespace OmicronTK {
namespace QT {

class OTKQT_CORE_EXPORT AppInfo
{
public:
    static void setAppName(const QString &name);
    static void setAppVersion(const QString &ver);
    static void setRootPath(const QString &path);
    static void setSharePath(const QString &path);
    static void setPluginsPath(const QString &path);
    static void setConfigPath(const QString &path);
    static void setExecutablePath(const QString &path);
    static void setGuiBasePath(const QString &path);
    static void setThemePath(const QString &path);

    static const QString &appName();
    static const QString &appVersion();
    static const QString &rootPath();
    static const QString &sharePath();
    static const QString &pluginsPath();
    static const QString &configPath();
    static const QString &executablePath();
    static const QString &guiBasePath();
    static const QString &themePath();

private:
    static QString s_appName;
    static QString s_appVersion;
    static QString s_rootPath;
    static QString s_sharePath;
    static QString s_pluginsPath;
    static QString s_configPath;
    static QString s_executablePath;
    static QString s_guiBasePath;
    static QString s_themePath;
};

}
}
