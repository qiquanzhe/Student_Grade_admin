#include "student.h"

student::student()
{

}

student::student(QString sno, QString sname, QString ssex, int sage, QString sadd, int spol, QDate stime, QString stel)
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
