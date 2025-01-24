import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy";  // <= Name of the smart contract

const testLabel = "arbitrum_grt_undelegate"; // <= Name of the test
const testDirSuffix = "arbitrum_grt_undelegate"; // <= directory to compare device snapshots to
const testNetwork = "arbitrum";
const signedPlugin = false;

const contractAddr = "0x00669a4cf01450b64e8a2a20e9b1fcb71e61ef03";   // <= Address of the smart contract
const chainID = 42161;

// From : https://arbiscan.io/tx/0x8149e6fe2a13bef12dc0652720cd5856163138af6c4f6545a92cd651495139ad
const inputData = "0x4d99dd16000000000000000000000000feff9093f6b32d0e5cddba743b06a1fedb87c004000000000000000000000000000000000000000000000000049e5e12b47b88bd";

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
