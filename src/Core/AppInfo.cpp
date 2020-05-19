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

#include "OmicronTK/Qt/AppInfo.hpp"

#include <QStandardPaths>

namespace OmicronTK {
namespace QT {

QString AppInfo::s_appName;
QString AppInfo::s_appVersion;
QString AppInfo::s_rootPath;
QString AppInfo::s_sharePath;
QString AppInfo::s_pluginsPath;
QString AppInfo::s_configPath;
QString AppInfo::s_executablePath;
QString AppInfo::s_guiBasePath;
QString AppInfo::s_themePath;

void AppInfo::setAppName(const QString &name)
{
    s_appName = name;
}

void AppInfo::setAppVersion(const QString &ver)
{
    s_appVersion = ver;
}

void AppInfo::setRootPath(const QString &path)
{
    s_rootPath = path;
}

void AppInfo::setSharePath(const QString &path)
{
    s_sharePath = path;
}

void AppInfo::setPluginsPath(const QString &path)
{
    s_pluginsPath = path;
}

void AppInfo::setConfigPath(const QString &path)
{
    s_configPath = path;
}

void AppInfo::setExecutablePath(const QString &path)
{
    s_executablePath = path;
}

void AppInfo::setGuiBasePath(const QString &path)
{
    s_guiBasePath = path;
}

void AppInfo::setThemePath(const QString &path)
{
    s_themePath = path;
}

const QString &AppInfo::appName()
{
    return s_appName;
}

const QString &AppInfo::appVersion()
{
    return s_appVersion;
}

const QString &AppInfo::rootPath()
{
    return s_rootPath;
}

const QString &AppInfo::sharePath()
{
    return s_sharePath;
}

const QString &AppInfo::pluginsPath()
{
    return s_pluginsPath;
}

const QString &AppInfo::configPath()
{
    return s_configPath;
}

const QString &AppInfo::executablePath()
{
    return s_executablePath;
}

const QString &AppInfo::guiBasePath()
{
    return s_guiBasePath;
}

const QString &AppInfo::themePath()
{
    return s_themePath;
}

}
}
