#include "window2.h"
#include "ui_window2.h"
#include "mainwindow.h"
#include <QMessageBox>


Window2::Window2(MainWindow *mainWindow,QWidget *parent)
    :mainWindow(mainWindow),QMainWindow(parent),ui(new Ui::Window2)
{
    ui->setupUi(this);
    triangle01=new Triangle(310, 174, 50, 43, QColor(0xFF, 0x00, 0x00), ui->centralwidget);
    triangle02=new Triangle(770, 174, 50, 43, QColor(0xFF, 0xD7, 0x00), ui->centralwidget);
    triangle03=new Triangle(310, 554, 50, 43, QColor(0x2E, 0x8B, 0x57), ui->centralwidget);
    triangle04=new Triangle(770, 554, 50, 43, QColor(0x1E, 0x90, 0xFF), ui->centralwidget);
    triangle01->show();
    triangle02->show();
    triangle03->show();
    triangle04->show();

    const QStringList T1_ButtonNames =
    {   "Red_Button01", "Red_Button02", "Red_Button03","Red_Button04","Red_Button05","Red_Button06", "Red_Button07", "Red_Button08","Red_Button09","Red_Button10",
        "Red_Button11", "Red_Button12", "Red_Button13","Red_Button14","Red_Button15","Red_Button16", "Red_Button17", "Red_Button18","Red_Button19","Red_Button20",
        "Red_Button21", "Red_Button22", "Red_Button23","Red_Button24","Red_Button25","Green_Button01", "Green_Button02", "Green_Button03","Green_Button04","Green_Button05",
        "Green_Button06", "Green_Button07", "Green_Button08","Green_Button09","Green_Button10","Green_Button11", "Green_Button12", "Green_Button13","Green_Button14","Green_Button15",
        "Green_Button16", "Green_Button17", "Green_Button18","Green_Button19","Green_Button20","Green_Button21", "Green_Button22", "Green_Button23","Green_Button24","Green_Button25"
    };
    const QStringList T2_ButtonNames =
    {   "Yellow_Button01", "Yellow_Button02", "Yellow_Button03","Yellow_Button04","Yellow_Button05","Yellow_Button06", "Yellow_Button07", "Yellow_Button08","Yellow_Button09","Yellow_Button10",
        "Yellow_Button11", "Yellow_Button12", "Yellow_Button13","Yellow_Button14","Yellow_Button15","Yellow_Button16", "Yellow_Button17", "Yellow_Button18","Yellow_Button19","Yellow_Button20",
        "Yellow_Button21", "Yellow_Button22", "Yellow_Button23","Yellow_Button24","Yellow_Button25","Blue_Button01", "Blue_Button02", "Blue_Button03","Blue_Button04","Blue_Button05",
        "Blue_Button06", "Blue_Button07", "Blue_Button08","Blue_Button09","Blue_Button10","Blue_Button11", "Blue_Button12", "Blue_Button13","Blue_Button14","Blue_Button15",
        "Blue_Button16", "Blue_Button17", "Blue_Button18","Blue_Button19","Blue_Button20","Blue_Button21", "Blue_Button22", "Blue_Button23","Blue_Button24","Blue_Button25"
    };
    for(int8_t i=0;i<2*BUTTON_NUM;i++)
    {
        T1[i]=this->findChild<QPushButton*>(T1_ButtonNames[i]);
        T2[i]=this->findChild<QPushButton*>(T2_ButtonNames[i]);
    }
    for(int8_t i=0;i<PLAYER_NUM;i++)
    {
        for(int8_t j=0;j<BUTTON_NUM+1;j++)
        {
            //全部初始化为true
            shot[i][j]=true;
        }
    }

}

Window2::~Window2()
{
    delete ui;
}

void Window2::Team1_Button_clicked(const int8_t n)
{
    Compare_statu.Team1_selected_button_idx=n;
    for(int8_t i=0;i<2*BUTTON_NUM;i++)
    {
        if(i!=n)
            T1[i]->setStyleSheet(QString());
        else if(i==n &&i<BUTTON_NUM)
        {
            T1[i]->setStyleSheet(BUTTON_COLOR[0]);
            Compare_statu.Team1_player_idx=0;
            Compare_statu.Team1_qizi_int=mainWindow->get_int(Compare_statu.Team1_player_idx,n);
        }
        else if(i==n &&i>=BUTTON_NUM)
        {
            T1[i]->setStyleSheet(BUTTON_COLOR[2]);
            Compare_statu.Team1_player_idx=2;
            Compare_statu.Team1_qizi_int=mainWindow->get_int(Compare_statu.Team1_player_idx,n-BUTTON_NUM);
        }
    }
}

void Window2::Team2_Button_clicked(const int8_t n)
{
    Compare_statu.Team2_selected_button_idx=n;
    for(int8_t i=0;i<2*BUTTON_NUM;i++)
    {
        if(i!=n)
            T2[i]->setStyleSheet(QString());
        else if(i==n &&i<BUTTON_NUM)
        {
            T2[i]->setStyleSheet(BUTTON_COLOR[1]);
            Compare_statu.Team2_player_idx=1;
            Compare_statu.Team2_qizi_int=mainWindow->get_int(Compare_statu.Team2_player_idx,n);
        }
        else if(i==n &&i>=BUTTON_NUM)
        {
            T2[i]->setStyleSheet(BUTTON_COLOR[3]);
            Compare_statu.Team2_player_idx=3;
            Compare_statu.Team2_qizi_int=mainWindow->get_int(Compare_statu.Team2_player_idx,n-BUTTON_NUM);
        }
    }
}


void Window2::on_Compare_Button_clicked()
{
    if(T1[Compare_statu.Team1_selected_button_idx]->isEnabled() && T2[Compare_statu.Team2_selected_button_idx]->isEnabled())
    {
        QString re_str=JUNQI_Compare(Compare_statu.Team1_qizi_int,Compare_statu.Team2_qizi_int,PLAYER_NAME[Compare_statu.Team1_player_idx],PLAYER_NAME[Compare_statu.Team2_player_idx]);
        ui->textEdit->setText(re_str);
        if(re_str!="不可能事件")
            Compare_history.push_back(Compare_statu);
    }
    else
    {
        QMessageBox::warning(NULL,"警告","所选的棋子已经阵亡");
    }
}

QString Window2::Show_History()
{
    QString tempStr=NULL;
    const static QString re[12][12]=
    {
        { "?","=","?","<","<","<","<", "<", "<", "<", "<", "<" },
        { "=","=","=","=","=","=","=", "=" ,"=","=" ,"=","=" },
        { "?","=","?","<",">",">",">", ">", ">", ">", ">", ">"},
        { ">","=",">","=","<","<","<", "<" , "<", "<" , "<", "<" },
        { ">","=","<",">","=","<","<", "<" , "<", "<" , "<", "<"},
        { ">","=","<",">",">","=","<", "<" , "<", "<" , "<", "<"},
        { ">","=","<",">",">",">","=", "<" , "<", "<" , "<", "<"},
        { ">","=","<",">",">",">",">", "=" , "<", "<" , "<", "<"},
        { ">","=","<",">",">",">",">", ">" , "=", "<" , "<", "<"},
        { ">","=","<",">",">",">",">", ">" , ">", "=" , "<", "<"},
        { ">","=","<",">",">",">",">", ">" , ">", ">" , "=", "<"},
        { ">","=","<",">",">",">",">", ">" , ">", ">" , ">", "="}
    };
    for(int8_t i=0;i<PLAYER_NUM;i++)
    {
        for(int8_t j=0;j<BUTTON_NUM;j++)
        {
            if(j<=3||j==8||j==10||(j>=15&&j<=18)||(j>=20&&j<=23))
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j));
            }
            else if(j==4||j==7||j==11||j==14||j==19)
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"\n";
            }
            else if(j==24)
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"\n\n";
            }
            else
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"〇";
            }
        }
    }
    //tempStr+='\n';
    for(int i=0;i<Compare_history.size();i++)
    {
        tempStr+=PLAYER_NAME[Compare_history[i].Team1_player_idx];//红色
        tempStr+=LB_CONTENT[Compare_history[i].Team1_selected_button_idx];//1-1
        tempStr+=INT_TO_QI_MAP.at(Compare_history[i].Team1_qizi_int);//师
        tempStr+=re[Compare_history[i].Team1_qizi_int+1][Compare_history[i].Team2_qizi_int+1];// > < =
        tempStr+=PLAYER_NAME[Compare_history[i].Team2_player_idx];//黄色
        tempStr+=LB_CONTENT[Compare_history[i].Team2_selected_button_idx];//1-5
        tempStr+=INT_TO_QI_MAP.at(Compare_history[i].Team2_qizi_int);//营
        tempStr+='\n';
    }
    // QMessageBox::information(NULL,"日志",tempStr);
    ui->textEdit->setText(tempStr);
    return tempStr;
}

QString Window2::JUNQI_Compare(const int8_t& s1,const int8_t& s2,const QString& team_A_name,const QString& team_B_name)
{
    QString r0,r1, r2, r3, r4, r5, r6, r7,r8,r9,r10,r11,r12;
    r0 = "不可能事件";
    r1 = team_A_name + "大";
    r2 = team_B_name + "大";
    r3 = "兑";
    r4 = QString("兑") + "，且" + team_A_name + "司令阵亡，请" + team_A_name + "亮出军旗";
    r5 = QString("兑") + "，且" + team_B_name + "司令阵亡，请" + team_B_name + "亮出军旗";
    r6= QString("兑") + "，且" + team_A_name+"和"+team_B_name + "司令阵亡，请" + team_A_name + "和" + team_B_name + "亮出军旗";
    r7 = QString("兑") + "，且" + team_A_name + "军旗被扛";
    r8=  QString("兑") + "，且" + team_B_name + "军旗被扛";
    r9 = team_A_name + "大，且"+team_B_name+"司令阵亡，请"+team_B_name+"亮出军旗";
    r10 = team_A_name + "大，且" + team_B_name + "军旗被扛";
    r11= team_B_name + "大，且" + team_A_name + "司令阵亡，请" + team_A_name + "亮出军旗";
    r12= team_B_name + "大，且" + team_A_name + "军旗被扛";
    const QString rule[12][12]=
    {
        { r0, r7, r0, r12, r12, r12, r12, r12, r12, r12, r12, r12 },
        { r8, r3, r3, r3, r3, r3, r3, r3, r3, r3, r3, r5 },
        { r0, r3, r0, r2, r1, r1, r1, r1, r1, r1, r1, r9 },
        { r10, r3, r1, r3, r2, r2, r2, r2, r2, r2, r2, r2 },
        { r10, r3, r2, r1, r3, r2, r2, r2, r2, r2, r2, r2 },
        { r10, r3, r2, r1, r1, r3, r2, r2, r2, r2, r2, r2 },
        { r10, r3, r2, r1, r1, r1, r3, r2, r2, r2, r2, r2 },
        { r10, r3, r2, r1, r1, r1, r1, r3, r2, r2, r2, r2 },
        { r10, r3, r2, r1, r1, r1, r1, r1, r3, r2, r2, r2 },
        { r10, r3, r2, r1, r1, r1, r1, r1, r1, r3, r2, r2 },
        { r10, r3, r2, r1, r1, r1, r1, r1, r1, r1, r3, r2 },
        { r10, r4, r11, r1, r1, r1, r1, r1, r1, r1, r1, r6 }
    };
    const int8_t rule_idx[12][12]=
    {
        {1,3,1,4,4,4,4,4,4,4,4,4},
        {2,11,11,11,11,11,11,11,11,11,11,7},
        {1,11,1,13,12,12,12,12,12,12,12,9},
        {5,11,12,11,13,13,13,13,13,13,13,13},
        {5,11,13,12,11,13,13,13,13,13,13,13},
        {5,11,13,12,12,11,13,13,13,13,13,13},
        {5,11,13,12,12,12,11,13,13,13,13,13},
        {5,11,13,12,12,12,12,11,13,13,13,13},
        {5,11,13,12,12,12,12,12,11,13,13,13},
        {5,11,13,12,12,12,12,12,12,11,13,13},
        {5,11,13,12,12,12,12,12,12,12,11,13},
        {5,6,8,12,12,12,12,12,12,12,12,10}
    };
    /*序号	操作
        1	error
        2	左灰显，右全灰
        3	右灰显，左全灰
        4	左全灰
        5	右全灰
        6	兑，左亮旗
        7	兑，右亮旗
        8	左灰显，左亮旗
        9	右灰显，右亮旗
        10	左右灰显，左右亮旗
        11	兑（左右灰显）
        12	>（右灰显）
        13	<（左灰显）
    */
    if(ui->Team1_is_bing->isChecked()&&Compare_statu.Team1_qizi_int!=2)
        return r0;
    if(ui->Team2_is_bing->isChecked()&&Compare_statu.Team2_qizi_int!=2)
        return r0;
    if(ui->Team1_is_lei->isChecked()&&Compare_statu.Team1_qizi_int==1)
        return r0;
    if(ui->Team2_is_lei->isChecked()&&Compare_statu.Team2_qizi_int==1)
        return r0;
    switch (rule_idx[s1+1][s2+1])
    {
    case 1:
        //QMessageBox::warning(NULL,"警告","不可能事件");
        break;
    case 2:
        Left_gray();
        Team2_died();
        break;
    case 3:
        Right_gray();
        Team1_died();
        break;
    case 4:
        Team1_died();
        break;
    case 5:
        Team2_died();
        break;
    case 6:
        Left_gray();
        Right_gray();
        Left_Show_JunQi();
        break;
    case 7:
        Left_gray();
        Right_gray();
        Right_Show_JunQi();
        break;
    case 8:
        Left_gray();
        Left_Show_JunQi();
        break;
    case 9:
        Right_gray();
        Right_Show_JunQi();
        break;
    case 10:
        Left_gray();
        Right_gray();
        Left_Show_JunQi();
        Right_Show_JunQi();
        break;
    case 11:
        Left_gray();
        Right_gray();
        break;
    case 12:
        Right_gray();
        break;
    case 13:
        Left_gray();
        break;
    }
    ui->Team1_is_bing->setChecked(false);
    ui->Team2_is_bing->setChecked(false);
    ui->Team1_is_lei->setChecked(false);
    ui->Team2_is_lei->setChecked(false);
    return rule[s1 + 1][s2 + 1];
}

void Window2::Left_Show_JunQi()
{
    //当前选中的Team1玩家司令阵亡，军旗亮出
    if(Compare_statu.Team1_selected_button_idx<25)
    {
        if(mainWindow->get_int(0,21)==-1)
            T1[21]->setText("旗");
        else if(mainWindow->get_int(0,23)==-1)
            T1[23]->setText("旗");
    }
    else
    {
        if(mainWindow->get_int(2,21)==-1)
            T1[46]->setText("旗");
        else if(mainWindow->get_int(2,23)==-1)
            T1[48]->setText("旗");
    }
}

void Window2::Right_Show_JunQi()
{
    //当前选中的Team2玩家司令阵亡，军旗亮出
    if(Compare_statu.Team2_selected_button_idx<25)
    {
        if(mainWindow->get_int(1,21)==-1)
            T2[21]->setText("旗");
        else if(mainWindow->get_int(1,23)==-1)
            T2[23]->setText("旗");
    }
    else
    {
        if(mainWindow->get_int(3,21)==-1)
            T2[46]->setText("旗");
        else if(mainWindow->get_int(3,23)==-1)
            T2[48]->setText("旗");
    }
}

void Window2::Team1_died()
{
    //当前选中的Team1玩家被抗军旗，所有棋子灰显并清空该玩家对应所有按钮的文本
    if(Compare_statu.Team1_player_idx==0)
    {
        shot[Compare_statu.Team1_player_idx][BUTTON_NUM]=!(T1[21]->text()=="旗" || T1[23]->text()=="旗");
        for(int8_t i=0;i<BUTTON_NUM;i++)
        {
            shot[Compare_statu.Team1_player_idx][i]=T1[i]->isEnabled();//保存临走前的按钮状态，以供撤销时恢复使用
            T1[i]->setEnabled(false);
            T1[i]->setText(NULL);
        }
        triangle01->hide();
    }
    else if(Compare_statu.Team1_player_idx==2)
    {
        shot[Compare_statu.Team1_player_idx][BUTTON_NUM]=!(T1[46]->text()=="旗" || T1[48]->text()=="旗");
        for(int8_t i=BUTTON_NUM;i<2*BUTTON_NUM;i++)
        {
            shot[Compare_statu.Team1_player_idx][i-BUTTON_NUM]=T1[i]->isEnabled();
            T1[i]->setEnabled(false);
            T1[i]->setText(NULL);
        }
        triangle03->hide();
    }
}


void Window2::Team2_died()
{
    //当前选中的Team2玩家被抗军旗，所有棋子灰显并清空该玩家对应所有按钮的文本
    if(Compare_statu.Team2_player_idx==1)
    {
        shot[Compare_statu.Team2_player_idx][BUTTON_NUM]=!(T2[21]->text()=="旗" || T2[23]->text()=="旗");
        for(int8_t i=0;i<BUTTON_NUM;i++)
        {
            shot[Compare_statu.Team2_player_idx][i]=T2[i]->isEnabled();
            T2[i]->setEnabled(false);
            T2[i]->setText(NULL);
        }
        triangle02->hide();
    }
    else if(Compare_statu.Team2_player_idx==3)
    {
        shot[Compare_statu.Team2_player_idx][BUTTON_NUM]=!(T2[46]->text()=="旗" || T2[48]->text()=="旗");
        for(int8_t i=BUTTON_NUM;i<2*BUTTON_NUM;i++)
        {
            shot[Compare_statu.Team2_player_idx][i-BUTTON_NUM]=T2[i]->isEnabled();
            T2[i]->setEnabled(false);
            T2[i]->setText(NULL);
        }
        triangle04->hide();
    }
}

void Window2::Left_gray()
{
    //左侧Team1当前选中按钮灰显，按钮上的文本清空
    T1[Compare_statu.Team1_selected_button_idx]->setEnabled(false);
    T1[Compare_statu.Team1_selected_button_idx]->setText(NULL);
}

void Window2::Right_gray()
{
    //右侧Team2当前选中按钮灰显，按钮上的文本清空
    T2[Compare_statu.Team2_selected_button_idx]->setEnabled(false);
    T2[Compare_statu.Team2_selected_button_idx]->setText(NULL);
}


void Window2::on_History_Button_clicked()
{
    QString tempStr=NULL;
    const static QString re[12][12]=
        {
            { "?","=","?","<","<","<","<", "<", "<", "<", "<", "<" },
            { "=","=","=","=","=","=","=", "=" ,"=","=" ,"=","=" },
            { "?","=","?","<",">",">",">", ">", ">", ">", ">", ">"},
            { ">","=",">","=","<","<","<", "<" , "<", "<" , "<", "<" },
            { ">","=","<",">","=","<","<", "<" , "<", "<" , "<", "<"},
            { ">","=","<",">",">","=","<", "<" , "<", "<" , "<", "<"},
            { ">","=","<",">",">",">","=", "<" , "<", "<" , "<", "<"},
            { ">","=","<",">",">",">",">", "=" , "<", "<" , "<", "<"},
            { ">","=","<",">",">",">",">", ">" , "=", "<" , "<", "<"},
            { ">","=","<",">",">",">",">", ">" , ">", "=" , "<", "<"},
            { ">","=","<",">",">",">",">", ">" , ">", ">" , "=", "<"},
            { ">","=","<",">",">",">",">", ">" , ">", ">" , ">", "="}
        };
    for(int8_t i=0;i<PLAYER_NUM;i++)
    {
        for(int8_t j=0;j<BUTTON_NUM;j++)
        {
            if(j<=3||j==8||j==10||(j>=15&&j<=18)||(j>=20&&j<=23))
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j));
            }
            else if(j==4||j==7||j==11||j==14||j==19)
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"\n";
            }
            else if(j==24)
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"\n\n";
            }
            else
            {
                tempStr+=INT_TO_QI_MAP.at(mainWindow->get_int(i,j))+"〇";
            }
        }
    }
    for(int i=0;i<Compare_history.size();i++)
    {
        tempStr+="第"+QString::number(i+1)+"次碰撞：";
        tempStr+=PLAYER_NAME[Compare_history[i].Team1_player_idx];//红色
        if(Compare_history[i].Team1_selected_button_idx<BUTTON_NUM)
            tempStr+=LB_CONTENT[Compare_history[i].Team1_selected_button_idx];//1-1
        else
            tempStr+=LB_CONTENT[Compare_history[i].Team1_selected_button_idx-BUTTON_NUM];
        tempStr+=INT_TO_QI_MAP.at(Compare_history[i].Team1_qizi_int);//师
        tempStr+=re[Compare_history[i].Team1_qizi_int+1][Compare_history[i].Team2_qizi_int+1];// > < =
        tempStr+=PLAYER_NAME[Compare_history[i].Team2_player_idx];//黄色
        if(Compare_history[i].Team2_selected_button_idx<BUTTON_NUM)
            tempStr+=LB_CONTENT[Compare_history[i].Team2_selected_button_idx];//1-5
        else
            tempStr+=LB_CONTENT[Compare_history[i].Team2_selected_button_idx-BUTTON_NUM];
        tempStr+=INT_TO_QI_MAP.at(Compare_history[i].Team2_qizi_int);//营
        tempStr+='\n';
    }
    // QMessageBox::information(NULL,"日志",tempStr);
    ui->textEdit->setText(tempStr);
}


void Window2::on_Cancel_Button_clicked()
{
    ui->textEdit->setText("撤销");
    if(Compare_history.size()>0)
    {
        //将上一次碰撞的两个对应的按钮重新激活
        T1[Compare_history.back().Team1_selected_button_idx]->setEnabled(true);
        T2[Compare_history.back().Team2_selected_button_idx]->setEnabled(true);
        //将当前选中的按钮颜色重置
        T1[Compare_statu.Team1_selected_button_idx]->setStyleSheet(QString());
        T2[Compare_statu.Team2_selected_button_idx]->setStyleSheet(QString());
        //将上一次碰撞的两个对应的按钮重新染色
        T1[Compare_history.back().Team1_selected_button_idx]->setStyleSheet(BUTTON_COLOR[Compare_history.back().Team1_player_idx]);
        T2[Compare_history.back().Team2_selected_button_idx]->setStyleSheet(BUTTON_COLOR[Compare_history.back().Team2_player_idx]);
        //恢复上一次碰撞的两个对应的按钮的文字
        if(Compare_history.back().Team1_selected_button_idx<25)
            T1[Compare_history.back().Team1_selected_button_idx]->setText(LB_CONTENT[Compare_history.back().Team1_selected_button_idx]);
        else
            T1[Compare_history.back().Team1_selected_button_idx]->setText(LB_CONTENT[Compare_history.back().Team1_selected_button_idx-BUTTON_NUM]);
        if(Compare_history.back().Team2_selected_button_idx<25)
            T2[Compare_history.back().Team2_selected_button_idx]->setText(LB_CONTENT[Compare_history.back().Team2_selected_button_idx]);
        else
            T2[Compare_history.back().Team2_selected_button_idx]->setText(LB_CONTENT[Compare_history.back().Team2_selected_button_idx-BUTTON_NUM]);

        if(Compare_history.back().Team1_qizi_int==-1)
        {
            //上一步导致Team1的一位玩家死亡，撤销时应恢复其原来的棋子状态
            if(Compare_history.back().Team1_player_idx==0)
            {
                //如果阵亡的是玩家1（红色）
                for(int8_t i=0;i<BUTTON_NUM;i++)
                {
                    if(shot[Compare_history.back().Team1_player_idx][i])
                    {
                        T1[i]->setEnabled(true);
                        T1[i]->setText(LB_CONTENT[i]);
                    }
                    else
                    {
                        T1[i]->setEnabled(false);
                        T1[i]->setText(NULL);
                    }
                }
                if(!shot[Compare_history.back().Team1_player_idx][BUTTON_NUM])
                {
                    if(mainWindow->get_int(0,21)==-1)
                        T1[21]->setText("旗");
                    else if(mainWindow->get_int(0,23)==-1)
                        T1[23]->setText("旗");
                }
                triangle01->show();
            }
            else
            {
                //如果阵亡的是玩家3（绿色）
                for(int8_t i=BUTTON_NUM;i<2*BUTTON_NUM;i++)
                {
                    if(shot[Compare_history.back().Team1_player_idx][i-BUTTON_NUM])
                    {
                        T1[i]->setEnabled(true);
                        T1[i]->setText(LB_CONTENT[i-BUTTON_NUM]);
                    }
                    else
                    {
                        T1[i]->setEnabled(false);
                        T1[i]->setText(NULL);
                    }
                }
                if(!shot[Compare_history.back().Team1_player_idx][BUTTON_NUM])
                {
                    if(mainWindow->get_int(2,21)==-1)
                        T1[46]->setText("旗");
                    else if(mainWindow->get_int(2,23)==-1)
                        T1[48]->setText("旗");
                }
                triangle03->show();
            }
        }
        if(Compare_history.back().Team2_qizi_int==-1)
        {
            //上一步导致Team2的一位玩家死亡，撤销时应恢复其原来的棋子状态
            if(Compare_history.back().Team2_player_idx==1)
            {
                //如果阵亡的是玩家2（黄色）
                for(int8_t i=0;i<BUTTON_NUM;i++)
                {
                    if(shot[Compare_history.back().Team2_player_idx][i])
                    {
                        T2[i]->setEnabled(true);
                        T2[i]->setText(LB_CONTENT[i]);
                    }
                    else
                    {
                        T2[i]->setEnabled(false);
                        T2[i]->setText(NULL);
                    }
                }
                if(!shot[Compare_history.back().Team2_player_idx][BUTTON_NUM])
                {
                    if(mainWindow->get_int(1,21)==-1)
                        T2[21]->setText("旗");
                    else if(mainWindow->get_int(1,23)==-1)
                        T2[23]->setText("旗");
                }
                triangle02->show();
            }
            else
            {
                //如果阵亡的是玩家4（蓝色）
                for(int8_t i=BUTTON_NUM;i<2*BUTTON_NUM;i++)
                {
                    if(shot[Compare_history.back().Team2_player_idx][i-BUTTON_NUM])
                    {
                        T2[i]->setEnabled(true);
                        T2[i]->setText(LB_CONTENT[i-BUTTON_NUM]);
                    }
                    else
                    {
                        T2[i]->setEnabled(false);
                        T2[i]->setText(NULL);
                    }
                }
                if(!shot[Compare_history.back().Team2_player_idx][BUTTON_NUM])
                {
                    if(mainWindow->get_int(3,21)==-1)
                        T2[46]->setText("旗");
                    else if(mainWindow->get_int(3,23)==-1)
                        T2[48]->setText("旗");
                }
                triangle04->show();
            }
        }
        if(Compare_history.back().Team1_qizi_int==10)
        {
            //如果上一个Team1碰的是司
            switch(Compare_history.back().Team2_qizi_int)
            {
            case 10:
                //Team1和Team2兑司令，撤销操作应将两方军旗重新隐藏
                if(Compare_history.back().Team2_player_idx==1)
                {
                    T2[21]->setText(LB_CONTENT[21]);
                    T2[23]->setText(LB_CONTENT[23]);
                }
                else
                {
                    T2[46]->setText(LB_CONTENT[21]);
                    T2[48]->setText(LB_CONTENT[23]);
                }
            case 0:
            case 1:
                //Team2的棋子导致Team1的司令阵亡，撤销操作需要重新隐藏已经暴露的Team1的旗位置
                if(Compare_history.back().Team1_player_idx==0)
                {
                    T1[21]->setText(LB_CONTENT[21]);
                    T1[23]->setText(LB_CONTENT[23]);
                }
                else
                {
                    T1[46]->setText(LB_CONTENT[21]);
                    T1[48]->setText(LB_CONTENT[23]);
                }
            }
        }
        if(Compare_history.back().Team2_qizi_int==10)
        {
            if(Compare_history.back().Team1_qizi_int==0 || Compare_history.back().Team1_qizi_int==1)
            {
                if(Compare_history.back().Team2_player_idx==1)
                {
                    T2[21]->setText(LB_CONTENT[21]);
                    T2[23]->setText(LB_CONTENT[23]);
                }
                else
                {
                    T2[46]->setText(LB_CONTENT[21]);
                    T2[48]->setText(LB_CONTENT[23]);
                }
            }
        }
        //重置当前的Compare_statu与Compare_history.back()相同,这一步以及后边的“删除vector<Butt>Compare_history中的最后一个元素”需要放在最后做。
        Compare_statu.Team1_selected_button_idx=Compare_history.back().Team1_selected_button_idx;
        Compare_statu.Team2_selected_button_idx=Compare_history.back().Team2_selected_button_idx;
        Compare_statu.Team1_player_idx=Compare_history.back().Team1_player_idx;
        Compare_statu.Team2_player_idx=Compare_history.back().Team2_player_idx;
        Compare_statu.Team1_qizi_int=Compare_history.back().Team1_qizi_int;
        Compare_statu.Team2_qizi_int=Compare_history.back().Team2_qizi_int;
        //删除vector<Butt>Compare_history中的最后一个元素
        Compare_history.pop_back();
    }
}


void Window2::on_Red_Button01_clicked()
{
    Team1_Button_clicked(0);
}


void Window2::on_Red_Button02_clicked()
{
    Team1_Button_clicked(1);
}


void Window2::on_Red_Button03_clicked()
{
    Team1_Button_clicked(2);
}


void Window2::on_Red_Button04_clicked()
{
    Team1_Button_clicked(3);
}


void Window2::on_Red_Button05_clicked()
{
    Team1_Button_clicked(4);
}


void Window2::on_Red_Button06_clicked()
{
    Team1_Button_clicked(5);
}


void Window2::on_Red_Button07_clicked()
{
    Team1_Button_clicked(6);
}


void Window2::on_Red_Button08_clicked()
{
    Team1_Button_clicked(7);
}


void Window2::on_Red_Button09_clicked()
{
    Team1_Button_clicked(8);
}


void Window2::on_Red_Button10_clicked()
{
    Team1_Button_clicked(9);
}


void Window2::on_Red_Button11_clicked()
{
    Team1_Button_clicked(10);
}


void Window2::on_Red_Button12_clicked()
{
    Team1_Button_clicked(11);
}


void Window2::on_Red_Button13_clicked()
{
    Team1_Button_clicked(12);
}


void Window2::on_Red_Button14_clicked()
{
    Team1_Button_clicked(13);
}


void Window2::on_Red_Button15_clicked()
{
    Team1_Button_clicked(14);
}


void Window2::on_Red_Button16_clicked()
{
    Team1_Button_clicked(15);
}


void Window2::on_Red_Button17_clicked()
{
    Team1_Button_clicked(16);
}


void Window2::on_Red_Button18_clicked()
{
    Team1_Button_clicked(17);
}


void Window2::on_Red_Button19_clicked()
{
    Team1_Button_clicked(18);
}


void Window2::on_Red_Button20_clicked()
{
    Team1_Button_clicked(19);
}


void Window2::on_Red_Button21_clicked()
{
    Team1_Button_clicked(20);
}


void Window2::on_Red_Button22_clicked()
{
    Team1_Button_clicked(21);
}


void Window2::on_Red_Button23_clicked()
{
    Team1_Button_clicked(22);
}


void Window2::on_Red_Button24_clicked()
{
    Team1_Button_clicked(23);
}


void Window2::on_Red_Button25_clicked()
{
    Team1_Button_clicked(24);
}


void Window2::on_Green_Button01_clicked()
{
    Team1_Button_clicked(25);
}


void Window2::on_Green_Button02_clicked()
{
    Team1_Button_clicked(26);
}


void Window2::on_Green_Button03_clicked()
{
    Team1_Button_clicked(27);
}


void Window2::on_Green_Button04_clicked()
{
    Team1_Button_clicked(28);
}


void Window2::on_Green_Button05_clicked()
{
    Team1_Button_clicked(29);
}

void Window2::on_Green_Button06_clicked()
{
    Team1_Button_clicked(30);
}


void Window2::on_Green_Button07_clicked()
{
    Team1_Button_clicked(31);
}


void Window2::on_Green_Button08_clicked()
{
    Team1_Button_clicked(32);
}


void Window2::on_Green_Button09_clicked()
{
    Team1_Button_clicked(33);
}


void Window2::on_Green_Button10_clicked()
{
    Team1_Button_clicked(34);
}


void Window2::on_Green_Button11_clicked()
{
    Team1_Button_clicked(35);
}


void Window2::on_Green_Button12_clicked()
{
    Team1_Button_clicked(36);
}


void Window2::on_Green_Button13_clicked()
{
    Team1_Button_clicked(37);
}


void Window2::on_Green_Button14_clicked()
{
    Team1_Button_clicked(38);
}


void Window2::on_Green_Button15_clicked()
{
    Team1_Button_clicked(39);
}


void Window2::on_Green_Button16_clicked()
{
    Team1_Button_clicked(40);
}


void Window2::on_Green_Button17_clicked()
{
    Team1_Button_clicked(41);
}


void Window2::on_Green_Button18_clicked()
{
    Team1_Button_clicked(42);
}


void Window2::on_Green_Button19_clicked()
{
    Team1_Button_clicked(43);
}


void Window2::on_Green_Button20_clicked()
{
    Team1_Button_clicked(44);
}


void Window2::on_Green_Button21_clicked()
{
    Team1_Button_clicked(45);
}


void Window2::on_Green_Button22_clicked()
{
    Team1_Button_clicked(46);
}


void Window2::on_Green_Button23_clicked()
{
    Team1_Button_clicked(47);
}


void Window2::on_Green_Button24_clicked()
{
    Team1_Button_clicked(48);
}


void Window2::on_Green_Button25_clicked()
{
    Team1_Button_clicked(49);
}


void Window2::on_Yellow_Button01_clicked()
{
    Team2_Button_clicked(0);
}


void Window2::on_Yellow_Button02_clicked()
{
    Team2_Button_clicked(1);
}


void Window2::on_Yellow_Button03_clicked()
{
    Team2_Button_clicked(2);
}


void Window2::on_Yellow_Button04_clicked()
{
    Team2_Button_clicked(3);
}


void Window2::on_Yellow_Button05_clicked()
{
    Team2_Button_clicked(4);
}

void Window2::on_Yellow_Button06_clicked()
{
    Team2_Button_clicked(5);
}


void Window2::on_Yellow_Button07_clicked()
{
    Team2_Button_clicked(6);
}


void Window2::on_Yellow_Button08_clicked()
{
    Team2_Button_clicked(7);
}


void Window2::on_Yellow_Button09_clicked()
{
    Team2_Button_clicked(8);
}


void Window2::on_Yellow_Button10_clicked()
{
    Team2_Button_clicked(9);
}


void Window2::on_Yellow_Button11_clicked()
{
    Team2_Button_clicked(10);
}


void Window2::on_Yellow_Button12_clicked()
{
    Team2_Button_clicked(11);
}


void Window2::on_Yellow_Button13_clicked()
{
    Team2_Button_clicked(12);
}


void Window2::on_Yellow_Button14_clicked()
{
    Team2_Button_clicked(13);
}


void Window2::on_Yellow_Button15_clicked()
{
    Team2_Button_clicked(14);
}


void Window2::on_Yellow_Button16_clicked()
{
    Team2_Button_clicked(15);
}


void Window2::on_Yellow_Button17_clicked()
{
    Team2_Button_clicked(16);
}


void Window2::on_Yellow_Button18_clicked()
{
    Team2_Button_clicked(17);
}


void Window2::on_Yellow_Button19_clicked()
{
    Team2_Button_clicked(18);
}


void Window2::on_Yellow_Button20_clicked()
{
    Team2_Button_clicked(19);
}


void Window2::on_Yellow_Button21_clicked()
{
    Team2_Button_clicked(20);
}


void Window2::on_Yellow_Button22_clicked()
{
    Team2_Button_clicked(21);
}


void Window2::on_Yellow_Button23_clicked()
{
    Team2_Button_clicked(22);
}


void Window2::on_Yellow_Button24_clicked()
{
    Team2_Button_clicked(23);
}


void Window2::on_Yellow_Button25_clicked()
{
    Team2_Button_clicked(24);
}


void Window2::on_Blue_Button01_clicked()
{
    Team2_Button_clicked(25);
}


void Window2::on_Blue_Button02_clicked()
{
    Team2_Button_clicked(26);
}


void Window2::on_Blue_Button03_clicked()
{
    Team2_Button_clicked(27);
}


void Window2::on_Blue_Button04_clicked()
{
    Team2_Button_clicked(28);
}


void Window2::on_Blue_Button05_clicked()
{
    Team2_Button_clicked(29);
}

void Window2::on_Blue_Button06_clicked()
{
    Team2_Button_clicked(30);
}


void Window2::on_Blue_Button07_clicked()
{
    Team2_Button_clicked(31);
}


void Window2::on_Blue_Button08_clicked()
{
    Team2_Button_clicked(32);
}


void Window2::on_Blue_Button09_clicked()
{
    Team2_Button_clicked(33);
}


void Window2::on_Blue_Button10_clicked()
{
    Team2_Button_clicked(34);
}


void Window2::on_Blue_Button11_clicked()
{
    Team2_Button_clicked(35);
}


void Window2::on_Blue_Button12_clicked()
{
    Team2_Button_clicked(36);
}


void Window2::on_Blue_Button13_clicked()
{
    Team2_Button_clicked(37);
}


void Window2::on_Blue_Button14_clicked()
{
    Team2_Button_clicked(38);
}


void Window2::on_Blue_Button15_clicked()
{
    Team2_Button_clicked(39);
}


void Window2::on_Blue_Button16_clicked()
{
    Team2_Button_clicked(40);
}


void Window2::on_Blue_Button17_clicked()
{
    Team2_Button_clicked(41);
}


void Window2::on_Blue_Button18_clicked()
{
    Team2_Button_clicked(42);
}


void Window2::on_Blue_Button19_clicked()
{
    Team2_Button_clicked(43);
}


void Window2::on_Blue_Button20_clicked()
{
    Team2_Button_clicked(44);
}


void Window2::on_Blue_Button21_clicked()
{
    Team2_Button_clicked(45);
}


void Window2::on_Blue_Button22_clicked()
{
    Team2_Button_clicked(46);
}


void Window2::on_Blue_Button23_clicked()
{
    Team2_Button_clicked(47);
}


void Window2::on_Blue_Button24_clicked()
{
    Team2_Button_clicked(48);
}


void Window2::on_Blue_Button25_clicked()
{
    Team2_Button_clicked(49);
}
