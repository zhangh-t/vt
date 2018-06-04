#ifndef VTMAINFRAME_H
#define VTMAINFRAME_H

#include <QWidget>
#include <QList>
#include "vehicleterminaluserinterface_global.h"
class VTMainFrameExtension;
class VTMainFramePrivate;
class VTCentralWidgetUpdater;
class VEHICLETERMINALUSERINTERFACE_EXPORT VTMainFrame : public QWidget
{
    friend class VTMainFramePrivate;
    Q_OBJECT
public:
    VTMainFrame();
    ~VTMainFrame();
public:
    void registFrameExtension(VTMainFrameExtension* pExtension);
    void setQSS(const QString& path);
    VTCentralWidgetUpdater* updater();
public:
    void finalize();
private:
    QWidget* welcomWidget();
private:
    void freeExtensions();
private:
    VTMainFramePrivate* m_private;
    QList<VTMainFrameExtension*> m_oExtensions;
};

#endif // VTMAINFRAME_H
