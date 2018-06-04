#ifndef VTDASHBOARD_H
#define VTDASHBOARD_H

#include <VTHtmlBoard.h>
#include "vtcommon.h"
#include "vehicleterminalcontrols_global.h"

//note 凡是注释有#标记的表示不可缺少的配置项，如果缺少，会抛出异常
enum VTDashBoardOptions
{
    dboTitle = 0,            //仪表盘标题(QString)
    dboStartAngle,           //#起始角度, (-180~180)0为12点钟方向 (int)
    dboEndAngle,             //#终止角度, (-180~180, && > startangle) (int)
    dboRangeMin,             //#量程最小值(double)
    dboRangeMax,             //#量程最大值(double)
    //表盘指针相关 Major 大刻度 Minor 小刻度
    dboMajorTickInterval,    //#大刻度间隔(int)
    dboMajorTickLabelStep,   //#大刻度的标注显示步进, 每隔几个大刻度显示一个标注(int)
    dboMinorTickInterval,    //小刻度间隔，必须小于dboMajorTickInterval(int), , -1表示自动, 0或没有表示不显示
    dboUnit,                 //显示在表盘中央的单位,(QString)
    dboPlotsBands,           //#仪表盘刻度分区(QJsonArray), 结构为{plotsBand:[{plotfrom:x,plotto:y,color:z}, {xxx}...{xxx}]}
    //dboPlotBandFrom,         //分区起始值(double)
    //dboPlotBandTo,           //分区终止值(double)
    //dboPlotColor,            //分区颜色(QColor)
    dboValueHint,            //数值名称(QString)
    dboValueSuffix,          //数值的显示单位(QString)
    dboWidth,                //宽度(int)
    dboHeight,               //宽高(int)
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
