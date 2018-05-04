#ifndef BANKDATASTRUCT_H
#define BANKDATASTRUCT_H
#define N_MAXREC_NO 100

struct MyStruct
{
	int accNumber;
	char accName[8];
	char accPWD[7];
	double balance;
	char flag[2];
};
typedef struct MyStruct RECORD;
RECORD rs[N_MAXREC_NO];
int maxAccount;
#endif