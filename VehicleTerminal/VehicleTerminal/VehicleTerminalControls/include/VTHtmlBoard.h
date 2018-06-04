#pragma once
#include <QWebView>
#include <QWidget>
#include "vehicleterminalcontrols_global.h"

class VTHtmlBoardReadyNotifier;
class VEHICLETERMINALCONTROLS_EXPORT VTHtmlBoard : public QWidget
{
    friend class VTHtmlBoardReadyNotifier;
    Q_OBJECT
public:
    VTHtmlBoard(QWidget* parent = nullptr);
    virtual ~VTHtmlBoard(void);
public:
    inline void loadHtml(QString& path);
private slots:
    void onLoaded(bool);
    void onJavascriptObjectsCleared();
protected:
    virtual void loadFinished(){}
    virtual void actualSizeChanged(int nWidth, int nHeight);
protected:
    inline QWebView* webView();
private:
    QWebView* m_pCoreWebView;
    VTHtmlBoardReadyNotifier* m_pNotifier;
};

class VTHtmlBoardReadyNotifier : public QObject
{
    Q_OBJECT
public:
    VTHtmlBoardReadyNotifier(VTHtmlBoard* pReciver);
    virtual ~VTHtmlBoardReadyNotifier() {}
public slots:
    virtual void ready();
    virtual void actualSizeChanged(int nWidth, int nHeight);
private:
    VTHtmlBoard* m_pReciver;
};
