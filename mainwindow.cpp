#include "mainwindow.h"
#include "window2.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

#include <QFile>
#include <QTextStream>
#include <QDataStream>

// 辅助函数，用于填充数组
// template <typename T, size_t N>
// void fillArray(T (&arr)[N], const QStringList &names, QWidget *parent)
// {
//     for (size_t i = 0; i < N; ++i)
//     {
//         arr[i] = parent->findChild<T>(names[i]);
//     }
// }
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , send_state(false),proxy_int(0),right_button_selected_idx(0),player_idx(0)
{
    ui->setupUi(this);
    const QStringList LbuttonNames = {"LButton01", "LButton02", "LButton03","LButton04","LButton05","LButton06", "LButton07", "LButton08","LButton09","LButton10","LButton11", "LButton12", "LButton13","LButton14","LButton15","LButton16", "LButton17", "LButton18","LButton19","LButton20","LButton21", "LButton22", "LButton23","LButton24","LButton25"};
    const QStringList RbuttonNames={"RButton01", "RButton02", "RButton03","RButton04","RButton05","RButton06", "RButton07", "RButton08","RButton09","RButton10","RButton11", "RButton12", "RButton13","RButton14","RButton15","RButton16", "RButton17", "RButton18","RButton19","RButton20","RButton21", "RButton22", "RButton23","RButton24","RButton25"};
    //fillArray(a, buttonNames, this);
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        LB[i]=this->findChild<QPushButton*>(LbuttonNames[i]);
        RB[i]=this->findChild<QPushButton*>(RbuttonNames[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::right_button_clicked(int8_t n)
{
    send_state=true;
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        if(i==n)
            RB[i]->setStyleSheet(BUTTON_COLOR[player_idx]);//修改按钮的背景颜色
        else
            RB[i]->setStyleSheet(QString());//重置按钮颜色
    }
    proxy_int=QI_ZI_MAP[n];
    right_button_selected_idx=n;
}

void MainWindow::left_button_clicked(int8_t n)
{
    // for(int8_t i=0;i<BUTTON_NUM;i++)
    // {
    //     if(i!=n)
    //         LB[i]->setEnabled(true);
    //     else
    //         LB[i]->setEnabled(false);
    // }
    if (n < 0 || n >= BUTTON_NUM || LB[n] == nullptr)
    {
        qWarning() << "Invalid index or null pointer in left_button_clicked";
        return;
    }
    if(send_state&&!LButton_Statu[player_idx][n].is_data_existed)
    {
        //合法性检测
        if(proxy_int==0&&n<5)
            QMessageBox::warning(NULL,"违规摆放","炸弹不能摆在第一排");
        else if(proxy_int==1&&n<15)
            QMessageBox::warning(NULL,"违规摆放","地雷只能摆在后两排");
        else if(proxy_int==-1&&n!=21&&n!=23)
            QMessageBox::warning(NULL,"违规摆放","军旗只能摆在大本营6-2或6-4");
        else
        {
            send_state=false;
            //更新结构体
            LButton_Statu[player_idx][n].is_data_existed=true;
            LButton_Statu[player_idx][n].qizi_int=proxy_int;
            LButton_Statu[player_idx][n].data_from_right_idx=right_button_selected_idx;
            LB[n]->setStyleSheet(BUTTON_COLOR[player_idx]);//该按钮变红
            LB[n]->setText(CONTENT_SIMPLIFIED[right_button_selected_idx]+LB_CONTENT[n]);//更新该按钮字体
            RB[right_button_selected_idx]->setEnabled(false);//对应右按钮灰显
            RB[right_button_selected_idx]->setStyleSheet(QString());//对应右按钮颜色重置
            if(proxy_int!=-1&&proxy_int!=1&&proxy_int!=3&&(n==21||n==23))
                QMessageBox::warning(NULL,"警告信息","请注意大本营6-2和6-4中的棋子在游戏中无法移动，你当前摆放的是："+INT_TO_QI_MAP.at(proxy_int));
        }
    }
    else if(!send_state&&LButton_Statu[player_idx][n].is_data_existed)
    {
        send_state=true;
        LButton_Statu[player_idx][n].is_data_existed=false;
        RB[LButton_Statu[player_idx][n].data_from_right_idx]->setEnabled(true);
        RB[LButton_Statu[player_idx][n].data_from_right_idx]->setStyleSheet(BUTTON_COLOR[player_idx]);
        proxy_int=LButton_Statu[player_idx][n].qizi_int;
        right_button_selected_idx=LButton_Statu[player_idx][n].data_from_right_idx;
        LB[n]->setText(LB_CONTENT[n]);
        LB[n]->setStyleSheet(QString());
    }
    else if(send_state&&LButton_Statu[player_idx][n].is_data_existed)
    {
        LButton_Statu[player_idx][n].is_data_existed=false;
        LB[n]->setStyleSheet(QString());
        LB[n]->setText(LB_CONTENT[n]);
        RB[LButton_Statu[player_idx][n].data_from_right_idx]->setEnabled(true);
        RB[LButton_Statu[player_idx][n].data_from_right_idx]->setStyleSheet(QString());
    }
}

void MainWindow::on_LButton01_clicked()
{
    //在按下pushButton01时触发的代码
    left_button_clicked(0);
}

void MainWindow::on_LButton02_clicked()
{
    left_button_clicked(1);
}

void MainWindow::on_LButton03_clicked()
{
    left_button_clicked(2);
}

void MainWindow::on_LButton04_clicked()
{
    left_button_clicked(3);
}

void MainWindow::on_LButton05_clicked()
{
    left_button_clicked(4);
}

void MainWindow::on_LButton06_clicked()
{
    left_button_clicked(5);
}

void MainWindow::on_LButton07_clicked()
{
    left_button_clicked(6);
}

void MainWindow::on_LButton08_clicked()
{
    left_button_clicked(7);
}

void MainWindow::on_LButton09_clicked()
{
    left_button_clicked(8);
}

void MainWindow::on_LButton10_clicked()
{
    left_button_clicked(9);
}

void MainWindow::on_LButton11_clicked()
{
    left_button_clicked(10);
}

void MainWindow::on_LButton12_clicked()
{
    left_button_clicked(11);
}

void MainWindow::on_LButton13_clicked()
{
    left_button_clicked(12);
}

void MainWindow::on_LButton14_clicked()
{
    left_button_clicked(13);
}

void MainWindow::on_LButton15_clicked()
{
    left_button_clicked(14);
}

void MainWindow::on_LButton16_clicked()
{
    left_button_clicked(15);
}

void MainWindow::on_LButton17_clicked()
{
    left_button_clicked(16);
}

void MainWindow::on_LButton18_clicked()
{
    left_button_clicked(17);
}

void MainWindow::on_LButton19_clicked()
{
    left_button_clicked(18);
}

void MainWindow::on_LButton20_clicked()
{
    left_button_clicked(19);
}

void MainWindow::on_LButton21_clicked()
{
    left_button_clicked(20);
}

void MainWindow::on_LButton22_clicked()
{
    left_button_clicked(21);
}

void MainWindow::on_LButton23_clicked()
{
    left_button_clicked(22);
}

void MainWindow::on_LButton24_clicked()
{
    left_button_clicked(23);
}

void MainWindow::on_LButton25_clicked()
{
    left_button_clicked(24);
}

void MainWindow::on_RButton01_clicked()
{
    right_button_clicked(0);
}

void MainWindow::on_RButton02_clicked()
{
    right_button_clicked(1);
}

void MainWindow::on_RButton03_clicked()
{
    right_button_clicked(2);
}

void MainWindow::on_RButton04_clicked()
{
    right_button_clicked(3);
}

void MainWindow::on_RButton05_clicked()
{
    right_button_clicked(4);
}

void MainWindow::on_RButton06_clicked()
{
    right_button_clicked(5);
}

void MainWindow::on_RButton07_clicked()
{
    right_button_clicked(6);
}

void MainWindow::on_RButton08_clicked()
{
    right_button_clicked(7);
}

void MainWindow::on_RButton09_clicked()
{
    right_button_clicked(8);
}

void MainWindow::on_RButton10_clicked()
{
    right_button_clicked(9);
}

void MainWindow::on_RButton11_clicked()
{
    right_button_clicked(10);
}

void MainWindow::on_RButton12_clicked()
{
    right_button_clicked(11);
}

void MainWindow::on_RButton13_clicked()
{
    right_button_clicked(12);
}

void MainWindow::on_RButton14_clicked()
{
    right_button_clicked(13);
}

void MainWindow::on_RButton15_clicked()
{
    right_button_clicked(14);
}

void MainWindow::on_RButton16_clicked()
{
    right_button_clicked(15);
}

void MainWindow::on_RButton17_clicked()
{
    right_button_clicked(16);
}

void MainWindow::on_RButton18_clicked()
{
    right_button_clicked(17);
}

void MainWindow::on_RButton19_clicked()
{
    right_button_clicked(18);
}

void MainWindow::on_RButton20_clicked()
{
    right_button_clicked(19);
}

void MainWindow::on_RButton21_clicked()
{
    right_button_clicked(20);
}

void MainWindow::on_RButton22_clicked()
{
    right_button_clicked(21);
}

void MainWindow::on_RButton23_clicked()
{
    right_button_clicked(22);
}

void MainWindow::on_RButton24_clicked()
{
    right_button_clicked(23);
}

void MainWindow::on_RButton25_clicked()
{
    right_button_clicked(24);
}

void MainWindow::ResetAll()
{
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        RB[i]->setStyleSheet(QString());
        RB[i]->setEnabled(true);
        LButton_Statu[player_idx][i].is_data_existed=false;
        LButton_Statu[player_idx][i].qizi_int=0;
        LButton_Statu[player_idx][i].data_from_right_idx=0;
        LB[i]->setText(LB_CONTENT[i]);
        LB[i]->setStyleSheet(QString());
    }
}

void MainWindow::on_Reset_Button_clicked()
{
    ResetAll();
}


void MainWindow::on_Confirm_Button_clicked()
{
    bool completed=true;
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        if(!LButton_Statu[player_idx][i].is_data_existed)
        {
            completed=false;
            QMessageBox::information(NULL,"准备状态错误","请摆完所有棋子后再点击确认");
            break;
        }
    }
    if(completed)
    {
        if(player_idx<PLAYER_NUM-1)
        {
            player_idx++;
            ResetAll();
            this->setWindowTitle(TITLE[player_idx]);
        }
        else
        {
            Window2 *w2=new Window2(this);
            w2->show();
            this->hide();
        }
    }
}

void MainWindow::Disp_M(int8_t p)
{
    QString tempStr=NULL;
    for(int8_t i=0;i<PLAYER_NUM;i++)
    {
        for(int8_t j=0;j<BUTTON_NUM;j++)
        {
            if(j<=3||j==8||j==10||(j>=15&&j<=18)||(j>=20&&j<=23))
            {
                tempStr+=INT_TO_QI_MAP.at(LButton_Statu[i][j].qizi_int);
            }
            else if(j==4||j==7||j==11||j==14||j==19)
            {
                tempStr+=INT_TO_QI_MAP.at(LButton_Statu[i][j].qizi_int)+"\n";
            }
            else if(j==24)
            {
                tempStr+=INT_TO_QI_MAP.at(LButton_Statu[i][j].qizi_int)+"\n\n";
            }
            else
            {
                tempStr+=INT_TO_QI_MAP.at(LButton_Statu[i][j].qizi_int)+"〇";
            }
        }
    }
    QMessageBox::information(NULL,"当前布局状态",tempStr);
}


void MainWindow::on_Disp_Button_clicked()
{
    Disp_M(0);
}


void MainWindow::on_Open_Button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "二进制文件 (*.dat)");//"二进制文件 (*.dat)" //"所有文件 (*.*)"
    if (!filePath.isEmpty())
    {
        // 这里可以添加其他处理代码，例如显示文件路径
        //QMessageBox::information(this, "文件路径", Path);
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_5_15); // 设置数据流版本
            for (int8_t j = 0; j < BUTTON_NUM; j++)
            {
                in >> LButton_Statu[player_idx][j].qizi_int ;
                //in >> LButton_Statu[player_idx][j].is_data_existed;
                in >> LButton_Statu[player_idx][j].data_from_right_idx;
                LButton_Statu[player_idx][j].is_data_existed=true;
                LB[j]->setText(INT_TO_QI_MAP.at(LButton_Statu[player_idx][j].qizi_int)+LB_CONTENT[j]);
                LB[j]->setStyleSheet(BUTTON_COLOR[player_idx]);
                RB[j]->setEnabled(false);
                RB[j]->setStyleSheet(QString());
            }
            file.close();
            //QMessageBox::information(this, "读取成功", "布局已从文件中恢复！");
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法打开文件进行读取！");
        }
    }
}


void MainWindow::on_Save_Button_clicked()
{
    bool completed=true;
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        if(!LButton_Statu[player_idx][i].is_data_existed)
        {
            completed=false;
            QMessageBox::information(NULL,"准备状态错误","摆完所有棋子才能保存布局");
            break;
        }
    }
    if(completed)
    {
        QString filePath = QFileDialog::getSaveFileName(this, "选择文件", "", "二进制文件 (*.dat)");
        if (!filePath.isEmpty())
        {
            // 这里可以添加其他处理代码，例如显示文件路径
            //QMessageBox::information(this, "文件路径", Path);
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly))
            {
                QDataStream out(&file);
                out.setVersion(QDataStream::Qt_5_15); // 设置数据流版本
                for (int8_t j = 0; j < BUTTON_NUM; ++j)
                {
                    out << LButton_Statu[player_idx][j].qizi_int;
                    out << LButton_Statu[player_idx][j].data_from_right_idx;
                }

                file.close();
                QMessageBox::information(this, "保存成功", "布局已成功保存到文件："+filePath);
            }
            else
            {
                QMessageBox::critical(this, "错误", "无法打开文件进行写入！");
            }
        }
    }
}

const int8_t& MainWindow::get_int(const int8_t& p_idx,const int8_t& button_idx) const
{
    return LButton_Statu[p_idx][button_idx].qizi_int;
}
