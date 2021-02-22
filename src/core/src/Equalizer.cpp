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

#include "OmicronTK/qt/Equalizer.hpp"
#include "OmicronTK/qt/ComboBox.hpp"
#include "OmicronTK/qt/AppInfo.hpp"

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

namespace OmicronTK {
namespace QT {

Equalizer::Equalizer(QWidget *parent, std::vector<int> &values)
    : Dialog(parent),
      m_values(values),
      m_oldValues(values),
      m_isNewPreset(false),
      m_presetComboUpdate(false),
      m_lastId(false)
{
    createLabels();
    createButtons();
    createSlider();
    createBoxLayout();
    createEvents();
    setWindowTitle(QString("Equalizador » ").append(AppInfo::appName()));
}

Equalizer::~Equalizer()
{
}

//================================================================================================================
// protected
//================================================================================================================

void Equalizer::setPresetIndex(int idx)
{
    m_currentIndex = idx;
}

void Equalizer::loadPresetIndex()
{
    std::vector<int> ids;
    std::vector<std::string> titles;
    size_t eqLen = static_cast<size_t>(getEqualizerPresets(ids, titles));

    m_presetCombo->setEditable(false);

    if (eqLen > 0 && eqLen == ids.size() && eqLen == titles.size())
    {
        m_lastId = ids[eqLen - 1];

        if (m_presetCombo->count() > 0)
            m_currentIndex = m_presetCombo->currentIndex();

        m_presetCombo->clear();

        for (size_t i = 0; i < eqLen; i++)
            m_presetCombo->addItem(titles[i].c_str(), ids[i]);

        if (m_presetCombo->count() > 0)
            m_presetCombo->setCurrentIndex(m_currentIndex);
    }
    else
    {
        m_presetCombo->clear();
    }
}

//================================================================================================================
// private
//================================================================================================================

void Equalizer::createLabels()
{
    std::vector<QString> list;
    list.push_back("Pré Amplificador");
    list.push_back("35Hz");
    list.push_back("50Hz");
    list.push_back("75Hz");
    list.push_back("100Hz");
    list.push_back("150Hz");
    list.push_back("200Hz");
    list.push_back("400Hz");
    list.push_back("600Hz");
    list.push_back("800Hz");
    list.push_back("1KHz");
    list.push_back("2,5KHz");
    list.push_back("4KHz");
    list.push_back("6KHz");
    list.push_back("8KHz");
    list.push_back("10KHz");
    list.push_back("12KHz");
    list.push_back("14KHz");
    list.push_back("16KHz");


    for (size_t i = 0; i < 19; i++)
    {
        m_eqFr[i] = new QLabel(list[i]);
        m_eqDb[i] = new QLabel(QString("%1dB").arg(m_values[i]));

        m_eqFr[i]->setObjectName("equalizerLabel");
        m_eqDb[i]->setObjectName("equalizerLabel");
        m_eqDb[i]->setMinimumWidth(32);
    }

    m_presetCombo = new ComboBox;
    m_presetCombo->setObjectName("presetCombo");
}

void Equalizer::createButtons()
{
    m_okButton = new QPushButton("Ok");
    m_cancelButton = new QPushButton("Cancelar");
    m_defaultButton = new QPushButton("Redefinir Padrão");

    m_newButton = new QPushButton("Novo");
    m_editButton = new QPushButton("Renomear");
    m_saveButton = new QPushButton("Salvar");
    m_deleteButton = new QPushButton("Deletar");
}

void Equalizer::createSlider()
{
    m_eq[0] = new QSlider(Qt::Horizontal);
    m_eq[0]->setFixedWidth(260);
    m_eq[0]->setRange(-50, 50);
    m_eq[0]->setSliderPosition(m_values[0]);

    for (size_t i = 1; i < 19; i++)
    {
        m_eq[i] = new QSlider(Qt::Vertical);
        m_eq[i]->setRange(-30, 30);
        m_eq[i]->setSliderPosition(m_values[i]);
    }
}

void Equalizer::createBoxLayout()
{
    QVBoxLayout *volLayout = new QVBoxLayout;
    volLayout->addWidget(m_eqFr[0]);
    volLayout->addWidget(m_eq[0]);
    volLayout->addWidget(m_eqDb[0]);

    QGroupBox *volGroup = new QGroupBox("Ajustes");
    volGroup->setLayout(volLayout);

    QHBoxLayout *presetHLayout = new QHBoxLayout;
    presetHLayout->addWidget(m_newButton);
    presetHLayout->addWidget(m_saveButton);
    presetHLayout->addWidget(m_deleteButton);
    presetHLayout->addWidget(m_editButton);
    presetHLayout->setSpacing(8);

    QVBoxLayout *presetLayout = new QVBoxLayout;
    presetLayout->addWidget(m_presetCombo, 1, Qt::AlignHCenter);
    presetLayout->addLayout(presetHLayout);

    QGroupBox *presetGroup = new QGroupBox("Preset");
    presetGroup->setLayout(presetLayout);

    QHBoxLayout *optionsLayout = new QHBoxLayout;
    optionsLayout->addWidget(volGroup);
    optionsLayout->addWidget(presetGroup, 1);

    QHBoxLayout *eqLayout = new QHBoxLayout;
    eqLayout->setSpacing(10);

    QVBoxLayout *vLayout[18];

    for (int i = 0; i < 18; i++)
    {
        vLayout[i] = new QVBoxLayout;
        vLayout[i]->addWidget(m_eqFr[i + 1]);
        vLayout[i]->addWidget(m_eq[i + 1]);
        vLayout[i]->addWidget(m_eqDb[i + 1]);
        vLayout[i]->setSpacing(5);

        eqLayout->addLayout(vLayout[i]);
    }

    QGroupBox *eqGroup = new QGroupBox("Equalizador");
    eqGroup->setLayout(eqLayout);

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(m_defaultButton);
    buttons->addStretch(1);
    buttons->addWidget(m_okButton);
    buttons->addWidget(m_cancelButton);

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addWidget(eqGroup);
    layoutMain->addLayout(optionsLayout);
    layoutMain->addLayout(buttons);
    layoutMain->setContentsMargins(8, 6, 8, 8);
    layoutMain->setSpacing(8);

    setLayout(layoutMain);
}

void Equalizer::createEvents()
{
    connect(m_defaultButton, SIGNAL(clicked()), this, SLOT(defaultEqualizer()));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(ok()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(m_newButton, SIGNAL(clicked()), this, SLOT(newPreset()));
    connect(m_editButton, SIGNAL(clicked()), this, SLOT(editPreset()));
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(savePreset()));
    connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(deletePreset()));

    connect(m_presetCombo, SIGNAL(activated(int)), this, SLOT(loadPreset()));
    connect(m_presetCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged()));

    for (int i = 0; i < 19; i++)
    {
        connect(m_eq[i], &QSlider::valueChanged, [this, i](int arg) {
            equalizerChanged(i, arg);
            m_eqDb[i]->setText(QString("%1dB").arg(arg));
        });
    }
}

//================================================================================================================
// private slots
//================================================================================================================

void Equalizer::ok()
{
    QDialog::accept();
    QString val;

    for (size_t i = 0; i < 19; i++)
        val += QString("(%1, %2), ").arg(i).arg(m_values[i]);

    val.remove(QRegExp(", $"));

    setCurrentPresetIndex(m_presetCombo->currentIndex());
    setEqualizerValues(val.toStdString());
}

void Equalizer::close()
{
    m_values = m_oldValues;

    for (size_t i = 0; i < 19; i++)
    {
        emit updateEqualizer(static_cast<int>(i), m_oldValues[i]);
    }

    QDialog::close();
}

void Equalizer::defaultEqualizer()
{
    for (size_t i = 0; i < 19; i++)
    {
        m_eq[i]->setValue(0);
        m_values[i] = 0;
        emit updateEqualizer(static_cast<int>(i), 0);
    }
}

void Equalizer::indexChanged()
{
    if (m_isNewPreset)
    {
        m_isNewPreset = false;
        m_presetCombo->removeItem(m_presetCombo->count() - 1);
    }
}

void Equalizer::equalizerChanged(int id, int value)
{
    m_values[static_cast<size_t>(id)] = value;
    emit updateEqualizer(id, value);
}

void Equalizer::newPreset()
{
    if (!m_isNewPreset)
    {
        m_presetCombo->addItem("", m_lastId);
        m_presetCombo->setCurrentIndex(m_presetCombo->count() - 1);
        m_presetCombo->setEditable(true);
        m_presetCombo->setFocus();
        m_isNewPreset = true;
    }
}

void Equalizer::editPreset()
{
    if (!m_presetComboUpdate && m_presetCombo->count() > 0)
    {
        m_presetCombo->setEditable(true);
        m_presetCombo->setFocus();
        m_editButton->setText("Cancelar");
        m_presetComboUpdate = true;
    }
    else
    {
        m_presetCombo->setEditable(false);
        m_editButton->setText("Renomear");
        m_presetComboUpdate = false;
    }

    m_presetCombo->update();
}

void Equalizer::savePreset()
{
    if (m_presetCombo->count() < 1)
        return;

    if (m_presetCombo->currentText().isEmpty())
        m_presetCombo->setCurrentText("New Preset");

    if (m_isNewPreset)
    {
        m_isNewPreset = false;
        if (!addEqualizerPreset(m_presetCombo->currentText().toStdString(), m_values))
            m_presetCombo->removeItem(m_presetCombo->count() - 1);
    }
    else
    {
        setEqualizerPreset(m_presetCombo->currentData().toInt(), m_presetCombo->currentText().toStdString(), m_values);
    }

    loadPresetIndex();
}

void Equalizer::deletePreset()
{
    if (m_presetCombo->count() > 0 && !m_isNewPreset)
    {
        if (QMessageBox::question(this, "Apagar", QString("Confirmar a exclusão de: ").append(m_presetCombo->currentText()).append("?"),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            removeById(m_presetCombo->currentData().toString().toStdString());
            loadPresetIndex();
        }
    }
}

void Equalizer::loadPreset()
{
    if (!m_presetCombo->currentText().isEmpty() && m_presetCombo->currentIndex() != m_currentIndex)
        m_presetCombo->setEditable(false);

    std::vector<int> list = getEqualizerPreset(m_presetCombo->currentData().toInt());

    if (list.size() < 19)
        return;

    for (size_t i = 0; i < 19; i++)
    {
        m_eq[i]->setValue(list[i]);
        m_values[i] = list[i];
        emit updateEqualizer(static_cast<int>(i), list[i]);
    }

    m_presetCombo->setEditable(false);
    m_editButton->setText("Renomear");
    m_presetComboUpdate = false;
    m_presetCombo->update();
}

}
}
