#ifndef VTMAINFRAMEMENUEXTENSION_H
#define VTMAINFRAMEMENUEXTENSION_H
#include "mainFrame/vtmainframeconstruct.h"

class VEHICLETERMINALUSERINTERFACE_EXPORT VTMainFrameMenuExtension : public VTMainFrameExtension
{
public:
    VTMainFrameMenuExtension();
    ~VTMainFrameMenuExtension();
public:
    void buildMenuBar(VTMainFrameMenuBarBuilder* pBuilder);
private:
    QMenu* createSystemManagementMenu();
    QMenu* createDetectModeMenu();
    QMenu* createHelperMenu();
};

#endif // VTMAINFRAMEMENUEXTENSION_H
