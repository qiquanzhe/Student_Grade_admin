+ ##### student grade,简写sg数据库
```
create database sg;
```


+ ##### users表，用于登录
```
create table users(
	id varchar(20) primary key,
	password varchar(20)
);
```

+ ##### students表，记录学生信息
```
create table students(
	sno varchar(20) primary key,
	sname varchar(20),
	ssex varchar(10),
	sage int,
	sadd varchar(50),
	spol int,
	stime date,
	stel varchar(20)
);
```

+ ##### courses表，记录课程信息
```
create table courses(
	cno varchar(20) primary key,
	cteacher varchar(20),
	cname varchar(25),
	ccredit int
);
```

+ ##### grade表，记录学生成绩
```
create table grade(
	sno varchar(20) not null,
	cno varchar(20) not null,
	grade double(5,2)
);
```

+ ##### 设置外键
```
alter table grade add constraint fk_students foreign key(sno) references students(sno);
alter table grade add constraint fk_courses foreign key(cno) references courses(cno);
```

****
#### 各个界面中的控件名称，类型，作用 ，取值

1. ## 登录界面(mainwindow.ui)
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| idLabel | QLabel | 显示账号标志 |
	| pwdLabel | QLabel | 显示密码标志|
	| idInput | QLineEdit | 用于输入账号|
	| pwdInput | QLineEdit | 用于输入密码|
	| loginButton | QPushButton | 用于登录 |
	| timelabel | QLabel | 用于显示时间|

2. ## 添加用户界面(detailwindow.ui)
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| idTipLabel | QLabel | 用于提示输入用户名|
	| pwdLabel | QLabel | 用于提示输入密码 |
	| pwdAgainLabel| QLabel | 用于提示再次输入密码 |
	| idEdit | QLineEdit | 用于输入用户名 |
	| pwdEdit | QLineEdit | 用于输入密码 |
	| pwdAgainEdit | QLineEdit | 用于再次输入密码|
	| addbtn | QPushButton | 用于确认添加用户|
	 | canceladdbtn | QPushButton | 用于取消添加用户|

3. ## 修改密码界面(detailwindow.ui)
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| oldPwdLabel | QLabel |用于提示输入旧密码 |
	| newPwdLabel | QLabel | 用于提示输入新密码 |
	| newPwdAgainLabel | QLabel |用于提示再次输入新密码|
	| modOldPwdInput | QLineEdit | 用于输入旧密码 |
	| modNewPwdInput | QLineEdit | 用于输入新密码 |
	| modNewAgainPwdInput | QLineEdit| 用于再次输入新密码|
	| modbtn | QPushButton | 用于修改密码|
	| cancelmodbtn | QPushbutton | 用于取消修改密码 |

4. ## 管理课程界面(detailwindow.ui)
	* ### 添加课程界面

	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| addCbtn | QPushButton | 用于添加课程|
	| addCnoInput | QLineEdit | 用于输入新课程号|
	| addCnoLabel | QLabel | 用于提示输入课程号|
	| addTeaInput| QLineEdit| 用于输入授课教师|
	| addTeaLabel | QLabel | 用于提示输入授课教师|
	| addCnameLabel | QLabel | 用于提示输入课程名称|
	| addCnameInput | QLineEdit | 用于输入课程名称 |
	| addCreInput | QlineEdit | 用于输入课程学分（限制整数）|
	| resetCaddbtn | QPushButton | 用于重置输入|

	* ### 删除课程界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| delCbtn | QPushButton | 用于删除课程（默认禁用) |
	| delCourseFindBtn |QPushButton | 用于删除课程之前的查询和确认|
	| delShowTable | QTabelWidget | 用于展示查询结果|
	| delCnoInput | QLineEdit | 用于输入课程编号|
	| delCnoLabel | QLabel | 用于提示输入课程编号|
	| delCnameInput | QLineEdit | 用于输入课程名称 |
	| delCnameLabel | QLabel | 用于提示输入课程名称|
	| resetCdelbtn | QPushButton | 用于重置输入状态|

	* ### 修改课程界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| modCnoInput | QLineEdit | 用于输入课程编号|
	| modCnoLabel | QLabel | 用于提示输入课程编号|
	| modContentLabel| QLabel | 用于提示选择修改内容|
	| modNewContentInput | QLineEdit | 用于输入修改内容| 
	| modNewContentLabel | QLineEdit | 用于提示输入修改内容
	| modCbtn | QPushButton | 用于修改课程|
	| resetCmodbtn | QPushButton | 用于重置输入状态|

	* ### 查询课程界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| findCbtn | QPushButton | 用于查找课程 |
	| findShowTable | QTableWidget | 用于展示查找结果 |
	| findCnoInput | QLineEdit | 用于输入查找的课程编号|
	| findCnoLabel | QLabel | 用于提示输入课程编号|
	| findCnameInput | QLineEdit | 用于输入课程名称|
	| findCnameLabel | QLabel | 用于提示输入课程名称|
	| resetCfindbtn | QPushButton | 用于重置查询的输入和结果|

	* ### 遍历课程界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| displayCTable | QTableWidget | 用于显示遍历结果|
	| displayCourseRefreshBtn| QPushButton | 用于初始化和刷新表|

5. ## 管理成绩界面(detailwindow.ui)

	* ### 添加成绩界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| addGradeSnoInput | QLineEdit | 用于输入学号|
	| addGradeSnoLabel | QLabel | 用于提示输入学号|
	| addGradeCnoInput | QLineEdit | 用于输入课程编号|
	| addGradeCnoLabel | QLabel | 用于提示输入课程编号|
	| addGradeBtn | QPushButton | 用于添加成绩| 
	| addGradeGradeInput | QLineEdit | 用于输入成绩|
	| addGradeGradeLabel | QLabel | 用于提示输入成绩|
	| resetGradeaddBtn | QPushButton | 用于重置输入|

	* ### 删除成绩界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| delGradeBtn | QPushButton | 用于删除成绩|
	| delGradeDisplayTable | QTableWidget | 用于展示查询结果|
	| delGradeFindBtn | QPushButton | 用于查询和确认|
	| delGradeSnoInput| QLineEdit | 用于输入学号|
	| delGradeSnoLabel| QLabel | 用于提示输入学号|
	| delGradeCnoInput | QLineEdit | 用于输入课程编号|
	| delGradeCnoLabel | QLabel | 用于提示删除课程编号|
	| resetDelGradeBtn | QPushButton | 用于重置输入和查询|

	* ### 修改成绩界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| modGradeSnoInput | QLineEdit | 用于输入学号|
	| modGradeSnoLabel | QLabel | 用于提示输入学号|
	| modGradeCnoInput | QLineEdit | 用于输入课程编号|
	| modGradeCnoLabel | QLabel | 用于提示输入课程编号|
	| modGradeNewGradeInput | QLineEdit | 用于输入新的成绩|
	| modGradeNewGradeLabel | QLabel | 用于提示输入新的成绩|
	| modGradeBtn | QPushButton | 用于修改成绩|
	| resetModGradeBtn | QPushButton | 用于重置输入|

	* ### 查询成绩界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| findGradeBtn | QPushButton | 用于查询|
	| findGradeTable | QTableWidget | 用于展示查询结果|
	| findGradeSnoInput | QLineEdit | 用于输入学号|
	| findGradeSnoLabel | QLabel | 用于提示输入学号|
	| findGradeCnoInput | QLineEdit | 用于输入课程编号|
	| findGradeCnoLabel | QLabel | 用于提示输入课程编号|
	| resetFindGradeBtn | QPushButton | 用于重置查询输入|

	* ### 遍历成绩界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| displayGradeRefreshBtn | QPushButton | 用于刷新展示|
	| displayGradeTable |　QTableWidget | 用于展示遍历|

6. ## 管理学生界面(detailwindow.ui)

	* ### 添加学生界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| addStuBtn | QPushButton | 用于添加学生|
	| addStuSaddInput | QLineEdit | 用于输入地址 | 
	| addStuSaddLabel | QLabel | 用于提示输入地址|
	| addStuSnoInput | QLineEdit | 用于输入学号 |
	| addStuSnoLabel | QLabel | 用于提示输入学号|
	| addStuSnameInput | QLineEdit |用于输入姓名|
	| addStuSnameLabel | QLabel | 用于提示输入姓名|
	| addStuSpolCombo | QComboBox | 用于选择政治面貌|
	| addStuSpolLabel | QLabel | 用于提示选择政治面貌|
	| addStuSexComboBox | QComboBox | 用于选择性别 |
	| addStuSsexLabel | QLabel | 用于提示选择性别|
	| addStuStimeDate | QDateEdit | 用于选择入学日期|
	| addStuStimeLabel | QLabel | 用于提示选择日期|
	| addStuSageInput | QLineEdit | 用于输入年龄|
	| addStuSageLabel | QLabel | 用于提示输入年龄|
	| addStuStelInput | QLineEdit |用于输入电话|
	| addStuStelLabel | QLabel | 用于提示输入电话|
	| resetAddStuBtn | QPushButton | 用于重置输入|

	* ### 删除学生界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| delStuBtn | QPushButton | 用于删除学生|
	| delStuFindBtn | QPushButton | 用于删除之前的查询|
	| delStuFindTable | QTabelWidget | 用于展示删除之前的查询|
	| delStuSnoInput | QLineEdit | 用于输入学号|
	| delStuSnoLabel | QLabel | 用于提示输入学号|
	| resetDelStuBtn | QPushButton | 用于重置删除输入|

	* ### 修改学生界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| modStuSnoInput | QLineEdit | 用于输入学号|
	| modStuSnoLabel | QLabel | 用于提示输入学号|
	| modStuContentLabel | QLabel | 用于提示选择修改内容|
	| modStuContentSelect | QComboBox | 用于选择修改内容|
	| modStuContentInput | QLineEdit | 用于输入修改后的内容|
	| modStuInputLabel | QLabel | 用于提示输入修改的内容|
	| modStuContentCombo | QComboBox | 用于修改政治面貌时（默认禁用）|
	| modStuSelectLabel | QLabel | 用于提示选择政治面貌|

	* ### 查询学生界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| findStuBtn | QPushButton | 用于查询|
	| findStuTable |　QTableWidget | 用于展示查询|
	| findStuConditionCombo | QComboBox | 用于选择查询条件|
	| findStuConditionLabel | QLabel | 用于提示选择查询条件|
	| findStuContentInput | QLineEdit | 用于输入查询内容|
	| findStuContentLabel | QLabel | 用于提示输入查询内容|
	| resetFindStuBtn | QPushButton | 用于重置查询内容|

	* ### 遍历学生界面
	| 控件名 | 控件类型 | 描述 | 
	|:-:|:-:|:-:|
	| displayStuRefreshBtn| QPushButton | 用于刷新表中数据|
	| displayStuTable | QTableWidget | 用于展示遍历表|
