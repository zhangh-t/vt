#include "vtmainframeconstruct.h"
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <stdio.h>
#include <QVector>
#include <QKeySequence>

VTMainFrameMenuBarBuilder::VTMainFrameMenuBarBuilder()
    :m_pMenuBar(nullptr)
{

}

VTMainFrameMenuBarBuilder::~VTMainFrameMenuBarBuilder()
{
    for (int i = 0 ; i < m_menus.size(); ++i)
    {
        delete m_menus[i];
    }
    m_menus.clear();
}

void VTMainFrameMenuBarBuilder::addSeparator()
{
    m_pMenuBar->addSeparator();
}

void VTMainFrameMenuBarBuilder::addMenu(QMenu* pMenu)
{
    if (pMenu != nullptr)
    {
        m_pMenuBar->addMenu(pMenu);
        m_menus.push_back(pMenu);
    }
}

VTMainFrameExtension::VTMainFrameExtension()
{
}

VTMainFrameExtension::~VTMainFrameExtension()
{

}

void VTMainFrameExtension::buildMenuBar(VTMainFrameMenuBarBuilder* pBuilder)
{

}

void VTMainFrameExtension::setCentralWidgetUpdater(VTCentralWidgetUpdater* pUpdater)
{
    m_pUpdater = pUpdater;
}

void VTMenuAction::onTriggered()
{
    m_oFacade.m_oCallBack();
}

VTMenuAction::VTMenuAction(const VTMenuActionFacade& oFacade, 
     QObject* pParent)
    :QAction(pParent)
{
    m_oFacade = oFacade;
    this->setText(oFacade.m_strTitle);
    if (!oFacade.m_oIcon.isNull())
    {
        this->setIcon(oFacade.m_oIcon);
    }
    if (oFacade.m_bCheckable)
    {
        this->setCheckable(true);
    }
    if (!oFacade.m_strToolTip.isEmpty())
    {
        this->setToolTip(oFacade.m_strToolTip);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    this->setShortcut(oFacade.m_oKeySequence);
}

VTMenuAction::~VTMenuAction()
{
}

void VTActionTriggerCallBack::operator()()
{
    this->onActionTriggered();
}

void VTActionTriggerCallBack::onActionTriggered()
{
#ifdef WINDOWS
    if (m_func)
    {
        m_func();
    }
#endif
}

VTMenuActionFacade::VTMenuActionFacade(const QString& title,
    const QString& toolTip,
    const QIcon& icon, 
    QKeySequence& keySeq,
    VTActionTriggerCallBack oCallBack,
    bool bCheckable)
    :m_strTitle(title), m_strToolTip(toolTip), m_oIcon(icon), m_oKeySequence(keySeq), m_oCallBack(oCallBack), m_bCheckable(bCheckable)
{

}
