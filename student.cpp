#include "student.h"

student::student()
{
    this->sno = "******";
}

student::student(QString sno, QString sname, QString ssex, int sage, QString sadd, int spol, QString stime, QString stel)
{
    this->sno = sno;
    this->sname = sname;
    this->ssex = ssex;
    this->sage = sage;
    this->sadd = sadd;
    this->spol = spol;
    this->stime = stime;
    this->stel = stel;
}
