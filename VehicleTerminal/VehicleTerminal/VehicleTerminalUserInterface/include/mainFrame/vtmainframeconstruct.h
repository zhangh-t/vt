#ifndef VTMAINFRAMECONSTRUCT_H
#define VTMAINFRAMECONSTRUCT_H
#include <QObject>
#include <QWidget>
#include <QString>
#include <QIcon>
#include <QAction>
#include <QVector>
#include "vehicleterminaluserinterface_global.h"
#ifdef WINDOWS
#include <functional>
#endif

class VTMenuActionResponder;
class VTMainFrame;
class VTCentralWidgetUpdater;
class QMenuBar;
class QMenu;
class QKeySequence;
class VTMainFrameMenuBarBuilder;

/*
*@file:
*@brief:   界面拓展
*@author   zhangh-t
*@date:    2017年7月11日
*@remarks
*@version 1.0
*/
class VEHICLETERMINALUSERINTERFACE_EXPORT VTMainFrameExtension : public QObject
{
    Q_OBJECT
public:
    VTMainFrameExtension();
    virtual ~VTMainFrameExtension();
public:
    virtual void buildMenuBar(VTMainFrameMenuBarBuilder* pBuilder);
public:
    virtual void setCentralWidgetUpdater(VTCentralWidgetUpdater* pUpdater);
protected:
    VTCentralWidgetUpdater* m_pUpdater;
};
/*
*@file:
*@brief:   主UI更新
*@author   zhangh-t
*@date:    2017年7月11日
*@remarks
*@version 1.0
*/
class VEHICLETERMINALUSERINTERFACE_EXPORT VTCentralWidgetUpdater
{
public:
    virtual void replaceCentralWidget(QWidget* pCentralWidget) = 0;
    virtual QWidget* centralWidget() = 0;
};
/*
*@file:
*@brief:   菜单建造者
*@author   zhangh-t
*@date:    2017年7月11日
*@remarks
*@version 1.0
*/
class VEHICLETERMINALUSERINTERFACE_EXPORT VTMainFrameMenuBarBuilder
{
public:
    VTMainFrameMenuBarBuilder();
    virtual ~VTMainFrameMenuBarBuilder();
public:
    void addMenu(QMenu* pMenu);
    void addSeparator();
protected:
    QMenuBar* m_pMenuBar;
    QVector<QMenu*> m_menus;
};

typedef std::function<void ()> VTActionCallBackFunc;

class VEHICLETERMINALUSERINTERFACE_EXPORT VTActionTriggerCallBack
{
public:
    void operator () ();
    virtual void onActionTriggered();
    VTActionTriggerCallBack(VTActionCallBackFunc func) : m_func(func){}
    VTActionCallBackFunc m_func;
    VTActionTriggerCallBack() {}
    VTActionTriggerCallBack(const VTActionTriggerCallBack& other) {m_func = other.m_func;}
};

struct VTMenuActionFacade
{
    QString m_strTitle;
    QString m_strToolTip;
    QIcon m_oIcon;
    QKeySequence m_oKeySequence;
    VTActionTriggerCallBack m_oCallBack;
    bool m_bCheckable;
    VTMenuActionFacade(const QString& title,
        const QString& toolTip,
        const QIcon& icon,
        QKeySequence& keySeq,
        VTActionTriggerCallBack oCallBack,
        bool bCheckable);
    VTMenuActionFacade(){}
};

class VEHICLETERMINALUSERINTERFACE_EXPORT VTMenuAction : public QAction
{
    Q_OBJECT
public:
    VTMenuAction(const VTMenuActionFacade& oFacade, 
        QObject* pParent = nullptr);
    ~VTMenuAction();
private slots:
    void onTriggered();
private:
    VTMenuActionFacade m_oFacade;
};
#endif // VTMAINFRAMECONSTRUCT_H
