/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "sysInfo.h"
#include "sysReq.h"

#define STRLEN 30
/** Initializes the sysInfo module */
void
init_sysInfo(void)
{
    const oid cpuUsage_oid[] = { 1,3,6,1,4,1,33332,1,1 };
    const oid memUsage_oid[] = { 1,3,6,1,4,1,33332,1,2 };
    const oid DiskUsage_oid[] = { 1,3,6,1,4,1,33332,1,3 };
    const oid NetUsage_oid[] = { 1,3,6,1,4,1,33332,1,4 };

  DEBUGMSGTL(("sysInfo", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("cpuUsage", handle_cpuUsage,
                               cpuUsage_oid, OID_LENGTH(cpuUsage_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("memUsage", handle_memUsage,
                               memUsage_oid, OID_LENGTH(memUsage_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("DiskUsage", handle_DiskUsage,
                               DiskUsage_oid, OID_LENGTH(DiskUsage_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("NetUsage", handle_NetUsage,
                               NetUsage_oid, OID_LENGTH(NetUsage_oid),
                               HANDLER_CAN_RONLY
        ));
}

int
handle_cpuUsage(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
        static char cpu_buf[STRLEN];    
    switch(reqinfo->mode) {

        case MODE_GET:
            CPUQuery(cpu_buf);
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                    cpu_buf /* XXX: a pointer to the scalar's data */,
                                    strlen(cpu_buf) /* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_cpuUsage\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_memUsage(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
        static int mem;    
    switch(reqinfo->mode) {

        case MODE_GET:
            mem = MEMQuery();
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &mem/* XXX: a pointer to the scalar's data */,
                                     sizeof(int)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_memUsage\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_DiskUsage(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
        static char disk_buf[STRLEN]; 
    switch(reqinfo->mode) {

        case MODE_GET:
            DISKQuery(disk_buf);
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     disk_buf/* XXX: a pointer to the scalar's data */,
                                     strlen(disk_buf)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_DiskUsage\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_NetUsage(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */
   static char net_buf[STRLEN]; 
    switch(reqinfo->mode) {

        case MODE_GET:
            NETQuery(net_buf);
            snmp_set_var_typed_value(requests->requestvb, ASN_OCTET_STR,
                                     net_buf/* XXX: a pointer to the scalar's data */,
                                     strlen(net_buf)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_NetUsage\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
