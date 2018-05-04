#include "lead.h"

/*void openAccount()//开户，在结构体数组中增加一个数组成员，即一个储户的信息；
{
	int accNumber;//账号
	char accName[9];//账户名
	char accPWD[7];//账户密码
	double cash;//现金余额
	//初始化
	accNumber = 0;
	memset(accName, 0, sizeof(accName));
	memset(accPWD, 0, sizeof(accPWD));
	cash = 0;
	accNumber = creatAccNumber();
	getaccName(accName);
	getaccPWD(accPWD);
	//getaccNumber(accNumber);
	cash = getcash(0);

	maxAccount++;

	//将数值赋值到结构体数组中
	rs[maxAccount].accNumber = accNumber;
	strcpy(rs[maxAccount].accName, accName);
	strcpy(rs[maxAccount].accPWD, accPWD);
	rs[maxAccount].balance = cash;
	strcpy(rs[maxAccount].flag, "0");
	//每开一个户都及时保存数据
	if (writeData())
	{
		printf("写文件出错！");
		return;
	}
	dispAnAccount(maxAccount);
	printf("开户成功！大吉大利晚上吃鸡！\n");
	getchar();
}

void deposit()//存款，将存款金额加到该账户的余额上；
{
	int	accNumber = 0;
	int weizhi = -1;
	double cash = 0;
	accNumber = getaccNumber(0);
	weizhi = findAnAccount(accNumber);
	if (weizhi==-1)
	{
		printf("查无此账户，按任意键返回...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	if (strcmp(rs[weizhi].flag,"0")!=0)
	{
		printf("该账户已经销户，不能存款！按任意键返回...\n");
		getchar();
		return;
	}
	cash = getcash(0);
	rs[weizhi].balance += cash;

	if (writeData())
	{
		printf("写文件出错！");
		return;
	}

	dispAnAccount(weizhi);
	printf("存款成功！按任意键返回主菜单...\n");
	getchar();
}
void withdraw()//取款，从该账户的余额上扣除取款金额；
{
	;
}
void query()//查询，查询某账户信息；
{
	;
}

void closeAccount()//销户，将该账户的账户状态置为1，账户余额置为0；
{
	;
}*/
//dxj,2013-9-2
//与bankServe.h对应的实现文件
void openAccount()//开户
{
	int accNumber;       // 账号
	char accName[9];   // 户名
	char accPWD[7];    // 密码
	double  cash;     // 存入金额
	accNumber = 0;
	memset(accName, 0, sizeof(accName));
	memset(accPWD, 0, sizeof(accPWD));
	cash = 0;
	accNumber = creatAccNumber();
	getaccName(accName);
	getaccPWD(accPWD);
	cash = getcash(0);

	maxAccount++;//帐户的数量

	rs[maxAccount].accNumber = accNumber;
	strcpy(rs[maxAccount].accName, accName);
	strcpy(rs[maxAccount].accPWD, accPWD);
	rs[maxAccount].balance = cash;
	strcpy(rs[maxAccount].flag, "0");
	//每开一个户都及时保存数据
	if (writeData())
	{
		printf("写文件出错！");
		return;
	}
	dispAnAccount(maxAccount);  //显示帐户信息
	printf("开户成功！按任意键返回主菜单...\n");
	getchar();
	getchar();
}

void deposit()   //存款
{
	int accNumber = 0;
	int accountPosition = -1; //帐户在数组中的位置
	double cash = 0;         //存入金额

	accNumber = getaccNumber(0);//获取帐号
	//查找该帐户
	accountPosition = findAnAccount(accNumber);
	if (accountPosition == -1)
	{
		printf("查无此帐户，按任意键返回...");
		getchar();
		return;
	}//endif

	//显示帐户信息
	dispAnAccount(accountPosition);
	if (strcmp(rs[accountPosition].flag, "0") != 0)
	{
		printf("该帐户已经销户，不能存款！按任意键返回...");
		getchar();
		return;
	}

	//得到存款金额
	cash = getcash(0);
	rs[accountPosition].balance += cash;
	//保存数据
	if (writeData())
	{
		printf("写文件出错！");
		return;
	}
	dispAnAccount(accountPosition);
	printf("存款成功！按任意键返回主菜单...");
	getchar();
	getchar();
}//enddeposit()

void withdraw()  //取款
{
	int accNumber, i;
	char accPWD[7];    // 取款时需要验证密码
	int accountPosition;//帐户在数组中的位置
	double cash;//取款金额
	//初始化
	accNumber = 0;
	accountPosition = -1;
	cash = 0;
	accNumber = getaccNumber(1);//"1"为获取取款帐号
	//查找该帐户
	accountPosition = findAnAccount(accNumber);
	if (accountPosition == -1)
	{
		printf("查无此帐户，按任意键返回...\n");
		getchar();
		getchar();
		return;
	}//endif

	for (i = 0; i<3; i++)//允许三次机会输入用户密码
	{
		getaccPWD(accPWD);
		//验证密码
		if (strcmp(rs[accountPosition].accPWD, accPWD) == 0)
			break;//密码正确，退出验证
		else{
			if (i<2) printf("密码不正确，请重新输入！");
			else {
				printf("密码不正确，按任意键返回...\n");
				getchar();
				return;
			}
		}//endelse
	}//endfor

	if (strcmp(rs[accountPosition].flag, "0") != 0)
	{
		printf("该帐户已经销户，不能取款！按任意键返回...");
		getchar();
		return;
	}
	dispAnAccount(accountPosition);//显示帐户信息

	cash = getcash(1);//"1"为得到取款金额
	if (cash>rs[accountPosition].balance)
	{
		printf("取款金额超出帐户余额，不能透支!按任意键返回...\n");
		getchar();
		getchar();
		return;
	}
	rs[accountPosition].balance = rs[accountPosition].balance - cash;

	//保存数据
	if (writeData())
	{
		printf("写文件出错！");
		return;
	}
	dispAnAccount(accountPosition);
	printf("取款成功！按任意键返回主菜单...");

	getchar();
	getchar();
}


void query()    //查询
{
	int choice, i;
	int accNumber;
	char accPWD[7];
	char accName[9];   // 户名
	int accountPosition;//帐户在数组中的位置

	//初始化变量
	accNumber = 0;
	memset(accName, 0, sizeof(accName));//数组初始化
	memset(accPWD, 0, sizeof(accPWD));
	accountPosition = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    按帐号查询  请按1     |\n");
	printf("|    按姓名查询  请按2     |\n");
	printf("+--------------------------+\n");
	printf("请输入您的选择：");
	scanf("%d", &choice);
	if (choice == 1)
	{
		accNumber = getaccNumber(3);//"3"为获取查询帐号
		accountPosition = findAnAccount(accNumber);
		if (accountPosition == -1)
		{
			printf("查无此帐户，按任意键返回...");
			fflush(stdin);
			getchar();
			return;
		}
		getaccPWD(accPWD);
		if (strcmp(rs[accountPosition].accPWD, accPWD) != 0)
		{
			printf("密码错误! 按任意键返回...");
			fflush(stdin);
			getchar();
			return;
		}


		dispAnAccount(accountPosition);
	}
	else if (choice == 2)
	{
		getaccName(accName);
		for (i = 0; i <= maxAccount; i++)
		{
			if (strcmp(rs[i].accName, accName) == 0)
			{
				accountPosition = i;
				break;
			}
		}
		if (accountPosition == -1)
		{
			printf("查无此储户名，按任意键返回...");
			fflush(stdin);
			getchar();
			return;
		}

		getaccPWD(accPWD);
		if (strcmp(rs[accountPosition].accPWD, accPWD) != 0)
		{
			printf("密码错误! 按任意键返回...");
			fflush(stdin);
			getchar();
			return;
		}
		dispAnAccount(accountPosition);
	}
	else printf("无效选择！");
}

void closeAccount()//销户
{
	char userAnswer;
	int i = 0, accNumber = 0;
	char accPWD[7];
	double balance;
	int accountPosition;  //帐户在数组中的位置
	memset(accPWD, 0, sizeof(accPWD));
	accountPosition = -1;
	accNumber = getaccNumber(2); //参数"2"为获取销户帐号
	accountPosition = findAnAccount(accNumber);
	if (accountPosition == -1)
	{
		printf("查无此帐户，");
		mypause();
		return;
	}
	while (i<3)
	{
		getaccPWD(accPWD);
		i++;
		if (!strcmp(rs[accountPosition].accPWD, accPWD)) break;
		printf("密码错误! ");
	}
	if (i == 3)
	{
		printf("\n3次输入密码错误! 返回系统主菜单...");
		return;
	}

	dispAnAccount(accountPosition);
	if (strcmp(rs[accountPosition].flag, "0") != 0)
	{
		printf("该帐户已经销户，不能重复销户! ");
		mypause();
		return;
	}
	printf("确认将帐户%d销户吗？[y销户｜n取消]", rs[accountPosition].accNumber);
	fflush(stdin);
	scanf("%c", &userAnswer);
	if (userAnswer == 'y' || userAnswer == 'Y')
	{
		balance = rs[accountPosition].balance;
		printf("该帐户现有余额:%8.2f,请确认取出！\n", balance);
		printf("按任意键继续...");
		fflush(stdin);
		getchar();
		rs[accountPosition].balance = 0;
		strcpy(rs[accountPosition].flag, "1");
		if (writeData()) //保存数据
		{
			printf("写文件出错！");
			return;
		}
		dispAnAccount(accountPosition);
		printf("销户成功! ");
		mypause();
		return;
	}
	else if (userAnswer == 'n' || userAnswer == 'N')
	{
		printf("取消销户! ");
		mypause();
		return;
	}
	else  printf("无效选择！");
	mypause();
}
