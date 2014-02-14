#ifndef _SYSREQ_H
#define _SYSREQ_H

int CPUQuery( char *info);
int MEMQuery(void);
int DISKQuery(char *info);
int NETQuery(char * info);
#endif
