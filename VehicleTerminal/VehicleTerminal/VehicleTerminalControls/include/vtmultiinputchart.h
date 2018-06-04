#ifndef VTMULTIINPUTCHART_H
#define VTMULTIINPUTCHART_H
/*
*@file:
*@brief:   多路输入的图表控件，X轴为时间
*@author   zhangh-t
*@date:    2017年6月6日
*@remarks
*@version 1.0
*/
#include "VTHtmlBoard.h"
#include "vehicleterminalcontrols_global.h"
#include <QList>
#include <QFlags>
#include "vtcommon.h"

class VTSingleInputSignal;
class VTMultiInputChartPrivate;
class QVariant;

//图标外观选项
enum VTMultiInputChartOption
{
    micDynamic = 0x00000001,    //动态的，X轴随时间变化
    micStatic = 0x00000002,     //静态图，直接从Signal中要数据
    micUseUTC = 0x00000004,     //是否使用世界标准时
    micDenseXAxis = 0x00000008, //时间轴较为密集
};

//图表附加选项
enum VTMultiInputChartAdditionalOption{
    aoTitle = 0,                        //图标标题, 默认为"N/A"(QString)
    aoSubTitle,                         //图标副标题, 默认没有(QString)
    aoYAxisTitle,                       //Y轴标题，默认"N/A"(QString)
    aoValueSuffix,                      //静态图中, 数据点的单位(QString)
    aoEnableLegend,                     //使能图例(bool)
    aoLegendLayout,                     //图例布局(enum)
    aoLegendAlign,                      //图例对齐方式(enum)
    aoLengenVertAlign,                  //图例竖直对其方式(enum)
    aoLegenBorderWidth,                 //图例的边框线宽度(int)
    aoEnableXAxisLabels,                //动态图是否使能X轴坐标
    aoXAxisCategories,                  //静态图的X轴刻度线名称(QStringList)
};

enum VTMultiInputChartLayoutOption {
    loVertical,                         //图例水平布局
    loHorizental,                       //图例竖直布局
};

enum VTMultiInputChartAlignOption {
    aoLeftOrTop,
    aoCenter,
    aoRightOrBottm,
};
typedef QFlags<VTMultiInputChartOption> VTMultiInputChartOptions;


VEHICLETERMINALCONTROLS_EXPORT extern VTMultiInputChartOptions defaultOption;   //
enum VTMultiInputChartNotifyType{
    micntPrepared = 0,
    micntBeforeDestroy,
};

class VEHICLETERMINALCONTROLS_EXPORT VTMultiInputChart : public VTHtmlBoard
{
    Q_OBJECT
public:
    VTMultiInputChart(QWidget *parent,
        VTMultiInputChartOptions& options,
        VTOptions& oAdditionalOptions,
        int nSignals,
        ...);

    VTMultiInputChart(VTMultiInputChartOptions& options,
        QList<VTSingleInputSignal*> inputs,
        VTOptions& oAdditionalOptions,
        QWidget* parent = nullptr);

    ~VTMultiInputChart();
public:
    void clearAllSignals();
    void clearSignal(VTSingleInputSignal* pSignal);
    void removeSignal(int index);
public:
    void notify(VTMultiInputChartNotifyType notifyType);
private:
    void notifyDelete(VTSingleInputSignal* pSignal);
    void notifyUpdate(VTSingleInputSignal* pSignal, double val);
protected:
    virtual void loadFinished();
private:
    QList<VTSingleInputSignal*> m_listSignals;
private:
    friend class VTMultiInputChartPrivate;
    friend class VTSingleInputSignal;
    VTMultiInputChartPrivate* m_pPrivate;
};

#endif // VTMULTIINPUTCHART_H
