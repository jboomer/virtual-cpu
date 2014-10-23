//TODO: File input method for executing binary files


#include <vector>
#include <stdint.h>
#include <QObject>
#include "virtualcpu.h"
#include "ui_virtualcpu.h"
#include "cpu.h"
#include "memory.h"
#include "opcodes.h"

using namespace vCPU;
using std::vector;

VirtualCPU::VirtualCPU(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VirtualCPU)
{
    ui->setupUi(this);
    myRAM = new RAM();
    v_cpu = new CPU(myRAM);

    QObject::connect(v_cpu, SIGNAL(output(int)),this, SLOT(on_cpuOutput(int)));
    QObject::connect(this, SIGNAL(newOutput(int)), ui->lcdNumber, SLOT(display(int)));
    QObject::connect(v_cpu, SIGNAL(process_cmd(int)), this, SLOT(on_cpuCmd(int)));
    QObject::connect(this, SIGNAL(newCmd(QString)), ui->textBrowser, SLOT(append(QString)));

    /* Test program */
    uint8_t addr_target = 0xd2;
    uint8_t a = 12;
    uint8_t b = 17;

    uint8_t prog_arr[10] = {PUTA,
                           a,
                           PUTB,
                           b,
                           ADD,
                           STORE,
                           addr_target,
                           PRINT,
                           addr_target,
                           HALT};
    for (uint8_t i = 0; i < sizeof(prog_arr); i++){
        myRAM->write(i, prog_arr[i]);
    }
}
VirtualCPU::~VirtualCPU()
{
    delete ui;
}

void VirtualCPU::runProgram()
{
    v_cpu->run();
}

void VirtualCPU::on_runButton_clicked()
{
    runProgram();
}

void VirtualCPU::on_cpuOutput(int output)
{
    emit newOutput(output);
}

void VirtualCPU::on_cpuCmd(int opcode)
{
    switch(opcode & 0xff){
        case(HALT) : {
            emit newCmd("HALT");
            break;
        }
        case(ADD) : {
            emit newCmd("ADD");
            break;
        }
        case(STORE) : {
            emit newCmd("STORE");
            break;
        }
        case(PRINT) : {
            emit newCmd("PRINT");
            break;
        }
        case(LOADA) : {
            emit newCmd("LOAD_A");
            break;
        }
        case(LOADB) : {
            emit newCmd("LOAD_B");
            break;
        }
        case(PUTA) : {
            emit newCmd("PUT_A");
            break;
        }
        case(PUTB) : {
            emit newCmd("PUT_B");
            break;
        }
        default : {
            break;
        }
    }
}
