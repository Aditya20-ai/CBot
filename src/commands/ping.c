#include <concord/discord.h>
#include <concord/log.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <include/timestamp.h>
#include <include/apiPing.h>

// Eventually push this into an embed and display it properly
// Use .done and .fail instead of .sync 
// .done and .fail are async functions while .sync is a sync function which is far less efficient and can cause issues when multiple people use the command at the same time

void apiPing(struct discord *client, const struct discord_message *this) {
    char ping_str[DISCORD_MAX_MESSAGE_LEN];
    char gateway_ping_str[DISCORD_MAX_MESSAGE_LEN];
    struct discord_message msg = { 0 };
    struct discord_ret_message ret = { .sync = &msg };
    // Send the websocket ping
    int WSPING;
    WSPING = discord_get_ping(client);
    snprintf(ping_str, sizeof(ping_str), "Pong! 🏓: %dms\n", WSPING);
    struct discord_create_message params = {
        .content = ping_str
    };
    discord_create_message(client, this->channel_id, &params, &ret);
    time_t message_timestamp = discordSnowflakeToUnixMs(msg.id);
    time_t current_timestamp = currentTimestamp();
    long int gateway_ping = current_timestamp - message_timestamp;
    if (gateway_ping < 0) {
        log_error("The gateway ping is negetive - It is %ld", gateway_ping);
        gateway_ping = gateway_ping * -1;
    } // This is an incredibly ugly workaround for this bug that I can't figure out
    snprintf(gateway_ping_str, sizeof(gateway_ping_str), "Gateway 💗: %ldms\n The current timestamp is %ld \nthe timestamp at which the message was sent is %ld", gateway_ping, current_timestamp, message_timestamp);
    strcat(ping_str, gateway_ping_str);
    struct discord_edit_message params2 = {
        .content = ping_str
    };
    discord_edit_message(client, this->channel_id, msg.id, &params2, NULL);
}