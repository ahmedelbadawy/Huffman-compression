#include "Huffman-T7-GUI.h"
#include "ui_Huffman-T7-GUI.h"
#include "read-GUI.hpp"
#include "Decompression-GUI.h"
#include <QFileDialog>
#include <QDebug>


Enc_Dec::Enc_Dec(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Enc_Dec)
{
    ui->setupUi(this);
   this->setFixedSize(QSize(705, 464));
    connect(ui->compress_button, SIGNAL(clicked()), this, SLOT(compress_fn()));
    connect(ui->decompress_button, SIGNAL(clicked()), this, SLOT(decompress_fn()));


}

Enc_Dec::~Enc_Dec()
{
    delete ui;
}
void Enc_Dec::compress_fn()
{
    this->file_path = QFileDialog::getOpenFileName(this, tr("select .PGM file"),
                                                   "../", tr("Image Files (*.pgm)"));
    DisplayImage();

    SizeOfFile(file_path.toStdString());

    fileinfo(data , file_path.toStdString()) ;
   
    vector<int>freq(256,0);

        int i = 0;
        while (i < data.Pixels.size())
        {
            ++freq[data.Pixels[i]];
            ++i;
        }

        buildhuffmantree(freq, valueTOcode);
        string serializedData = serialize(data, valueTOcode);
        
            writeEncoded(serializedData);
            writeCodes(data, valueTOcode);

            ui->fileLabel->setText(file_path);
            ui->heightLabel->setText(QString::number(data.hight));
            ui->widthLabel->setText(QString::number(data.width));



            double compressed_files_size =SizeOfFile("compressMod.enc")
                                        + SizeOfFile("codeFile.freq");
            double original_pgm_size = SizeOfFile(file_path.toStdString());
            double CR = compressed_files_size / original_pgm_size;
            ui->CRLabel->setText(QString::number(100 - (CR*100)));

}
void Enc_Dec::decompress_fn()
{
    QStringList compressionResults = QFileDialog::getOpenFileNames(this,tr("Select CompressedMod & code file (.enc & .freq)"), "../", tr("compressed files (*.enc *.freq)"));

    readCompressed(binary_string);
    readCodes(value, codearr, width, hight);

    for(int i=0; i<codearr.size();i++)
        {
        codeTOvalue[codearr[i]]= value[i];
         }

    decode_write(codeTOvalue , binary_string,width,hight);
}

void Enc_Dec::DisplayImage()
{
    pgmImage.load(file_path);

    displayed_scene = new QGraphicsScene(this);

    displayed_scene->addPixmap(pgmImage);

        displayed_scene->setSceneRect(pgmImage.rect());

    ui->view->setScene(displayed_scene);

    ui->view->fitInView(pgmImage.rect());
}

