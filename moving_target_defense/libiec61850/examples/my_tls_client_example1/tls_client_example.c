/*
 * client_example1.c
 *
 * This example is intended to be used with server_example_basic_io or server_example_goose.
 */

#include "iec61850_client.h"

#include <stdlib.h>
#include <stdio.h>

#include "hal_thread.h"

void reportCallbackFunction(void *parameter, ClientReport report)
{
    MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

    printf("received report for %s\n", ClientReport_getRcbReference(report));

    int i;
    for (i = 0; i < 4; i++)
    {
        ReasonForInclusion reason = ClientReport_getReasonForInclusion(report, i);

        if (reason != IEC61850_REASON_NOT_INCLUDED)
        {
            printf("  GGIO1.CurrentPressure.mag.f: %i (included for reason %i)\n",
                   MmsValue_toInt32(MmsValue_getElement(dataSetValues, i)), reason);
        }
    }
}

// void reportCallbackFunction(void *parameter, ClientReport report)
// {
//     // sprintf(log_msg_iecclient, "Received report for  %s with rptId %s\n", ClientReport_getRcbReference(report), ClientReport_getRptId(report));
//     // log(log_msg_iecclient);

//     // read from config to determine what element is of what type and writes to what
//     MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

//     LinkedList dataSetDirectory = (LinkedList)parameter;
//     if (dataSetDirectory)
//     {
//         int i;
//         for (i = 0; i < LinkedList_size(dataSetDirectory); i++)
//         {
//             ReasonForInclusion reason = ClientReport_getReasonForInclusion(report, i);
//             char valBuffer[500];
//             sprintf(valBuffer, "no value");

//             if (dataSetValues)
//             {
//                 MmsValue *value = MmsValue_getElement(dataSetValues, i);

//                 if (value)
//                 {
//                     MmsValue_printToBuffer(value, valBuffer, 500);
//                 }

//                 LinkedList entry = LinkedList_get(dataSetDirectory, i);

//                 char *entryName = (char *)entry->data;
//                 // std::string object = trimFC(entryName);

//                 printf("%s", valBuffer);
//             }
//         }
//     }
//     else
//     {
//         printf("Datasetdirectory not found for %s\n", ClientReport_getRcbReference(report));
//     }
// }

static void
securityEventHandler(void *parameter, TLSEventLevel eventLevel, int eventCode, const char *msg, TLSConnection con)
{
    (void)parameter;

    char *peerAddr = TLSConnection_getPeerAddress(con, NULL);

    printf("[SECURITY EVENT] %s (%s)(t: %i, c: %i)\n", msg, peerAddr, eventLevel, eventCode);

    free(peerAddr);
}

int main(int argc, char **argv)
{

    char *hostname;
    int tcpPort = 102;
    const char *localIp = NULL;
    int localTcpPort = -1;

    if (argc > 1)
        hostname = argv[1];
    else
        hostname = "192.168.0.105";

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    if (argc > 3)
        localIp = argv[3];

    if (argc > 4)
        localTcpPort = atoi(argv[4]);

    TLSConfiguration tlsConfig = TLSConfiguration_create();

    TLSConfiguration_setChainValidation(tlsConfig, true);
    TLSConfiguration_setAllowOnlyKnownCertificates(tlsConfig, false);

    TLSConfiguration_setEventHandler(tlsConfig, securityEventHandler, NULL);

    if (!TLSConfiguration_setOwnKeyFromFile(tlsConfig, "client_CA1_1.key", NULL))
    {
        printf("ERROR: Failed to load private key!\n");
        return 0;
    }

    if (!TLSConfiguration_setOwnCertificateFromFile(tlsConfig, "client_CA1_1.pem"))
    {
        printf("ERROR: Failed to load own certificate!\n");
        return 0;
    }

    if (!TLSConfiguration_addCACertificateFromFile(tlsConfig, "root_CA1.pem"))
    {
        printf("ERROR: Failed to load root certificate\n");
        return 0;
    }

    IedClientError error;

    IedConnection con = IedConnection_createWithTlsSupport(tlsConfig);

    /* Optional bind to local IP address/interface */
    // if (localIp)
    // {
    //     IedConnection_setLocalAddress(con, localIp, localTcpPort);
    //     printf("Bound to Local Address: %s:%i\n", localIp, localTcpPort);
    // }

    IedConnection_connect(con, &error, hostname, 3782);
    // printf("Connecting to %s:%i\n", hostname, tcpPort);

    if (error == IED_ERROR_OK)
    {
        printf("Connected\n");

        /* read an analog measurement value from server */

        // Current Pressure
        MmsValue *CurrentPressure = IedConnection_readObject(con, &error, "IED01LogicalDevice/GGIO1.CurrentPressure.mag.f", IEC61850_FC_MX);

        if (CurrentPressure != NULL)
        {
            // printf("\nMmsValue_getType(value) : %d\n", MmsValue_getType(CurrentPressure));
            if (MmsValue_getType(CurrentPressure) == MMS_INTEGER)
            {
                int fval = MmsValue_toInt32(CurrentPressure);
                printf("Current Pressure Value : %d\n", fval);
            }
            else if (MmsValue_getType(CurrentPressure) == MMS_DATA_ACCESS_ERROR)
            {
                printf("Failed to read value (error code: %i)\n", MmsValue_getDataAccessError(CurrentPressure));
            }

            MmsValue_delete(CurrentPressure);
        }

        // // Opening Pressure
        // MmsValue *OpeningPressure = IedConnection_readObject(con, &error, "IED01LogicalDevice/GGIO1.OpeningPressure.mag.f", IEC61850_FC_SP);

        // if (OpeningPressure != NULL)
        // {
        //     // printf("\nMmsValue_getType(value) : %d\n", MmsValue_getType(OpeningPressure));
        //     if (MmsValue_getType(OpeningPressure) == MMS_INTEGER)
        //     {
        //         int fval = MmsValue_toInt32(OpeningPressure);
        //         printf("Opening Pressure Value : %d\n", fval);
        //     }
        //     else if (MmsValue_getType(OpeningPressure) == MMS_DATA_ACCESS_ERROR)
        //     {
        //         printf("Failed to read value (error code: %i)\n", MmsValue_getDataAccessError(OpeningPressure));
        //     }

        //     MmsValue_delete(OpeningPressure);
        // }

        // // Coil Status
        // MmsValue *CoilStatus = IedConnection_readObject(con, &error, "IED01LogicalDevice/GGIO1.CoilStatus.mag.f", IEC61850_FC_MX);

        // if (CoilStatus != NULL)
        // {
        //     // printf("\nMmsValue_getType(value) : %d\n", MmsValue_getType(CoilStatus));
        //     if (MmsValue_getType(CoilStatus) == MMS_BOOLEAN)
        //     {
        //         bool status = MmsValue_getBoolean(CoilStatus);
        //         // printf("\nfval bool : %d", fval);
        //         printf("Safety Valve Opened : %s\n", status == 1 ? "True" : "False");
        //     }
        //     else if (MmsValue_getType(CoilStatus) == MMS_DATA_ACCESS_ERROR)
        //     {
        //         printf("Failed to read value (error code: %i)\n", MmsValue_getDataAccessError(CoilStatus));
        //     }

        //     MmsValue_delete(CoilStatus);
        // }

        /* read data set */
        ClientDataSet clientDataSet = IedConnection_readDataSetValues(con, &error, "IED01LogicalDevice/LLN0.Measurements", NULL);
        // IED01LogicalDevice/LLN0$Measurements

        if (clientDataSet == NULL)
            printf("failed to read dataset\n");

        /* Read RCB values */
        ClientReportControlBlock rcb =
            IedConnection_getRCBValues(con, &error, "IED01LogicalDevice/LLN0.RP.Measurements01", NULL);

        bool rptEna = ClientReportControlBlock_getRptEna(rcb);

        printf("RptEna = %i\n", rptEna);

        /* Install handler for reports */
        IedConnection_installReportHandler(con, "IED01LogicalDevice/LLN0.RP.Measurements01",
                                           ClientReportControlBlock_getRptId(rcb), reportCallbackFunction, NULL);

        /* Set trigger options and enable report */
        ClientReportControlBlock_setTrgOps(rcb, TRG_OPT_DATA_UPDATE | TRG_OPT_INTEGRITY | TRG_OPT_GI);
        ClientReportControlBlock_setRptEna(rcb, true);
        ClientReportControlBlock_setIntgPd(rcb, 5000);
        IedConnection_setRCBValues(con, &error, rcb, RCB_ELEMENT_RPT_ENA | RCB_ELEMENT_TRG_OPS | RCB_ELEMENT_INTG_PD, true);

        if (error != IED_ERROR_OK)
            printf("report activation failed (code: %i)\n", error);

        Thread_sleep(1000);

        /* trigger GI report */
        ClientReportControlBlock_setGI(rcb, true);
        IedConnection_setRCBValues(con, &error, rcb, RCB_ELEMENT_GI, true);

        if (error != IED_ERROR_OK)
            printf("Error triggering a GI report (code: %i)\n", error);

        Thread_sleep(60000);

        /* disable reporting */
        ClientReportControlBlock_setRptEna(rcb, false);
        IedConnection_setRCBValues(con, &error, rcb, RCB_ELEMENT_RPT_ENA, true);

        if (error != IED_ERROR_OK)
            printf("disable reporting failed (code: %i)\n", error);

        ClientDataSet_destroy(clientDataSet);

        ClientReportControlBlock_destroy(rcb);

        // close_connection:

        //     IedConnection_close(con);
    }
    else
    {
        printf("Failed to connect to %s:%i\n", hostname, tcpPort);
        Thread_sleep(60000);
    }

    IedConnection_destroy(con);

    return 0;
}
