/*
	根据已知的6个整数，以时间格式任意组合，要求得到的时间最小，且时间格式符合常理
	例如：7 0 8 9 0 0，所得的最小时间是 07：08：09
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANDOM_AUTO 1

int main()
{
	long time_by_sec = 0;
#if RANDOM_AUTO
	int buf[6];
	char tmp[4] = {0};
	int x = 0;
	int y = 0;
#else
	int buf[6] = {0,0,0,7,8,9};
	//int buf[6] = {0,4,5,7,8,9};
	//int buf[6] = {0,0,5,7,8,9};
	//int buf[6] = {8,6,0,3,5,7};
	//int buf[6] = {8,1,2,3,5,7};
	//int buf[6] = {8,6,4,5,8,5};	//error
#endif
	int i = 5;
	int j = 5;
	int num = 0;
	int save = 0;
	int flag = 0;

#if RANDOM_AUTO
	printf("generating random number...\n");
	for(i=0; i<3; i++)
	{
		srand((long)time(0));
		sleep(1);
		if(i == 0)
			num = rand() % 24;
		else
			num = rand() % 60;
		//printf("%d\n", num);

		x = 2 * i;
		y = 2 * i + 1;

		if(num < 10)
		{
			buf[x] = 0;
			buf[y] = num;
		}
		else
		{
			sprintf(tmp, "%d", num);
			buf[x] = tmp[0] - 48;
			buf[y] = tmp[1] - 48;
		}

		printf("%d\n%d\n", buf[x], buf[y]);
	}
#endif
	printf("buf=[%d %d %d %d %d %d]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	for(j=5; j>=0; j--)
	{
		if((j==2 || j==4) && buf[j]>5)
		{
			save = buf[j];
			flag = 1;
			buf[j] = 0;
			for(i=j-1; i>=0; i--)
			{
				if(buf[i]<6 && buf[j]<=buf[i])
				{
					if(flag == 1)
					{
						buf[j] = buf[i];
						buf[i] = save; 
						flag = 0;
					}
					else
					{
						num = buf[j];
						buf[j] = buf[i];
						buf[i] = num;
					}
				}
			}
			//printf("buf[%d]=%d\n", j, buf[j]);
			continue;
		}

		for(i=j; i>=0; i--)
		{
			if(buf[j] < buf[i])
			{
				if(j==0 && buf[i]>2)
					continue;
				if((j==2 || j==4) && buf[i]>5)
					continue;
				if((j==1 && buf[j-1]==2) && buf[i]>3)
					continue;
				num = buf[j];
				buf[j] = buf[i];
				buf[i] = num;
			}
		}
		//printf("buf[%d]=%d\n", j, buf[j]);
	}
	printf("time=%d%d:%d%d:%d%d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	return 0;
}
