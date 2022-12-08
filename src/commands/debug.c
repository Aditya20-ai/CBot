#include <concord/discord.h>
#include <concord/log.h>
#include <assert.h>
#include <string.h>
#include <time.h>
//#include "../utils/timestamp.c"

void debug(struct discord *client, const struct discord_message *this) {
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
    time_t gateway_ping = current_timestamp - message_timestamp;
    snprintf(gateway_ping_str, sizeof(gateway_ping_str), "Gateway 💗: %ldms\n The current timestamp is %ld \nthe timestamp at which the message was sent is %ld", gateway_ping, current_timestamp, message_timestamp);
    strcat(ping_str, gateway_ping_str);
    struct discord_edit_message params2 = {
        .content = ping_str
    };
    discord_edit_message(client, this->channel_id, msg.id, &params2, NULL);
}


    /*
    Check the gateway ping of the app by sending a message called "checking gateway ping" and then editing 
    it again, after that subtract the time that it took to perform the request and 
    display it as the gateway ping
    */

    