/*
 * static_model.c
 *
 * automatically generated from ied01.icd
 */
#include "static_model.h"

static void initializeValues();

extern DataSet iedModelds_LogicalDevice_LLN0_Measurements;


extern DataSetEntry iedModelds_LogicalDevice_LLN0_Measurements_fcda0;

DataSetEntry iedModelds_LogicalDevice_LLN0_Measurements_fcda0 = {
  "LogicalDevice",
  false,
  "GGIO1$MX$CurrentPressure$mag$f", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_LogicalDevice_LLN0_Measurements = {
  "LogicalDevice",
  "LLN0$Measurements",
  1,
  &iedModelds_LogicalDevice_LLN0_Measurements_fcda0,
  NULL
};

LogicalDevice iedModel_LogicalDevice = {
    LogicalDeviceModelType,
    "LogicalDevice",
    (ModelNode*) &iedModel,
    NULL,
    (ModelNode*) &iedModel_LogicalDevice_LLN0,
    NULL
};

LogicalNode iedModel_LogicalDevice_LLN0 = {
    LogicalNodeModelType,
    "LLN0",
    (ModelNode*) &iedModel_LogicalDevice,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod,
};

DataObject iedModel_LogicalDevice_LLN0_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_LogicalDevice_LLN0,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_LLN0_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_LLN0_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_LogicalDevice_LLN0,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_LLN0_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_LLN0_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_LogicalDevice_LLN0,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_LLN0_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_LLN0_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_LogicalDevice_LLN0,
    NULL,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_LLN0_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt_ldNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_LLN0_NamPlt_ldNs = {
    DataAttributeModelType,
    "ldNs",
    (ModelNode*) &iedModel_LogicalDevice_LLN0_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

LogicalNode iedModel_LogicalDevice_GGIO1 = {
    LogicalNodeModelType,
    "GGIO1",
    (ModelNode*) &iedModel_LogicalDevice,
    NULL,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod,
};

DataObject iedModel_LogicalDevice_GGIO1_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_GGIO1_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_GGIO1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_GGIO1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_GGIO1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_GGIO1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_GGIO1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_GGIO1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt_ldNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_NamPlt_ldNs = {
    DataAttributeModelType,
    "ldNs",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_LogicalDevice_GGIO1_CurrentPressure = {
    DataObjectModelType,
    "CurrentPressure",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1,
    NULL,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure_mag,
    0,
    -1
};

DataAttribute iedModel_LogicalDevice_GGIO1_CurrentPressure_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure_q,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_CurrentPressure_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT16,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_CurrentPressure_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure,
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_LogicalDevice_GGIO1_CurrentPressure_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_LogicalDevice_GGIO1_CurrentPressure,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

extern ReportControlBlock iedModel_LogicalDevice_LLN0_report0;
extern ReportControlBlock iedModel_LogicalDevice_LLN0_report1;
extern ReportControlBlock iedModel_LogicalDevice_LLN0_report2;
extern ReportControlBlock iedModel_LogicalDevice_LLN0_report3;
extern ReportControlBlock iedModel_LogicalDevice_LLN0_report4;

ReportControlBlock iedModel_LogicalDevice_LLN0_report0 = {&iedModel_LogicalDevice_LLN0, "Measurements01", "Measurements", false, "Measurements", 0, 31, 255, 50, 1000, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_LogicalDevice_LLN0_report1};
ReportControlBlock iedModel_LogicalDevice_LLN0_report1 = {&iedModel_LogicalDevice_LLN0, "Measurements02", "Measurements", false, "Measurements", 0, 31, 255, 50, 1000, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_LogicalDevice_LLN0_report2};
ReportControlBlock iedModel_LogicalDevice_LLN0_report2 = {&iedModel_LogicalDevice_LLN0, "Measurements03", "Measurements", false, "Measurements", 0, 31, 255, 50, 1000, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_LogicalDevice_LLN0_report3};
ReportControlBlock iedModel_LogicalDevice_LLN0_report3 = {&iedModel_LogicalDevice_LLN0, "Measurements04", "Measurements", false, "Measurements", 0, 31, 255, 50, 1000, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_LogicalDevice_LLN0_report4};
ReportControlBlock iedModel_LogicalDevice_LLN0_report4 = {&iedModel_LogicalDevice_LLN0, "Measurements05", "Measurements", false, "Measurements", 0, 31, 255, 50, 1000, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, NULL};







IedModel iedModel = {
    "IED01",
    &iedModel_LogicalDevice,
    &iedModelds_LogicalDevice_LLN0_Measurements,
    &iedModel_LogicalDevice_LLN0_report0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    initializeValues
};

static void
initializeValues()
{

iedModel_LogicalDevice_LLN0_Mod_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_LogicalDevice_LLN0_Mod_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(0);

iedModel_LogicalDevice_LLN0_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_LogicalDevice_LLN0_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_LogicalDevice_GGIO1_Mod_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_LogicalDevice_GGIO1_Mod_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(0);

iedModel_LogicalDevice_GGIO1_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_LogicalDevice_GGIO1_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);
}
