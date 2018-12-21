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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //初始化窗口事件函数
    explicit MainWindow(QWidget *parent = nullptr);
    //在当前窗口按下回车时触发的事件，自动调用登录函数
    void keyPressEvent(QKeyEvent * event);
    ~MainWindow();

protected:
    //三个与鼠标相关的事件，控制窗口的拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    //最小化按钮点击事件，用于最小化窗口
    void on_btnMin_clicked();
    //退出按钮点击事件，用于窗口的退出
    void on_btnExit_clicked();
    //登录按钮点击事件，用于登录
    void on_loginButton_clicked();
    //时间相关的事件，在右下角显示时间
    void timerUpdate(void);

private:
    //界面对象指针ui
    Ui::MainWindow *ui;
    //指示拖动的布尔变量，初值为false
    bool mDrag;
    //获取位置信息用于拖动窗口
    QPoint mDragPos;
    QRect mLocation;
    //字体，用于设置字体样式
    //QFont mIconFont;
    //显示用户名和密码标志的容器QLabel对象
    QLabel *idLabel;
    QLabel *pwdLabel;
    //输入用户名和密码的行输入对象指针
    QLineEdit *idInput;
    QLineEdit *pwdInput;
    //登录按钮
    QPushButton *loginButton;

    //显示时间
    QLabel *timeLabel;
    //创建自定义类DBoperate的对象用于操作数据库
    DBoperate *dbo;
};

#endif // MAINWINDOW_H
