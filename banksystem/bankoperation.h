//关于银行业务函数的头文件
#ifndef BANKOPERATION_H

#define BANKOPERATION_H
void openAccount();//开户，在结构体数组中增加一个数组成员，即一个储户的信息；
void closeAccount();//销户，将该账户的账户状态置为1，账户余额置为0；
void deposit();//存款，将存款金额加到该账户的余额上；
void withdraw();//取款，从该账户的余额上扣除取款金额；
void query();//查询，查询某账户信息；

#endif