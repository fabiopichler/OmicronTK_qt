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

#include "OmicronTK/Qt/Theme.hpp"
#include "OmicronTK/Qt/AppInfo.hpp"

#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <QDirIterator>
#include <QFontDatabase>
#include <QDebug>

namespace OmicronTK {
namespace QT {

QSettings *Theme::s_settings = nullptr;
QString Theme::s_defaultTheme;
QString Theme::s_themeDir;

std::function<bool(const QString &)> Theme::s_setThemeValue;
std::function<bool(const QString &)> Theme::s_setStyleValue;
std::function<QString()> Theme::s_themeValue;
std::function<QString()> Theme::s_styleValue;

bool Theme::init(const QString &dtheme)
{
    s_defaultTheme = dtheme;
    s_settings = nullptr;
    s_themeDir = "/themes/";

    return true;
}

void Theme::free()
{
    delete s_settings;
    s_settings = nullptr;

    QFontDatabase::removeAllApplicationFonts();
}

bool Theme::load()
{
    QString css,
            style,
            themePath = s_themeValue();

    if (themePath.contains(QRegExp("^app:")))
        themePath = QString(AppInfo::sharePath()).append(s_themeDir).append(themePath.remove(QRegExp("^app:"))).append("/");

    else if (themePath.contains(QRegExp("^config:")))
        themePath = QString(AppInfo::configPath()).append("/themes/").append(themePath.remove(QRegExp("^config:"))).append("/");

    if (!QFile::exists(QString(themePath).append("theme.ini")))
    {
        if (s_themeValue() == s_defaultTheme)
        {
            QMessageBox::critical(nullptr, "Erro", "Não foi possível carregar o Tema Padrão. Reinstale o programa para "
                                                   "resolver este problema.");
            return false;
        }

        setCurrentTheme(s_defaultTheme);
        return load();
    }

    AppInfo::setThemePath(themePath);

    delete s_settings;
    s_settings = new QSettings(QString(themePath).append("theme.ini"), QSettings::IniFormat);
    s_settings->setIniCodec("UTF-8");

    QDirIterator dirIterator(QString(themePath).append("fonts"), QDirIterator::Subdirectories);
    QRegExp suffix("ttf", Qt::CaseInsensitive);

    while (dirIterator.hasNext())
    {
        QFileInfo fileInfo(dirIterator.next());

        if (fileInfo.isFile() && fileInfo.suffix().contains(suffix))
            QFontDatabase::addApplicationFont(fileInfo.absoluteFilePath());
    }

    style = s_styleValue();

    if (!QFile::exists(QString(themePath).append(style).append(".css")))
    {
        s_setStyleValue("default");
        style = "default";
    }

    css = loadCss("/images.css");
    css.append(loadCss("/theme.css"));

    if (style != "default")
        css.append(loadCss(QString("/").append(style).append(".css")));

#ifdef Q_OS_LINUX
    css.append(loadCss("/linux.css"));
#elif defined(Q_OS_WIN)
    css.append(loadCss("windows.css"));
#endif // Q_OS_WIN

    qApp->setStyleSheet(css);

    return true;
}

bool Theme::setCurrentTheme(const QString &name)
{
    if (s_setThemeValue(name))
    {
        s_setStyleValue("default");
        return true;
    }

    return false;
}

QVariant Theme::get(const QString &key, const QVariant &value)
{
    return s_settings->value(key, value);
}

QString Theme::getString(const QString &key, const QVariant &value)
{
    return s_settings->value(key, value).toString().replace("{theme_path}", AppInfo::themePath());
}

QVector<QVector<QString> > Theme::themes()
{
    QVector<QVector<QString>> list;

    for (int i = 0; i < 2; i++)
    {
        QString path;

        if (i == 0)
            path = QString(AppInfo::sharePath()).append(s_themeDir);
        else
            path = QString(AppInfo::configPath()).append("/themes");

        QDirIterator dir(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

        while (dir.hasNext())
        {
            dir.next();
            QString iniPath = dir.filePath();
            iniPath.append("/theme.ini");

            if (QFile::exists(iniPath))
            {
                QVector<QString> values;
                QSettings ini(iniPath, QSettings::IniFormat);
                ini.setIniCodec("UTF-8");

                values << ini.value("Info/Name", "Unnamed").toString();
                values << QString((i == 0 ? "app:" : "config:")).append(dir.fileName());

                list << values;
            }
        }
    }

    return list;
}

QVector<QVector<QString>> Theme::styles()
{
    QVector<QVector<QString>> list;
    QStringList styles = s_settings->value("Styles/List").toStringList();
    list += {"Padrão", "default"};

    for (int i = 0; i < styles.length(); i++)
    {
        QStringList s = styles[i].split("=");

        if (QFile::exists(QString(AppInfo::themePath()).append("/").append(s[0]).append(".css")))
        {
            s.move(0, 1);
            list << s.toVector();
        }
    }

    return list;
}

QString Theme::getDefaultTheme()
{
    return s_defaultTheme;
}

//================================================================================================================
// private
//================================================================================================================

QString Theme::loadCss(const QString &name)
{
    QString str;
    QFile file(AppInfo::themePath() + name);

    if (file.exists())
    {
        if (file.open(QFile::ReadOnly))
        {
            str = file.readAll();
            file.close();
        }
        else
        {
            QMessageBox::warning(nullptr, "Erro!", "Erro ao carregar o arquivo de estilo: " + name);
        }
    }

    return str.replace("{theme_path}", QString(AppInfo::themePath())).append("\n");
}

}
}
