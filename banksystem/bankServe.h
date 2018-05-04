//dxj,2014-9-2,
//关于服务性函数的说明的头文件
#ifndef BANKSERVE_H //三条条件编译指令，头文件的安全保证
#define BANKSERVE_H
void welcome();
void mainmenu();
int  findAnAccount();
void dispAnAccount();
int  creatAccNumber();
int  readData();
int  writeData();
int  checkInput(int flag, char *checkStr);
//检查录入的用户名、密码、存入金额格式是否合法
void queryall();  //显示所有帐户
void getaccName(char accName[]); //得到键盘录入的户名
void getaccPWD(char accPWD[]);   //得到键盘录入的密码
double getcash(); //得到键盘录入的金额
int getaccNumber(int flag);      //得到键盘录入的帐号
int  readData();
int  writeData();
void  mypause();
#endif