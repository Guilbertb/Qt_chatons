#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getC() const
{
    return c;
}

void MainWindow::on_pushButton_clicked() // n&b
{
    QImage b=QImage(150,150,QImage::Format_RGB32); //allocation memoire image
    b.fill(qRgb(0,0,0));  // rempli de noir
  //  b.load("/home/work/work/Qt/image2/res/chaton.jpg");
    b.load("res/chaton.jpg");

// photo n&b
            QRgb col2;
            int gray2;
            int width2 = b.width();
            int height2 = b.height();
            for (int i = 0; i < width2; ++i)
            {
                for (int j = 0; j < height2; ++j)
                {
                    col2 = b.pixel(i, j);
                    gray2 = qGray(col2);
                    b.setPixel(i, j, qRgb(gray2, gray2, gray2));
                }
            }
            ui->label->setGeometry(40,30,b.width(),b.height());
    QPixmap a=QPixmap::fromImage(b); // transformation vers pixmap
    ui->label->setPixmap(a); // chargement vers le label
}

//void MainWindow::paintEvent(QPaintEvent * Ev)
//{
//    ui->label->show();
//}

void MainWindow::on_pushButton_2_clicked() // quit
{
close();
}

void MainWindow::on_pushButton_3_clicked()
{
    {


        QImage b=QImage(150,150,QImage::Format_RGB32); //allocation memoire image
        b.fill(qRgb(0,0,0));  // rempli de noir
      //  b.load("/home/work/work/Qt/image2/res/chaton.jpg");
        b.load("res/chaton.jpg");

        // diagonale
        //for (x=0;x<=dimx;x++)
            //for (y=0;y<dimy;y++)
            //b.setPixel(x,y,qGray());

    // photo n&b
                QRgb col2;
                int gray2;
                int width2 = b.width();
                int height2 = b.height();
                for (int i = 0; i < width2; ++i)
                {
                    for (int j = 0; j < height2; ++j)
                    {
                        col2 = b.pixel(i, j);
                        //gray2 = qRed(col2); // element rouge


                        //gray2 = qGray(col2);  // moyenne des 3 couleurs

                        // Luminance = 0,2126 × Rouge + 0,7152 × Vert + 0,0722 × Bleu.

                        gray2=(qRed(col2)+qBlue(col2)+qGreen(col2))/3;

                        b.setPixel(i, j, qRgb(gray2, gray2, gray2));
                    }
                }
        ui->label->setGeometry(40,30,b.width(),b.height());
        QPixmap a=QPixmap::fromImage(b); // transformation vers pixmap
        ui->label->setPixmap(a); // chargement vers le label
    }

}

void MainWindow::on_pushButton_4_clicked() // chaton couleur (on ne fait rien
{

    {
        QImage b=QImage(400,400,QImage::Format_RGB32); //allocation memoire image
        b.fill(qRgb(0,0,0));  // rempli de noir
        b.load("res/chaton.jpg");

        ui->label->setGeometry(40,30,b.width(),b.height());

        QPixmap a=QPixmap::fromImage(b); // transformation vers pixmap
        ui->label->setPixmap(a); // chargement vers le label

    }

}

void MainWindow::on_pushButton_5_clicked()   // Filtre 1
{
    //la matrice de convolution
    int Cf00= -1; int Cf10=0; int Cf20=1;
    int Cf01= -2; int Cf11=0; int Cf21=+2;
    int Cf02= -1; int Cf12=0; int Cf22=1;

QRgb col2,pt00,pt10,pt20,pt01,pt11,pt21,pt02,pt12,pt22;

        QImage b=QImage(400,400,QImage::Format_RGB32); //allocation memoire image



        b.fill(qRgb(0,0,0));  // rempli de noir


        b.load("res/chaton.jpg"); // on charge le chaton dans b

        QImage c=QImage(b.width(),b.height(),QImage::Format_RGB32); // Image filtrée
        int gray2,filtre;
        c.fill(qRgb(0,0,0));

        for (int i = 0; i < b.width(); ++i)
                {
                    for (int j = 0; j < b.height(); ++j)
                    {
                        col2 = b.pixel(i, j);
                        gray2=(qRed(col2)+qBlue(col2)+qGreen(col2))/3;
                        b.setPixel(i, j, qRgb(gray2, gray2, gray2));
                    }
                }
//        //l'image b est en N&B
                for (int i = 1; i < (b.width()-1); ++i) // pas tenir compte du  bord de 1 pixel d'epaisseur
                {
                    for (int j = 1; j < (b.height()-1); ++j)
                    {

                        pt00 = b.pixel(i-1,j-1);
                        pt10 = b.pixel(i,j-1);
                        pt20 = b.pixel(i+1,j-1);
                        pt01 = b.pixel(i-1,j);
                        pt11 = b.pixel(i,j);
                        pt21 = b.pixel(i+1,j);
                        pt02 = b.pixel(i-1,j+1);
                        pt12 = b.pixel(i,j+1);
                        pt22 = b.pixel(i+1,j+1);

                        filtre=   qRed(pt00)*Cf00+qRed(pt10)*Cf10+qRed(pt20)*Cf20
                                + qRed(pt01)*Cf01+qRed(pt11)*Cf11+qRed(pt21)*Cf21
                                + qRed(pt02)*Cf02+qRed(pt12)*Cf12+qRed(pt22)*Cf22;
                        filtre= filtre /(Cf00+Cf10+Cf20+Cf01+Cf11+Cf21+Cf02+Cf12+Cf22+1);


                        c.setPixel(i,j,qRgb(filtre,filtre,filtre));



                    }
                }

                ui->label->setGeometry(40,30,c.width(),c.height());
                QPixmap a=QPixmap::fromImage(c); // transformation vers pixmap
                ui->label->setPixmap(a); // chargement vers le label




}

