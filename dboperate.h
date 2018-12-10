#ifndef DBOPERATE_H
#define DBOPERATE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include "course.h"
#include "grade.h"
#include "student.h"



class DBoperate
{
private:
    QSqlDatabase db;
    QSqlQuery *query;
public:
    DBoperate();
    //对用户的操作
    int loginSystem(QString id,QString pwd);
    int addNewUser(QString id,QString pwd);
    int modUserPwd(QString id,QString newpwd);

    //对课程的操作
    int searchCourseByCno(QString cno);
    course searchCourseByCnoAndCname(QString cno,QString cname);
    int addNewCourse(course c);
    int modCourseName(QString cno,QString newcname);
    int modCourseTeacher(QString cno,QString newCourseTeacher);
    int modCourseCredit(QString cno,QString credit);
    int delCourse(QString cno);
    course* returnAllCourses();

    //对成绩的操作
    grade searchGrade(QString sno,QString cno);
    int addNewGrade(grade newGrade);
    int modGrade(QString sno,QString cno,double newGrade);
    int delGrade(QString sno,QString cno);
    grade* returnAllGrade();

    //对学生的操作
    student searchStudentByNo(QString sno);
    student searchStudentByTel(QString stel);
    student* searchStudentByName(QString sname);
    int addNewStudent(student newStudent);
    int modStudentName(QString sno,QString newName);
    int modStudentPol(QString sno,int newPol);
    int modStudentTel(QString sno,QString newTel);
    int delStudent(QString sno);
    student* returnAllStudents();

    int courseSize;
    int searchStudentSize;
    int studentSize;
    int gradeSize;
};

#endif // DBOPERATE_H
