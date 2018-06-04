#ifndef VTGKDETECTINGWIDGET_H
#define VTGKDETECTINGWIDGET_H

#include <QWidget>
#include "vehicleterminaluserinterface_global.h"
#include <QMap>
#include "frames/vtcontrolitem.h"

class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class VEHICLETERMINALUSERINTERFACE_EXPORT VTGKDetectingWidget : public QWidget
{
    Q_OBJECT

public:
    VTGKDetectingWidget(QWidget *parent = 0);
    ~VTGKDetectingWidget();
private:
    void initUI();
    void free();
private:
    void initUpperPart(QVBoxLayout* pMainLayout);
    void initLowerPart(QVBoxLayout* pMainLayout);
    void initLowerLeftPart(QHBoxLayout* pLayout);
    void initLowerRightPart(QHBoxLayout* pLayout);
private:
    void fillVehicleTypeCombobx(QComboBox* pCombobox);
private:
    VTControlItem* createControlItem(const QString& name,
        VTControlType oType);
public slots:
    void onPositionManually() {}    //手工到位
    void startDetecting() {}        //开始检测
    void liftPlatform() {}          //升台
private:
    QMap<QString, VTControlItem*> m_oControls;
};

#endif // VTGKDETECTINGWIDGET_H
