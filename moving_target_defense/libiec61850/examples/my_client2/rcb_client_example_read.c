// /*
//  * client_example1.c
//  *
//  * This example is intended to be used with server_example_basic_io or server_example_goose.
//  */

// #include "iec61850_client.h"

// #include <stdlib.h>
// #include <stdio.h>

// #include "hal_thread.h"

// void reportCallbackFunction(void *parameter, ClientReport report)
// {
//     MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

//     printf("received report for %s\n", ClientReport_getRcbReference(report));

//     int i;
//     for (i = 0; i < 4; i++)
//     {
//         ReasonForInclusion reason = ClientReport_getReasonForInclusion(report, i);

//         if (reason != IEC61850_REASON_NOT_INCLUDED)
//         {
//             printf("  GGIO1.SPCSO%i.stVal: %i (included for reason %i)\n", i,
//                    MmsValue_getBoolean(MmsValue_getElement(dataSetValues, i)), reason);
//         }
//     }
// }

// int main(int argc, char **argv)
// {

//     char *hostname;
//     int tcpPort = 102;
//     const char *localIp = NULL;
//     int localTcpPort = -1;

//     if (argc > 1)
//         hostname = argv[1];
//     else
//         // hostname = "192.168.0.108";
//         hostname = "h2.com";

//     if (argc > 2)
//         tcpPort = atoi(argv[2]);

//     if (argc > 3)
//         localIp = argv[3];

//     if (argc > 4)
//         localTcpPort = atoi(argv[4]);

//     IedClientError error;

//     IedConnection con = IedConnection_create();

//     /* Optional bind to local IP address/interface */
//     if (localIp)
//     {
//         IedConnection_setLocalAddress(con, localIp, localTcpPort);
//         printf("Bound to Local Address: %s:%i\n", localIp, localTcpPort);
//     }

//     IedConnection_connect(con, &error, hostname, tcpPort);
//     printf("Connecting to %s:%i\n", hostname, tcpPort);

//     if (error == IED_ERROR_OK)
//     {
//         printf("Connected\n");

//         /* read an analog measurement value from server */

//         // Current Pressure
//         MmsValue *CurrentPressure = IedConnection_readObject(con, &error, "IED01LogicalDevice/GGIO1.CurrentPressure.mag.f", IEC61850_FC_MX);

//         if (CurrentPressure != NULL)
//         {
//             // printf("\nMmsValue_getType(value) : %d\n", MmsValue_getType(CurrentPressure));
//             if (MmsValue_getType(CurrentPressure) == MMS_INTEGER)
//             {
//                 int fval = MmsValue_toInt32(CurrentPressure);
//                 printf("Current Pressure Value : %d\n", fval);
//             }
//             else if (MmsValue_getType(CurrentPressure) == MMS_DATA_ACCESS_ERROR)
//             {
//                 printf("Failed to read value (error code: %i)\n", MmsValue_getDataAccessError(CurrentPressure));
//             }

//             MmsValue_delete(CurrentPressure);
//         }

//     close_connection:

//         IedConnection_close(con);
//     }
//     else
//     {
//         printf("Failed to connect to %s:%i\n", hostname, tcpPort);
//         Thread_sleep(60000);
//     }

//     IedConnection_destroy(con);

//     return 0;
// }

#include "iec61850_client.h"

#include <stdlib.h>
#include <stdio.h>

#include "hal_thread.h"

// void reportHandler(void *parameter, ClientReport report)
// {
//     MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

//     printf("received report for %s\n", ClientReport_getRcbReference(report));

//     printf("pressure value = %d", MmsValue_toInt32(MmsValue_getElement(dataSetValues, 8)));

//     // int i;
//     // for (i = 0; i < 4; i++)
//     // {
//     //     ReasonForInclusion reason = ClientReport_getReasonForInclusion(report, i);

//     //     if (reason != IEC61850_REASON_NOT_INCLUDED)
//     //     {
//     //         printf("  GGIO1.SPCSO%i.stVal: %i (included for reason %i)\n", i,
//     //                MmsValue_getBoolean(MmsValue_getElement(dataSetValues, i)), reason);
//     //     }
//     // }
// }

// void reportHandler(void *parameter, ClientReport report)
// {
//     MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

//     if (dataSetValues == NULL)
//     {
//         printf("Failed to get data set values.\n");
//         return;
//     }

//     int numValues = MmsValue_getArraySize(dataSetValues);
//     printf("Received report for %s with %d values\n", ClientReport_getRcbReference(report), numValues);

//     if (numValues > 8)
//     {                                                                    // Check if the expected index exists
//         MmsValue *pressureValue = MmsValue_getElement(dataSetValues, 8); // 8th item (index 7)

//         if (MmsValue_getType(pressureValue) == MMS_INTEGER)
//         {
//             int pressure = MmsValue_toInt32(pressureValue);
//             printf("Current Pressure: %d\n", pressure);
//         }
//         else
//         {
//             printf("Unexpected data type for pressure value.\n");
//         }
//     }
//     else
//     {
//         printf("Not enough values in report.\n");
//     }
// }

// void reportHandler(void *parameter, ClientReport report)
// {
//     MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

//     if (dataSetValues == NULL)
//     {
//         printf("Failed to get data set values.\n");
//         return;
//     }

//     int numValues = MmsValue_getArraySize(dataSetValues);
//     printf("Received report for %s with %d values\n", ClientReport_getRcbReference(report), numValues);

//     // Debug print all values
//     for (int i = 0; i < numValues; i++)
//     {
//         MmsValue *value = MmsValue_getElement(dataSetValues, i);
//         if (value == NULL)
//         {
//             printf("Value %d is NULL\n", i);
//             continue;
//         }

//         switch (MmsValue_getType(value))
//         {
//         case MMS_VISIBLE_STRING:
//             printf("Value %d: %s (String)\n", i, MmsValue_toString(value));
//             break;
//         case MMS_INTEGER:
//             printf("Value %d: %d (Integer)\n", i, MmsValue_toInt32(value));
//             break;
//         case MMS_UNSIGNED:
//             printf("Value %d: %u (Unsigned)\n", i, MmsValue_toUint32(value));
//             break;
//         // case MMS_BIT_STRING:
//         //     printf("Value %d: %s (Bit String)\n", i, MmsValue_newBitString(value));
//         //     break;
//         case MMS_BINARY_TIME:
//             printf("Value %d: (Binary Time)\n", i);
//             break;
//         default:
//             printf("Value %d: (Unhandled Type)\n", i);
//             break;
//         }
//     }

//     if (numValues > 8)
//     { // Check if the expected index exists
//         MmsValue *pressureValue = MmsValue_getElement(dataSetValues, 8);

//         if (MmsValue_getType(pressureValue) == MMS_INTEGER)
//         {
//             int pressure = MmsValue_toInt32(pressureValue);
//             printf("Current Pressure: %d\n", pressure);
//         }
//         else
//         {
//             printf("Unexpected data type for pressure value.\n");
//         }
//     }
//     else
//     {
//         printf("Not enough values in report.\n");
//     }
// }

void reportHandler(void *parameter, ClientReport report)
{
    MmsValue *dataSetValues = ClientReport_getDataSetValues(report);

    if (dataSetValues == NULL)
    {
        printf("Failed to get data set values.\n");
        return;
    }

    int numValues = MmsValue_getArraySize(dataSetValues);
    printf("Received report for %s with %d values\n", ClientReport_getRcbReference(report), numValues);

    MmsValue *pressureValue = MmsValue_getElement(dataSetValues, 0);

    if (MmsValue_getType(pressureValue) == MMS_INTEGER)
    {
        int pressure = MmsValue_toInt32(pressureValue);
        printf("Current Pressure: %d\n", pressure);
    }
    else
    {
        printf("Unexpected data type for pressure value.\n");
    }
}

int main(int argc, char **argv)
{

    const char *serverIp = "h2.com";
    int serverPort = 102;

    IedClientError error;
    IedConnection connection = IedConnection_create();

    IedConnection_connect(connection, &error, serverIp, serverPort);
    if (error != IED_ERROR_OK)
    {
        printf("Failed to connect to server: %d\n", error);
        IedConnection_destroy(connection);
        return 1;
    }

    printf("Connected to server %s:%d\n", serverIp, serverPort);

    ClientReportControlBlock rcb =
        IedConnection_getRCBValues(connection, &error, "IED01LogicalDevice/LLN0.RP.Measurements01", NULL);

    if (rcb)
    {
        bool rptEna = ClientReportControlBlock_getRptEna(rcb);

        printf("RptEna = %i\n", rptEna);

        /* Install handler for reports */
        IedConnection_installReportHandler(connection, "IED01LogicalDevice/LLN0.RP.Measurements01",
                                           ClientReportControlBlock_getRptId(rcb), reportHandler, NULL);

        /* Set trigger options and enable report */
        ClientReportControlBlock_setTrgOps(rcb, TRG_OPT_DATA_UPDATE | TRG_OPT_INTEGRITY | TRG_OPT_GI);
        ClientReportControlBlock_setRptEna(rcb, true);
        ClientReportControlBlock_setIntgPd(rcb, 5000);
        IedConnection_setRCBValues(connection, &error, rcb, RCB_ELEMENT_RPT_ENA | RCB_ELEMENT_TRG_OPS | RCB_ELEMENT_INTG_PD, true);
    }

    // IedConnection_installReportHandler(connection, "IED01LogicalDevice/LLN0.RP.Measurements01", ClientReportControlBlock_getRptId(rcb), reportHandler, NULL);

    while (1)
    {
        sleep(5); // Fixed interval
    }

    IedConnection_destroy(connection);
    return 0;
}
