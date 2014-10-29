//TODO: File input method for executing binary files
//TODO: MIPS Instructions maken


#include <vector>
#include <stdint.h>
#include <QObject>
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
    //Initialize Proc & RAM

    //Connect signals & slots

    //Load test program into memory
}
VirtualCPU::~VirtualCPU()
{
    delete ui;
}

void VirtualCPU::runProgram()
{
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

void VirtualCPU::receive_cpuCmd(int instr)
{
    // EMIT Instruction
}
