#ifndef VTCONTROLITEM_H
#define VTCONTROLITEM_H

#include <QObject>
#include <QVariant>
enum VTControlType
{
    ctLineEdit,
    ctLable,
    ctCheckBox,
    ctCombobox,
};
class QWidget;
class VTControlItem : public QObject
{
    Q_OBJECT

public:
    VTControlItem(QObject *parent = nullptr);
    VTControlItem(VTControlType oType,
        const QString& strName,
        QWidget *parent = nullptr);
    ~VTControlItem();
public:
    QVariant value();
    void setValue(const QVariant& value);
public:
    template <class T>
        T* toContol();
public:
    void* m_pControlPtr;
    VTControlType m_oType;
    QVariant m_oValue;
};

template <class T>
    T* VTControlItem::toContol()
{
    return static_cast<T*>(m_pControlPtr);
}

#endif // VTCONTROLITEM_H
