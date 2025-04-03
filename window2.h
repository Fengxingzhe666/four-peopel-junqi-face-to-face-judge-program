#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include "./ui_window2.h"
#include "mainwindow.h"
#include "triangle.h"
#include <vector>

const QString PLAYER_NAME[4]={"红色","黄色","绿色","蓝色"};

namespace Ui {
class Window2;
}

class Window2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window2(MainWindow *mainWindow,QWidget *parent = nullptr);
    ~Window2();

private slots:
    void Team1_Button_clicked(int8_t n);
    void Team2_Button_clicked(int8_t n);
    void Left_Show_JunQi();
    void Right_Show_JunQi();
    void Team1_died();
    void Team2_died();
    void Left_gray();
    void Right_gray();

    QString JUNQI_Compare(const int8_t& s1,const int8_t& s2,const QString& team_A_name,const QString& team_B_name);
    QString Show_History();

    void on_Compare_Button_clicked();

    void on_Red_Button01_clicked();

    void on_Red_Button02_clicked();

    void on_Red_Button03_clicked();

    void on_Red_Button04_clicked();

    void on_Red_Button05_clicked();

    void on_Red_Button06_clicked();

    void on_Red_Button07_clicked();

    void on_Red_Button08_clicked();

    void on_Red_Button09_clicked();

    void on_Red_Button10_clicked();

    void on_Red_Button11_clicked();

    void on_Red_Button12_clicked();

    void on_Red_Button13_clicked();

    void on_Red_Button14_clicked();

    void on_Red_Button15_clicked();

    void on_Red_Button16_clicked();

    void on_Red_Button17_clicked();

    void on_Red_Button18_clicked();

    void on_Red_Button19_clicked();

    void on_Red_Button20_clicked();

    void on_Red_Button21_clicked();

    void on_Red_Button22_clicked();

    void on_Red_Button23_clicked();

    void on_Red_Button24_clicked();

    void on_Red_Button25_clicked();

    void on_Green_Button01_clicked();

    void on_Green_Button02_clicked();

    void on_Green_Button03_clicked();

    void on_Green_Button04_clicked();

    void on_Green_Button05_clicked();

    void on_Green_Button06_clicked();

    void on_Green_Button07_clicked();

    void on_Green_Button08_clicked();

    void on_Green_Button09_clicked();

    void on_Green_Button10_clicked();

    void on_Green_Button11_clicked();

    void on_Green_Button12_clicked();

    void on_Green_Button13_clicked();

    void on_Green_Button14_clicked();

    void on_Green_Button15_clicked();

    void on_Green_Button16_clicked();

    void on_Green_Button17_clicked();

    void on_Green_Button18_clicked();

    void on_Green_Button19_clicked();

    void on_Green_Button20_clicked();

    void on_Green_Button21_clicked();

    void on_Green_Button22_clicked();

    void on_Green_Button23_clicked();

    void on_Green_Button24_clicked();

    void on_Green_Button25_clicked();

    void on_Yellow_Button01_clicked();

    void on_Yellow_Button02_clicked();

    void on_Yellow_Button03_clicked();

    void on_Yellow_Button04_clicked();

    void on_Yellow_Button05_clicked();

    void on_Yellow_Button06_clicked();

    void on_Yellow_Button07_clicked();

    void on_Yellow_Button08_clicked();

    void on_Yellow_Button09_clicked();

    void on_Yellow_Button10_clicked();

    void on_Yellow_Button11_clicked();

    void on_Yellow_Button12_clicked();

    void on_Yellow_Button13_clicked();

    void on_Yellow_Button14_clicked();

    void on_Yellow_Button15_clicked();

    void on_Yellow_Button16_clicked();

    void on_Yellow_Button17_clicked();

    void on_Yellow_Button18_clicked();

    void on_Yellow_Button19_clicked();

    void on_Yellow_Button20_clicked();

    void on_Yellow_Button21_clicked();

    void on_Yellow_Button22_clicked();

    void on_Yellow_Button23_clicked();

    void on_Yellow_Button24_clicked();

    void on_Yellow_Button25_clicked();

    void on_Blue_Button01_clicked();

    void on_Blue_Button02_clicked();

    void on_Blue_Button03_clicked();

    void on_Blue_Button04_clicked();

    void on_Blue_Button05_clicked();

    void on_Blue_Button06_clicked();

    void on_Blue_Button07_clicked();

    void on_Blue_Button08_clicked();

    void on_Blue_Button09_clicked();

    void on_Blue_Button10_clicked();

    void on_Blue_Button11_clicked();

    void on_Blue_Button12_clicked();

    void on_Blue_Button13_clicked();

    void on_Blue_Button14_clicked();

    void on_Blue_Button15_clicked();

    void on_Blue_Button16_clicked();

    void on_Blue_Button17_clicked();

    void on_Blue_Button18_clicked();

    void on_Blue_Button19_clicked();

    void on_Blue_Button20_clicked();

    void on_Blue_Button21_clicked();

    void on_Blue_Button22_clicked();

    void on_Blue_Button23_clicked();

    void on_Blue_Button24_clicked();

    void on_Blue_Button25_clicked();

    void on_History_Button_clicked();

    void on_Cancel_Button_clicked();

private:
    MainWindow* mainWindow;
    Ui::Window2 *ui;
    //ChessBoard *chessBoard;
    Triangle* triangle01,*triangle02,*triangle03,*triangle04;
    QPushButton* T1[2*BUTTON_NUM];
    QPushButton* T2[2*BUTTON_NUM];
    struct Butt
    {
        int8_t Team1_qizi_int=0;
        int8_t Team2_qizi_int=0;
        int8_t Team1_player_idx=0;
        int8_t Team2_player_idx=1;
        int8_t Team1_selected_button_idx;
        int8_t Team2_selected_button_idx;
    };
    Butt Compare_statu;
    std::vector<Butt> Compare_history;
    bool shot[PLAYER_NUM][BUTTON_NUM+1];
};

#endif // WINDOW2_H
