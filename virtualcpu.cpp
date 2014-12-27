//TODO: File input method for executing binary files
//TODO: MIPS Instructions maken


#include <vector>
#include <stdint.h>
#include <QObject>
#include <string>
#include "virtualcpu.h"
#include "ui_virtualcpu.h"
#include "mipsproc.h"
#include "memory.h"
#include "mipsopcodes.h"

using namespace vCPU;
using std::vector;

VirtualCPU::VirtualCPU(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VirtualCPU)
{
    ui->setupUi(this);

    myRAM = new RAM();

    v_cpu = new MIPSproc(myRAM);

    //Connect signals & slots

    //Load test program into memory
		// TEST PROGRAM
}

VirtualCPU::~VirtualCPU()
{
    delete ui;
}

void VirtualCPU::runProgram()
{
    fprintf(stdout, "RUNNING...");
    v_cpu->run();
}

// SLOTS
void VirtualCPU::on_runButton_clicked()
{
    runProgram();
}

void VirtualCPU::receive_cpuOutput(int output)
{
    emit newOutput(output);
}

void VirtualCPU::receive_cpuCmd(std::string cmd)
{
    emit newCmd(QString::QString(cmd));
}
