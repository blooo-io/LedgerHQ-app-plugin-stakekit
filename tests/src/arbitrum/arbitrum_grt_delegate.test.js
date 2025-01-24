import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy";  // <= Name of the smart contract

const testLabel = "arbitrum_grt_delegate"; // <= Name of the test
const testDirSuffix = "arbitrum_grt_delegate"; // <= directory to compare device snapshots to
const testNetwork = "arbitrum";
const signedPlugin = false;

const contractAddr = "0x00669a4cf01450b64e8a2a20e9b1fcb71e61ef03";   // <= Address of the smart contract
const chainID = 42161;

// From : https://arbiscan.io/tx/0xf421b54e8fe9a2d0ae3a1c0d668ca2cca4ba6ac1ace5ff03ce3b0a449a6e2331
const inputData = "0x026e402b0000000000000000000000001b7e0068ca1d7929c8c56408d766e1510e54d98d000000000000000000000000000000000000000000001535cd06d1a3268e0f8a";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 7, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 5, // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanosp",
        label: "Nano S+",
        steps: 5, // <= Define the number of steps for this test case and this device
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
