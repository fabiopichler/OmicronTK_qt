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
#include "Dialog.hpp"

#include <functional>

class QLabel;
class QSlider;

namespace OmicronTK {
namespace qt {

class ComboBox;

class OTKQT_CORE_EXPORT Equalizer : public Dialog
{
    Q_OBJECT

public:
    Equalizer(QWidget *parent, std::vector<int> &values);
    ~Equalizer() override;

protected:
    virtual int getCurrentPresetIndex() = 0;
    virtual void setCurrentPresetIndex(int index) = 0;
    virtual void removeById(const std::string &id) = 0;

    virtual bool addEqualizerPreset(const std::string &, const std::vector<int> &) = 0;
    virtual bool setEqualizerValues(const std::string &) = 0;
    virtual bool setEqualizerPreset(int, const std::string &, const std::vector<int> &) = 0;

    virtual std::vector<int> getEqualizerPreset(int) = 0;
    virtual int getEqualizerPresets(std::vector<int> &, std::vector<std::string> &) = 0;

    void setPresetIndex(int);
    void loadPresetIndex();

private:
    void createLabels();
    void createButtons();
    void createSlider();
    void createBoxLayout();
    void createEvents();

private slots:
    void ok();
    void close() override;
    void defaultEqualizer();
    void indexChanged();
    void equalizerChanged(int, int);
    void newPreset();
    void editPreset();
    void savePreset();
    void deletePreset();
    void loadPreset();

signals:
    void updateEqualizer(int, int);

private:
    QPushButton *m_okButton, *m_cancelButton, *m_defaultButton, *m_saveButton, *m_newButton, *m_deleteButton, *m_editButton;
    QLabel *m_eqFr[19];
    QLabel *m_eqDb[19];
    QSlider *m_eq[19];
    ComboBox *m_presetCombo;

    std::vector<int> &m_values, m_oldValues;

    bool m_isNewPreset, m_presetComboUpdate;
    int m_currentIndex, m_lastId;
};

}
}
