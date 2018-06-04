#include "vtsingleinputsignal.h"
#include "vtmultiinputchart.h"
#include <QTimer>
#include <QStringList>
VTSingleInputSignal::VTSingleInputSignal(QObject *parent)
    : QObject(parent), m_pChart(nullptr)
{

}

VTSingleInputSignal::~VTSingleInputSignal()
{

}

QString VTSingleInputSignal::name()
{
    return m_strName.isEmpty() ? "N/A" : m_strName;
}

QColor VTSingleInputSignal::color()
{
    return m_Color.isValid() ? m_Color : QColor(0, 0, 0, 255);
}

void VTSingleInputSignal::clear()
{
    if (m_pChart)
    {
        m_pChart->clearSignal(this);
    }
}

void VTSingleInputSignal::updateValue(double val)
{
    if (m_pChart)
    {
        m_pChart->notifyUpdate(this, val);
    }
}

void VTSingleInputSignal::setChart(VTMultiInputChart* pChart)
{
    m_pChart = pChart;
}

void VTSingleInputSignal::onNotify(VTMultiInputChartNotifyType notifyType)
{
    switch (notifyType) {
    case micntPrepared:
        this->afterChartPrepared();
        break;
    case micntBeforeDestroy:
        this->beforeChartDestroy();
        break;
    default:
        break;
    }
}

unsigned int VTSingleInputSignal::overflowThreshold()
{
    return 7500;
}

QList<double> VTSingleInputSignal::staticValues()
{
    return QList<double>();
}

VTSimpleSingleInputSignal::VTSimpleSingleInputSignal(int ms, 
    QString& strName,
    QColor& oColor,
    VTCustomaizedTimeOutCallBackFunction pFunc,
    QObject* parent)
    :VTSingleInputSignal(parent),
    m_callBack(pFunc), m_nIntervalInMS(ms)
{
    m_strName = strName;
    m_Color = oColor;
}

void VTSimpleSingleInputSignal::timeout()
{
    onTimeOut();
}

void VTSimpleSingleInputSignal::onTimeOut()
{
    if (m_callBack)
    {
        this->updateValue(m_callBack());
    }
}

VTSimpleSingleInputSignal::~VTSimpleSingleInputSignal()
{
    beforeChartDestroy();
}

void VTSimpleSingleInputSignal::beforeChartDestroy()
{
    if (m_callBack)
    {
        m_callBack = 0;
    }
    if (m_pTimer)
    {
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}

void VTSimpleSingleInputSignal::afterChartPrepared()
{
    m_pTimer = new QTimer();
    m_pTimer->setInterval(m_nIntervalInMS);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    m_pTimer->start();
}

VTSimpleStaticInputSignal::VTSimpleStaticInputSignal(QString& strName,
    QColor& oColor,
    QList<double>& values,
    QObject* parent)
    :VTSingleInputSignal(parent), m_values(values)
{
    m_strName = strName;
    m_Color = oColor;
}

QList<double> VTSimpleStaticInputSignal::staticValues()
{
    return m_values;
}
