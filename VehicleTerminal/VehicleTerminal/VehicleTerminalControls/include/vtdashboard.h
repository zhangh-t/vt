#ifndef VTDASHBOARD_H
#define VTDASHBOARD_H

#include <VTHtmlBoard.h>
#include "vtcommon.h"
#include "vehicleterminalcontrols_global.h"

//note ����ע����#��ǵı�ʾ����ȱ�ٵ���������ȱ�٣����׳��쳣
enum VTDashBoardOptions
{
    dboTitle = 0,            //�Ǳ��̱���(QString)
    dboStartAngle,           //#��ʼ�Ƕ�, (-180~180)0Ϊ12���ӷ��� (int)
    dboEndAngle,             //#��ֹ�Ƕ�, (-180~180, && > startangle) (int)
    dboRangeMin,             //#������Сֵ(double)
    dboRangeMax,             //#�������ֵ(double)
    //����ָ����� Major ��̶� Minor С�̶�
    dboMajorTickInterval,    //#��̶ȼ��(int)
    dboMajorTickLabelStep,   //#��̶ȵı�ע��ʾ����, ÿ��������̶���ʾһ����ע(int)
    dboMinorTickInterval,    //С�̶ȼ��������С��dboMajorTickInterval(int), , -1��ʾ�Զ�, 0��û�б�ʾ����ʾ
    dboUnit,                 //��ʾ�ڱ�������ĵ�λ,(QString)
    dboPlotsBands,           //#�Ǳ��̶̿ȷ���(QJsonArray), �ṹΪ{plotsBand:[{plotfrom:x,plotto:y,color:z}, {xxx}...{xxx}]}
    //dboPlotBandFrom,         //������ʼֵ(double)
    //dboPlotBandTo,           //������ֵֹ(double)
    //dboPlotColor,            //������ɫ(QColor)
    dboValueHint,            //��ֵ����(QString)
    dboValueSuffix,          //��ֵ����ʾ��λ(QString)
    dboWidth,                //���(int)
    dboHeight,               //���(int)
};

class VTDashBoardPrivate;
class QJsonObject;
class VEHICLETERMINALCONTROLS_EXPORT VTDashBoard : public VTHtmlBoard
{
    Q_OBJECT
public:
    VTDashBoard(VTOptions& dashboardOptions,
        QWidget *parent = 0);

    ~VTDashBoard();
public:
    virtual void updateValue(double value);
    static QJsonObject genPlotBand(int nRangeFrom, int nRangeTo, QColor& color);    //throws exception
protected:
    virtual void loadFinished();
private:
    friend class VTDashBoardPrivate;
    VTDashBoardPrivate* m_pPrivate;
};

#endif // VTDASHBOARD_H
