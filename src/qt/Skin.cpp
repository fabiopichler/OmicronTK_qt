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

#include "OmicronTK/qt/Skin.hpp"
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

class MyUiLoader : public QUiLoader
{
    const QVector<MyUiLoaderWidget> &m_customWidgets;

public:
    explicit MyUiLoader(const QVector<MyUiLoaderWidget> &customWidgets, QObject *parent = nullptr)
        : QUiLoader(parent)
        , m_customWidgets(customWidgets) {}

    QWidget *createWidget(const QString &className, QWidget *parent = nullptr, const QString &name = QString()) override
    {
        for (const auto &customWidget : m_customWidgets)
        {
            if (customWidget.className == className && customWidget.callback)
            {
                QWidget *widget = customWidget.callback(parent);
                widget->setObjectName(name);
                return widget;
            }
        }

        return QUiLoader::createWidget(className, parent, name);
    }
};

QSettings *Skin::s_settings = nullptr;
QString Skin::s_defaultSkin;
QString Skin::s_skinDir;

std::function<bool(const QString &)> Skin::s_setSkinValue;
std::function<bool(const QString &)> Skin::s_setStyleValue;
std::function<QString()> Skin::s_skinValue;
std::function<QString()> Skin::s_styleValue;

bool Skin::init(const QString &dskin)
{
    s_defaultSkin = dskin;
    s_settings = nullptr;
    s_skinDir = "/skins/";

    return true;
}

void Skin::free()
{
    delete s_settings;
    s_settings = nullptr;

    QFontDatabase::removeAllApplicationFonts();
}

// Nota para mim mesmo (para a refatoração):
// Skin também precisa carregar o QSS assim como Theme (preciso refatorar e implementar isso corretamente);
// Skin deve ser carregado após Theme;
// Skin pode substituir imagens da janela princial e adicionar fontes para a janela principal (não para o tema globalmente)

bool Skin::load()
{
    //QString qss;
    //QString style;
    QString skinPath = s_skinValue();

    if (skinPath.contains(QRegularExpression("^app:")))
        skinPath = QString(AppInfo::sharePath()).append(s_skinDir).append(skinPath.remove(QRegularExpression("^app:"))).append("/");

    else if (skinPath.contains(QRegularExpression("^config:")))
        skinPath = QString(AppInfo::configPath()).append("/skins/").append(skinPath.remove(QRegularExpression("^config:"))).append("/");

    if (!QFile::exists(QString(skinPath).append("skin.ini")))
    {
        if (s_skinValue() == s_defaultSkin)
        {
            QMessageBox::critical(nullptr, "Erro", "Não foi possível carregar o Skin Padrão. Reinstale o programa para "
                                                   "resolver este problema.");
            return false;
        }

        setCurrentSkin(s_defaultSkin);
        return load();
    }

    AppInfo::setSkinPath(skinPath);

    delete s_settings;
    s_settings = new QSettings(QString(skinPath).append("skin.ini"), QSettings::IniFormat);
    //s_settings->setIniCodec("UTF-8");

    QDirIterator dirIterator(QString(skinPath).append("fonts"), QDirIterator::Subdirectories);
    QRegularExpression suffix("ttf", QRegularExpression::CaseInsensitiveOption);

    while (dirIterator.hasNext())
    {
        QFileInfo fileInfo(dirIterator.next());

        if (fileInfo.isFile() && fileInfo.suffix().contains(suffix))
            QFontDatabase::addApplicationFont(fileInfo.absoluteFilePath());
    }

    // style = s_styleValue();

    // if (!QFile::exists(QString(skinPath).append(style).append(".qss")))
    // {
    //     s_setStyleValue("default");
    //     style = "default";
    // }

//     qss = loadQss("/images.qss");
//     qss.append(loadQss("/skin.qss"));

//     if (style != "default")
//         qss.append(loadQss(QString("/").append(style).append(".qss")));

// #ifdef Q_OS_LINUX
//     qss.append(loadQss("/linux.qss"));
// #elif defined(Q_OS_WIN)
//     qss.append(loadQss("windows.qss"));
// #endif // Q_OS_WIN

//     qApp->setStyleSheet(qss);

    return true;
}

QWidget *Skin::loadUi(const QString &fileName, QWidget *parent, const QVector<MyUiLoaderWidget> &customWidgets,
                       const QVector<QString> &pluginPaths)
{
    QWidget *uiWidget = nullptr;
    QFile file(AppInfo::skinPath() + fileName);

#if 0
    QUiLoader loader;

    loader.addPluginPath(AppInfo::pluginsPath() + "/designer");

    for (const auto &path : pluginPaths)
        loader.addPluginPath(path);
#else
    MyUiLoader loader(customWidgets);
#endif

    if (!file.open(QFile::ReadOnly) || !(uiWidget = loader.load(&file, parent)))
        setCurrentSkin(s_defaultSkin);

    file.close();
    return uiWidget;
}

bool Skin::setCurrentSkin(const QString &name)
{
    if (s_setSkinValue(name))
    {
        s_setStyleValue("default");
        return true;
    }

    return false;
}

QVariant Skin::get(const QString &key, const QVariant &value)
{
    return s_settings->value(key, value);
}

QString Skin::getString(const QString &key, const QVariant &value)
{
    return s_settings->value(key, value).toString().replace("{skin_path}", AppInfo::skinPath());
}

QVector<QVector<QString> > Skin::skins()
{
    QVector<QVector<QString>> list;

    for (int i = 0; i < 2; i++)
    {
        QString path;

        if (i == 0)
            path = QString(AppInfo::sharePath()).append(s_skinDir);
        else
            path = QString(AppInfo::configPath()).append("/skins");

        QDirIterator dir(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

        while (dir.hasNext())
        {
            dir.next();
            QString iniPath = dir.filePath();
            iniPath.append("/skin.ini");

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

QVector<QVector<QString>> Skin::styles()
{
    QVector<QVector<QString>> list;
    QStringList styles = s_settings->value("Styles/List").toStringList();
    list.push_back({"Padrão", "default"});

    for (int i = 0; i < styles.length(); i++)
    {
        QStringList s = styles[i].split("=");

        if (QFile::exists(QString(AppInfo::skinPath()).append("/").append(s[0]).append(".qss")))
        {
            s.move(0, 1);
            list << s.toVector();
        }
    }

    return list;
}

QString Skin::getDefaultSkin()
{
    return s_defaultSkin;
}

//================================================================================================================
// private
//================================================================================================================

QString Skin::loadQss(const QString &name)
{
    QString str;
    QFile file(AppInfo::skinPath() + name);

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

    return str.replace("{skin_path}", QString(AppInfo::skinPath())).append("\n");
}

}
}
