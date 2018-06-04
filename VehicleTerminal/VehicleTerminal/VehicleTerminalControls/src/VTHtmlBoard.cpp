#include "VTHtmlBoard.h"
#include <QUrl>
#include <QHBoxLayout>
#include <QWebPage>
#include <QWebFrame>
VTHtmlBoard::VTHtmlBoard(QWidget* parent)
{
    m_pNotifier = new VTHtmlBoardReadyNotifier(this);
    QHBoxLayout* pLayout = new QHBoxLayout;
    m_pCoreWebView = new QWebView(parent);
    m_pCoreWebView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_pCoreWebView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(onJavascriptObjectsCleared()));
    pLayout->addWidget(m_pCoreWebView);
    this->setLayout(pLayout);
}


VTHtmlBoard::~VTHtmlBoard(void)
{
    if (!m_pCoreWebView->parent())
    {
        delete m_pCoreWebView;
        m_pCoreWebView = nullptr;
    }
    if (m_pNotifier)
    {
        delete m_pNotifier;
        m_pNotifier = nullptr;
    }
}

void VTHtmlBoard::loadHtml(QString& path)
{
    QUrl url = QUrl::fromUserInput(path);
    m_pCoreWebView->load(url);
}

QWebView* VTHtmlBoard::webView()
{
    return m_pCoreWebView;
}

void VTHtmlBoard::onLoaded(bool)
{
    loadFinished();
}

void VTHtmlBoard::onJavascriptObjectsCleared()
{
    m_pCoreWebView->page()->mainFrame()->addToJavaScriptWindowObject(QString("qtReadyNotifier"), m_pNotifier);
}

void VTHtmlBoard::actualSizeChanged(int nWidth, int nHeight)
{

}

VTHtmlBoardReadyNotifier::VTHtmlBoardReadyNotifier(VTHtmlBoard* pReciver)
    :m_pReciver(pReciver)
{

}

void VTHtmlBoardReadyNotifier::ready()
{
    if (m_pReciver)
    {
        m_pReciver->onLoaded(true);
    }
}

void VTHtmlBoardReadyNotifier::actualSizeChanged(int nWidth, int nHeight)
{
    if (m_pReciver)
    {
        m_pReciver->actualSizeChanged(nWidth, nHeight);
    }
}
