#include "detailswindow.h"
#include "ui_detailswindow.h"

DetailsWindow::DetailsWindow(QWidget *parent,QString id) :
    QMainWindow(parent),
    ui(new Ui::DetailsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("学生成绩管理系统");
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(),this->height());

    //窗口背景图片
    setAutoFillBackground(true);
    QPalette pal=this->palette();
    QPixmap *pixmap = new QPixmap(":/image/bg1.jpg");
    pal.setBrush(backgroundRole(),pixmap->scaled(420,300,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setPalette(pal);

    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");

    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    ui->pwdAgainEdit->setEchoMode(QLineEdit::Password);
    ui->modOldPwdInput->setEchoMode(QLineEdit::Password);
    ui->modNewPwdInput->setEchoMode(QLineEdit::Password);
    ui->modNewAgainPwdInput->setEchoMode(QLineEdit::Password);

    currentUser = id;
    dbo = new DBoperate();

    ui->delShowTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->delShowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->delShowTable->setSelectionMode(QAbstractItemView::SingleSelection);


    on_displayCourseRefreshBtn_clicked();
    on_diplayStuRefreshBtn_clicked();
    on_displayGradeRefreshBtn_clicked();
}

DetailsWindow::~DetailsWindow()
{
    delete ui;
}

//添加用户的按钮
void DetailsWindow::on_addbtn_clicked(){
    QString id = ui->idEdit->text();
    QString pwd = ui->pwdEdit->text();
    QString pwdAgain = ui->pwdAgainEdit->text();
    bool flag = true;

    if(id.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入用户名！");
        return;
    }
    if(pwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入密码！");
        return;
    }
    if(pwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请再次输入密码！");
        return;
    }
    if(pwd!=pwdAgain)
    {
        QMessageBox::information(this,"Error","两次输入密码不一致！");
        return;
    }

    for(int i = 0;i < id.length();i++)
    {
        if((id[i] >= 'a'&&id[i]<='z')||(id[i]>='A'&&id[i]<='Z'))
            continue;
        else
        {
            flag = false;
            break;
        }
    }

    if(!flag)  {
        QMessageBox::information(this,"Error","账号中包含数字字符!");
        return;
    }

    int res = dbo->addNewUser(id,pwd);
    if(res == -1)
    {
        QMessageBox::information(this,"Error","用户id已存在");
        return;
    }
    else
    {
        QMessageBox::information(this,"Infromation","添加成功");
        on_canceladdbtn_clicked();
    }
}
void DetailsWindow:: on_canceladdbtn_clicked(){
    ui->idEdit->setText("");
    ui->pwdEdit->setText("");
    ui->pwdAgainEdit->setText("");
}

//修改密码的按钮
void DetailsWindow:: on_modbtn_clicked(){
    QString oldpwd = ui->modOldPwdInput->text();
    QString newpwd = ui->modNewPwdInput->text();
    QString newpwdAgain = ui->modNewAgainPwdInput->text();
    if(oldpwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入当前密码！");
        return;
    }
    if(newpwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入新密码！");
        return;
    }
    if(newpwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请再次输入新密码！");
        return;
    }

    if(dbo->loginSystem(currentUser,oldpwd) != 1)
    {
        QMessageBox::information(this,"Error","密码输入错误！");
        return;
    }

    //qDebug()<<currentUser;
    int res = dbo->modUserPwd(currentUser,newpwd);
    if(res == -1)
        QMessageBox::information(this,"Error","改密失败");
    else
    {
        QMessageBox::information(this,"goodNews","改密成功");
        on_cancelmodbtn_clicked();
    }
}
void DetailsWindow:: on_cancelmodbtn_clicked(){
    ui->modOldPwdInput->setText("");
    ui->modNewPwdInput->setText("");
    ui->modNewAgainPwdInput->setText("");
}

//管理课程的按钮事件
//添加课程
void DetailsWindow:: on_addCbtn_clicked(){
    QString cname = ui->addCnameInput->text();
    QString cno = ui->addCnoInput->text();
    QString cteacher = ui->addTeaInput->text();
    QString ccredit = ui->addCreInput->text();

    if(cname.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程名称！");
        return;
    }
    if(cno.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程号！");
        return;
    }
    if(cteacher.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入授课教师！");
        return;
    }
    if(ccredit.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入学分！");
        return;
    }

    QRegExp reg ( "^[0-9]*[1-9][0-9]*$");
    QRegExpValidator qrv(reg);
    int pos = 0;

    qDebug()<<ccredit<<qrv.validate(ccredit,pos);
    if(qrv.validate(ccredit,pos)==QValidator::Invalid)
    {
        QMessageBox::information(this,"Error","请输入正确的正整数课程学分！");
        return;
    }
    else{
        //credit = ccredit.toDouble();
        course newCourse(cno,cname,cteacher,ccredit);
        //qDebug()<<ccredit<<cno<<cname<<cteacher;
        if(dbo->searchCourseByCno(cno) == -1)
        {
            QMessageBox::information(this,"Error","已存在的课程号");
            on_resetCaddbtn_clicked();
            return;
        }
        int num = dbo->addNewCourse(newCourse);
        if(num == 1)
        {
            QMessageBox::information(this,"infomation","添加成功");
            on_resetCaddbtn_clicked();
            //on_displayCourseRefreshBtn_clicked();
        }
        else
        {
            QMessageBox::information(this,"Error","添加失败");
        }
    }



}
void DetailsWindow:: on_resetCaddbtn_clicked(){
    ui->addCnameInput->setText("");
    ui->addCnoInput->setText("");
    ui->addTeaInput->setText("");
    ui->addCreInput->setText("");
}

//删除课程
void DetailsWindow:: on_delCourseFindBtn_clicked(){
    QString cno = ui->delCnoInput->text();
    QString cname = ui->delCnameInput->text();
    if(cno == "")
    {
        QMessageBox::information(this,"Error","请输入要删除的课程号");
        return;
    }
    else if(cname == "")
    {
        QMessageBox::information(this,"Error","请输入要删除的课程名");
        return;
    }
    //course searchCourse("111","111","111","111");
    course searchCourse = dbo->searchCourseByCnoAndCname(cno,cname);

    if(searchCourse.cno == "******")
    {
        QMessageBox::information(this,"Error","没有找到该课程！");
        on_resetCdelbtn_clicked();
        return;
    }
    int row = ui->delShowTable->rowCount();
    if(row == 2)
    {
        ui->delShowTable->removeRow(1);
        row--;
    }
    ui->delShowTable->insertRow(row);
    ui->delShowTable->setItem(row,0,new QTableWidgetItem(searchCourse.cno));
    ui->delShowTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->delShowTable->setItem(row,1,new QTableWidgetItem(searchCourse.cteacher));
    ui->delShowTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->delShowTable->setItem(row,2,new QTableWidgetItem(searchCourse.cname));
    ui->delShowTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->delShowTable->setItem(row,3,new QTableWidgetItem(""+searchCourse.ccredit));
    ui->delShowTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->delCbtn->setEnabled(true);
    courseToDelete = searchCourse;
}
void DetailsWindow:: on_delCbtn_clicked(){
    //qDebug()<<courseToDelete.cno;
    int num = dbo->delCourse(courseToDelete.cno);
    if(num == -1)
    {
        QMessageBox::information(this,"Error","没有找到该课程！");
        on_resetCdelbtn_clicked();
        return;
    }
    else if(num == -2)
    {
        QMessageBox::information(this,"Error","删除失败！");
        return;
    }
    else{
        QMessageBox::information(this,"Error","删除成功");
        on_resetCdelbtn_clicked();
    }
}

void DetailsWindow:: on_resetCdelbtn_clicked(){
    ui->delCnameInput->setText("");
    ui->delCnoInput->setText("");
    if(ui->delShowTable->rowCount() == 2)
        ui->delShowTable->removeRow(1);
    ui->delCbtn->setEnabled(false);
}

//修改课程
void DetailsWindow:: on_modCbtn_clicked(){
    QString cno = ui->modCnoInput->text();
    QString content = ui->modNewContentInput->text();
    int num = ui->selectModCombo->currentIndex();
    if(cno == "")
    {
        QMessageBox::information(this,"Error","请输入要修改的课程号");
        return;
    }
    if(content == "")
    {
        QMessageBox::information(this,"Error","请输入修改后的内容");
        return;
    }

    int result = -1;

    switch (num) {
    case 0:
        result = dbo->modCourseName(cno,content);
        break;
    case 1:
        result = dbo->modCourseTeacher(cno,content);
        break;
    case 2:
        result = dbo->modCourseCredit(cno,content);
        break;
    }
    if(result == 1)
    {
        QMessageBox::information(this,"information","修改"+ui->selectModCombo->currentText()+"成功");
        on_resetCmodbtn_clicked();
    }
    else
    {
        QMessageBox::information(this,"Error","修改"+ui->selectModCombo->currentText()+"失败");
    }
}
void DetailsWindow:: on_resetCmodbtn_clicked(){
    ui->modCnoInput->setText("");
    ui->modNewContentInput->setText("");
    ui->modStuContentCombo->setCurrentIndex(0);
}

//查找课程
void DetailsWindow:: on_findCbtn_clicked(){
    QString cno = ui->findCnoInput->text();
    QString cname = ui->findCnameInput->text();
    if(cno == "")
    {
        QMessageBox::information(this,"Error","请输入要查找的课程号");
        return;
    }
    else if(cname == "")
    {
        QMessageBox::information(this,"Error","请输入要查找的课程名");
        return;
    }

    course findTheCourse = dbo->searchCourseByCnoAndCname(cno,cname);
    if(findTheCourse.cno == "******")
    {
        QMessageBox::information(this,"Error","没有找到该课程");
        on_resetCfindbtn_clicked();
        return;
    }
    else
    {
        int row = ui->findShowTable->rowCount();
        if(row == 2)
        {
            ui->findShowTable->removeRow(1);
            row--;
        }
        ui->findShowTable->insertRow(row);
        ui->findShowTable->setItem(row,0,new QTableWidgetItem(findTheCourse.cno));
        ui->findShowTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->findShowTable->setItem(row,1,new QTableWidgetItem(findTheCourse.cteacher));
        ui->findShowTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->findShowTable->setItem(row,2,new QTableWidgetItem(findTheCourse.cname));
        ui->findShowTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->findShowTable->setItem(row,3,new QTableWidgetItem(""+findTheCourse.ccredit));
        ui->findShowTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}
void DetailsWindow:: on_resetCfindbtn_clicked(){
    ui->findCnoInput->setText("");
    ui->findCnameInput->setText("");
    int row = ui->findShowTable->rowCount();
    if(row == 2)
        ui->findShowTable->removeRow(1);
}

//遍历课程
void DetailsWindow:: on_displayCourseRefreshBtn_clicked(){
    int currentRows = ui->displayCTable->rowCount();
    while(currentRows > 1)
    {
        ui->displayCTable->removeRow(currentRows-1);
        currentRows--;
    }
    course *allCourses = dbo->returnAllCourses();
    if(allCourses == nullptr)
        return;
    else{
        int row = ui->displayCTable->rowCount();
        for(int i = 0;i < dbo->courseSize;i++)
        {
            ui->displayCTable->insertRow(row);
            ui->displayCTable->setItem(row,0,new QTableWidgetItem(allCourses[i].cno));
            ui->displayCTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayCTable->setItem(row,1,new QTableWidgetItem(allCourses[i].cteacher));
            ui->displayCTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayCTable->setItem(row,2,new QTableWidgetItem(allCourses[i].cname));
            ui->displayCTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayCTable->setItem(row,3,new QTableWidgetItem(allCourses[i].ccredit));
            ui->displayCTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            row++;
        }
    }
}

//管理成绩的事件
//添加成绩
void DetailsWindow:: on_addGradeBtn_clicked(){
    QString sno = ui->addGradeSnoInput->text();
    QString cno = ui->addGradeCnoInput->text();
    QString s_grade = ui->addGradeGradeInput->text();
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(cno.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程号！");
        return;
    }
    if(s_grade.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程成绩！");
        return;
    }
    student findStudent = dbo->searchStudentByNo(sno);
    if(findStudent.sno == "******")
    {
        QMessageBox::information(this,"Error","没有找到该学号");
        on_resetDelStuBtn_clicked();
        return;
    }
    int findTheCourse = dbo->searchCourseByCno(cno);
    if(findTheCourse == 1)
    {
        QMessageBox::information(this,"Error","没有找到该课程");
        on_resetCfindbtn_clicked();
        return;
    }
    bool ok = false;
    double d_grade = s_grade.toDouble(&ok);
    if(!ok)
    {
        QMessageBox::information(this,"Error","请输入正确的成绩");
        return;
    }
    grade searchGrade = dbo->searchGrade(sno,cno);
    if(searchGrade.sno!="******")
    {
        QMessageBox::information(this,"Error","已存在的成绩");
        on_resetGradeaddBtn_clicked();
        return;
    }
    grade newGrade(sno,cno,d_grade);
    int success = dbo->addNewGrade(newGrade);
    if(success)
    {
        QMessageBox::information(this,"information","添加成功");
        on_resetGradeaddBtn_clicked();
    }
    else
        QMessageBox::information(this,"Error","添加失败");
}
void DetailsWindow:: on_resetGradeaddBtn_clicked(){
    ui->addGradeCnoInput->setText("");
    ui->addGradeGradeInput->setText("");
    ui->addGradeSnoInput->setText("");
}

//删除成绩
void DetailsWindow:: on_delGradeFindBtn_clicked(){
    QString sno = ui->delGradeSnoInput->text();
    QString cno = ui->delGradeCnoInput->text();
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(cno.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程号！");
        return;
    }
    grade searchGrade = dbo->searchGrade(sno,cno);
    if(searchGrade.sno == "******")
    {
        QMessageBox::information(this,"Error","查找失败或没有该成绩信息");
        return;
    }
    else
    {
        int row = ui->delGradeDisplayTable->rowCount();
        if(row == 2)
            ui->delGradeDisplayTable->removeRow(1);
        ui->delGradeDisplayTable->insertRow(1);
        ui->delGradeDisplayTable->setItem(1,0,new QTableWidgetItem(searchGrade.sno));
        ui->delGradeDisplayTable->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->delGradeDisplayTable->setItem(1,1,new QTableWidgetItem(searchGrade.cno));
        ui->delGradeDisplayTable->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->delGradeDisplayTable->setItem(1,2,new QTableWidgetItem(QString::number(searchGrade.sgrade,10,2)));
        ui->delGradeDisplayTable->item(1,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        gradeToDelete = searchGrade;
        ui->delGradeBtn->setEnabled(true);
    }

}
void DetailsWindow:: on_delGradeBtn_clicked(){
    int num = dbo->delGrade(gradeToDelete.sno,gradeToDelete.cno);
    if(num == 1)
    {
        QMessageBox::information(this,"information","删除成功");
        on_resetDelGradeBtn_clicked();
        return;
    }
    else
    {
        QMessageBox::information(this,"Error","删除失败");
        return;
    }
}
void DetailsWindow:: on_resetDelGradeBtn_clicked(){
    ui->delGradeCnoInput->setText("");
    ui->delGradeSnoInput->setText("");
    int row = ui->delGradeDisplayTable->rowCount();
    if(row == 2)
        ui->delGradeDisplayTable->removeRow(1);
    ui->delGradeBtn->setEnabled(false);
}

//修改成绩
void DetailsWindow:: on_modGradeBtn_clicked(){
    QString sno = ui->modGradeSnoInput->text();
    QString cno = ui->modGradeCnoInput->text();
    QString newgrade = ui->modGradeNewGradeInput->text();
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(cno.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程号！");
        return;
    }
    grade searchGrade = dbo->searchGrade(sno,cno);
    if(searchGrade.sno == "******")
    {
        QMessageBox::information(this,"Error","查找失败或没有该成绩信息");
        return;
    }

    bool ok = false;
    double d_grade = newgrade.toDouble(&ok);
    int num = dbo->modGrade(sno,cno,d_grade);
    if(num == 1)
    {
        QMessageBox::information(this,"information","修改成功");
        on_resetDelGradeBtn_clicked();
        return;
    }
    else
    {
        QMessageBox::information(this,"Error","修改失败");
        return;
    }
}
void DetailsWindow:: on_resetModGradeBtn_clicked(){
    ui->modGradeCnoInput->setText("");
    ui->modGradeNewGradeInput->setText("");
    ui->modGradeSnoInput->setText("");
}

//查询成绩
void DetailsWindow:: on_findGradeBtn_clicked(){
    QString sno = ui->findGradeSnoInput->text();
    QString cno = ui->findGradeCnoInput->text();
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(cno.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入课程号！");
        return;
    }
    grade searchGrade = dbo->searchGrade(sno,cno);
    if(searchGrade.sno == "******")
    {
        QMessageBox::information(this,"Error","查找失败或没有该成绩信息");
        return;
    }
    else
    {
        int row = ui->findGradeTable->rowCount();
        if(row == 2)
            ui->findGradeTable->removeRow(1);
        ui->findGradeTable->insertRow(1);
        ui->findGradeTable->setItem(1,0,new QTableWidgetItem(searchGrade.sno));
        ui->findGradeTable->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findGradeTable->setItem(1,1,new QTableWidgetItem(searchGrade.cno));
        ui->findGradeTable->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findGradeTable->setItem(1,2,new QTableWidgetItem(QString::number(searchGrade.sgrade,10,2)));
        ui->findGradeTable->item(1,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    }
}
void DetailsWindow:: on_resetFindGradeBtn_clicked(){
    ui->findGradeCnoInput->setText("");
    ui->findGradeSnoInput->setText("");
    int row = ui->findGradeTable->rowCount();
    if(row == 2)
        ui->findGradeTable->removeRow(1);
}

//遍历成绩
void DetailsWindow:: on_displayGradeRefreshBtn_clicked(){
    grade *allGrades = dbo->returnAllGrade();
    int row = ui->displayGradeTable->rowCount();
    while(row!=1)
        ui->displayGradeTable->removeRow(--row);
    if(dbo->gradeSize == 0)
        return;
    else
    {
        int i = 0;
        while (i < dbo->gradeSize) {
            ui->displayGradeTable->insertRow(row);
            ui->displayGradeTable->setItem(row,0,new QTableWidgetItem(allGrades[i].sno));
            ui->displayGradeTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayGradeTable->setItem(row,1,new QTableWidgetItem(allGrades[i].cno));
            ui->displayGradeTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayGradeTable->setItem(row,2,new QTableWidgetItem(QString::number(allGrades[i].sgrade)));
            ui->displayGradeTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            row++;
            i++;
        }
    }
}

//管理学生
//添加学生
void DetailsWindow:: on_addStuBtn_clicked(){
    QString sno = ui->addStuSnoInput->text();
    QString sname = ui->addStuSnameInput->text();
    QString sage_s = ui->addStuSageInput->text();
    QString stel_s = ui->addStuStelInput->text();
    QString saddr = ui->addStuSaddInput->text();
    QString stime = ui->addStuStimeDate->date().toString("yyyy-MM-dd");
    int spol = ui->addStuSpolCombo->currentIndex();
    QString ssex = ui->addStuSexCombo->currentIndex() == 0?"男":"女";
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(sname == "")
    {
        QMessageBox::information(this,"Error","请输入学生姓名");
        return;
    }
    if(sage_s == "")
    {
        QMessageBox::information(this,"Error","请输入年龄");
        return;
    }
    if(stel_s == "")
    {
        QMessageBox::information(this,"Error","请输入电话");
        return;
    }
    if(saddr == "")
    {
        QMessageBox::information(this,"Error","请输入地址");
        return;
    }

    QRegExp reg ( "^[0-9]*[1-9][0-9]*$");
    QRegExpValidator qrv(reg);
    int pos = 0;

    //qDebug()<<ccredit<<qrv.validate(ccredit,pos);
    if(qrv.validate(sage_s,pos)!=QValidator::Acceptable)
    {
        QMessageBox::information(this,"Error","请输入正确的正整数年龄");
        return;
    }

    QRegExp reg2("^1[3|5|8|4|7][0-9]{9}$");
    QRegExpValidator qrv2(reg2);
    if(qrv2.validate(stel_s,pos)!= QValidator::Acceptable)
    {
        QMessageBox::information(this,"Error","请输入正确的数字电话号码");
        return;
    }

    if(dbo->searchStudentByNo(sno).sno != "******")
    {
        QMessageBox::information(this,"Error","已存在的学号");
        on_resetAddStuBtn_clicked();
        return;
    }

    int sage = sage_s.toInt();
    student newStudent(sno,sname,ssex,sage,saddr,spol,stime,stel_s);
    int num = dbo->addNewStudent(newStudent);
    if(num == 1)
    {
        QMessageBox::information(this,"information","添加成功");
        on_resetAddStuBtn_clicked();
        return;
    }
    else
        QMessageBox::information(this,"Error","添加失败");

}
void DetailsWindow:: on_resetAddStuBtn_clicked(){
    ui->addStuSnoInput->setText("");
    ui->addStuSaddInput->setText("");
    ui->addStuSageInput->setText("");
    ui->addStuSnameInput->setText("");
    ui->addStuSpolCombo->setCurrentIndex(0);
    ui->addStuSexCombo->setCurrentIndex(0);
    ui->addStuStelInput->setText("");
    ui->addStuStimeDate->setDate(QDate::fromString("2008-09-01","yyyy-MM-dd"));
}

//删除学生
void DetailsWindow:: on_delStuFindBtn_clicked(){
    QString sno = ui->delStuSnoInput->text();
    student findStudent = dbo->searchStudentByNo(sno);
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }

    if(findStudent.sno == "******")
    {
        QMessageBox::information(this,"Error","没有找到该学号");
        on_resetDelStuBtn_clicked();
        return;
    }

    int row = ui->delStuFindTable->rowCount();
    if(row == 2)
    {
        ui->delStuFindTable->removeRow(1);
        row--;
    }

    QString pol;
    switch (findStudent.spol) {
    case 0:pol = "群众";break;
    case 1:pol = "共青团员";break;
    case 2:pol = "中共党员";break;
    }
    ui->delStuFindTable->insertRow(row);

    ui->delStuFindTable->setItem(row,0,new QTableWidgetItem(findStudent.sno));
    ui->delStuFindTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,1,new QTableWidgetItem(findStudent.sname));
    ui->delStuFindTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,2,new QTableWidgetItem(findStudent.ssex));
    ui->delStuFindTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,3,new QTableWidgetItem(QString::number(findStudent.sage)));
    ui->delStuFindTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,4,new QTableWidgetItem(findStudent.sadd));
    ui->delStuFindTable->item(row,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,5,new QTableWidgetItem(pol));
    ui->delStuFindTable->item(row,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,6,new QTableWidgetItem(findStudent.stime));
    ui->delStuFindTable->item(row,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    ui->delStuFindTable->setItem(row,7,new QTableWidgetItem(findStudent.stel));
    ui->delStuFindTable->item(row,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    studentToDelete = findStudent;
    ui->delStuBtn->setEnabled(true);
}
void DetailsWindow:: on_delStuBtn_clicked(){
    int num = dbo->delStudent(studentToDelete.sno);
    if(num == 1)
    {
        QMessageBox::information(this,"information","删除成功");
        on_resetDelStuBtn_clicked();
        return;
    }
    else
    {
        QMessageBox::information(this,"Error","删除失败");
    }
}
void DetailsWindow:: on_resetDelStuBtn_clicked(){
    ui->delStuSnoInput->setText("");
    if(ui->delStuFindTable->rowCount() == 2)
        ui->delStuFindTable->removeRow(1);
    ui->delStuBtn->setEnabled(false);
}

//修改学生
void DetailsWindow:: on_modStuBtn_clicked(){
    QString sno = ui->modStuSnoInput->text();
    QString mod = ui->modStuContentSelect->currentText();
    QString content = ui->modStuContentInput->text();
    if(sno == "")
    {
        QMessageBox::information(this,"Error","请输入学号");
        return;
    }
    if(content == ""&&mod !="政治面貌")
    {
        QMessageBox::information(this,"Error","请输入修改后的内容");
        return;
    }

    student searchStudent = dbo->searchStudentByNo(sno);
    if(searchStudent.sno == "******")
    {
        QMessageBox::information(this,"Error","找不到该学号");
        on_resetModStuBtn_clicked();
        return;
    }
    int num = 0;
    switch (ui->modStuContentSelect->currentIndex()) {
    case 0:
        num = dbo->modStudentName(sno,content);
        break;
    case 1:
        num = dbo->modStudentPol(sno,ui->modStuContentCombo->currentIndex());
        break;
    case 2:
        QRegExp reg2("^1[3|5|8|4|7][0-9]{9}$");
        QRegExpValidator qrv2(reg2);
        int pos = 0;
        if(qrv2.validate(content,pos)!= QValidator::Acceptable)
        {
            QMessageBox::information(this,"Error","请输入正确的数字电话号码");
            return;
        }
        num = dbo->modStudentTel(sno,content);
        break;
    }
    if(num == 1)
    {
        QMessageBox::information(this,"information","修改成功");
        on_resetModStuBtn_clicked();
    }
    else
    {
        QMessageBox::information(this,"Error","修改失败");
    }
}
void DetailsWindow::on_modStuContentSelect_currentIndexChanged() {
    if(ui->modStuContentSelect->currentIndex() == 1)
    {
        ui->modStuContentInput->setText("");
        ui->modStuContentInput->setEnabled(false);
        ui->modStuContentCombo->setEnabled(true);
    }
    else{

        ui->modStuContentCombo->setCurrentIndex(0);
        ui->modStuContentCombo->setEnabled(false);
        ui->modStuContentInput->setEnabled(true);
    }
}
void DetailsWindow:: on_resetModStuBtn_clicked(){
    ui->modStuSnoInput->setText("");
    ui->modStuContentSelect->setCurrentIndex(0);
    ui->modStuContentInput->setEnabled(true);
    ui->modStuContentInput->setText("");
    ui->modStuContentCombo->setCurrentIndex(0);
    ui->modStuContentCombo->setEnabled(false);
}

//查询学生
void DetailsWindow:: on_findStuBtn_clicked(){
    int select = ui->findStuConditionCombo->currentIndex();
    QString content = ui->findStuContentInput->text();
    if(content == "")
    {
        QMessageBox::information(this,"Error","请输入查询内容");
        return;
    }
    student *findStudents = nullptr;
    int row = ui->findStuTable->rowCount();
    //int size = 0;
    switch (select) {
    case 0:
        findStudents = new student[1];
        findStudents[0] = dbo->searchStudentByNo(content);
        if(findStudents[0].sno == "******")
        {
            QMessageBox::information(this,"Error","没有找到该学号！");
            return;
        }
        break;
    case 1:
        findStudents = dbo->searchStudentByName(content);
        if(dbo->searchStudentSize == 0)
        {
            QMessageBox::information(this,"Error","没有找到该姓名！");
            return;
        }
        break;
    case 2:
        findStudents = new student[1];
        findStudents[0] = dbo->searchStudentByTel(content);
        if(dbo->searchStudentSize == 0)
        {
            QMessageBox::information(this,"Error","没有找到该电话！");
            return;
        }
        break;
    }

    int i = 0;
    while(row > 1)
    {
        ui->findStuTable->removeRow(--row);
    }
    while (i < dbo->searchStudentSize) {
        QString pol;
        switch (findStudents[i].spol) {
        case 0: pol = "群众";break;
        case 1:pol = "共青团员";break;
        case 2:pol = "中共党员";break;
        }
        ui->findStuTable->insertRow(row);
        ui->findStuTable->setItem(row,0,new QTableWidgetItem(findStudents[i].sno));
        ui->findStuTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,1,new QTableWidgetItem(findStudents[i].sname));
        ui->findStuTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,2,new QTableWidgetItem(findStudents[i].ssex));
        ui->findStuTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,3,new QTableWidgetItem(QString::number(findStudents[i].sage)));
        ui->findStuTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,4,new QTableWidgetItem(findStudents[i].sadd));
        ui->findStuTable->item(row,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,5,new QTableWidgetItem(pol));
        ui->findStuTable->item(row,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,6,new QTableWidgetItem(findStudents[i].stime));
        ui->findStuTable->item(row,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        ui->findStuTable->setItem(row,7,new QTableWidgetItem(findStudents[i].stel));
        ui->findStuTable->item(row,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
        row++;
        i++;
    }
}
void DetailsWindow:: on_resetFindStuBtn_clicked(){
    ui->findStuContentInput->setText("");
    ui->findStuConditionCombo->setCurrentIndex(0);
    int row = ui->findStuTable->rowCount();
    while(row > 1)
    {
        ui->findStuTable->removeRow(--row);
    }
}

//遍历学生
void DetailsWindow:: on_diplayStuRefreshBtn_clicked(){
    int currentRows = ui->displayStuTable->rowCount();
    while(currentRows > 1)
        ui->displayStuTable->removeRow(--currentRows);
    student *allStudents = dbo->returnAllStudents();
    if(allStudents == nullptr)
        return;
    else{
        int row = 1;
        for(int i = 0;i < dbo->studentSize;i++)
        {
            QString pol;
            switch (allStudents[i].spol) {
            case 0: pol = "群众";break;
            case 1:pol = "共青团员";break;
            case 2:pol = "中共党员";break;
            }
            ui->displayStuTable->insertRow(row);
            ui->displayStuTable->setItem(row,0,new QTableWidgetItem(allStudents[i].sno));
            ui->displayStuTable->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,1,new QTableWidgetItem(allStudents[i].sname));
            ui->displayStuTable->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,2,new QTableWidgetItem(allStudents[i].ssex));
            ui->displayStuTable->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,3,new QTableWidgetItem(QString::number(allStudents[i].sage)));
            ui->displayStuTable->item(row,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,4,new QTableWidgetItem(allStudents[i].sadd));
            ui->displayStuTable->item(row,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,5,new QTableWidgetItem(pol));
            ui->displayStuTable->item(row,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,6,new QTableWidgetItem(allStudents[i].stime));
            ui->displayStuTable->item(row,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            ui->displayStuTable->setItem(row,7,new QTableWidgetItem(allStudents[i].stel));
            ui->displayStuTable->item(row,7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignCenter);
            row++;
        }
    }
}
