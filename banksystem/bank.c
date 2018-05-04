#include "lead.h"
void  main()
{
	char userName[8];
	char userPWD[7];
	int i;
	welcome();
	for ( i = 0; i < 3; i++)
	{
		printf("请输入您的用户名：(第%d次)\n",i+1);
		scanf("%s",userName);
		printf("请输入您的密码：(第%d次)\n",i+1);
		scanf("%s", userPWD);
		if ((strcmp(userName,"admin")==0)&&(strcmp(userPWD,"123456")==0))
		{
			mainmenu();
			break;
		}
		else
		{
			if (i<2)
			{
				printf("用户名或密码错误，请重新输入!：(第%d次)\n",i+1);
				
			}
			else
			{
				printf("%d次机会用完，用户名或者密码错误，退出系统！", i + 1);
				exit(1);
			}
		}
	}
	system("pause");
}