#include "vtlcdcontrol.h"

VTLCDControl::VTLCDControl(const VTLCDOption& oOption, QWidget *parent)
    : QWidget(parent)
{
    m_lcdNum = new QLCDNumber(this);
    switch (oOption) {
    case vloBinMode:
        m_lcdNum->setBinMode();
        break;
    case vloDecMode:
        m_lcdNum->setDecMode();
        break;
    case vloHexMode:
        m_lcdNum->setHexMode();
        break;
    case vloOctMode:
        m_lcdNum->setOctMode();
        break;
    }
}

VTLCDControl::~VTLCDControl()
{
    delete m_lcdNum;
}

void VTLCDControl::display(const int nNum)
{
    m_lcdNum->display(nNum);
}

void VTLCDControl::display(const double dNum)
{
    m_lcdNum->display(dNum);
}

void VTLCDControl::display(const QString& strNum)
{
    m_lcdNum->display(strNum);
}
