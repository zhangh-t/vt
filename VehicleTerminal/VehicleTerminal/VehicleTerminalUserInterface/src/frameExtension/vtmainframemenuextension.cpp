#include "frameExtension/vtmainframemenuextension.h"
#include <QMenu>
static const QString s_SystemManagement = QStringLiteral("系统管理(&M)");
static const QString s_DetectMode = QStringLiteral("检测模式(&T)");
static const QString s_Helper = QStringLiteral("帮助(&H)");



VTMainFrameMenuExtension::VTMainFrameMenuExtension()
{

}

VTMainFrameMenuExtension::~VTMainFrameMenuExtension()
{

}

void VTMainFrameMenuExtension::buildMenuBar(VTMainFrameMenuBarBuilder* pBuilder)
{
    //增加菜单
    pBuilder->addMenu(createSystemManagementMenu());
    pBuilder->addMenu(createDetectModeMenu());
    pBuilder->addMenu(createHelperMenu());
}

QMenu* VTMainFrameMenuExtension::createSystemManagementMenu()
{
    QMenu* pSystemManagemet = new QMenu(s_SystemManagement);
    VTMenuActionFacade oLCDFacade(QString("VTLCDDemoWidget"), 
        QString("VTLCDDemoWidget"),
        QIcon(),
        QKeySequence("ALT+L"),
        VTActionTriggerCallBack([] {

        }),
        false);

    VTMenuActionFacade oDetectWidget(QString("VTDetectDemoWidget"), 
        QString("VTDetectWidget"),
        QIcon(),
        QKeySequence("ALT+D"),
        VTActionTriggerCallBack([] {
                 }),
        false);

    VTMenuActionFacade oChartWidget(QString("VTChartDemoWidget"), 
        QString("VTDetectWidget"),
        QIcon(),
        QKeySequence("ALT+C"),
        VTActionTriggerCallBack([] {
              }),
        false);

    QAction* pLCDTest = new VTMenuAction(oLCDFacade, pSystemManagemet);
    QAction* pDetecTest = new VTMenuAction(oDetectWidget, pSystemManagemet);
    QAction* pChartTest = new VTMenuAction(oChartWidget, pSystemManagemet);
    pSystemManagemet->addAction(pLCDTest);
    pSystemManagemet->addAction(pDetecTest);
    pSystemManagemet->addAction(pChartTest);

    return pSystemManagemet;
}

QMenu* VTMainFrameMenuExtension::createDetectModeMenu()
{
    QMenu* pDetectMode = new QMenu(s_DetectMode);
    return pDetectMode;
}

QMenu* VTMainFrameMenuExtension::createHelperMenu()
{
    QMenu* pHelper = new QMenu(s_Helper);
    return pHelper;
}

