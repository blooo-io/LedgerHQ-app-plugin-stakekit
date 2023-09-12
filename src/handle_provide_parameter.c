#include "stakekit_plugin.h"

static void handle_deposit_self_apecoin(ethPluginProvideParameter_t *msg,
                                        plugin_parameters_t *context) {
    switch (context->next_param) {
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    plugin_parameters_t *context = (plugin_parameters_t *) msg->pluginContext;

    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DEPOSIT_SELF_APECOIN:
            copy_parameter(context->amount_sent, msg->parameter, INT256_LENGTH);
            break;
        case WITHDRAW_SELF_APECOIN:
            copy_parameter(context->amount_received, msg->parameter, INT256_LENGTH);
            break;
        default:
            PRINTF("Selector Index %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}