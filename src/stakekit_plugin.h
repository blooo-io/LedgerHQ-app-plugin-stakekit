#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define NUM_STAKEKIT_SELECTORS 33

#define PLUGIN_NAME "StakeKit"

#define TOKEN_SENT_FOUND     1       // REMOVE IF NOT USED
#define TOKEN_RECEIVED_FOUND 1 << 1  // REMOVE IF NOT USED

#define CHAIN_ID_LENGTH 1

extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];    // REMOVE IF NOT USED
extern const uint8_t ETH_CHAIN_ID[CHAIN_ID_LENGTH];
extern const uint8_t BSC_CHAIN_ID[CHAIN_ID_LENGTH];

// Returns 1 if corresponding address is the address for the chain token (ETH, BNB, MATIC,...)
#define ADDRESS_IS_NETWORK_TOKEN(_addr) !memcmp(_addr, NULL_ETH_ADDRESS, ADDRESS_LENGTH)

// Returns 1 if corresponding address is NULL
#define ADDRESS_IS_NULL(_addr) !memcmp(_addr, NULL_ETH_ADDRESS, ADDRESS_LENGTH)

typedef enum {
    DEPOSIT_SELF_APECOIN,
    WITHDRAW_SELF_APECOIN,
    CLAIM_SELF_APECOIN,
    SUBMIT_ETH_LIDO,
    SWAP_TO,
    SWAP_FROM,
    STAKE,
    SUBMIT_MATIC_LIDO,
    REQUEST_WITHDRAW,
    CLAIM_TOKENS,
    BUY_VOUCHER,
    SELL_VOUCHER_NEW,
    MORPHO_SUPPLY_1,
    MORPHO_SUPPLY_2,
    MORPHO_SUPPLY_3,
    MORPHO_WITHDRAW_1,
    MORPHO_WITHDRAW_2,
    PARASPACE_DEPOSIT,
    PARASPACE_WITHDRAW,
    GRT_DELEGATE,
    GRT_UNDELEGATE,
    GRT_WITHDRAW_DELEGATED,
    ENTER,
    LEAVE,
    COMET_SUPPLY,
    COMET_WITHDRAW,
    COMET_CLAIM,
    TRANSFER_OUT,
    CREATE_ACCOUNT,
    LOCK,
    UNLOCK,
    VOTE,
    REVOKE_ACTIVE,
} selector_t;

extern const uint8_t *const STAKEKIT_SELECTORS[NUM_STAKEKIT_SELECTORS];

typedef enum {
    SEND_SCREEN,
    SEND_VALUE_SCREEN,
    RECEIVE_SCREEN,
    RECIPIENT_SCREEN,
    RECIPIENT_2_SCREEN,
    RECIPIENT_3_SCREEN,
    SMART_CONTRACT_SCREEN,
    WARN_SCREEN,
    ERROR,
} screens_t;

#define AMOUNT_SENT     0  // Amount sent by the user to the contract.
#define AMOUNT_RECEIVED 1  // Amount sent by the contract to the user.
#define TOKEN_SENT      2  // Amount sent by the contract to the user.
#define TOKEN_RECEIVED  3  // Amount sent by the contract to the user.
#define RECIPIENT       4  // Recipient address receiving the funds.
#define RECIPIENT_2     5  // Recipient address receiving the funds.
#define RECIPIENT_3     6  // Recipient address receiving the funds.
#define NONE            7  // Placeholder variant to be set when parsing is done.

// Number of decimals used when the token wasn't found in the CAL.
#define DEFAULT_DECIMAL WEI_TO_ETHER

// Ticker used when the token wasn't found in the CAL.
#define DEFAULT_TICKER ""

// Ticker used for ETH.
#define ETH_TICKER "ETH"

// Ticker used for BSC.
#define BNB_TICKER "BNB"

// Ticker used for WETH.
#define WETH_TICKER "WETH"

// Ticker used for APE coin staking.
#define APE_TICKER "APE"

// Ticker used for rETH.
#define ROCKET_POOL_ETH_TICKER "rETH"

// Ticker used for rETH.
#define MATIC_TICKER "MATIC"

// Ticker used for GRT.
#define GRT_TICKER "GRT"

// Ticker used for SUSHI.
#define SUSHI_TICKER "SUSHI"

// Ticker used for xSUSHI.
#define XSUSHI_TICKER "xSUSHI"

// Ticker used for rETH.
#define STAKEWISE_STAKED_ETH2_TICKER "sETH2"

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct plugin_parameters_t {
    uint8_t amount_sent[INT256_LENGTH];
    uint8_t amount_received[INT256_LENGTH];
    uint8_t contract_address_sent[ADDRESS_LENGTH];
    uint8_t contract_address_received[ADDRESS_LENGTH];
    uint8_t recipient[ADDRESS_LENGTH];
    char ticker_sent[MAX_TICKER_LEN];
    char ticker_received[MAX_TICKER_LEN];

    uint16_t offset;
    uint16_t checkpoint;
    uint8_t next_param;
    uint8_t tokens_found;
    uint8_t valid;
    uint8_t decimals_sent;
    uint8_t decimals_received;
    uint8_t selectorIndex;
    uint8_t skip;
    bool go_to_offset;
} plugin_parameters_t;  // Remove any variable not used
// 32*2 + 3*20 + 12*2 = 148
// 2*2 + 1*7 = 11
// 11+148 = 159

// Piece of code that will check that the above structure is not bigger than 5 * 32.
// Do not remove this check.
_Static_assert(sizeof(plugin_parameters_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_finalize(void *parameters);
void handle_init_contract(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}
