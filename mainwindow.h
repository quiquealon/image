#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vptree.h"
#include <vector>


typedef int II;
typedef float FF;


struct Point {
    std::string name;
    std::vector<FF> char_vector;
};


typedef std::vector<Point> points;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static double m_distance( const Point& p1, const Point& p2 );
    void remove(QLayout *layout);

private slots:
    void on_pushButton_clicked();

private:

    VpTree<Point, m_distance> tree;
    std::vector<Point> points;
    std::vector<Point> results;
    std::vector<double> distances;



    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
