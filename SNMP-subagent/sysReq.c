#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "sysReq.h"
#define MAXLEN 140 
#define MEMLEN 10
FILE *fp;
static char strBuf[MAXLEN];	

struct cpuStatStruct{
	int user;
	int nice;
	int system;
	int idle;
	int iowait;
	int irq;
	int softirq;
	int unknown1;
	int unknown2;
	int unknown3;
};

static  struct cpuStatStruct cpuStat;
static int total;
int CPUQuery(char *info)
{
	fp = popen("cat /proc/stat","r");
	if(fp == NULL) 
		return -1;
	if( fgets(strBuf,MAXLEN,fp) == NULL)
	 	return -1;
//	puts(strBuf);
	sscanf(strBuf,"cpu %d %d %d %d %d %d %d %d %d %d",
			&cpuStat.user,
			&cpuStat.nice,
			&cpuStat.system,
			&cpuStat.idle,
			&cpuStat.iowait,
			&cpuStat.irq,
			&cpuStat.softirq,
			&cpuStat.unknown1,
			&cpuStat.unknown2,
			&cpuStat.unknown3);
	total = cpuStat.user +  cpuStat.nice + cpuStat.system + cpuStat.idle
		+cpuStat.iowait + cpuStat.irq + cpuStat.softirq;
	
	sprintf(info,"%d:%d",cpuStat.idle,total);
	return 0;
}
int DISKQuery(char* info)
{
        static char *pos;
        fp = popen("df","r");
        if(fp == NULL)
                return -1;
        if(fgets(strBuf,MAXLEN,fp)==NULL)
                return -1;
        if(fgets(strBuf,MAXLEN,fp)==NULL)
                return -1;
        pos = strchr(strBuf,'%');
        *(info+0) = *(pos -2);
        *(info+1) = *(pos -1);
        *(info+2) = '\0';
	return 0;
}

int NETQuery(char* info)
{
        char *pch;
        int i = 0;
        fp = popen("cat /proc/net/dev","r");
        if(fp == NULL)
                return -1;
        if(fgets(strBuf,MAXLEN,fp)==NULL)
                return -1;
        if(fgets(strBuf,MAXLEN,fp)==NULL)
                return -1;
        if(fgets(strBuf,MAXLEN,fp)==NULL)
                return -1;
        pch = strtok(strBuf," ");
        for(i=0; i < 16; i++)
        {
                pch = strtok(NULL," ");
                if( i == 0)
                {
                        strcpy(info,pch);
                        strncat(info,":",1);
                }
                if( i == 8)
                {
                        strncat(info,pch,MEMLEN);
                }
        }
        
	return 0;
}
int MEMQuery()
{	
	FILE *fp = NULL;
	static int tt,us,fr;
	fp = popen("free","r");
	if(fp == NULL) 
		return -1;
	if( fgets(strBuf,MAXLEN,fp) == NULL)
	 	return -1;
	if( fgets(strBuf,MAXLEN,fp) == NULL)
	 	return -1;
	sscanf(strBuf,"Mem: %d %d %d ",&tt,&us,&fr);
	//printf("Total:%d, Used:%d, Free:%d\n",tt,us,fr);
	return (100*us/tt);
}


