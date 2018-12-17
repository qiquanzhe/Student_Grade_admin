#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>
#include <QPixmap>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include "detailswindow.h"
#include <QTimer>
#include <QDateTime>
#include "dboperate.h"
//#include "keyreciver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent * event);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_btnMin_clicked();
    void on_btnExit_clicked();
    void on_loginButton_clicked();
    void timerUpdate(void);

private:
    Ui::MainWindow *ui;
    bool mDrag;
    QPoint mDragPos;
    QRect mLocation;
    QFont mIconFont;
    QLabel *idLabel;
    QLabel *pwdLabel;
    QLineEdit *idInput;
    QLineEdit *pwdInput;
    QPushButton *loginButton;
    QLabel *timeLabel;
    DBoperate *dbo;
};

#endif // MAINWINDOW_H
