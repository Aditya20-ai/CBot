#include <concord/discord.h>
#include <concord/log.h>
#include <time.h>
#include "../utils/timestamp.c"

void slashy_ping(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */
    int ping = discord_get_ping(client);
    char message[DISCORD_MAX_MESSAGE_LEN];
    snprintf(message, sizeof(message), "The ping of the bot is %dms", ping);
    if (strcmp(event->data->name, "ping") == 0) {
        struct discord_interaction_response params = {
            .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
            .data = &(struct discord_interaction_callback_data){
                .content = message
            }
        };
        discord_create_interaction_response(client, event->id, event->token, &params, NULL);
    }
    
}