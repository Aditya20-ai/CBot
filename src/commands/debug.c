#include <concord/discord.h>
#include <concord/log.h>
#include <assert.h>
#include <string.h>

void debug(struct discord *client, const struct discord_message *this) {
    char gateway_ping_str[DISCORD_MAX_MESSAGE_LEN];
    /*
    Check the gateway ping of the app by sending a message called "checking gateway ping" and then editing 
    it again, after that subtract the time that it took to perform the request and 
    display it as the gateway ping
    */
    time_t start = time(NULL);  // start timer
    struct discord_create_message params = {
        .content = "Checking gateway ping..."
    };
    struct discord_message msg = { 0 };
    struct discord_ret_message ret = { .sync = &msg };
    discord_create_message(client, this->channel_id, &params, &ret); // send message
    // struct discord_edit_message params1 = {
    //     .content = "Gateway ping is being calculated..."
    // };
    // discord_edit_message(client, this->channel_id, msg.id, &params1, &ret);
    time_t end = time(NULL); 
    long int gateway_ping = end - start;
    snprintf(gateway_ping_str, sizeof(gateway_ping_str), "Gateway 💗: %ldms\n The start is %ldms and the end is %ldms ", gateway_ping, start, end);
    // strcat(ping_str, gateway_ping_str);
    struct discord_edit_message params2 = {
        .content = gateway_ping_str
    };

    discord_edit_message(client, this->channel_id, msg.id, &params2, NULL);
}
