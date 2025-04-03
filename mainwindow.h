#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include <unordered_map>

const int8_t BUTTON_NUM=25;
const int8_t PLAYER_NUM=4;
const int8_t QI_ZI_MAP[25]={10,9,8,8,7,7,6,6,5,5,4,4,4,3,3,3,2,2,2,1,1,1,0,0,-1};
const QString CONTENT_SIMPLIFIED[25]={"司","军","师","师","旅","旅","团","团","营","营","连","连","连","排","排","排","兵","兵","兵","雷","雷","雷","炸","炸","旗"};
const QString LB_CONTENT[25]={"1-1","1-2","1-3","1-4","1-5","2-1","2-3","2-5","3-1","3-2","3-4","3-5","4-1","4-3","4-5","5-1","5-2","5-3","5-4","5-5","6-1","6-2","6-3","6-4","6-5"};
const QString TITLE[4]={"玩家1准备","玩家2准备","玩家3准备","玩家4准备"};
const QString BUTTON_COLOR[4]={"background-color:#FF0000;","background-color:#FFD700;","background-color:#2E8B57;","background-color:#1E90FF;"};
const std::unordered_map<int8_t,QString> INT_TO_QI_MAP= {{-1,"旗"},{0,"炸"},{1,"雷"},{2,"兵"},{3,"排"},{4,"连"},{5,"营"},{6,"团"},{7,"旅"},{8,"师"},{9,"军"},{10,"司"}};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void left_button_clicked(int8_t n);
    void right_button_clicked(int8_t n);
    const int8_t& get_int(const int8_t& p_idx,const int8_t& button_idx)const;

private slots:
    void on_LButton01_clicked();
    void on_LButton02_clicked();
    void on_LButton03_clicked();
    void on_LButton04_clicked();
    void on_LButton05_clicked();
    void on_LButton06_clicked();
    void on_LButton07_clicked();
    void on_LButton08_clicked();
    void on_LButton09_clicked();
    void on_LButton10_clicked();
    void on_LButton11_clicked();
    void on_LButton12_clicked();
    void on_LButton13_clicked();
    void on_LButton14_clicked();
    void on_LButton15_clicked();
    void on_LButton16_clicked();
    void on_LButton17_clicked();
    void on_LButton18_clicked();
    void on_LButton19_clicked();
    void on_LButton20_clicked();
    void on_LButton21_clicked();
    void on_LButton22_clicked();
    void on_LButton23_clicked();
    void on_LButton24_clicked();
    void on_LButton25_clicked();

    void on_RButton01_clicked();
    void on_RButton02_clicked();
    void on_RButton03_clicked();
    void on_RButton04_clicked();
    void on_RButton05_clicked();
    void on_RButton06_clicked();
    void on_RButton07_clicked();
    void on_RButton08_clicked();
    void on_RButton09_clicked();
    void on_RButton10_clicked();
    void on_RButton11_clicked();
    void on_RButton12_clicked();
    void on_RButton13_clicked();
    void on_RButton14_clicked();
    void on_RButton15_clicked();
    void on_RButton16_clicked();
    void on_RButton17_clicked();
    void on_RButton18_clicked();
    void on_RButton19_clicked();
    void on_RButton20_clicked();
    void on_RButton21_clicked();
    void on_RButton22_clicked();
    void on_RButton23_clicked();
    void on_RButton24_clicked();
    void on_RButton25_clicked();
    void ResetAll();
    void Disp_M(int8_t p);
    void on_Reset_Button_clicked();

    void on_Confirm_Button_clicked();

    void on_Disp_Button_clicked();

    void on_Open_Button_clicked();

    void on_Save_Button_clicked();



private:
    Ui::MainWindow *ui;
    struct Butt
    {
        int8_t qizi_int=0;
        bool is_data_existed=false;
        int8_t data_from_right_idx=0;
        //Butt(int x=0):qizi_int(x),choose_state(false),is_data_existed(false){QPushButton();}//构造函数
    };
    QPushButton* LB[BUTTON_NUM];
    QPushButton* RB[BUTTON_NUM];
    bool send_state;
    int8_t proxy_int;
    int8_t right_button_selected_idx;
    int8_t player_idx;
    Butt LButton_Statu[PLAYER_NUM][BUTTON_NUM];
};


#endif // MAINWINDOW_H
