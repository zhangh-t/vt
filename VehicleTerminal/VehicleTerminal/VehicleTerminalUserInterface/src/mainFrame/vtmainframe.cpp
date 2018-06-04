#include "vtmainframe.h"
#include "vtmainframeprivate.h"
#include "vtmainframeconstruct.h"

VTMainFrame::VTMainFrame()
{
    m_private = new VTMainFramePrivate(this);
}

VTMainFrame::~VTMainFrame()
{
    delete m_private;
}

QWidget* VTMainFrame::welcomWidget()
{
    return m_private->m_pCentralWidget;
}

void VTMainFrame::registFrameExtension(VTMainFrameExtension* pExtension)
{
    m_private->extend(pExtension);
    m_oExtensions.push_back(pExtension);
}

void VTMainFrame::setQSS(const QString& path)
{

}

VTCentralWidgetUpdater* VTMainFrame::updater()
{
    return m_private;
}

void VTMainFrame::freeExtensions()
{
    for (auto iter = m_oExtensions.begin(); iter != m_oExtensions.end(); ++iter)
    {
        delete *iter;
    }
    m_oExtensions.swap(QList<VTMainFrameExtension*>());
}

void VTMainFrame::finalize()
{
    freeExtensions();
}
