#include "vtmultiinputchart.h"
#include "vtsingleinputsignal.h"
#include <QDir>
#include <QCoreApplication>
#include <QWebSettings>
#include <QWebFrame>
#ifdef WINDOWS
#include <stdarg.h>
#else
#ifdef LINUX
#include <stdarg.h>
#endif
#endif
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "vtcontrolconsts.h"
#include "VTPrivate.h"
#include "vtexception.h"
using namespace vt;

static const QString c_strDynamicHtml = "multiinputchart_dynamic.html";
static const QString c_strStaticHtml = "multiinputchart_static.html";
static const QString c_cmdUpdateValue = "call_from_qt_upate_data(%1, %2)";
static const QString c_cmdClearAll = "call_from_qt_clear_all()";
static const QString c_cmdClearSignal = "call_from_qt_clear_series(%1)";
static const QString c_cmdInitByQt = "call_from_qt_init_chart(%1)";
VTMultiInputChartOptions defaultOption = micDynamic | micDenseXAxis;

class VTMultiInputChartPrivate : public VTPrivate
{
public:
    VTMultiInputChartPrivate(VTMultiInputChart* pChart);
    ~VTMultiInputChartPrivate();
public:
    VTMultiInputChart* m_pChartControl;
public:
    int signalCount;
    QString title;
    QString yTitle;
    int tickPixel;
    VTMultiInputChartOptions options;
    VTOptions additionalOptions;
public:
    void initJavaScriptEnviroment();
    void injectCallBackObject();
    void evaluateJavaScript(const QString& cmd);
    void initialize();
    void load();
private:
    void initializeForDynamicChart();
    void initializeForStaticChart();
private:
    QString optionString();
    QJsonArray stringListToArrayStyle(QStringList& stringList);
    template <typename T>
    QJsonArray listToJsonArray(QList<T>& list);
private:
    void fillDynamicChartOptions(QJsonObject& oJson);
    void fillStaticChartOptions(QJsonObject& oJson);
private:
    void fillLegendOption(QJsonObject& oOptionJSON);
};

template <typename T>
QJsonArray VTMultiInputChartPrivate::listToJsonArray(QList<T>& list)
{
    QJsonArray res;
    for (int i = 0 ; i < list.size(); ++i)
    {
        QJsonValue value(list.at(i));
        res.append(value);
    }
    return res;
}

VTMultiInputChartPrivate::VTMultiInputChartPrivate(VTMultiInputChart* pChart)
    :m_pChartControl(pChart)
{

}

VTMultiInputChartPrivate::~VTMultiInputChartPrivate()
{

}

void VTMultiInputChartPrivate::initJavaScriptEnviroment()
{
    //injectCallBackObject();
}

void VTMultiInputChartPrivate::initialize()
{
    if (options.testFlag(micDynamic))
    {
        initializeForDynamicChart();
    }
    else {
        initializeForStaticChart();
    }
}

void VTMultiInputChartPrivate::injectCallBackObject()
{
   /* m_pChartControl
        ->m_pCoreWebView
        ->page()
        ->mainFrame()
        ->addToJavaScriptWindowObject("qtPlugin", m_pJSCallBack);*/
}

void VTMultiInputChartPrivate::evaluateJavaScript(const QString& cmd)
{
    QWebView* pWebView = m_pChartControl->webView();
    if (pWebView)
    {
        pWebView->page()
            ->mainFrame()->evaluateJavaScript(cmd);
    }
}

void VTMultiInputChartPrivate::load()
{
    QString strPath = QCoreApplication::applicationDirPath() + 
        QDir::separator() + "htmls" + QDir::separator();
    if (options.testFlag(micDynamic))
    {
        strPath += c_strDynamicHtml;
    }
    else {
        strPath += c_strStaticHtml;
    }
    m_pChartControl->loadHtml(strPath);
}

void VTMultiInputChartPrivate::initializeForDynamicChart()
{
    initJavaScriptEnviroment();
    QString strCmdParam = optionString();
    strCmdParam = c_cmdInitByQt.arg("'" + strCmdParam + "'");
    evaluateJavaScript(strCmdParam);
}

void VTMultiInputChartPrivate::initializeForStaticChart()
{
    initJavaScriptEnviroment();
    QString strCmdParam = optionString();
    strCmdParam = c_cmdInitByQt.arg("'" + strCmdParam + "'");
    evaluateJavaScript(strCmdParam);
}

QString VTMultiInputChartPrivate::optionString()
{
    QJsonObject oInitOptions;
    //1.seriesCount;
    oInitOptions.insert(QString(jfnSeriesCount), this->signalCount);
    //2. title
    oInitOptions.insert(QString(jfnTitle), this->title);
    //3. yTtitle
    oInitOptions.insert(QString(jfnYAxisTitle), this->yTitle);
    //4. tickPixelInterval
    oInitOptions.insert(QString(jfnTickPixelInterval), this->tickPixel);
    //5. series options;
    if (options.testFlag(micDynamic))
    {
        bool bEnableXAxisLabels = getOption(additionalOptions, aoEnableXAxisLabels, true).toBool();
        if (!bEnableXAxisLabels)
        {
            QJsonObject xAxisObj;
            QJsonObject labelsObj;
            labelsObj.insert(QString(jfnEnabled), false);
            xAxisObj.insert(QString(jfnLabels), labelsObj);
            oInitOptions.insert(QString(jfnXAxis), xAxisObj);
        }
        fillDynamicChartOptions(oInitOptions);
    }
    else 
    {
        fillStaticChartOptions(oInitOptions);
    }
    //6. legend
    fillLegendOption(oInitOptions);
    QJsonDocument doc(oInitOptions);
    QString strCmdParam = doc.toJson(QJsonDocument::Compact);
    strCmdParam.replace("\\\"", "");
    strCmdParam.replace("\"", "\\\"");
    return strCmdParam;
}

void VTMultiInputChartPrivate::fillLegendOption(QJsonObject& oOptionJson)
{
    VTOptionsIter iter = additionalOptions.find(aoEnableLegend);
    if (iter != additionalOptions.end()) {
        bool bEnable = iter.value().toBool();
        QJsonObject legenJSON;
        if (false) {
            /*legenJSON.insert(QString(jfnEnabled), true);
            VTMultiInputChartLayoutOption laytouOrientation = loVertical;
            VTMultiInputChartAlignOption alignOption = aoCenter;
            int legendWidth = 0;
            iter = additionalOptions.find(aoLegendLayout);
            if (iter != additionalOptions.end())
            {
                laytouOrientation = (VTMultiInputChartLayoutOption)(iter.value().toInt());
                if (laytouOrientation == loHorizental)
                {
                    iter = additionalOptions.find(aoLegendAlign);
                    if (iter != additionalOptions.end())
                    {
                        alignOption = (VTMultiInputChartAlignOption)(iter.value().toInt());
                    }
                }
                else 
                {
                    iter = additionalOptions.find(aoLengenVertAlign);
                    if (iter != additionalOptions.end())
                    {
                        alignOption = (VTMultiInputChartAlignOption)(iter.value().toInt());
                    }
                }
            }
            iter = additionalOptions.find(aoLegenBorderWidth);
            if (iter != additionalOptions.end())
            {
                legendWidth = iter.value().toInt();
            }
            legenJSON.insert(QString(jfnEnabled), true);
            legenJSON.insert(QString(jfnEnabled), true);
            legenJSON.insert(QString(jfnEnabled), true);
            legenJSON.insert(QString(jfnEnabled), true);*/
        }
        else {
            legenJSON.insert(QString(jfnEnabled), false);
        }
        oOptionJson.insert(QString(jfnLegend), legenJSON);
    }
}

void VTMultiInputChartPrivate::fillDynamicChartOptions(QJsonObject& oJson)
{
    QJsonArray seriesArray;
    for (int i = 0; i < signalCount; ++i)
    {
        VTSingleInputSignal* pSignal = m_pChartControl->m_listSignals.at(i);
        QString strName = pSignal->name();
        QString strColor = colorToString(pSignal->color());
        int nOverflowThreshold = pSignal->overflowThreshold();
        QJsonObject obj;
        obj.insert(QString(jfnName), strName);
        obj.insert(QString(jfnColor), strColor);
        obj.insert(QString(jfnOverflowThreshold), nOverflowThreshold);
        seriesArray.append(obj);
    }
    oJson.insert(QString(jfnSeriesSchemaArray), seriesArray);
}

void VTMultiInputChartPrivate::fillStaticChartOptions(QJsonObject& oJson)
{
    VTOptions::iterator iter = additionalOptions.find(aoSubTitle);
    if (iter != additionalOptions.end())
    {
        oJson.insert(QString(jfnSubTitle), iter.value().toString());
    }
    iter = additionalOptions.find(aoValueSuffix);
    if (iter != additionalOptions.end())
    {
        oJson.insert(QString(jfnValueSuffix), iter.value().toString());
    }
    QJsonArray signalArray;
    int nMaxCount = 0;
    for (int i = 0 ; i < signalCount; ++i)
    {
        QJsonObject signal;
        VTSingleInputSignal* pSignal = m_pChartControl->m_listSignals.at(i);
        QString strName = pSignal->name();
        QString strColor = colorToString(pSignal->color());
        QList<double> valueList = pSignal->staticValues();
        int nSize = valueList.size();
        nMaxCount = nSize > nMaxCount ? nSize : nMaxCount;
        QJsonArray values = listToJsonArray(valueList);
        signal.insert(QString(jfnName), strName);
        signal.insert(QString(jfnColor), strColor);
        signal.insert(QString(jfnData), values);
        signalArray.append(signal);
    }
    oJson.insert(QString(jfnSeriesSchemaArray), signalArray);
    QStringList categories;
    iter = additionalOptions.find(aoXAxisCategories);
    if (iter != additionalOptions.end())
    {
        categories = iter.value().toStringList();
    }
    else 
    {
        for (int i = 0 ; i < nMaxCount; ++i)
        {
            categories << QString::number(i);
        }
    }
    QJsonArray categoriesArray = stringListToArrayStyle(categories);
    oJson.insert(QString(jfnCategories), categoriesArray);
}

QJsonArray VTMultiInputChartPrivate::stringListToArrayStyle(QStringList& stringList)
{
    QJsonArray res;
    for (int i = 0 ; i < stringList.size(); ++i)
    {
        QJsonValue value(stringList.at(i));
        res.append(value);
    }
    return res;
}

VTMultiInputChart::VTMultiInputChart(QWidget *parent,
    VTMultiInputChartOptions& options,
    VTOptions& oAdditionalOptions,
    int nSignals,
    ...)
    :VTHtmlBoard(parent)
{
    va_list inputs;
    va_start(inputs, nSignals);
    for (int i = 0 ; i < nSignals; ++i)
    {
        VTSingleInputSignal* pSignal = va_arg(inputs, VTSingleInputSignal*);
        pSignal->setChart(this);
        m_listSignals.push_back(pSignal);
    }
    va_end(inputs);
    m_pPrivate = new VTMultiInputChartPrivate(this);
    m_pPrivate->options = options;
    m_pPrivate->signalCount = m_listSignals.size();
    m_pPrivate->title = oAdditionalOptions.find(aoTitle) == oAdditionalOptions.end() ?
                        "N/A" : oAdditionalOptions[aoTitle].toString();
    m_pPrivate->yTitle = oAdditionalOptions.find(aoYAxisTitle) == oAdditionalOptions.end() ?
                        "N/A" : oAdditionalOptions[aoYAxisTitle].toString();
    m_pPrivate->tickPixel = options.testFlag(micDenseXAxis) ? 30 : 150;
    m_pPrivate->additionalOptions = oAdditionalOptions;
    m_pPrivate->load();
}

VTMultiInputChart::VTMultiInputChart(VTMultiInputChartOptions& options,
    QList<VTSingleInputSignal*> inputs,
    VTOptions& oAdditionalOptions,
    QWidget* parent)
    :VTHtmlBoard(parent)
{
     m_listSignals = inputs;
     for (int i = 0 ; i < m_listSignals.size(); ++i)
     {
         m_listSignals.at(i)->setChart(this);
     }
     m_pPrivate = new VTMultiInputChartPrivate(this);
     m_pPrivate->options = options;
     m_pPrivate->signalCount = m_listSignals.size();
     m_pPrivate->title = oAdditionalOptions.find(aoTitle) == oAdditionalOptions.end() ?
         "N/A" : oAdditionalOptions[aoTitle].toString();
     m_pPrivate->yTitle = oAdditionalOptions.find(aoYAxisTitle) == oAdditionalOptions.end() ?
         "N/A" : oAdditionalOptions[aoYAxisTitle].toString();
     m_pPrivate->tickPixel = options.testFlag(micDenseXAxis) ? 30 : 150;
     m_pPrivate->additionalOptions = oAdditionalOptions;
     m_pPrivate->load();
}

VTMultiInputChart::~VTMultiInputChart()
{
    for (int i = 0 ; i < m_listSignals.size(); ++i)
    {
        m_listSignals[i]->beforeChartDestroy();
    }
    m_listSignals.clear();
    delete m_pPrivate;
}

void VTMultiInputChart::clearAllSignals()
{
    m_pPrivate->evaluateJavaScript(c_cmdClearAll);
}

void VTMultiInputChart::clearSignal(VTSingleInputSignal* pSignal)
{
    if (pSignal)
    {
        int index = 0;
        for (index ; index < m_listSignals.size(); ++index)
        {
            if (m_listSignals[index] == pSignal)
            {
                break;
            }
        }
        m_pPrivate->evaluateJavaScript(c_cmdClearSignal.arg(index));
    }
}

void VTMultiInputChart::notifyDelete(VTSingleInputSignal* pSignal)
{
    if (pSignal)
    {
        for (int i = 0 ; i < m_listSignals.size(); ++i)
        {
            if (m_listSignals[i] == pSignal)
            {
                m_listSignals.removeAt(i);
                break;
            }
        }
    }
}

void VTMultiInputChart::notifyUpdate(VTSingleInputSignal* pSignal, double val)
{
    if (pSignal)
    {
        int index = 0;
        for (index ; index < m_listSignals.size(); ++index)
        {
            if (m_listSignals[index] == pSignal)
            {
                break;
            }
        }
        QString strUpdateValue = c_cmdUpdateValue;
        m_pPrivate->evaluateJavaScript(strUpdateValue.arg(index).arg(val));
    }
}

void VTMultiInputChart::removeSignal(int index)
{
    if (index >= 0 && index < m_listSignals.size())
    {
        m_listSignals.removeAt(index);
    }
}

void VTMultiInputChart::loadFinished()
{
    m_pPrivate->initialize();
    notify(micntPrepared);
}

void VTMultiInputChart::notify(VTMultiInputChartNotifyType notifyType)
{
    for (int i = 0 ; i < m_listSignals.size(); ++i)
    {
        m_listSignals[i]->onNotify(notifyType);
    }
}
