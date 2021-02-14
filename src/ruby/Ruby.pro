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
TARGET = OmicronTK+qt_ruby$${DEBUG}
DEFINES += OTKQT_BUILD_RUBY_LIB

unix:INCLUDEPATH += "$${MRUBY_INCLUDE_PATH}"

unix:LIBS += -ldl

LIBS += -lm -ldl -lmruby

contains(QMAKE_HOST.arch, x86_64) {

    unix:LIBS += -L$${MRUBY_LIB_PATH_UNIX64}

} else {

}

win32:RC_FILE = lua.rc

SOURCES += \
    RubyComboBox.cpp \
    RubyLabel.cpp \
    RubyLayout.cpp \
    RubyLineEdit.cpp \
    RubyObject.cpp \
    RubyProgressBar.cpp \
    RubyPushButton.cpp \
    RubySlider.cpp \
    RubyTitleBarWidget.cpp \
    RubyVolumeControl.cpp \
    RubyWidget.cpp \
    base/RubyObjectBase.cpp \
    base/RubyWidgetBase.cpp

HEADERS += \
    ../../include/OmicronTK/Qt/ruby/RubyComboBox.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyLabel.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyLayout.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyLineEdit.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyObject.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyProgressBar.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyPushButton.hpp \
    ../../include/OmicronTK/Qt/ruby/RubySlider.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyTitleBarWidget.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyVolumeControl.hpp \
    ../../include/OmicronTK/Qt/ruby/RubyWidget.hpp \
    ../../include/OmicronTK/Qt/ruby/base/RubyObjectBase.hpp \
    ../../include/OmicronTK/Qt/ruby/base/RubyWidgetBase.hpp


