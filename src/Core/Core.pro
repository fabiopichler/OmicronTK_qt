#*******************************************************************************
#  OmicronTK+Qt
#
#  Author: Fábio Pichler
#  Website: http://fabiopichler.net
#  License: MIT License
#
#  Copyright 2018-2019, Fábio Pichler
#
#  Permission is hereby granted, free of charge, to any person obtaining
#  a copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the Software
#  is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be
#  included in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
#  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#*******************************************************************************

include(../project.pri)

QT = core gui widgets
TARGET = OmicronTK+Qt$${DEBUG}
DEFINES += OTKQT_BUILD_CORE_LIB

win32:RC_FILE = core.rc

SOURCES += \
    AppInfo.cpp \
    ComboBox.cpp \
    Dialog.cpp \
    DirectoryDialog.cpp \
    DropArea.cpp \
    Equalizer.cpp \
    ErrorWindow.cpp \
    Label.cpp \
    PopUp.cpp \
    Slider.cpp \
    Theme.cpp \
    TitleBar.cpp \
    TitleBarWidget.cpp \
    VolumeControl.cpp \
    Widget.cpp

HEADERS += \
    ../../include/OmicronTK/Qt/AppInfo.hpp \
    ../../include/OmicronTK/Qt/global.h \
    ../../include/OmicronTK/Qt/PopUp.hpp \
    ../../include/OmicronTK/Qt/ComboBox.hpp \
    ../../include/OmicronTK/Qt/Dialog.hpp \
    ../../include/OmicronTK/Qt/DirectoryDialog.hpp \
    ../../include/OmicronTK/Qt/DropArea.hpp \
    ../../include/OmicronTK/Qt/Equalizer.hpp \
    ../../include/OmicronTK/Qt/ErrorWindow.hpp \
    ../../include/OmicronTK/Qt/Label.hpp \
    ../../include/OmicronTK/Qt/Slider.hpp \
    ../../include/OmicronTK/Qt/Theme.hpp \
    ../../include/OmicronTK/Qt/TitleBar.hpp \
    ../../include/OmicronTK/Qt/TitleBarWidget.hpp \
    ../../include/OmicronTK/Qt/Widget.hpp \
    ../../include/OmicronTK/Qt/VolumeControl.hpp \
    ../../include/OmicronTK/Qt/version.h

