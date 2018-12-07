#ifndef COURSE_H
#define COURSE_H
#include <QString>


class course
{
public:
    course();
    course(QString cno,QString cname,QString cteacher,QString ccredit);
public:
    QString cno;
    QString cname;
    QString cteacher;
    QString ccredit;
};

#endif // COURSE_H
