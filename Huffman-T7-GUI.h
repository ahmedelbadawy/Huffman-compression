#ifndef ENC_DEC_H
#define ENC_DEC_H
#include "read-GUI.hpp"
#include "Decompression-GUI.h"
#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include <QFile>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Enc_Dec; }
QT_END_NAMESPACE

class Enc_Dec : public QMainWindow
{
    Q_OBJECT

public:
    Enc_Dec(QWidget *parent = nullptr);
    ~Enc_Dec();

public slots:
    void compress_fn();
    void decompress_fn();

private:
    void showGraphics();
    void FileNames(QStringList);

    void DisplayImage();

    map<int, string> valueTOcode;
    map<string,int> codeTOvalue;
    vector<int>value;
    vector<string>codearr;
    int width=0;
    int hight=0;
    string binary_string;
    Ui::Enc_Dec *ui;
    QString file_path;
    QString file_data ;
    QGraphicsScene *displayed_scene;
    QPixmap pgmImage;
    image data ;
    QString filepath ;
    QGraphicsView *image_displayed;


};
#endif // ENC_DEC_H
