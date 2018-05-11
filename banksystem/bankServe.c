#include "lead.h"

void welcome()//进入欢迎界面函数定义；
{
	printf("+ --------------------------------------------------------- +\n");
	printf("\n|                                                           |\n");
	printf("\n|              欢迎使用‘天天银行’定制版储蓄系统           |\n");
	printf("\n|                                                           |\n");
	printf("\n+ --------------------------------------------------------- +\n");
}

void mainmenu()//显示主菜单函数定义；
{
	int choice=1;
	if (readData())
	{
		maxAccount = -1;
	}
	while (1)
	{
		printf("\n");
		printf("+ --------------------------------------------------------- +\n");
		printf("\n|                                                           |\n");
		printf("\n|         存款  【请按1】         开户  【请按2】           |\n");
		printf("\n|         取款  【请按3】         销户  【请按4】           |\n");
		printf("\n|         查询  【请按5】         退出  【请按0】           |\n");
		printf("\n|                 显示所有账户信息【请按6】                 |\n");
		printf("\n|                                                           |\n");
		printf("\n+ --------------------------------------------------------- +\n");
		printf("请输入您的选择：\n");
		scanf("%d",&choice);
		switch (choice)
		{
		case 0: exit(0);
		case 1: deposit(); break;
		case 2:	openAccount(); break;
		case 3: withdraw(); break;
		case 4: closeAccount(); break;
		case 5: query(); break;
		case 6: queryall(); break;
		default: printf("无效选项，不支持的额功能！\n"); break;
		}

	}
}

void dispAnAccount(int i)//显示指定序号数组；
{
	printf("\n");
	printf("+-------+----------+--------+-------------+------+\n");
	printf("| %-5s | %-8s | %-6s | %-12s| %4s |\n", "账户", "姓名", "密码", "余额", "状态");
	printf("+-------+----------+--------+-------------+------+\n");
	printf("| %5d | %-8s | %-6s | %12.2f| %4s |\n",
		rs[i].accNumber, rs[i].accName, "******"/*rs[i].accPWD*/, rs[i].balance,atoi(rs[i].flag) ? "销户" : "正常");
	printf("+-------+----------+--------+-------------+------+\n");
}

int creatAccNumber()//自动创建编号；
{
	if (maxAccount==-1)
	{
		return (10001);
	}
	else
	{
		return rs[maxAccount].accNumber + 1;
	}
}

void getaccName(char accName[])//从键盘获取用户名；
{
	printf("请输入储户姓名：\n");
	scanf("%s",accName);
	while (1)
	{
		if (!checkInput(0,accName))
		{
			break;
		}
		printf("超过最大用户名长度！请重新输入储户户名！：\n");
		scanf("%s",accName);
	}
}

void getaccPWD(char accPWD[])//从键盘获取密码；
{
	char ccaccPWD[100];
	int i = 1;
	while (i)
	{
		memset(ccaccPWD, 0, sizeof(ccaccPWD));
		printf("请输入储户密码：\n");
		scanf("%s", ccaccPWD);
		if (checkInput(1, ccaccPWD))
		{
			printf("超过最大密码长度！请重新输入储户密码！：\n");
			continue;
		}
		i = 0;
	}
	memcpy(accPWD, ccaccPWD, 7);
}

double getcash(int flag)//从键盘获取金额；
{
	char icash[100];
	double dcash = 0;
	int i=1;
	while (i)
	{
		memset(icash, 0, sizeof(icash));
		dcash = 0;
		switch (flag)
		{
		case 0: printf("请输入存款金额：\n"); break;
		case 1: printf("请输入取款金额：\n"); break;
		}
		scanf("%lf", &dcash);
		sprintf(icash, "%12.2f", dcash);
		if (checkInput(2,icash))
		{
			printf("超过最大金额！\n");
			continue;
		}
		i = 0;
	}
	return dcash;
}

int checkInput(int flag,char *checkStr)//检查输入格式是否正确；
{
	switch (flag)
	{
	case 0:if (strlen(checkStr) > 8) return 1; break;
	case 1:if (strlen(checkStr) > 6) return 1; break;
	case 2:if (strlen(checkStr) > 12) return 1; break;
	default:return 0;break;
	}
	return 0;
}

int getaccNumber(int flag)//从键盘获取账户编号；
{
	int iaccNumber=0;
	printf("\n");
	switch (flag)
	{
	case 0: printf("请输入要存款的帐号："); break;
	case 1: printf("请输入要取款的帐号："); break;
	case 2: printf("请输入要销户的帐号："); break;
	case 3: printf("请输入要查询的帐号："); break;
	}
	scanf("%d",&iaccNumber);
	return iaccNumber;
}

int  findAnAccount(int accNumber)//查找指定位置的账户信息；
{
	int weizhi = -1;
	int i;
	for ( i = 0; i <= maxAccount; i++)
	{
		if (rs[i].accNumber == accNumber)
		{
			weizhi = i;
			break;
		}
	}
	return weizhi;
}

int  writeData()//写入文件D盘根目录bank.txt；
{
	FILE *fp;
	int i;

	fp = fopen("Bank.txt","w");
	if (fp==NULL)
	{
		return 1;
	}
	for ( i = 0; i <=maxAccount; i++)
	{
		fprintf(fp,"%-6d%-10s%-10s%12.2f%2s\n",rs[i].accNumber,rs[i].accName,rs[i].accPWD,rs[i].balance,rs[i].flag);
	}
	fclose(fp);
	return 0;
}

int  readData()//读取文件D盘根目录bank.txt；
{
	FILE *fp;
	fp = fopen("Bank.txt","w+");
	if (fp==NULL)
	{
		return 1;
	}
	int i = 0,ef;
	while (!feof(fp))
	{
		fscanf(fp,"%-6d%-10s%-10s%12.2f%2s\n",rs[i].accNumber,rs[i].accName, rs[i].accPWD, rs[i].balance, rs[i].flag);
		ef = fgetc(fp);
		if (ef==EOF)
		{
			break;
		}
		i++;
	}
	maxAccount = i - 1;
	fclose(fp);
	return 0;
}

void queryall()//显示所有账户信息；
{
	int i;
	printf("\n");
	printf("+-------+----------+--------+-------------+------+\n");
	printf("| %-5s | %-8s | %-6s | %-12s| %4s |\n", "账户", "姓名", "密码", "余额", "状态");
	for ( i = 0; i <=maxAccount; i++)
	{
		printf("+-------+----------+--------+-------------+------+\n");
		printf("| %5d | %-8s | %-6s | %12.2f| %4s |\n",
			rs[i].accNumber, rs[i].accName, "******"/*rs[i].accPWD*/, rs[i].balance, atoi(rs[i].flag) ? "销户" : "正常");
	}
	printf("+-------+----------+--------+-------------+------+\n");
	system("pause");
}

void  mypause()//暂停；
{
	printf("按任意键返回...");
	fflush(stdin);
	getchar();
	return;
}