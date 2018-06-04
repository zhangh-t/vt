#include <QtWidgets/QApplication>
#include "vtmultiinputchart.h"
#include "vtsingleinputsignal.h"
#include "vtdashboard.h"
#include "mainFrame/vtmainframe.h"
#include "frameExtension/vtmainframemenuextension.h"
#include <QMainWindow>
#include <QTime>
#include <QStringList>
#include <QVBoxLayout>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

void registMainFrameExtension(VTMainFrame* pMainFrame) {
    //注册拓展
    VTMainFrameMenuExtension* pMenuExtension = new VTMainFrameMenuExtension();
    pMenuExtension->setCentralWidgetUpdater(pMainFrame->updater());
    pMainFrame->registFrameExtension(pMenuExtension);
}

void initMainFrame(VTMainFrame* pMainFrame) {
    if (pMainFrame)
    {
        registMainFrameExtension(pMainFrame);
        pMainFrame->setWindowTitle(QStringLiteral("长安大学底盘测功机测控软件"));
    }
}

void finalizeMainFrame(VTMainFrame* pMainFrame)
{
    if (pMainFrame)
    {
        pMainFrame->finalize();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VTOptions options;
    VTMultiInputChartOptions option = defaultOption;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    VTSimpleSingleInputSignal signal1(15, QString("signal1"), QColor(255, 0, 0), []()->double{
        return qrand() % 20;
    });
    VTSimpleSingleInputSignal signal2(10, QString("signal2"), QColor(0, 255, 0), []()->double{
        return qrand() % 50;
    });

    options[aoTitle] =  QStringLiteral("测试");
    options[aoYAxisTitle] = QStringLiteral("值");
    options[aoEnableXAxisLabels] = false;
    VTMultiInputChart* pChart = new VTMultiInputChart(0, 
        option, 
        options,
        2, 
        &signal1,
        &signal2);
    option = micStatic;
    options[aoSubTitle] = QStringLiteral("一个测试");
    options[aoValueSuffix] = QStringLiteral("℃");
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    options[aoXAxisCategories] = categories;
    QList<double> values1, values2;
    values1 << 7.0 << 6.9 << 9.5 << 14.5 << 18.2 << 21.5 << 25.2 << 26.5 << 23.3 << 18.3 << 13.9 << 9.6;
    values2 << 3.0 << 1.9 << 0.5 << 25.5 << 37.2 << 45.5 << 95.2 << 126.5 << 1.3 << 0.3 << 113.9 << 19.6;

    VTSimpleStaticInputSignal signal3(QString("signal3"), QColor(123, 11, 0), values1);
    VTSimpleStaticInputSignal signal4(QString("signal4"), QColor(223, 143, 0), values2);
    VTMultiInputChart* pStaticChart = new VTMultiInputChart(0,
        option,
        options,
        2,
        &signal3,
        &signal4);

    options.clear();
    options[dboWidth] = 300;
    options[dboHeight] = 300;
    options[dboTitle] = QStringLiteral("dashboard测试");
    options[dboStartAngle] = -150;
    options[dboEndAngle] = 150;
    options[dboRangeMin] = 0;
    options[dboRangeMax] = 150;
    options[dboMinorTickInterval] = -1;
    options[dboMajorTickInterval] = 30;
    options[dboMajorTickLabelStep] = 2;
    options[dboUnit] = QStringLiteral("Km/h");
    QJsonArray plotBands;
    plotBands.append(VTDashBoard::genPlotBand(0, 80, QColor(0, 255, 0)));
    plotBands.append(VTDashBoard::genPlotBand(80, 120, QColor(232,80, 0)));
    plotBands.append(VTDashBoard::genPlotBand(120, 150, QColor(244, 0, 0)));
    options[dboPlotsBands] = plotBands;
    options[dboValueHint] = QStringLiteral("速度");
    options[dboValueSuffix] = QStringLiteral("Km/h");
    VTDashBoard* pDashBoard = new VTDashBoard(options);
    QMainWindow mainWindow;
    QWidget* pCentralWidget = new QWidget(&mainWindow);
    QVBoxLayout* pLayout = new QVBoxLayout;
    pLayout->addWidget(pDashBoard);
    pCentralWidget->setLayout(pLayout);
    mainWindow.setCentralWidget(pCentralWidget);
    mainWindow.show();
    //VTMainFrame oMainFrame;
    //initMainFrame(&oMainFrame);
    //oMainFrame.show();
    int nRes = a.exec();
    //finalizeMainFrame(&oMainFrame);
    return nRes;
}
