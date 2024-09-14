import React from "react";

function IED_xml({ IEDName, accessPointName, IP, IP_SUBNET, IP_GATEWAY }) {
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
  <IED name="${IEDName}" type="Telecontrol application" manufacturer="ADSC" configVersion="1.0">`}
            </pre>
        </div>
    );
}

export default IED_xml;
