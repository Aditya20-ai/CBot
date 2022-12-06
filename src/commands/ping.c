#include <concord/discord.h>
#include <concord/log.h>
#include <assert.h>


void ping(struct discord *client, const struct discord_message *this) {
    int WSPING;
    char ping_str[DISCORD_MAX_MESSAGE_LEN]; 
    WSPING = discord_get_ping(client);
    snprintf(ping_str, sizeof(ping_str), "Pong! ⏰: %dms", WSPING);
    struct discord_create_message params = {
        .content = ping_str
    };
    
    discord_create_message(client, this->channel_id, &params, NULL);
}