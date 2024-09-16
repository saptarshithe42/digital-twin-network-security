import React from "react";

function IED_xml({
    IEDName,
    IEDType,
    IEDManufacturer,
    accessPointName,
    IP,
    IP_SUBNET,
    IP_GATEWAY,
    LDeviceName,
    LN0lnType,
    LN0DatasetName,
    reportIntegrityPeriod,
    maxClientsAllowed,
    LNType,
    LNClass,
    LN_DOI_List,
}) {
    return (
        <div id="ied-xml-code">
            <pre>
                {`<?xml version="1.0" encoding="utf-8"?>
<SCL xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns="http://www.iec.ch/61850/2003/SCL">
  <Header id="${IEDName}" nameStructure="IEDName" />
  <Communication>
    <SubNetwork name="node">
      <ConnectedAP iedName="${IEDName}" apName="${accessPointName}">
        <Address>
          <P type="IP">${IP}</P>
          <P type="IP-SUBNET">${IP_SUBNET}</P>
          <P type="IP-GATEWAY">${IP_GATEWAY}</P>
        </Address>
      </ConnectedAP>
    </SubNetwork>
  </Communication>
  <IED name="${IEDName}" type="${IEDType}" manufacturer="${IEDManufacturer}" configVersion="1.0">
    <Services>
      <DynAssociation />
      <SettingGroups />
      <GetDirectory />
      <GetDataObjectDefinition />
      <GetDataSetValue />
      <SetDataSetValue />
      <DataSetDirectory />
      <ConfDataSet max="2" />
      <DynDataSet max="2" maxAttributes="50" />
      <ReadWrite />
      <TimerActivatedControl />
      <ConfReportControl max="14" />
      <GetCBValues />
      <ReportSettings cbName="Fix" datSet="Fix" rptID="Dyn" optFields="Dyn" bufTime="Dyn"
        trgOps="Dyn" intgPd="Dyn" />
      <ConfLNs fixPrefix="true" fixLnInst="true" />
      <GOOSE max="0" />
    </Services>
    <AccessPoint name="${accessPointName}" desc="">
      <Server>
        <Authentication none="true" />
        <LDevice inst="${LDeviceName}" desc="">
          <LN0 desc="" lnType="${LN0lnType}" lnClass="LLN0" inst="">
            <DataSet name="${LN0DatasetName}">
              <FCDA ldInst="LogicalDevice" prefix="" lnClass="GGIO" lnInst="1"
                doName="CurrentPressure"
                daName="mag.f" fc="MX" />
            </DataSet>

            <ReportControl name="Measurements" desc="" datSet="Measurements" intgPd="${reportIntegrityPeriod}"
              rptID="Measurements" confRev="0" buffered="false" bufTime="50">
              <TrgOps dchg="true" qchg="true" dupd="true" period="true" />
              <OptFields seqNum="true" timeStamp="true" reasonCode="true" dataSet="true"
                dataRef="true" entryID="true" configRef="true" />
              <RptEnabled max="${maxClientsAllowed}" />
            </ReportControl>

            <DOI name="Mod">
              <DAI name="stVal">
                <Val>on</Val>
              </DAI>
              <DAI name="ctlModel">
                <Val>status-only</Val>
              </DAI>
            </DOI>
            <DOI name="Beh">
              <DAI name="stVal">
                <Val>on</Val>
              </DAI>
            </DOI>
            <DOI name="Health">
              <DAI name="stVal">
                <Val>ok</Val>
              </DAI>
            </DOI>
          </LN0>

          <LN desc="" lnType="${LNType}" lnClass="${LNClass}" inst="1" prefix="">
            <DOI name="Mod">
              <DAI name="stVal">
                <Val>on</Val>
              </DAI>
              <DAI name="ctlModel">
                <Val>status-only</Val>
              </DAI>
            </DOI>
            <DOI name="Beh">
              <DAI name="stVal">
                <Val>on</Val>
              </DAI>
            </DOI>
            <DOI name="Health">
              <DAI name="stVal">
                <Val>ok</Val>
              </DAI>
            </DOI>

<!--  =============================================================
                  User Defined DOIs
      ============================================================== -->
            `}
            </pre>
            <pre>
                {LN_DOI_List.map((doi, index) => {
                    return `            <DOI name="${doi?.name}" />\n`;
                })}
            </pre>
            <pre>
                {`\t  </LN>
        </LDevice>
      </Server>
    </AccessPoint>
  </IED>
  <DataTypeTemplates>
    <LNodeType id="LLN0_0" lnClass="LLN0">
      <DO name="Mod" type="ENC_1_Mod" />
      <DO name="Beh" type="ENS_1_Beh" />
      <DO name="Health" type="ENS_2_Health" />
      <DO name="NamPlt" type="LPL_1_NamPlt" />
    </LNodeType>
    <LNodeType id="${LNType}" lnClass="${LNClass}">
      <DO name="Mod" type="ENC_1_Mod" />
      <DO name="Beh" type="ENS_1_Beh" />
      <DO name="Health" type="ENS_2_Health" />
      <DO name="NamPlt" type="LPL_1_NamPlt" />
      
  <!--  =============================================================
              User Defined DOs
        ============================================================= -->
      `}
            </pre>
            <pre>
                {LN_DOI_List.map((doi, index) => {
                    return `      <DO name="${doi?.name}" type="${
                        doi?.cdc + "_" + doi?.name
                    }" />\n`;
                })}
            </pre>
            <pre>
                {`
      
    </LNodeType>

    <DOType id="ENC_1_Mod" cdc="ENC">
      <DA name="stVal" bType="Enum" type="Beh" fc="ST" dchg="true" />
      <DA name="q" bType="Quality" fc="ST" qchg="true" />
      <DA name="t" bType="Timestamp" fc="ST" />
      <DA name="ctlModel" type="CtlModels" bType="Enum" fc="CF" />
    </DOType>
    <DOType id="ENS_1_Beh" cdc="ENS">
      <DA name="stVal" bType="Enum" type="Beh" fc="ST" dchg="true" />
      <DA name="q" bType="Quality" fc="ST" qchg="true" />
      <DA name="t" bType="Timestamp" fc="ST" />
    </DOType>
    <DOType id="ENS_2_Health" cdc="ENS">
      <DA name="stVal" bType="Enum" type="HealthKind" fc="ST" dchg="true" />
      <DA name="q" bType="Quality" fc="ST" qchg="true" />
      <DA name="t" bType="Timestamp" fc="ST" />
    </DOType>
    <DOType id="LPL_1_NamPlt" cdc="LPL">
      <DA name="vendor" bType="VisString255" fc="DC" />
      <DA name="swRev" bType="VisString255" fc="DC" />
      <DA name="d" bType="VisString255" fc="DC" />
      <DA name="configRev" bType="VisString255" fc="DC" />
      <DA name="ldNs" bType="VisString255" fc="EX" />
    </DOType>

    <!--  =============================================================
                  User Defined DOTypes
          ============================================================== -->
    `}
            </pre>
            <pre>
                {LN_DOI_List.map((doi, index) => {
                    return `      <DOType id="${
                        doi?.cdc + "_" + doi?.name
                    }" cdc="${doi?.cdc}" />
        <DA name="mag" type="${
            doi?.cdc + "_" + doi?.name + "_Value"
        }" bType="Struct" fc="${doi?.fc}" dchg="true">
          <Private name="mag">
            <Private name="f">
                <Property Name="${doi?.openplcVarType}" Value="${
                        doi?.openplcVar
                    }" />
            </Private>
          </Private>
        </DA>
      </DOType>\n\n`;
                })}
            </pre>
            <pre>
                {`

<!--  =============================================================
                  User Defined DATypes
      ============================================================== -->
       `}
            </pre>
            <pre>
                {LN_DOI_List.map((doi, index) => {
                    return `      <DAType id="${
                        doi?.cdc + "_" + doi?.name + "_Value"
                    }" >
        <BDA name="f" bType="${doi?.bType}" />
      </DAType>\n\n`;
                })}
            </pre>
            <pre>
                {`

    <EnumType id="Beh">
      <EnumVal ord="1">on</EnumVal>
      <EnumVal ord="2">blocked</EnumVal>
      <EnumVal ord="3">test</EnumVal>
      <EnumVal ord="4">test/blocked</EnumVal>
      <EnumVal ord="5">off</EnumVal>
    </EnumType>
    <EnumType id="HealthKind">
      <EnumVal ord="1">ok</EnumVal>
      <EnumVal ord="2">warning</EnumVal>
      <EnumVal ord="3">alarm</EnumVal>
    </EnumType>
    <EnumType id="CtlModels">
      <EnumVal ord="0">status-only</EnumVal>
      <EnumVal ord="1">direct-with-normal-security</EnumVal>
      <EnumVal ord="2">sbo-with-normal-security</EnumVal>
      <EnumVal ord="3">direct-with-enhanced-security</EnumVal>
      <EnumVal ord="4">sbo-with-enhanced-security</EnumVal>
    </EnumType>
    <EnumType id="OrCat">
      <EnumVal ord="0">not-supported</EnumVal>
      <EnumVal ord="1">bay-control</EnumVal>
      <EnumVal ord="2">station-control</EnumVal>
      <EnumVal ord="3">remote-control</EnumVal>
      <EnumVal ord="4">automatic-bay</EnumVal>
      <EnumVal ord="5">automatic-station</EnumVal>
      <EnumVal ord="6">automatic-remote</EnumVal>
      <EnumVal ord="7">maintenance</EnumVal>
      <EnumVal ord="8">process</EnumVal>
    </EnumType>
  </DataTypeTemplates>
</SCL>`}
            </pre>
        </div>
    );
}

export default IED_xml;
