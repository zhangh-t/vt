#include "frames/vtcontrolitem.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QWidget>

VTControlItem::VTControlItem(QObject *parent)
    : QObject(parent)
{

}

VTControlItem::VTControlItem(VTControlType oType, 
    const QString& strName,
    QWidget *parent) : QObject(parent), m_oType(oType)
{
    this->setObjectName(strName);
    switch (m_oType)
    {
    case ctLineEdit:
        m_pControlPtr = static_cast<void*>(new QLineEdit(parent));
    case ctLable:
        m_pControlPtr = static_cast<void*>(new QLabel(parent));
    case ctCombobox:
        m_pControlPtr = static_cast<void*>(new QComboBox(parent));
    case ctCheckBox:
        m_pControlPtr = static_cast<void*>(new QCheckBox(parent));
    }
}

VTControlItem::~VTControlItem()
{

}

QVariant VTControlItem::value()
{
    return m_oValue;
}

void VTControlItem::setValue(const QVariant& value)
{
    m_oValue = value;
    switch (m_oType) {
    case ctLable:
    case ctLineEdit:
        {
            QString strValue = value.toString();
            if (m_oType == ctLable)
            {
                QLabel* pLable = toContol<QLabel>();
                if (pLable)
                {
                    pLable->setText(strValue);
                }
            }
            else if (m_oType == ctLineEdit)
            {
                QLineEdit* pEdit = toContol<QLineEdit>();
                if (pEdit)
                {
                    pEdit->setText(strValue);
                }
            }
        }
    case ctCheckBox:
        {
            bool bCheck = value.toBool();
            QCheckBox* pCheckBox = toContol<QCheckBox>();
            if (pCheckBox)
            {
                pCheckBox->setChecked(bCheck);
            }
        }
    case  ctCombobox:
        {
            int nIndex = value.toInt();
            QComboBox* pCombobox = toContol<QComboBox>();
            if (pCombobox)
            {
                pCombobox->setCurrentIndex(nIndex);
            }
        }
    }
}
