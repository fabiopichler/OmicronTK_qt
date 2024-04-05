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

#include "global.h"

#include <QVariant>
#include <QVector>

#include <functional>

class QWidget;
class QSettings;

namespace OmicronTK {
namespace qt {

class OTKQT_CORE_EXPORT Theme
{
public:
    static bool init(const QString &dtheme);
    static void free();
    static bool load();
    static QWidget *loadUi(const QString &fileName, QWidget *parent = nullptr, const QVector<QString> &pluginPaths = {});
    static bool setCurrentTheme(const QString &);
    static QVariant get(const QString &key, const QVariant &value = QVariant());
    static QString getString(const QString &key, const QVariant &value = QVariant());
    static QVector<QVector<QString>> themes();
    static QVector<QVector<QString>> styles();
    static QString getDefaultTheme();

    static std::function<bool(const QString &)> s_setThemeValue;
    static std::function<bool(const QString &)> s_setStyleValue;
    static std::function<QString()> s_themeValue;
    static std::function<QString()> s_styleValue;

private:
    static QString loadCss(const QString &);

private:
    static QSettings *s_settings;
    static QString s_defaultTheme;
    static QString s_themeDir;
};

}
}
