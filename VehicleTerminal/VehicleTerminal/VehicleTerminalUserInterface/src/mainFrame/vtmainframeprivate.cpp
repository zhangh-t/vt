#include "vtmainframeprivate.h"
#include "vtmainframe.h"
#include "vtmainframeconstruct.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

VTMainFramePrivate::VTMainFramePrivate(VTMainFrame *pMainFrame)
    : m_pMainFrame(pMainFrame), m_pCentralWidget(nullptr)
{
    if (m_pMainFrame);
    {
        initFrameLayout();
    }
}

VTMainFramePrivate::~VTMainFramePrivate()
{

}

void VTMainFramePrivate::extend(VTMainFrameExtension* pExtension)
{
    pExtension->buildMenuBar(this);
}

QWidget* VTMainFramePrivate::centralWidget()
{
    return m_pCentralWidget;
}

void VTMainFramePrivate::initFrameLayout()
{
    m_pMenuBar = new QMenuBar(m_pMainFrame);
    m_pMenuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout *pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(m_pMenuBar);
    m_pCentralWidget = new QWidget(m_pMainFrame);
    m_pCentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pMainLayout->addWidget(m_pCentralWidget);
    m_pMainFrame->setLayout(pMainLayout);
}

void VTMainFramePrivate::replaceCentralWidget(QWidget* pCentralWidget)
{
    QVBoxLayout* pMainFrameLayout = dynamic_cast<QVBoxLayout*>(m_pMainFrame->layout());
    if (pMainFrameLayout && pCentralWidget)
    {
        pMainFrameLayout->removeWidget(m_pCentralWidget);
        pCentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pMainFrameLayout->addWidget(pCentralWidget);
    }
}
