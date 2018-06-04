#include "vtdashboard.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "VTPrivate.h"
#include "vtexception.h"
#include "vtcontrolconsts.h"
#include <QStringList>
#include <QCoreApplication>
#include <QDir>
#include <QJsonArray>
#include <QWebFrame>
#include <QVector>
#include "VTInterval.h"
using namespace vt;
static const QString c_strDashBoard = "dashboard.html";
static const QString c_strInitDashBoard = "call_from_qt_init_chart('%1')";
static const QString c_strUpdateValue = "call_from_qt_upate_data(%1)";

class VTDashBoardPrivate : public VTPrivate
{
public:
    VTOptions options;
    VTDashBoard* dashBoard;
    VTDashBoardPrivate(VTOptions& _options, VTDashBoard* _dashBoard): options(_options), dashBoard(_dashBoard) {}
public:
    void loadHtml();
    void onLoadFinished();
    void initDashBoard();
    void evaluateJavaScript(QString& strJavaScriptCode);
public:
    virtual bool checkValidity(VTOptions& options);
    void update(double value);
private:
    bool checkRange(VTOptions& options, QStringList& errors);
    bool checkAngle(VTOptions& options, QStringList& errors);
    bool checkTick(VTOptions& options, QStringList& errors);
    bool checkPlotBands(VTOptions& options, QStringList& errors);
private:
    void initGeneralOptions(QJsonObject& jsonObj);
    void initTitle(QJsonObject& jsonObj);
    void initPane(QJsonObject& jsonObj);
    void initYAxis(QJsonObject& jsonObj);
    void initSeries(QJsonObject& jsonObj);
private:
    double m_dRangeMin;
    double m_dRangeMax;
};

void VTDashBoardPrivate::loadHtml()
{
    QString strPath = QCoreApplication::applicationDirPath() + 
        QDir::separator() + "htmls" + QDir::separator();
    strPath += c_strDashBoard;
    dashBoard->loadHtml(strPath);
}

void VTDashBoardPrivate::onLoadFinished()
{
    this->initDashBoard();
}

void VTDashBoardPrivate::initDashBoard()
{
    //生成option
    QJsonObject optionJson;
    //1. 通用选项
    initGeneralOptions(optionJson);
    //2. 标题
    initTitle(optionJson);
    //3. 背景
    initPane(optionJson);
    //4. Y轴
    initYAxis(optionJson);
    //4. series
    initSeries(optionJson);
    QJsonDocument doc(optionJson);
    QString strOption = doc.toJson(QJsonDocument::Compact);
    strOption.replace("\\\"", "");
    strOption.replace("\"", "\\\"");
    QString strJavaScriptCode = c_strInitDashBoard.arg(strOption);
    evaluateJavaScript(strJavaScriptCode);
}

void VTDashBoardPrivate::evaluateJavaScript(QString& strJavaScriptCode)
{
    QWebView* pWebView = dashBoard->webView();
    if (pWebView)
    {
        pWebView->page()
            ->mainFrame()->evaluateJavaScript(strJavaScriptCode);
    }
}

void VTDashBoardPrivate::initGeneralOptions(QJsonObject& jsonObj)
{
    QJsonObject chartJson;
    chartJson.insert(QString(jfnType), QString("gauge"));
    chartJson.insert(QString(jfnPlotBackgroundColor), QJsonValue::Null);
    chartJson.insert(QString(jfnPlotBackgroundImage), QJsonValue::Null);
    chartJson.insert(QString(jfnPlotBorderWidth), 0);
    chartJson.insert(QString(jfnPlotShadow), false);
    int nWidth = vt::getOption(options, (int)dboWidth, 500).toInt();
    int nHeight = vt::getOption(options, (int)dboHeight, 500).toInt();
    chartJson.insert(QString(jfnWidth), nWidth);
    chartJson.insert(QString(jfnHeight), nHeight);
    jsonObj.insert(QString("chart"), chartJson);
}

void VTDashBoardPrivate::initTitle(QJsonObject& jsonObj)
{
    QJsonObject titleJson;
    QString strTitle = vt::getOption(options, (int)dboTitle, QString("N/A")).toString();
    titleJson.insert(QString(jfnText), strTitle);
    jsonObj.insert(QString(jfnTitle), titleJson);
}

void VTDashBoardPrivate::initPane(QJsonObject& jsonObj)
{
    QJsonObject paneJson;
    double dStartAngle = options[(int)dboStartAngle].toDouble();     //这个值在校验的时候一定有
    double dEndAngle = options[(int)dboEndAngle].toDouble();     //这个值在校验的时候一定有
    paneJson.insert(QString(jfnStartAngle), dStartAngle);
    paneJson.insert(QString(jfnEndAngle), dEndAngle);
    QJsonObject backgroundJson;
    backgroundJson.insert(QString(jfnBackgroundColor), QString("#EEE"));
    backgroundJson.insert(QString(jfnBorderWidth), 1);
    backgroundJson.insert(QString(jfnOuterRadius), QString("105%"));
    backgroundJson.insert(QString(jfninnerRadius), QString("0%"));
    paneJson.insert(QString(jfnBackground), backgroundJson);
    jsonObj.insert(QString(jfnPane), paneJson);
}

void VTDashBoardPrivate::initYAxis(QJsonObject& jsonObj)
{
    double dRangeMin = options[(int)dboRangeMin].toDouble();     //这个值在校验的时候一定有
    double dRangeMax = options[(int)dboRangeMax].toDouble();     //这个值在校验的时候一定有
    int nMinorTickInterval = -2;
    VTOptionsIter iter = options.find((int)dboMinorTickInterval);
    if (iter != options.end())
    {
        nMinorTickInterval = iter.value().toInt();
    }
    int nMinorTickWidth = 1;
    int nMinorTickLength = 10;
    QString strTickPosition = "inside";
    QString strTickColor = "#666";
    int nMajorTickInterval = options[(int)dboMajorTickInterval].toInt();    //这个值在校验的时候一定有
    int nMajorTickStep = options[(int)dboMajorTickLabelStep].toInt();    //这个值在校验的时候一定有
    int nMajorTickWidth = 2;
    int nMajorTickLength = 10;
    QString strSuffix = vt::getOption(options, (int)dboValueSuffix, QString("N/A")).toString();
    QJsonArray plotBands = options[(int)dboPlotsBands].toJsonArray();    //这个值在校验的时候一定有
    QJsonObject yAxisJson;
    yAxisJson.insert(QString(jfnMin), dRangeMin);
    yAxisJson.insert(QString(jfnMax), dRangeMax);
    QVariant oMinorTickIntervalVariant;
    if (-2 == nMinorTickInterval)
    {
        oMinorTickIntervalVariant = QJsonValue(QJsonValue::Null);
    }
    else if (-1 == nMinorTickInterval)
    {
        oMinorTickIntervalVariant = QString("auto");
    }
    else {
        oMinorTickIntervalVariant = nMinorTickInterval;
    }
    yAxisJson.insert(QString(jfnMinorTickInterval), QJsonValue::fromVariant(oMinorTickIntervalVariant));
    yAxisJson.insert(QString(jfnMinorTickWidth), nMinorTickWidth);
    yAxisJson.insert(QString(jfnMinorTickLength), nMinorTickLength);
    yAxisJson.insert(QString(jfnMinorTickPosition), strTickPosition);
    yAxisJson.insert(QString(jfnMinorTickColor), strTickColor);
    yAxisJson.insert(QString(jfnTickPixelInterval), nMajorTickInterval);
    yAxisJson.insert(QString(jfnTickWidth), nMajorTickWidth);
    yAxisJson.insert(QString(jfnTickPosition), strTickPosition);
    yAxisJson.insert(QString(jfnTickLength), nMajorTickLength);
    yAxisJson.insert(QString(jfnTickColor), strTickColor);
    QJsonObject labelsJson;
    labelsJson.insert(QString(jfnStep), nMajorTickStep);
    labelsJson.insert(QString(jfnRotation), QString("auto"));
    yAxisJson.insert(QString(jfnLabels), labelsJson);
    QJsonObject titleJson;
    titleJson.insert(QString(jfnText), strSuffix);
    yAxisJson.insert(QString(jfnTitle), titleJson);
    yAxisJson.insert(QString(jfnPlotBands), plotBands);
    jsonObj.insert(QString(jfnYAxis), yAxisJson);
}

void VTDashBoardPrivate::initSeries(QJsonObject& jsonObj)
{
    QString strName = vt::getOption(options, (int)dboValueHint, QString("N/A")).toString();
    QString strSuffix = vt::getOption(options, (int)dboValueSuffix, QString("N/A")).toString();
    QJsonObject seriesJson;
    seriesJson.insert(QString(jfnName), strName);
    QJsonArray dataDummy;
    dataDummy.append(0);
    seriesJson.insert(QString(jfnData), dataDummy);
    QJsonObject toolTipJson;
    toolTipJson.insert(QString(jfnValueSuffix),strSuffix);
    seriesJson.insert(QString(jfnToolTip), toolTipJson);
    QJsonArray seriesArray;
    seriesArray.append(seriesJson);
    jsonObj.insert(QString(jfnSeries), seriesArray);
}

bool VTDashBoardPrivate::checkValidity(VTOptions& options)
{
    QStringList errors;
    bool bRes = checkRange(options, errors)
        && checkAngle(options, errors)
        && checkTick(options, errors)
        && checkPlotBands(options, errors);
    if (!bRes)
    {
        QString strErrors;
        int nErrCount = errors.length();
        for (int i = 0 ; i < nErrCount; ++i)
        {
            strErrors += errors[i];
            strErrors += "\r";
#ifdef WINDOWS
            strErrors += "\n";
#endif
        }
        raiseException(strErrors);
    }
    return bRes;
}

bool VTDashBoardPrivate::checkRange(VTOptions& options, QStringList& errors)
{
    bool bRes = true;
    VTOptionsIter iter = options.find(dboRangeMin);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack range lower boundary"));
    }
    else {
        m_dRangeMin = iter->toDouble();
    }
    iter = options.find(dboRangeMax);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack range upper boundary"));
    }
    else {
        m_dRangeMax = iter->toDouble();
    }
    if (m_dRangeMin > m_dRangeMax)
    {
        bRes = false;
        errors.append(QString("error: invalid range"));
    }
    return bRes;
}

bool VTDashBoardPrivate::checkAngle(VTOptions& options, QStringList& errors)
{
    bool bRes = true;
    double dStartAngle, dEndAngle;
    VTOptionsIter iter = options.find(dboStartAngle);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack start angle"));
    }
    else {
        dStartAngle = iter->toDouble();
    }

    iter = options.find(dboEndAngle);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack end angle"));
    }
    else {
        dEndAngle = iter->toDouble();
    }
    if (dStartAngle > dEndAngle)
    {
        bRes = false;
        errors.append(QString("error: invalid angle range"));
    }
    return bRes;
}

bool VTDashBoardPrivate::checkTick(VTOptions& options, QStringList& errors)
{
    bool bRes = true;
    double dMajorTickInterval, dMinorTickInterval;
    VTOptionsIter iter = options.find(dboMajorTickInterval);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack major tick interval"));
    }
    else {
        dMajorTickInterval = iter->toDouble();
    }

    iter = options.find(dboMinorTickInterval);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack minor tick interval"));
    }
    else {
        dMinorTickInterval = iter->toDouble();
    }
    if (dMinorTickInterval > dMajorTickInterval)
    {
        bRes = false;
        errors.append(QString("error: minor tick interval should not larger than major"));
    }
    return bRes;
}

bool VTDashBoardPrivate::checkPlotBands(VTOptions& options, QStringList& errors)
{
    bool bRes = true;
    VTOptionsIter iter = options.find(dboPlotsBands);
    if (iter == options.end())
    {
        bRes = false;
        errors.append(QString("error: lack plots bands"));
    }
    else {
        QJsonArray jsonArray = iter->toJsonArray();
        int nSize = jsonArray.count();
        QString strErrTemplate = "error:%1 invalid, index %2";
        QVector<VTIntervald> exsitedAngleRanges;
        for (int i = 0 ; i < nSize; ++i)
        {
            QJsonObject jsonObj = jsonArray.at(i).toObject();
            double dAngleRangeMin, dAngleRangeMax;
            QString strFieldName = QString(jfnFrom);
            QJsonObject::ConstIterator iter = jsonObj.find(strFieldName);
            if (iter != jsonObj.end())
            {
                dAngleRangeMin = iter.value().toDouble();
            }
            else {
                bRes = false;
                errors.append(strErrTemplate.arg(strFieldName).arg(i));
            }

            strFieldName = QString(jfnTo);
            iter = jsonObj.find(strFieldName);
            if (iter != jsonObj.end())
            {
                dAngleRangeMax = iter.value().toDouble();
            }
            else {
                bRes = false;
                errors.append(strErrTemplate.arg(strFieldName).arg(i));
            }

            VTIntervald range(dAngleRangeMin, dAngleRangeMax);
            if (!range.valid())
            {
                bRes = false;
                errors.append(strErrTemplate.arg("plot band range").arg(i));
            }
            else {
                for (int i = 0 ; i < exsitedAngleRanges.size(); ++i)
                {
                    if (range.intersected(exsitedAngleRanges.at(i)), 1) {
                        bRes = false;
                        errors.append(strErrTemplate.arg("[plot band range intersected]").arg(i));
                    }
                    else {
                        exsitedAngleRanges.push_back(range);
                    }
                }
            }
        }
    }
    return bRes;
}

void VTDashBoardPrivate::update(double value)
{
    if (value > m_dRangeMin && value < m_dRangeMax)
    {
        QString strCmdLine = c_strUpdateValue.arg(value);
        this->evaluateJavaScript(strCmdLine);
    }
}


VTDashBoard::VTDashBoard(VTOptions& dashboardOptions,
    QWidget *parent)
    : VTHtmlBoard(parent)
{
    m_pPrivate = new VTDashBoardPrivate(dashboardOptions, this);
    m_pPrivate->checkValidity(dashboardOptions);
    m_pPrivate->loadHtml();
}

VTDashBoard::~VTDashBoard()
{
    delete m_pPrivate;
}

void VTDashBoard::loadFinished()
{
    m_pPrivate->onLoadFinished();
}

void VTDashBoard::updateValue(double value)
{
    m_pPrivate->update(value);
}

QJsonObject VTDashBoard::genPlotBand(int nRangeFrom, int nRangeTo, QColor& color)
{
    QJsonObject res;
    if (nRangeFrom > nRangeTo)
    {
        VT_RAISEEXCEPTION("range from lager than range to, invalid range!");
    }
    else {
        res.insert(QString(jfnFrom), nRangeFrom);
        res.insert(QString(jfnTo), nRangeTo);
        res.insert(QString(jfnColor), colorToString(color));
    }
    return res;
}
