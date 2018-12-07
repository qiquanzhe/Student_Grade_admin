#ifndef GRADE_H
#define GRADE_H
#include <QString>


class grade
{
public:
    grade();
    grade(QString sno,QString cno,double sgrade);
public:
    QString sno;
    QString cno;
    double sgrade;
};

#endif // GRADE_H
