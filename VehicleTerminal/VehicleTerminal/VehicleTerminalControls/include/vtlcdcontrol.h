#ifndef VTLCDCONTROL_H
#define VTLCDCONTROL_H

#include <QWidget>
#include <QLCDNumber>
#include <QFlags>


class QLCDControlPrivate;

enum VTLCDOption
{
    vloBinMode,    //二进制
    vloOctMode,    //八进制
    vloHexMode,    //十六进制
    vloDecMode,    //十进制
};

class VTLCDControl : public QWidget
{
    Q_OBJECT
public:
    VTLCDControl(const VTLCDOption& oOption, QWidget *parent);
    ~VTLCDControl();
public:
    void display(const int nNum);
    void display(const double dNum);
    void display(const QString& strNum);
private:
    QLCDNumber* m_lcdNum;
};

#endif // VTLCDCONTROL_H
