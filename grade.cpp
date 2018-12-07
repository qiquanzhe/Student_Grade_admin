#include "grade.h"

grade::grade()
{

}

grade::grade(QString sno, QString cno, double sgrade)
{
    this->sno = sno;
    this->cno = cno;
    this->sgrade = sgrade;
}
