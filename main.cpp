
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    //强制程序编码UTF-8
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //创建内置类QApplication对象程序
    QApplication a(argc, argv);
    //程序风格设置
    a.setStyle(QStyleFactory::create("fusion"));
    //创建MainWindow对象，MainWindow是自定义类
    MainWindow w;
    //显示MainWindow
    w.show();
    return a.exec();
}
