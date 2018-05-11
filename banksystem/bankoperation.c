#include "lead.h"

void openAccount()//开户，在结构体数组中增加一个数组成员，即一个储户的信息；
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
	if (weizhi == -1)
	{
		printf("查无此账户，按任意键返回...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	if (strcmp(rs[weizhi].flag, "0") != 0)
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
	int accNumber, i,j,choice;
	char accPWD[7];
	char accName[9];
	int weizhi;
	double cash;
	
	accNumber = 0;
	weizhi = -1;
	cash = 0;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    按帐号查询  请按1     |\n");
	printf("|    按姓名查询  请按2     |\n");
	printf("+--------------------------+\n");
	printf("请输入您的选择：");
	scanf("%d", &choice);
	if (choice==1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice==2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi==-1)
	{
		printf("查无此账户！按任意键返回...\n");
		getchar();
		getchar();
		return;
	}

	for ( i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD,accPWD)==0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("密码输入不正确，请重新输入！\n");
			}
			else
			{
				printf("密码不正确，按任意键返回...\n");
				getchar();
				return;
			}
		}
	}

	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("该账户已经销户，不能取款！按任意键返回...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);

	cash = getcash(1);
	if (cash>rs[weizhi].balance)
	{
		printf("取款金额超出账户余额，不能透支！按任意键返回...\n");
	}
	else
	{
		rs[weizhi].balance -= cash;
	}
	if (writeData())
	{
		printf("写文件出错！\n");
		return;
	}
	dispAnAccount(weizhi);
	printf("取款成功！按任意键返回主菜单...\n");
	getchar();
	getchar();
}
void query()//查询，查询某账户信息；
{
	int accNumber, i, j, choice;
	char accPWD[7];
	char accName[9];
	int weizhi;

	accNumber = 0;
	weizhi = -1;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    按帐号查询  请按1     |\n");
	printf("|    按姓名查询  请按2     |\n");
	printf("+--------------------------+\n");
	printf("请输入您的选择：");
	scanf("%d", &choice);
	if (choice == 1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice == 2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi == -1)
	{
		printf("查无此账户！按任意键返回...\n");
		getchar();
		getchar();
		return;
	}

	for (i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD, accPWD) == 0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("密码输入不正确，请重新输入！\n");
			}
			else
			{
				printf("密码不正确，按任意键返回...\n");
				getchar();
				return;
			}
		}
	}

	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("查询到该账户已经销户！按任意键返回...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	getchar();
	getchar();
}

void closeAccount()//销户，将该账户的账户状态置为1，账户余额置为0；
{
	int accNumber, i, j, choice;
	char accPWD[7];
	char accName[9];
	char count[2];
	int weizhi;

	accNumber = 0;
	weizhi = -1;
	choice = -1;
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    按帐号查询  请按1     |\n");
	printf("|    按姓名查询  请按2     |\n");
	printf("+--------------------------+\n");
	printf("请输入您的选择：");
	scanf("%d", &choice);
	if (choice == 1)
	{
		accNumber = getaccNumber(3);
		weizhi = findAnAccount(accNumber);
	}
	else if (choice == 2)
	{
		getaccName(accName);
		for (j = 0; j <= maxAccount; j++)
		{
			if (strcmp(rs[j].accName, accName) == 0)
			{
				weizhi = j;
				break;
			}
		}
	}
	if (weizhi == -1)
	{
		printf("查无此账户！按任意键返回...\n");
		getchar();
		getchar();
		return;
	}

	for (i = 0; i < 3; i++)
	{
		getaccPWD(accPWD);

		if (strcmp(rs[weizhi].accPWD, accPWD) == 0)
		{
			break;
		}
		else
		{
			if (i<2)
			{
				printf("密码输入不正确，请重新输入！\n");
			}
			else
			{
				printf("密码不正确，按任意键返回...\n");
				getchar();
				return;
			}
		}
	}
	if (strcmp(rs[weizhi].flag, "0") != 0)
	{
		printf("查询到该账户已经销户！按任意键返回...\n");
		getchar();
		return;
	}
	dispAnAccount(weizhi);
	printf("\n");
	printf("+--------------------------+\n");
	printf("|    销户   请按是【Y】    |\n");
	printf("|    返回   请按否【N】    |\n");
	printf("+--------------------------+\n");
	printf("请输入您的选择：");
	scanf("%s",count);
	if (strcmp(count,"Y")==0)
	{
		if (rs[weizhi].balance!=0)
		{
			printf("账户余额：%12.2f", rs[weizhi].balance);
			printf("请到银行办理取款销户手续！\n");
			strcpy(rs[weizhi].flag, "1");
			dispAnAccount(weizhi);
		}
		else if (rs[weizhi].balance==0)
		{
			printf("账户余额：%12.2f", rs[weizhi].balance);
			strcpy(rs[weizhi].flag, "1");
			rs[weizhi].balance = 0;
			dispAnAccount(weizhi);
		}
	}
	else if (strcmp(count, "N") == 0)
	{
		mypause();
		return;
	}
	else
	{
		printf("选择无效！");
		mypause();
		return;
	}
	getchar();
	getchar();
}