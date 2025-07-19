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

#include "OmicronTK/qt/Theme.hpp"
#include "OmicronTK/qt/AppInfo.hpp"

#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QApplication>
#include <QDirIterator>
#include <QFontDatabase>
#include <QDebug>
#include <QRegularExpression>
#include <QUiLoader>

namespace OmicronTK {
namespace qt {

// class MyUiLoader : public QUiLoader
// {
//     const QVector<MyUiLoaderWidget> &m_customWidgets;

// public:
//     explicit MyUiLoader(const QVector<MyUiLoaderWidget> &customWidgets, QObject *parent = nullptr)
//         : QUiLoader(parent)
//         , m_customWidgets(customWidgets) {}

//     QWidget *createWidget(const QString &className, QWidget *parent = nullptr, const QString &name = QString()) override
//     {
//         for (const auto &customWidget : m_customWidgets)
//         {
//             if (customWidget.className == className && customWidget.callback)
//             {
//                 QWidget *widget = customWidget.callback(parent);
//                 widget->setObjectName(name);
//                 return widget;
//             }
//         }

//         return QUiLoader::createWidget(className, parent, name);
//     }
// };

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
    QString qss,
            style,
            themePath = s_themeValue();

    if (themePath.contains(QRegularExpression("^app:")))
        themePath = QString(AppInfo::sharePath()).append(s_themeDir).append(themePath.remove(QRegularExpression("^app:"))).append("/");

    else if (themePath.contains(QRegularExpression("^config:")))
        themePath = QString(AppInfo::configPath()).append("/themes/").append(themePath.remove(QRegularExpression("^config:"))).append("/");

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
    //s_settings->setIniCodec("UTF-8");

    QDirIterator dirIterator(QString(themePath).append("fonts"), QDirIterator::Subdirectories);
    QRegularExpression suffix("ttf", QRegularExpression::CaseInsensitiveOption);

    while (dirIterator.hasNext())
    {
        QFileInfo fileInfo(dirIterator.next());

        if (fileInfo.isFile() && fileInfo.suffix().contains(suffix))
            QFontDatabase::addApplicationFont(fileInfo.absoluteFilePath());
    }

    style = s_styleValue();

    if (!QFile::exists(QString(themePath).append(style).append(".qss")))
    {
        s_setStyleValue("default");
        style = "default";
    }

    qss = loadQss("/images.qss");
    qss.append(loadQss("/theme.qss"));

    if (style != "default")
        qss.append(loadQss(QString("/").append(style).append(".qss")));

#ifdef Q_OS_LINUX
    qss.append(loadQss("/linux.qss"));
#elif defined(Q_OS_WIN)
    qss.append(loadQss("windows.qss"));
#endif // Q_OS_WIN

    qApp->setStyleSheet(qss);

    return true;
}

// QWidget *Theme::loadUi(const QString &fileName, QWidget *parent, const QVector<MyUiLoaderWidget> &customWidgets,
//                        const QVector<QString> &pluginPaths)
// {
//     QWidget *uiWidget = nullptr;
//     QFile file(AppInfo::themePath() + fileName);

// #if 0
//     QUiLoader loader;

//     loader.addPluginPath(AppInfo::pluginsPath() + "/designer");

//     for (const auto &path : pluginPaths)
//         loader.addPluginPath(path);
// #else
//     MyUiLoader loader(customWidgets);
// #endif

//     if (!file.open(QFile::ReadOnly) || !(uiWidget = loader.load(&file, parent)))
//         setCurrentTheme(s_defaultTheme);

//     file.close();
//     return uiWidget;
// }

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
                //ini.setIniCodec("UTF-8");

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
    list.push_back({"Padrão", "default"});

    for (int i = 0; i < styles.length(); i++)
    {
        QStringList s = styles[i].split("=");

        if (QFile::exists(QString(AppInfo::themePath()).append("/").append(s[0]).append(".qss")))
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

QString Theme::loadQss(const QString &name)
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
