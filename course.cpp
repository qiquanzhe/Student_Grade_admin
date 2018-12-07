#include "course.h"

course::course()
{
    this->cno = "******";
}

course::course(QString cno, QString cname, QString cteacher, QString ccredit)
{
    this->cno = cno;
    this->cname = cname;
    this->cteacher = cteacher;
    this->ccredit = ccredit;
}
