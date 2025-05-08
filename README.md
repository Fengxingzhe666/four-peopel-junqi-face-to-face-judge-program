# 四国军棋线下裁判小程序  
## 开发背景  
本项目使用c++，qt编程。  
在传统的线上四国军棋中，4位玩家分别只能看到自己的棋子，两两与对面的玩家组成一对与另一对作战，当两颗棋子相碰时，较小的那颗棋会被判定死亡，而炸弹碰到任何棋子都会同归于尽，地雷不能主动移动，但大于除了工兵以外的所有棋子，工兵只能大于地雷而小于除了地雷和炸弹以外的所有棋子。由于只能看到自己的棋子和与敌方棋子的相对大小关系，需要玩家对局势有更准确的判断并进行攻防决策。  
如果在线下想要4人进行这个游戏项目，由于棋子的摆放问题，2人军棋可以让棋子站立摆放，有字的一面显示在自己一侧，对方只能看到棋子背面。但如果是四人游戏，会发现很难组织成4位玩家都只能看到自己棋子的盲棋模式（比如当棋子走到棋盘对面时，很容易就被左右两人看到棋子正面）。且由于4人不能互相知道别人的棋子，判定棋子碰撞结果还需要第5个人当裁判，成本大大增高。本项目即为了解决线下4人军棋暗棋而开发。  
## 使用方法  
使用本项目前，需要准备以下道具：一个四国军棋棋盘、4种颜色不同能相互区分的军棋棋子共100枚（每枚棋子背面朝上摆放，且上边写上1-1、1-2…5-5、5-6等编号）。每人需要拿一张纸或手机拍照记录自己的布局，即自己的棋子的编号对应的实际子力值，比如1-1司令、1-2连长、1-3师长、2-5炸弹等等。  
4位玩家依次将自己的布局输入程序，走棋时如果发生碰撞，输入碰撞的两颗棋子的编号，程序可以返回判断碰撞结果，且不暴露碰撞两方的真实子力。同时解决了棋子摆放难以组成暗棋模式和需要第5人当裁判2个问题。  
本项目模仿线上四国军棋平台，同步了以下功能：  
一：玩家可以选择保存自己的某一次布局到文件，然后以后再玩时可以直接从文件导入布局，无需逐个手动输入。  
二：摆放布局时，炸弹不能摆在第一排，地雷只能摆在后两排，军旗只能摆在大本营，即最后一排的第2位或第4位。当玩家的军旗阵亡时，该玩家立刻出局，所有棋子被判定死亡。  
三：当某位玩家的司令阵亡时，程序将自动亮出该玩家的军旗所在位置。  
## 实现原理  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-03%20095306.png?raw=true)  
玩家可以根据自己的对局习惯自定义布局，本项目设计了一个与用户交互的ui逻辑，应对用户各种的点击顺序，最终在用户选择了所有25颗棋子的位置后获得表示子力值的数组用于后续的比较。  
图1左侧半边是用户的棋子编号与真实子力值的对比，右侧可以选择的是待摆放的棋子，灰显的是已经摆放到左侧的棋子。玩家需要单击选择右侧一个待摆放的棋子再单击左侧选择摆放的位置，程序就会建立对应关系。单击左侧已摆放的位置将会使得该棋子重新放回右侧，变为待摆放状态。  
除此之外，程序支持用文件导入布局：  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-03%20101908.png?raw=true)  
该功能的实现代码：  
```c++
//调出选择二进制文件的窗口（连接“打开”按钮的槽函数）
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
                in >> LButton_Statu[player_idx][j].data_from_right_idx;
                LButton_Statu[player_idx][j].is_data_existed=true;
                LB[j]->setText(INT_TO_QI_MAP.at(LButton_Statu[player_idx][j].qizi_int)+LB_CONTENT[j]);
                LB[j]->setStyleSheet(BUTTON_COLOR[player_idx]);
                RB[j]->setEnabled(false);
                RB[j]->setStyleSheet(QString());
            }
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "错误", "无法打开文件进行读取！");
        }
    }
}

//（“保存”按钮的槽函数）
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
```
程序内部实际的ui交互逻辑如下：  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E4%BA%A4%E4%BA%92%E9%80%BB%E8%BE%91.jpg?raw=true)  
交互的难点是，**怎样对每位玩家左右各25个按钮进行批量操作**？每个按钮的逻辑都是类似的但不同的，如果每个槽函数都单独编写，不但代码量非常大不易维护，还非常容易出错。解决这个问题采用了结构体指针的思想：  
注意MainWindow中的构造函数：
```c++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , send_state(false),proxy_int(0),right_button_selected_idx(0),player_idx(0)
{
    ui->setupUi(this);
    const QStringList LbuttonNames = {"LButton01", "LButton02", "LButton03","LButton04","LButton05","LButton06", "LButton07", "LButton08","LButton09","LButton10","LButton11", "LButton12", "LButton13","LButton14","LButton15","LButton16", "LButton17", "LButton18","LButton19","LButton20","LButton21", "LButton22", "LButton23","LButton24","LButton25"};
    const QStringList RbuttonNames={"RButton01", "RButton02", "RButton03","RButton04","RButton05","RButton06", "RButton07", "RButton08","RButton09","RButton10","RButton11", "RButton12", "RButton13","RButton14","RButton15","RButton16", "RButton17", "RButton18","RButton19","RButton20","RButton21", "RButton22", "RButton23","RButton24","RButton25"};
    for(int8_t i=0;i<BUTTON_NUM;i++)
    {
        LB[i]=this->findChild<QPushButton*>(LbuttonNames[i]);
        RB[i]=this->findChild<QPushButton*>(RbuttonNames[i]);
    }
}
```
其中LB、RB都是class MainWindow的私有变量，都是结构体指针数组
```c++
class MainWindow : public QMainWindow
{
    //......
private:
    //......
    struct Butt
    {
        int8_t qizi_int=0;
        bool is_data_existed=false;
        int8_t data_from_right_idx=0;
    };
    QPushButton* LB[BUTTON_NUM];
    QPushButton* RB[BUTTON_NUM];
    //......（其他私有成员变量）
};
```
这样只需要定义2个函数（一个针对左半边按钮，一个针对右半边按钮），在函数中传入按钮的id，调整LB[id]或RB[id]的属性即可改变对应按钮的属性（比如更改颜色，灰显，改变文字等等），在左右若干个按钮分别调用函数传入不同的按钮id即可实现对每位玩家左右各25个按钮的批量操作。  
在与四位玩家全部交互完毕后，程序会进入下一个窗口，本窗口会传入一个二维数组，表示四位玩家对应的25颗棋子的子力值，之后用于裁判棋子碰撞结果的逻辑。  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-03%20102732.png?raw=true)  
用户依次单击选择2个碰撞的棋子，程序会在文本框返回碰撞的结果，被判定死亡的棋子会灰显。如图2即红色1-1碰撞黄色1-5，判定结果为黄色大，因此红色1-1被判定死亡，灰显。  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-03%20104059.png?raw=true)  
根据游戏规则，当某玩家的司令阵亡时，程序将发出提示并展示该玩家的军旗位置。当某玩家军旗阵亡时，该玩家所有棋子被判定死亡。  
除了以上功能外，程序会用一个结构体数组依次保存每次碰撞的过程，在游戏结束后，可以点击“显示记录”回放四位玩家的布局以及所有碰撞的结果，既可以用于对局复盘，也可以验证所有碰撞结果的正确性。  
```c++
class Window2 : public QMainWindow
{
    //......
private:
    struct Butt
    {
        int8_t Team1_qizi_int=0;
        int8_t Team2_qizi_int=0;
        int8_t Team1_player_idx=0;
        int8_t Team2_player_idx=1;
        int8_t Team1_selected_button_idx;
        int8_t Team2_selected_button_idx;
    };
    std::vector<Butt> Compare_history;//结构体数组保存碰撞过程，可用于显示碰撞记录，也可以用于撤销回溯
    //......
};
```
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-03%20104723.png?raw=true)  
此外该结构体还用于回溯，在裁判界面可以点击“撤销”，撤销至上一步碰撞的程序状态。  
裁判界面的“工兵”和“后两排移动”两个checkbox控件可以在有工兵飞铁路或后两排主动碰别人棋时选择，用于判定该玩家是否违反游戏规则。  
## 实际应用场景
该项目已用于家庭娱乐场合，实际使用场景如下图：  
一张为实际游戏的棋盘图，一张是玩家用于记录自己布局的编号与真实子力对比的图。  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E7%BB%88%E7%9B%98%E6%8B%8D%E7%85%A709.jpg?raw=true)  
![](https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program/blob/main/img/%E7%BA%B8%E7%89%87%E5%B8%83%E5%B1%80.jpg?raw=true)  
