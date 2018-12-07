#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <QDate>


class student
{
public:
    student();
    student(QString sno,QString sname,QString ssex,int sage,QString sadd,int spol,QString stime,QString stel);
public:
    QString sno;
    QString sname;
    QString ssex;
    int sage;
    QString sadd;
    int spol;
    QString stime;
    QString stel;
};

#endif // STUDENT_H
