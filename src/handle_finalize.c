#include "stakekit_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    plugin_parameters_t *context = (plugin_parameters_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    if (context->valid) {
        switch (context->selectorIndex)
        {
        case DEPOSIT_SELF_APECOIN:
            msg->numScreens = 1;
            context->decimals_sent = DEFAULT_DECIMAL;
            strlcpy(context->ticker_sent, APE_TICKER, sizeof(context->ticker_sent));
            PRINTF("Ticker sent: %s\n", context->ticker_sent);
            break;
        default:
            msg->numScreens = 1;
            break;
        }

        msg->result = ETH_PLUGIN_RESULT_OK;
    } else {
        PRINTF("Context not valid\n");
        msg->result = ETH_PLUGIN_RESULT_FALLBACK;
    }
}
