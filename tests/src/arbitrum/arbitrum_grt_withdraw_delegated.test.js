import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy";  // <= Name of the smart contract

const testLabel = "arbitrum_grt_withdraw_delegated"; // <= Name of the test
const testDirSuffix = "arbitrum_grt_withdraw_delegated"; // <= directory to compare device snapshots to
const testNetwork = "arbitrum";
const signedPlugin = false;

const contractAddr = "0x00669a4cf01450b64e8a2a20e9b1fcb71e61ef03";   // <= Address of the smart contract
const chainID = 42161;

// From : https://arbiscan.io/tx/0x94ff11c4144b4823a39acd6e861670d54010436c93f50608f2d84db8ac87941c
const inputData = "0x51a60b020000000000000000000000001b7e0068ca1d7929c8c56408d766e1510e54d98d0000000000000000000000000000000000000000000000000000000000000000";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 6, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 4, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 4, // <= Define the number of steps for this test case and this device
    },
    {
        name: "stax",
        label: "Stax",
    },
    {
        name: "flex",
        label: "Flex",
    }
];

devices.forEach((device) =>
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);
