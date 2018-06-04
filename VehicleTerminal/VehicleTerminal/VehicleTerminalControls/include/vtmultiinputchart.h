#ifndef VTMULTIINPUTCHART_H
#define VTMULTIINPUTCHART_H
/*
*@file:
*@brief:   ��·�����ͼ��ؼ���X��Ϊʱ��
*@author   zhangh-t
*@date:    2017��6��6��
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

//ͼ�����ѡ��
enum VTMultiInputChartOption
{
    micDynamic = 0x00000001,    //��̬�ģ�X����ʱ��仯
    micStatic = 0x00000002,     //��̬ͼ��ֱ�Ӵ�Signal��Ҫ����
    micUseUTC = 0x00000004,     //�Ƿ�ʹ�������׼ʱ
    micDenseXAxis = 0x00000008, //ʱ�����Ϊ�ܼ�
};

//ͼ����ѡ��
enum VTMultiInputChartAdditionalOption{
    aoTitle = 0,                        //ͼ�����, Ĭ��Ϊ"N/A"(QString)
    aoSubTitle,                         //ͼ�긱����, Ĭ��û��(QString)
    aoYAxisTitle,                       //Y����⣬Ĭ��"N/A"(QString)
    aoValueSuffix,                      //��̬ͼ��, ���ݵ�ĵ�λ(QString)
    aoEnableLegend,                     //ʹ��ͼ��(bool)
    aoLegendLayout,                     //ͼ������(enum)
    aoLegendAlign,                      //ͼ�����뷽ʽ(enum)
    aoLengenVertAlign,                  //ͼ����ֱ���䷽ʽ(enum)
    aoLegenBorderWidth,                 //ͼ���ı߿��߿��(int)
    aoEnableXAxisLabels,                //��̬ͼ�Ƿ�ʹ��X������
    aoXAxisCategories,                  //��̬ͼ��X��̶�������(QStringList)
};

enum VTMultiInputChartLayoutOption {
    loVertical,                         //ͼ��ˮƽ����
    loHorizental,                       //ͼ����ֱ����
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
