#ifndef VTSINGLEINPUTSIGNAL_H
#define VTSINGLEINPUTSIGNAL_H
/*
*@file:
*@brief:   信号发生器
*@author   zhangh-t
*@date:    2017年6月6日
*@remarks
*@version 1.0
*/
#include <QObject>
#include <QString>
#include <QColor>
#ifdef WINDOWS
#include <functional>
#endif
#include "vehicleterminalcontrols_global.h"
class VTMultiInputChart;
enum VTMultiInputChartNotifyType;
class QStringList;
class VEHICLETERMINALCONTROLS_EXPORT VTSingleInputSignal : public QObject
{
    Q_OBJECT
    friend class VTMultiInputChart;
public:
    VTSingleInputSignal(QObject *parent);
    ~VTSingleInputSignal();
public:
    virtual void onNotify(VTMultiInputChartNotifyType notifyType);
public:
    virtual void afterChartPrepared(){}
    virtual void beforeChartDestroy(){}
public:
    virtual QString name();    //信号名字
    virtual QColor color();    //曲线颜色
    virtual unsigned int overflowThreshold();    //超过多少个数据点则擦掉第一个点, 动态图有效
    virtual void clear();
    virtual void updateValue(double val);    //更新数据， 动态图有效
    virtual QList<double> staticValues();
protected:
    QString m_strName;
    QColor m_Color;
private:
    void setChart(VTMultiInputChart* pChart);
private:
    VTMultiInputChart* m_pChart;
};

/*
*@file:
*@brief:   简单的，单位时间产生一个数据的信号发生器
*@author   zhangh-t
*@date:    2017年6月6日
*@remarks
*@version 1.0
*/
#ifdef WINDOWS
typedef std::function<double ()> VTCustomaizedTimeOutCallBackFunction;   //windows下用stl的函数对象;
#else
double (*VTCustomaizedTimeOutCallBackFunction) ();    //其他可以给一个函数指针
#endif
class QTimer;
class VEHICLETERMINALCONTROLS_EXPORT VTSimpleSingleInputSignal : public VTSingleInputSignal
{
    Q_OBJECT;
public:
    VTSimpleSingleInputSignal(int ms, 
        QString& strName,
        QColor& oColor,
        VTCustomaizedTimeOutCallBackFunction pFunc = nullptr,
        QObject* parent = nullptr);
    ~VTSimpleSingleInputSignal();
public:
    virtual void beforeChartDestroy();
    virtual void afterChartPrepared();
private slots:
    void timeout();
protected:
    virtual void onTimeOut();
private:
    VTCustomaizedTimeOutCallBackFunction m_callBack;
    QTimer* m_pTimer;
    int m_nIntervalInMS;
};

class VEHICLETERMINALCONTROLS_EXPORT VTSimpleStaticInputSignal : public VTSingleInputSignal
{
    Q_OBJECT
public:
    VTSimpleStaticInputSignal(QString& strName,
        QColor& oColor,
        QList<double>& values,
        QObject* parent = nullptr);
    ~VTSimpleStaticInputSignal() {}
public:
    virtual QList<double> staticValues();
protected:
    QList<double> m_values;
};

#endif // VTSINGLEINPUTSIGNAL_H
