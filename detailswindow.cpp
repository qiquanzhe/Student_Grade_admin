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
        QMessageBox::information(this,"goodNews","添加成功");
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
        QMessageBox::information(this,"Error","请输入要删除的课程号");
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
        QMessageBox::information(this,"Error","请输入要删除的课程号");
        return;
    }
    else if(cname == "")
    {
        QMessageBox::information(this,"Error","请输入要删除的课程名");
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
        qDebug()<<"进来了。";
        int row = ui->displayCTable->rowCount();
        qDebug()<<dbo->courseSize;
        for(int i = 0;i < dbo->courseSize;i++)
        {
            qDebug()<<row;
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
void DetailsWindow:: on_addGradeBtn_clicked(){}
void DetailsWindow:: on_resetGradeaddBtn_clicked(){}

//删除成绩
void DetailsWindow:: on_delGradeFindBtn_clicked(){}
void DetailsWindow:: on_delGradeBtn_clicked(){}
void DetailsWindow:: on_resetDelGradeBtn_clicked(){}

//修改成绩
void DetailsWindow:: on_modGradeBtn_clicked(){}
void DetailsWindow:: on_resetModGradeBtn_clicked(){}

//查询成绩
void DetailsWindow:: on_findGradeBtn_clicked(){}
void DetailsWindow:: on_resetFindGradeBtn_clicked(){}

//遍历成绩
void DetailsWindow:: on_displayGradeRefreshBtn_clicked(){}

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
void DetailsWindow:: on_delStuFindBtn_clicked(){}
void DetailsWindow:: on_delStuBtn_clicked(){}
void DetailsWindow:: on_resetDelStuBtn_clicked(){}

//修改学生
void DetailsWindow:: on_modStuBtn_clicked(){}
void DetailsWindow:: on_resetModStuBtn_clicked(){}

//查询学生
void DetailsWindow:: on_findStuBtn_clicked(){}
void DetailsWindow:: on_resetFindStuBtn_clicked(){}

//遍历学生
void DetailsWindow:: on_diplayStuRefreshBtn_clicked(){}
