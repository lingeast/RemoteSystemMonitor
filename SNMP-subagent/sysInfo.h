/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */
#ifndef SYSINFO_H
#define SYSINFO_H

/* function declarations */
void init_sysInfo(void);
Netsnmp_Node_Handler handle_cpuUsage;
Netsnmp_Node_Handler handle_memUsage;
Netsnmp_Node_Handler handle_DiskUsage;
Netsnmp_Node_Handler handle_NetUsage;

#endif /* SYSINFO_H */
