#include <QApplication>
#include "virtualcpu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VirtualCPU w;
    w.show();
    
    return a.exec();
}
