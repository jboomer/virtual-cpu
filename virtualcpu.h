#ifndef VIRTUALCPU_H
#define VIRTUALCPU_H

#include <QString>
#include <QMainWindow>
#include <string>
#include "memory.h"
#include "mipsproc.h"

namespace Ui {
class VirtualCPU;
}

class VirtualCPU : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VirtualCPU(QWidget *parent = 0);
    ~VirtualCPU();
    
private:
    vCPU::MIPSproc *v_cpu;
    vCPU::RAM *myRAM;

    void runProgram();

signals:
    void newOutput(int output);
    void newCmd(QString cmd);

private slots:
    void on_runButton_clicked();
    void receive_cpuOutput(std::string cmd);
    void receive_cpuCmd(int opcode);
private:
    Ui::VirtualCPU *ui;
};

#endif // VIRTUALCPU_H
