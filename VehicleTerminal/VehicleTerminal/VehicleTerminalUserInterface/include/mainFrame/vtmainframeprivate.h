#ifndef VTMAINFRAMEPRIVATE_H
#define VTMAINFRAMEPRIVATE_H
/*
*@file:    MainFrame˽�༰������
*@brief:
*@author   zhangh-t
*@date:    2017��7��11��
*@remarks
*@version 1.0
*/
#include <QObject>
#include <QList>
#include <QString>
#include "vtmainframeconstruct.h"
#include "vehicleterminaluserinterface_global.h"

class QWidget;
class VTMainFrame;
class VTMainFrameMenuBarBuilder;
class VTCentralWidgetUpdater;
/*
*@file:
*@brief:   ˽��
*@author   zhangh-t
*@date:    2017��7��11��
*@remarks
*@version 1.0
*/
class VTMainFramePrivate : public QObject, public VTCentralWidgetUpdater, public VTMainFrameMenuBarBuilder
{
    Q_OBJECT
public:
    VTMainFramePrivate(VTMainFrame *pMainFrame);
    ~VTMainFramePrivate();
public:
    void extend(VTMainFrameExtension* pExtension);
public:
    virtual QWidget* centralWidget();
    virtual void replaceCentralWidget(QWidget* pCentralWidget);
private:
    void initFrameLayout();
private:
    VTMainFrame* m_pMainFrame;
    QWidget* m_pCentralWidget;
    friend class VTMainFrame;
};

#endif // VTMAINFRAMEPRIVATE_H
