#include "dboperate.h"

DBoperate::DBoperate()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("sg");
    db.setUserName("root");
    db.setPassword("123456");
    db.setPort(3306);
    db.open();

    courseSize = 0;
    searchStudentSize = 0;
    studentSize = 0;
    gradeSize = 0;
}

//登录事件查询
int DBoperate::loginSystem(QString id,QString pwd)
{
    QString sql = "select password from users where id='"+id+"';";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    while(query->next())
    {
        rec = query->record();
        int idcol = rec.indexOf("password");
        QString value = query->value(idcol).toString();
        if(value==pwd)
            return 1;
        else return 0;
    }
    return 0;
}

//插入新用户
int DBoperate::addNewUser(QString id,QString pwd)
{
    QString sql = "select * from users where id = '"+id+"';";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    if(query->next())
    {
        return -1;
    }
    sql = "insert into users values('"+id+"','"+pwd+"');";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success)
        return 0;
    else
        return -2;
}

//修改密码
int DBoperate::modUserPwd(QString id,QString newpwd)
{
    QString sql = "update users set password='"+newpwd+"' where id='"+id+"';";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}

//对课程的操作
int DBoperate::searchCourseByCno(QString cno)
{
    QString sql = "select * from courses where cno='"+cno+"'";
    query = new QSqlQuery(sql,db);

    if(query->next())
        return -1;
    else
        return 1;
}

course DBoperate::searchCourseByCnoAndCname(QString cno,QString cname)
{
    course searchCourse;
    QString sql = "select * from courses where cno='"+cno+"' and cname='"+cname+"'";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    while(query->next())
    {
        rec=query->record();
        searchCourse.cno = query->value(rec.indexOf("cno")).toString();
        searchCourse.cname = query->value(rec.indexOf("cname")).toString();
        searchCourse.cteacher = query->value(rec.indexOf("cteacher")).toString();
        searchCourse.ccredit = query->value(rec.indexOf("ccredit")).toString();
    }
    return searchCourse;
}

int DBoperate::addNewCourse(course c){
    QString sql = QObject::tr("insert into courses(cno,cteacher,cname,ccredit) values('%1','%2','%3','%4')").arg(c.cno).arg(c.cteacher).arg(c.cname).arg(c.ccredit);
    qDebug()<<sql;
    //"insert into courses(cno,cteacher,cname,ccredit) values('"+c.cno+"','"+c.cteacher+"','"+c.cname+"',"+c.ccredit+")";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
int DBoperate:: modCourseName(QString cno,QString newcname){
    QString sql = "update courses set cname='"+newcname+"' where cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success)     return 1;
    else return 0;
}
int DBoperate:: modCourseTeacher(QString cno,QString newCourseTeacher){
    QString sql = "update courses set cteacher='"+newCourseTeacher+"' where cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success)     return 1;
    else return 0;
}
int DBoperate:: modCourseCredit(QString cno,QString credit){
    QString sql = "update courses set ccredit='"+credit+"' where cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success)     return 1;
    else return 0;
}
int DBoperate:: delCourse(QString cno){
    QString sql = "delete from grade where cno='"+cno+"'";
    query = new QSqlQuery(db);
    query->exec(sql);
    sql="delete from courses where cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success  = query->exec(sql);
    if(success) return 1;
    else return -2;
}
course* DBoperate:: returnAllCourses(){
    QString sql = "select * from courses";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    courseSize = query->size();
    if(courseSize == 0)
        return nullptr;
    course *allCourses = new course[courseSize];
    int i = 0;
    while (query->next()) {
        rec = query->record();
        allCourses[i].cno = rec.value("cno").toString();
        allCourses[i].cname = rec.value("cname").toString();
        allCourses[i].cteacher = rec.value("cteacher").toString();
        allCourses[i].ccredit = rec.value("ccredit").toString();
        i++;
    }
    return allCourses;
}

//对成绩的操作
grade DBoperate:: searchGrade(QString sno,QString cno){
    QString sql = "select grade from grade where sno='"+sno+"' and cno='"+cno+"'";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    double sgrade = 0;
    if(query->next())
    {
        bool ok;
        rec=query->record();
        sgrade = rec.value("grade").toDouble(&ok);
        if(!ok)
        {
            return grade("******","******",0);
        }
        else
        {
            grade searchGrade(sno,cno,sgrade);
            return searchGrade;
        }
    }
    else
        return grade("******","******",0);
}

int DBoperate:: addNewGrade(grade newGrade){
    QString sql = "insert into grade values('"+newGrade.sno+"','"+newGrade.cno+"',"+QString::number(newGrade.sgrade)+")";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return 0;
}
int DBoperate:: modGrade(QString sno,QString cno,double newGrade){
    QString sql = "update grade set grade="+QString::number(newGrade,10,2)+" where sno='"+sno+"' and cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else    return -1;
}
int DBoperate:: delGrade(QString sno,QString cno){
    QString sql = "delete from grade where sno='"+sno+"' and cno='"+cno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
grade* DBoperate:: returnAllGrade(){
    QString sql = "select * from grade";
    query = new QSqlQuery(sql,db);
    gradeSize = query->size();
    grade *allGrades = new grade[gradeSize];
    QSqlRecord rec = query->record();
    int i = 0;
    while(query->next())
    {
        rec = query->record();
        allGrades[i].sno = rec.value("sno").toString();
        allGrades[i].cno = rec.value("cno").toString();
        allGrades[i].sgrade = rec.value("grade").toDouble();
        i++;
    }
    return allGrades;
}


//对学生的操作
student DBoperate:: searchStudentByNo(QString sno){
    QString sql = "select * from students where sno='"+sno+"'";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    searchStudentSize = query->size();
    if(query->next())
    {
        rec = query->record();
        student resultStudent(rec.value("sno").toString(),
                              rec.value("sname").toString(),
                              rec.value("ssex").toString(),
                              rec.value("sage").toInt(),
                              rec.value("sadd").toString(),
                              rec.value("spol").toInt(),
                              rec.value("stime").toString(),
                              rec.value("stel").toString());
        return resultStudent;
    }
    else
    {
        student resultStudent;
        return resultStudent;
    }
        //return new student;
}
student DBoperate::searchStudentByTel(QString stel){
    QString sql = "select * from students where stel='"+stel+"'";
    query = new QSqlQuery(sql,db);
    searchStudentSize = query->size();
    QSqlRecord rec = query->record();
    if(query->next())
    {
        rec = query->record();
        student resultStudent(rec.value("sno").toString(),
                              rec.value("sname").toString(),
                              rec.value("ssex").toString(),
                              rec.value("sage").toInt(),
                              rec.value("sadd").toString(),
                              rec.value("spol").toInt(),
                              rec.value("stime").toString(),
                              rec.value("stel").toString());
        return resultStudent;
    }
    else
    {
        student resultStudent;
        return resultStudent;
    }
}
student* DBoperate::searchStudentByName(QString sname){
    QString sql = "select * from students where sname='"+sname+"'";
    query = new QSqlQuery(sql,db);
    student *resultStudent = new student[query->size()];
    QSqlRecord rec = query->record();
    searchStudentSize = query->size();
    int i = 0;
    while(query->next())
    {
        rec = query->record();
        resultStudent[i].sno = rec.value("sno").toString();
        resultStudent[i].sname =rec.value("sname").toString();
        resultStudent[i].ssex =rec.value("ssex").toString();
        resultStudent[i].sage =rec.value("sage").toInt();
        resultStudent[i].sadd =rec.value("sadd").toString();
        resultStudent[i].spol =rec.value("spol").toInt();
        resultStudent[i].stime =rec.value("stime").toString();
        resultStudent[i].stel =rec.value("stel").toString();
        i++;
    }
    return resultStudent;
}
int DBoperate:: addNewStudent(student newStudent){
    QString sql = QObject::tr("insert into students(sno,sname,sage,sadd,spol,stime,stel,ssex) values('%1','%2',%3,'%4',%5,'%6','%7','%8')")
            .arg(newStudent.sno)
            .arg(newStudent.sname)
            .arg(newStudent.sage)
            .arg(newStudent.sadd)
            .arg(newStudent.spol)
            .arg(newStudent.stime)
            .arg(newStudent.stel)
            .arg(newStudent.ssex);
    //qDebug()<<sql;
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
int DBoperate:: modStudentName(QString sno,QString newName){
    QString sql = "update students set sname='"+newName+"' where sno='"+sno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
int DBoperate:: modStudentPol(QString sno,int newPol){
    QString sql = "update students set spol="+QString::number(newPol)+" where sno='"+sno+"'";
    //qDebug()<<sql;
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
int DBoperate:: modStudentTel(QString sno,QString newTel){
    QString sql = "update students set stel='"+newTel+"' where sno='"+sno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
int DBoperate:: delStudent(QString sno){
    query = new QSqlQuery("delete from grade where sno='"+sno+"'",db);
    QString sql = "delete from students where sno='"+sno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
student* DBoperate::returnAllStudents(){
    QString sql = "select * from students";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    studentSize = query->size();
    if(studentSize == 0)
        return nullptr;
    //course *allCourses = new course[courseSize];
    student *allStudents = new student[studentSize];
    int i = 0;
    while (query->next()) {
        rec = query->record();
        allStudents[i].sno = rec.value("sno").toString();
        allStudents[i].sname =rec.value("sname").toString();
        allStudents[i].ssex =rec.value("ssex").toString();
        allStudents[i].sage =rec.value("sage").toInt();
        allStudents[i].sadd =rec.value("sadd").toString();
        allStudents[i].spol =rec.value("spol").toInt();
        allStudents[i].stime =rec.value("stime").toString();
        allStudents[i].stel =rec.value("stel").toString();
        i++;
    }
    return allStudents;
}

