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

#include "omicrontk_qt_global.hpp"

#include <QVariant>
#include <QVector>

#include <functional>

class QWidget;
class QSettings;

namespace OmicronTK {
namespace qt {

struct MyUiLoaderWidget
{
    const QString className;
    const std::function<QWidget *(QWidget *parent)> callback;
};

// Lembrete: Essa classe está uma porcaria, eu preciso recriar ela do zero e fazer melhor.
// Nota: Skin é uma cópia da classe Theme para não perder tempo

class OTK_QT_EXPORT Skin
{
public:
    static bool init(const QString &dskin);
    static void free();
    static bool load();
    static QWidget *loadUi(const QString &fileName, QWidget *parent = nullptr,
        const QVector<MyUiLoaderWidget> &customWidgets = {}, const QVector<QString> &pluginPaths = {});
    static bool setCurrentSkin(const QString &);
    static QVariant get(const QString &key, const QVariant &value = QVariant());
    static QString getString(const QString &key, const QVariant &value = QVariant());
    static QVector<QVector<QString>> skins();
    static QVector<QVector<QString>> styles();
    static QString getDefaultSkin();

    static std::function<bool(const QString &)> s_setSkinValue;
    static std::function<bool(const QString &)> s_setStyleValue;
    static std::function<QString()> s_skinValue;
    static std::function<QString()> s_styleValue;

private:
    static QString loadCss(const QString &);

private:
    static QSettings *s_settings;
    static QString s_defaultSkin;
    static QString s_skinDir;
};

}
}
