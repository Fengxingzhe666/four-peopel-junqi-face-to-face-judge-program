开发背景
本项目使用c++，qt编程。本项目已经本人在github上开源。项目开源地址：https://github.com/Fengxingzhe666/four-peopel-junqi-face-to-face-judge-program
在传统的线上四国军棋中，4位玩家分别只能看到自己的棋子，两两与对面的玩家组成一对与另一对作战，当两颗棋子相碰时，较小的那颗棋会被判定死亡，而炸弹碰到任何棋子都会同归于尽，地雷不能主动移动，但大于除了工兵以外的所有棋子，工兵只能大于地雷而小于除了地雷和炸弹以外的所有棋子。由于只能看到自己的棋子和与敌方棋子的相对大小关系，需要玩家对局势有更准确的判断并进行攻防决策。
如果在线下想要4人进行这个游戏项目，由于棋子的摆放问题，2人军棋可以让棋子站立摆放，有字的一面显示在自己一侧，对方只能看到棋子背面。但如果是四人游戏，会发现很难组织成4位玩家都只能看到自己棋子的盲棋模式（比如当棋子走到棋盘对面时，很容易就被左右两人看到棋子正面）。且由于4人不能互相知道别人的棋子，判定棋子碰撞结果还需要第5个人当裁判，成本大大增高。本项目即为了解决线下4人军棋暗棋而开发。
使用方法
使用本项目前，需要准备以下道具：一个四国军棋棋盘、4种颜色不同能相互区分的军棋棋子共100枚（每枚棋子背面朝上摆放，且上边写上1-1、1-2…5-5、5-6等编号）。每人需要拿一张纸或手机拍照记录自己的布局，即自己的棋子的编号对应的实际子力值，比如1-1司令、1-2连长、1-3师长、2-5炸弹等等。
4位玩家依次将自己的布局输入程序，走棋时如果发生碰撞，输入碰撞的两颗棋子的编号，程序可以返回判断碰撞结果，且不暴露碰撞两方的真实子力。同时解决了棋子摆放难以组成暗棋模式和需要第5人当裁判2个问题。
本项目模仿线上四国军棋平台，同步了以下功能：
一：玩家可以选择保存自己的某一次布局到文件，然后以后再玩时可以直接从文件导入布局，无需逐个手动输入。
二：摆放布局时，炸弹不能摆在第一排，地雷只能摆在后两排，军旗只能摆在大本营，即最后一排的第2位或第4位。当玩家的军旗阵亡时，该玩家立刻出局，所有棋子被判定死亡。
三：当某位玩家的司令阵亡时，程序将自动亮出该玩家的军旗所在位置。
