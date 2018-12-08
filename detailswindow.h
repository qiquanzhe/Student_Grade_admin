#ifndef DETAILSWINDOW_H
#define DETAILSWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "dboperate.h"
#include <QMessageBox>
#include "course.h"
#include "student.h"
#include "grade.h"

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetailsWindow(QWidget *parent = nullptr,QString id="");
    ~DetailsWindow();

private:
    Ui::DetailsWindow *ui;
    DBoperate *dbo;
    QString currentUser;
    course courseToDelete;
    student studentToDelete;
private slots:
    //添加用户的按钮
    void on_addbtn_clicked();
    void on_canceladdbtn_clicked();

    //修改密码的按钮
    void on_modbtn_clicked();
    void on_cancelmodbtn_clicked();

    //管理课程的按钮事件
    //添加课程
    void on_addCbtn_clicked();
    void on_resetCaddbtn_clicked();

    //删除课程
    void on_delCourseFindBtn_clicked();
    void on_delCbtn_clicked();
    void on_resetCdelbtn_clicked();

    //修改课程
    void on_modCbtn_clicked();
    void on_resetCmodbtn_clicked();

    //查找课程
    void on_findCbtn_clicked();
    void on_resetCfindbtn_clicked();

    //遍历课程
    void on_displayCourseRefreshBtn_clicked();

    //管理成绩的事件
    //添加成绩
    void on_addGradeBtn_clicked();
    void on_resetGradeaddBtn_clicked();

    //删除成绩
    void on_delGradeFindBtn_clicked();
    void on_delGradeBtn_clicked();
    void on_resetDelGradeBtn_clicked();

    //修改成绩
    void on_modGradeBtn_clicked();
    void on_resetModGradeBtn_clicked();

    //查询成绩
    void on_findGradeBtn_clicked();
    void on_resetFindGradeBtn_clicked();

    //遍历成绩
    void on_displayGradeRefreshBtn_clicked();

    //管理学生
    //添加学生
    void on_addStuBtn_clicked();
    void on_resetAddStuBtn_clicked();

    //删除学生
    void on_delStuFindBtn_clicked();
    void on_delStuBtn_clicked();
    void on_resetDelStuBtn_clicked();

    //修改学生
    void on_modStuBtn_clicked();
    void on_modStuContentSelect_currentIndexChanged();
    void on_resetModStuBtn_clicked();

    //查询学生
    void on_findStuBtn_clicked();
    void on_resetFindStuBtn_clicked();

    //遍历学生
    void on_diplayStuRefreshBtn_clicked();
};

#endif // DETAILSWINDOW_H
