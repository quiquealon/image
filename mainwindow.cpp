#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <QElapsedTimer>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet("background-color: red");

    for(unsigned int num=1;num<100;num++){
        ui->comboBox->addItem(QString::number(num));

    }





    std::ifstream linea;
    std::vector<std::string> record;
    std::vector < std::vector<std::string>> data;
    std::string line;




    linea.open("/home/enrique/Documents/Image/db/imgs_features.csv");

    if (linea.is_open())
        {
            while (getline( linea, line ))
            {
                std::stringstream ss ( line );

                while (getline(ss,line,','))
                {
                    record.push_back(line);
                }

                data.push_back(record);
                record.clear();

            }
        }

   linea.close();


   for(unsigned int i=0;i<data.size();i++){
       Point point;
       for(unsigned int j=0;j<data[0].size();j++){
           if(j==0){
               point.name=data[i][j];
           }
           else{
               point.char_vector.push_back(std::stof(data[i][j]));
           }
        }
       points.push_back(point);
    }


   /************Timer*************/
   QElapsedTimer timer;
   timer.start();

   tree.create(points);
   ui->labelCreacion->setText(QString::number(timer.nsecsElapsed()));

   /************Timer*************/

    qDebug()<<points.size();

}




MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::m_distance(const Point &p1, const Point &p2)
{
    double distance = 0;
    for(    auto i = 0; i<p1.char_vector.size(); i++){
            distance += abs(p1.char_vector[i] - p2.char_vector[i]);
        }
    return distance;
}

void MainWindow::remove(QLayout *layout)
{

    QLayoutItem* child;
    while(layout->count()!=0)
    {
        child = layout->takeAt(0);
        if(child->layout() != 0)
        {
            remove(child->layout());
        }
        else if(child->widget() != 0)
        {
            delete child->widget();
        }

        delete child;
    }

}




void MainWindow::on_pushButton_clicked()
{

    results.clear();
    distances.clear();

    remove(ui->resultLayout);
    remove(ui->imgLayout);




    int numSearch;
    int numResults;

    numSearch=ui->lineEdit->text().toInt();
    numResults=ui->comboBox->currentIndex()+2;

    /************Timer*************/
    QElapsedTimer timer;
    timer.start();

    tree.search(points[numSearch], numResults, &results, &distances );

    ui->labelConsulta->setText(QString::number(timer.nsecsElapsed()));

     /************Timer*************/


    QString qstr = QString::fromStdString(results[0].name);
    QString url ("/home/enrique/Documents/Image/db/"+qstr);
    QPixmap img(url);
    QLabel *label = new QLabel();
    label->setPixmap(img);
    label->adjustSize();
    label->setStyleSheet("border: 2px solid magenta");
    ui->resultLayout->addWidget(label);
    label->setScaledContents( true );




    for( unsigned int i = 1; i < results.size(); i++ ) {
        QString qstr = QString::fromStdString(results[i].name);
        QString url ("/home/enrique/Documents/Image/db/"+qstr);
        QPixmap img(url);
        QLabel *label = new QLabel();
        label->setPixmap(img);
        label->adjustSize();
        label->setStyleSheet("border: 2px solid magenta");
        ui->imgLayout->addWidget(label);
        label->setScaledContents( true );

    }

   for (unsigned int h=0;h<distances.size();h++)
       qDebug()<<distances[h];


}
