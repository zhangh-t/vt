#include "frames/vtgkdetectingwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "frames/vtcontrolitem.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
VTGKDetectingWidget::VTGKDetectingWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

VTGKDetectingWidget::~VTGKDetectingWidget()
{
    free();
}

void VTGKDetectingWidget::initUI()
{
    QVBoxLayout* pMainLayout = new QVBoxLayout;
    initUpperPart(pMainLayout);
    initLowerPart(pMainLayout);
    this->setLayout(pMainLayout);
}

void VTGKDetectingWidget::free()
{
    for (auto iter = m_oControls.begin(); iter != m_oControls.end(); ++iter)
    {
        delete iter.value();
    }
    m_oControls.clear();
}

void VTGKDetectingWidget::initUpperPart(QVBoxLayout* pMainLayout)
{
    QVBoxLayout* pLineEditItemsLayout = new QVBoxLayout;
    //1. ��һ��
    //1.1 �����ƺ�
    QHBoxLayout* pHLayoutLine1 = new QHBoxLayout;
    QLabel* pVehicleNo = new QLabel(QStringLiteral("�����ƺ�"), this);
    VTControlItem* pVehicleNoContol = createControlItem(QString("_vehicleNo"), 
        ctLineEdit);
    //1.2 ��������
    QLabel* pVehicleType = new QLabel(QStringLiteral("��������"), this);
    VTControlItem* pVehicleTypeControl = createControlItem(QString("_vehicleType"),
        ctCombobox);
    fillVehicleTypeCombobx(static_cast<QComboBox*>(pVehicleTypeControl->m_pControlPtr));
    //1.3 �����ͺ�
    QLabel* pVehicleModel = new QLabel(QStringLiteral("�����ͺ�"), this);
    VTControlItem* pVehicleModelControl = createControlItem(QString("_vehicleModel"),
        ctLineEdit);
    //1.4 ��������
    QLabel* pDOP = new QLabel(QStringLiteral("��������"), this);
    VTControlItem* pDOPControl = createControlItem(QString("_dop"), ctLineEdit);
    QLabel* pDateTemplate = new QLabel(QStringLiteral("��/��/��"));
    pHLayoutLine1->addWidget(pVehicleNo);
    pHLayoutLine1->addWidget(pVehicleNoContol->toContol<QLineEdit>());
    pHLayoutLine1->addWidget(pVehicleType);
    pHLayoutLine1->addWidget(pVehicleTypeControl->toContol<QComboBox>());
    pHLayoutLine1->addWidget(pVehicleModel);
    pHLayoutLine1->addWidget(pVehicleModelControl->toContol<QLineEdit>());
    pHLayoutLine1->addWidget(pDOP);
    pHLayoutLine1->addWidget(pDOPControl->toContol<QLineEdit>());
    pHLayoutLine1->addWidget(pDateTemplate);
    pMainLayout->addLayout(pLineEditItemsLayout);

    //�ڶ���
}

void VTGKDetectingWidget::initLowerPart(QVBoxLayout* pMainLayout)
{

}

void VTGKDetectingWidget::initLowerLeftPart(QHBoxLayout* pLayout)
{

}

void VTGKDetectingWidget::initLowerRightPart(QHBoxLayout* pLayout)
{

}

void VTGKDetectingWidget::fillVehicleTypeCombobx(QComboBox* pCombobox)
{

}

VTControlItem* VTGKDetectingWidget::createControlItem(const QString& name, 
    VTControlType oType)
{
    VTControlItem* pItem = new VTControlItem(oType,
        name, this);
    if (m_oControls.contains(name))
    {
        delete m_oControls[name];
    }
    m_oControls[name] = pItem;
    return pItem;
}
