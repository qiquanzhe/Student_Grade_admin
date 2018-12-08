#include "dboperate.h"

DBoperate::DBoperate()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("sg");
    db.setUserName("root");
    db.setPassword("123");
    db.setPort(3306);
    if(db.open())
    {
        qDebug()<<"成功连接数据库";
    }
    else{
        QMessageBox::warning(nullptr,"警告","无法连接数据库");
    }

    courseSize = 0;
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
    QString sql = "select * from courses where cno = '"+cno+"';";
    query = new QSqlQuery(sql,db);
    QSqlRecord rec = query->record();
    if(!query->next())
    {
        return -1;
    }
    else{
        sql="delete from courses where cno='"+cno+"'";
        query = new QSqlQuery(db);
        bool success  = query->exec(sql);
        if(success) return 1;
        else return -2;
    }
    //return 0;
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
double searchGrade(QString sno,QString cno){return 0;}
int DBoperate:: addNewGrade(grade newGrade){return 0;}
int DBoperate:: modGrade(QString sno,QString cno,double newGrade){return 0;}
int DBoperate:: delGrade(QString sno,QString cno){return 0;}
grade DBoperate:: returnAllGrade(){
    grade newgrade;
    return newgrade;
}

//student(QString sno,QString sname,QString ssex,int sage,QString sadd,int spol,QString stime,QString stel);

//对学生的操作
student DBoperate:: searchStudentByNo(QString sno){
    QString sql = "select * from students where sno='"+sno+"'";
    query = new QSqlQuery(sql,db);
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
        //return new student;
}
student DBoperate::searchStudentByTel(QString stel){
    student newStudent;
    return newStudent;
}
student* DBoperate::searchStudentByName(QString sname){return nullptr;}
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
    qDebug()<<sql;
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
    QString sql = "delete from students where sno='"+sno+"'";
    query = new QSqlQuery(db);
    bool success = query->exec(sql);
    if(success) return 1;
    else return -1;
}
student* DBoperate::returnAllStudents(){return nullptr;}

