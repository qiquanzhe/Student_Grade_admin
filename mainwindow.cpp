#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //隐藏窗口边框
    setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle("学生成绩管理系统");

    //窗口背景图片
    setAutoFillBackground(true);
    QPalette pal=this->palette();
    QPixmap *pixmap = new QPixmap(":/image/bg.jpg");
    pal.setBrush(backgroundRole(),pixmap->scaled(380,240,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setPalette(pal);

    //窗口居中
    mLocation = this->geometry();
    mDrag = false;

    //添加用户账号标志
    idLabel = new QLabel(ui->widget);
    idLabel->setGeometry(rect().x()+75,rect().y()+30,32,32);
    QPixmap *idPix = new QPixmap(":/image/id.png");
    idPix->scaled(idLabel->size(),Qt::KeepAspectRatio);
    idLabel->setScaledContents(true);
    idLabel->setPixmap(*idPix);

    //添加用户账号输入框
    idInput = new QLineEdit(ui->widget);
    idInput->setGeometry(rect().x()+115,rect().y()+32,175,30);
    idInput->setFont(QFont("Cosmical disfase",10,QFont::Normal));

    //添加密码标志
    pwdLabel = new QLabel(ui->widget);
    pwdLabel->setGeometry(rect().x()+75,rect().y()+80,32,32);
    QPixmap *pwdPix = new QPixmap(":/image/password4.png");
    pwdPix->scaled(pwdLabel->size(),Qt::KeepAspectRatio);
    pwdLabel->setScaledContents(true);
    pwdLabel->setPixmap(*pwdPix);

    //添加密码输入框
    pwdInput = new QLineEdit(ui->widget);
    pwdInput->setGeometry(rect().x()+115,rect().y()+80,175,30);
    pwdInput->setFont(QFont("Cosmical disfase",10,QFont::Normal));
    pwdInput->setEchoMode(QLineEdit::Password);

    //添加登录按钮
    loginButton = new QPushButton(ui->widget);
    loginButton->setText("登\t录");
    loginButton->setFont(QFont("华文新魏",16,QFont::Bold));
    loginButton->setGeometry(rect().x()+115,rect().y()+130,160,30);

    //显示当前时间
    timeLabel = new QLabel(ui->widget);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    QPalette color;
    color.setColor(QPalette::WindowText,Qt::white);
    timeLabel->setPalette(color);
    timeLabel->setFont(QFont("华文楷体",10,QFont::Bold));
    timeLabel->setGeometry(rect().x()+200,rect().y()+190,180,20);


    QString btnStyle2 =
            "QPushButton{\
                color: rgb(255, 255, 255);\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(166,164,208), stop:0.3 rgb(171,152,230), stop:1 rgb(152,140,220));\
                border:1px;\
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px;  \
            }\
            QPushButton:hover{\
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(130,120,226), stop:0.3 rgb(120,130,230), stop:1 rgb(125,140,226));\
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }\
            QPushButton:pressed{    \
                color: rgb(255, 255, 255); \
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240,156,121), stop:0.3 rgb(220,160,140), stop:1 rgb(230,140,120));  \
                border:1px;  \
                border-radius:5px; /*border-radius控制圆角大小*/\
                padding:2px 4px; \
            }";
    loginButton->setStyleSheet(btnStyle2);


    //自定义按钮
    //ui->widgetTitle->installEventFilter(this);
    ui->btnMin->setIcon(QIcon(":/image/min.png"));
    ui->btnExit->setIcon(QIcon(":/image/exit.png"));

    connect(loginButton,SIGNAL(clicked()),this,SLOT(on_loginButton_clicked()));

    dbo = new DBoperate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
    if (e->button() == Qt::LeftButton)
    {
        mDrag = true;
        mDragPos = e->globalPos() - pos();
        e->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
    if (mDrag && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - mDragPos);
        e->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
    mDrag = false;
}

void MainWindow::on_btnMin_clicked()
{
    showMinimized();
}

void MainWindow::on_loginButton_clicked()
{
    //qDebug()<<"login";
    QString id = idInput->text();
    QString pwd = pwdInput->text();
    bool flag = true;
    if(id.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入用户名");
        return;
    }
    if(pwd.length() == 0)
    {
        QMessageBox::information(this,"Error","请输入密码");
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

    if(!flag)
    {
        QMessageBox::information(this,"Error","账号中包含数字字符!");
        idInput->setText("");
        pwdInput->setText("");
        return;
    }

    if(dbo->loginSystem(id,pwd)==0)
    {
        QMessageBox::information(this,"Error","账号或密码错误！");
        idInput->setText("");
        pwdInput->setText("");
        return;
    }
    DetailsWindow *dw = new DetailsWindow(this,id);
    this->close();
    dw->show();
}


void MainWindow::on_btnExit_clicked()
{
    qApp->exit();
}

void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy/MM/dd hh:mm:ss dddd");
    timeLabel->setText(str);
}
