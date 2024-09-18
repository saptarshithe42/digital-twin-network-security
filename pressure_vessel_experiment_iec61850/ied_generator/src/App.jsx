import { useEffect, useState } from "react";
import "./App.css";
import IED_xml from "./IED_xml";
import ShortUniqueId from "short-unique-id";
import { bTypeList } from "./data/DA_bType_list";
import { cdcList } from "./data/cdc_list";
import { fcList } from "./data/fc_list";

function App() {
    const [IEDName, setIEDName] = useState("");
    const [IEDType, setIEDType] = useState("");
    const [IEDManufacturer, setIEDManufacturer] = useState("");
    const [accessPointName, setAccessPointName] = useState("");
    const [IP, setIP] = useState("");
    const [IPSubnet, setIPSubnet] = useState("");
    const [IPGateway, setIPGateway] = useState("");
    const [LDeviceName, setLDeviceName] = useState("");
    const [LN0lnType, setLN0lnType] = useState("");
    const [LN0DatasetName, setLN0DatasetName] = useState("");
    const [reportIntegrityPeriod, setReportIntegrityPeriod] = useState(1000);
    const [maxClientsAllowed, setMaxClientsAllowed] = useState(5);
    const [LNType, setLNType] = useState("");
    const [LNClass, setLNClass] = useState("");
    const [LN_DOI_List, setLN_DOI_List] = useState([]);
    const [numberOfDOIs, setNumberOfDOIs] = useState(0);

    const { randomUUID } = new ShortUniqueId({ length: 6 });

    const fillExampleValues = () => {
        setIEDName("IED01");
        setIEDType("Pressure Sensor");
        setIEDManufacturer("ABC");
        setAccessPointName("W1");
        setIP("192.168.0.106");
        setIPSubnet("255.255.255.0");
        setIPGateway("192.168.0.1");
        setLDeviceName("LogicalDevice");
        setLN0lnType("LLN0_0");
        setLN0DatasetName("Measurements");
        setReportIntegrityPeriod(1000);
        setMaxClientsAllowed(5);
        setLNType("GGIO1");
        setLNClass("GGIO");

        setNumberOfDOIs(1);
        setLN_DOI_List([
            {
                name: "CurrentPressure",
                cdc: "MV",
                fc: "MX",
                openplcVar: "raw_pressure",
                openplcVarType: "sMonitoringVar",
                bType: "INT16",
            },
        ]);
    };

    const clearForm = () => {
        setIEDName("");
        setIEDType("");
        setIEDManufacturer("");
        setAccessPointName("");
        setIP("");
        setIPSubnet("");
        setIPGateway("");
        setLDeviceName("");
        setLN0lnType("");
        setLN0DatasetName("");
        setReportIntegrityPeriod(1000);
        setMaxClientsAllowed(5);
        setLNType("");
        setLNClass("");

        setNumberOfDOIs(0);
        setLN_DOI_List([]);
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
        element.download = `IED_${randomUUID()}.icd`;
        document.body.appendChild(element); // Required for this to work in FireFox
        element.click();
    };

    const handleDOINameChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], name: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    const handleDOICdcChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], cdc: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    const handleDOIfcChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], fc: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    const handleDOIOpenPLCVariableNameChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], openplcVar: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    const handleDOIOpenPLCVariableTypeChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], openplcVarType: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    const handlebTypeChange = (e, index) => {
        const newValue = e.target.value;
        let newValues = [...LN_DOI_List];
        newValues[index] = { ...newValues[index], bType: newValue };
        setLN_DOI_List(newValues);

        console.log(newValues);
    };

    useEffect(() => {
        setLN_DOI_List((prev) => {
            let arr = [...prev];
            arr.length = numberOfDOIs;
            return arr;
        });
    }, [numberOfDOIs]);

    return (
        <div className="App">
            <div className="ied-generator-panel">
                <h1 style={{ textAlign: "center" }}>IED Generator</h1>
                <div style={{ textAlign: "center" }}>
                    <a
                        href="https://github.com/saptarshithe42/digital-twin-network-security/tree/master/pressure_vessel_experiment_iec61850/ied_generator"
                        target="_"
                    >
                        Github Repo
                    </a>
                </div>
                <br />
                <div style={{ display: "flex", justifyContent: "center" }}>
                    <button onClick={fillExampleValues}>Example</button>
                    &nbsp;&nbsp;&nbsp;&nbsp;
                    <button onClick={clearForm}>Clear</button>
                </div>
                <section>
                    <div>
                        <h3>Communication Specification</h3>
                        <label>IED Name : </label>
                        <input
                            value={IEDName}
                            onChange={(e) => setIEDName(e.target.value)}
                        />
                        <br />
                        <br />
                        <label>IED Type : </label>
                        <input
                            value={IEDType}
                            onChange={(e) => setIEDType(e.target.value)}
                        />
                        <br />
                        <br />
                        <label>IED Manufacturer : </label>
                        <input
                            value={IEDManufacturer}
                            onChange={(e) => setIEDManufacturer(e.target.value)}
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
                        <input
                            value={IP}
                            onChange={(e) => setIP(e.target.value)}
                        />
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
                </section>
                <section>
                    <div>
                        <h3>Logical Device Specification</h3>
                        <label>Enter LDevice Name : </label>
                        <input
                            value={LDeviceName}
                            onChange={(e) => setLDeviceName(e.target.value)}
                        />
                        <br />
                        <br />
                    </div>
                </section>
                <section>
                    <div>
                        <h3>Logical Node 0 (LN0) Specification</h3>
                        <label>Enter lntype : </label>
                        <input
                            value={LN0lnType}
                            onChange={(e) => setLN0lnType(e.target.value)}
                        />
                        <br />
                        <br />
                        <label>Enter Dataset Name : </label>
                        <input
                            value={LN0DatasetName}
                            onChange={(e) => setLN0DatasetName(e.target.value)}
                        />
                        <br />
                        <br />
                        <h4>Report Settings</h4>
                        <label>Enter Report Integrity Period (in ms) : </label>
                        <input
                            value={reportIntegrityPeriod}
                            onChange={(e) =>
                                setReportIntegrityPeriod(e.target.value)
                            }
                            type="number"
                        />
                        <br />
                        <br />
                        <label>
                            Enter Max Number of Clients that can connect :{" "}
                        </label>
                        <input
                            value={maxClientsAllowed}
                            onChange={(e) =>
                                setMaxClientsAllowed(e.target.value)
                            }
                            type="number"
                        />
                        <br />
                        <br />
                    </div>
                </section>
                <section>
                    <div>
                        <h3>Logical Node Specification</h3>
                        <label>Enter lntype : </label>
                        <input
                            value={LNType}
                            onChange={(e) => setLNType(e.target.value)}
                        />
                        <br />
                        <br />
                        <label>Enter LN Class : </label>
                        <input
                            value={LNClass}
                            onChange={(e) => setLNClass(e.target.value)}
                        />
                        <br />
                        <br />
                        <h4>Logical Node Custom DOI Specification</h4>
                        <label>Enter number of DOIs : </label>
                        <input
                            value={numberOfDOIs}
                            onChange={(e) => setNumberOfDOIs(e.target.value)}
                            type="number"
                            min={0}
                        />
                        <br />
                        <br />
                        {Array.from({ length: numberOfDOIs }).map(
                            (_item, index) => (
                                <div>
                                    <h3>DOI{index + 1}</h3>
                                    <label>
                                        Enter name of DOI{index + 1} :{" "}
                                    </label>
                                    <input
                                        id={"DOI" + index}
                                        value={LN_DOI_List[index]?.name || ""}
                                        onChange={(e) =>
                                            handleDOINameChange(e, index)
                                        }
                                        type="text"
                                    />
                                    <br />
                                    <br />
                                    <label>
                                        Enter cdc of DOI{index + 1} :{" "}
                                    </label>
                                    <select
                                        value={LN_DOI_List[index]?.cdc || "MV"}
                                        onChange={(e) =>
                                            handleDOICdcChange(e, index)
                                        }
                                    >
                                        {cdcList.map((cdc, index) => {
                                            return (
                                                <option value={cdc} key={cdc}>
                                                    {cdc}
                                                </option>
                                            );
                                        })}
                                    </select>
                                    <br />
                                    <br />
                                    <label>
                                        Generated DOType name of DOI{index + 1}{" "}
                                        :{" "}
                                    </label>
                                    <input
                                        id={"DOI" + index}
                                        value={
                                            LN_DOI_List[index]?.cdc +
                                                "_" +
                                                LN_DOI_List[index]?.name || ""
                                        }
                                        disabled
                                        type="text"
                                    />
                                    <br />
                                    <br />
                                    <label>
                                        Generated DAType name of the DOType for
                                        DOI{index + 1} :{" "}
                                    </label>
                                    <input
                                        id={"DOI" + index}
                                        value={
                                            LN_DOI_List[index]?.cdc +
                                                "_" +
                                                LN_DOI_List[index]?.name +
                                                "_Value" || ""
                                        }
                                        disabled
                                        type="text"
                                    />
                                    <br />
                                    <br />
                                    <label>
                                        Enter fc value of DOI{index + 1} :{" "}
                                    </label>
                                    <select
                                        value={LN_DOI_List[index]?.fc || "MX"}
                                        onChange={(e) =>
                                            handleDOIfcChange(e, index)
                                        }
                                    >
                                        {fcList.map((fc, index) => {
                                            return (
                                                <option value={fc} key={fc}>
                                                    {fc}
                                                </option>
                                            );
                                        })}
                                    </select>
                                    <br />
                                    <br />
                                    <label>
                                        Enter corresponding OpenPLC61850
                                        variable name for DOI{index + 1} :{" "}
                                    </label>
                                    <input
                                        id={"DOI" + index}
                                        value={
                                            LN_DOI_List[index]?.openplcVar || ""
                                        }
                                        onChange={(e) =>
                                            handleDOIOpenPLCVariableNameChange(
                                                e,
                                                index
                                            )
                                        }
                                        type="text"
                                    />
                                    <br />
                                    <br />
                                    <label>
                                        Enter OpenPLC61850 variable type for DOI
                                        {index + 1} :{" "}
                                    </label>
                                    <select
                                        value={
                                            LN_DOI_List[index]
                                                ?.openplcVarType ||
                                            "sMonitoringVar"
                                        }
                                        onChange={(e) =>
                                            handleDOIOpenPLCVariableTypeChange(
                                                e,
                                                index
                                            )
                                        }
                                    >
                                        <option value="sMonitoringVar">
                                            sMonitoringVar
                                        </option>
                                        <option value="sControlVar">
                                            sControlVar
                                        </option>
                                    </select>
                                    <br />
                                    <br />
                                    <label>
                                        Enter bType of BDA for DAType :{" "}
                                    </label>
                                    <select
                                        value={LN_DOI_List[index]?.bType || ""}
                                        onChange={(e) =>
                                            handlebTypeChange(e, index)
                                        }
                                    >
                                        {bTypeList.map((type, index) => {
                                            return (
                                                <option value={type} key={type}>
                                                    {type}
                                                </option>
                                            );
                                        })}
                                    </select>
                                    <br />
                                    <br />
                                </div>
                            )
                        )}
                    </div>
                </section>
            </div>
            <div className="ied-xml-code-view">
                <h3>IED XML Code (.icd file)</h3>
                <button onClick={downloadTextFile}>Download</button>
                <IED_xml
                    IEDName={IEDName}
                    IEDType={IEDType}
                    IEDManufacturer={IEDManufacturer}
                    accessPointName={accessPointName}
                    IP={IP}
                    IP_SUBNET={IPSubnet}
                    IP_GATEWAY={IPGateway}
                    LDeviceName={LDeviceName}
                    LN0lnType={LN0lnType}
                    LN0DatasetName={LN0DatasetName}
                    LNType={LNType}
                    LNClass={LNClass}
                    LN_DOI_List={LN_DOI_List}
                    reportIntegrityPeriod={reportIntegrityPeriod}
                    maxClientsAllowed={maxClientsAllowed}
                />
            </div>
        </div>
    );
}

export default App;
