#include "Huffman-T7-GUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Enc_Dec w;
    w.show();
    return a.exec();
}
