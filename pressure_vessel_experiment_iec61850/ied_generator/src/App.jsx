import { useState } from "react";
import reactLogo from "./assets/react.svg";
import viteLogo from "/vite.svg";
import "./App.css";
import IED_xml from "./IED_xml";

function App() {
    const [IEDName, setIEDName] = useState("");
    const [accessPointName, setAccessPointName] = useState("");
    const [IP, setIP] = useState("");
    const [IPSubnet, setIPSubnet] = useState("");
    const [IPGateway, setIPGateway] = useState("");

    const fillExampleValues = () => {
        setIEDName("IED01");
        setAccessPointName("W1");
        setIP("192.168.0.106");
        setIPSubnet("255.255.255.0");
        setIPGateway("192.168.0.1");
    };

    const clearForm = () => {
        setAccessPointName("");
        setIEDName("");
        setIP("");
        setIPSubnet("");
        setIPGateway("");
    };

    const downloadTextFile = () => {
        const element = document.createElement("a");
        const file = new Blob(
            [document.getElementById("ied-xml-code").textContent],
            {
                type: "text/plain",
            }
        );
        element.href = URL.createObjectURL(file);
        element.download = "IED.xml";
        document.body.appendChild(element); // Required for this to work in FireFox
        element.click();
    };

    return (
        <div className="App">
            <div className="ied-generator-panel">
                <h1 style={{ textAlign: "center" }}>IED Generator</h1>
                <div style={{ display: "flex", justifyContent: "center" }}>
                    <button onClick={fillExampleValues}>Example</button>
                    &nbsp;&nbsp;&nbsp;&nbsp;
                    <button onClick={clearForm}>Clear</button>
                </div>
                <div>
                    <h3>Communication Specification</h3>
                    <label>IED Name : </label>
                    <input
                        value={IEDName}
                        onChange={(e) => setIEDName(e.target.value)}
                    />
                    <br />
                    <br />
                    <label>AccessPoint Name : </label>
                    <input
                        value={accessPointName}
                        onChange={(e) => setAccessPointName(e.target.value)}
                    />
                    <br />
                    <br />
                    <label>Enter IP Address : </label>
                    <input value={IP} onChange={(e) => setIP(e.target.value)} />
                    <br />
                    <br />
                    <label>Enter IP Subnet : </label>
                    <input
                        value={IPSubnet}
                        onChange={(e) => setIPSubnet(e.target.value)}
                    />
                    <br />
                    <br />
                    <label>Enter IP Gateway : </label>
                    <input
                        value={IPGateway}
                        onChange={(e) => setIPGateway(e.target.value)}
                    />
                </div>
            </div>
            <div className="ied-xml-code-view">
                <h3>IED XML Code (.icd file)</h3>
                <button onClick={downloadTextFile}>Download</button>
                <IED_xml
                    IEDName={IEDName}
                    accessPointName={accessPointName}
                    IP={IP}
                    IP_SUBNET={IPSubnet}
                    IP_GATEWAY={IPGateway}
                />
            </div>
        </div>
    );
}

export default App;
