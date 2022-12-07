#include <concord/discord.h>
#include <concord/log.h>
#include <assert.h>
#include <string.h>
#include "commands/ping.c"
//#include "commands/debug.c"

void create_commands(struct discord *client, const struct discord_ready *bot) {
  struct discord_create_guild_application_command params = { .name = "ping" };
  discord_create_guild_application_command(client, bot->application->id, 746437092774772737 ,&params, NULL);
}

void on_ready(struct discord *client, const struct discord_ready *event) {
    log_info("Logged in as %s#%s!", event->user->username, event->user->discriminator);
    //create_commands(client, event->user);
    //discord_create_guild_application_command(client, event->application->id, 746437092774772737, &param, NULL);
   // discord_create_guild_application_command(client, event->application->id, 746437092774772737, &params, NULL);
}


void on_interaction(struct discord *client, const struct discord_interaction *event) {
    log_info("Received interaction %s from %s#%s", event->data->name, event->member->user->username, event->member->user->discriminator);
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */
 
    if (strcmp(event->data->name, "ping") == 0) {
          struct discord_interaction_response params = {
                .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                .data = &(struct discord_interaction_callback_data){
                      .content = "pong"
                }
          };
    discord_create_interaction_response(client, event->id, event->token, &params, NULL);
    }
    if (strcmp(event->data->name, "test") == 0) {
            struct discord_interaction_response params = {
                    .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                    .data = & (struct discord_interaction_callback_data) {
                        .content = "This is a test command",
                        .flags = 64
                    }
            };
        discord_create_interaction_response(client, event->id, event->token, &params, NULL);
        };
    };




void on_message(struct discord *client, const struct discord_message *this) {
    char message[DISCORD_MAX_MESSAGE_LEN];
    log_info("Received message %s from %s#%s", this->content, this->author->username, this->author->discriminator);
    if (this->author->bot) {
        return; /* ignore other bots */
    } 
    if (strcmp(this -> content, "!!whoami") == 0 ) {
        snprintf(message, sizeof(message), "You are %s#%s", this->author->username, this->author->discriminator);
        struct discord_create_message params = {
            .content = message
        };
        discord_create_message(client, this->channel_id, &params, NULL);
    }
};

int main(int argc, char *argv[]) {
    
    const char *config_file;
    if (argc > 1) {
        config_file = argv[1];
    }
    else {
        config_file = "./config.json";
    }
    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert (NULL != client && "Failed to initialize discord client");
    discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES);
    discord_add_intents(client, DISCORD_GATEWAY_MESSAGE_CONTENT);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_set_on_message_create(client, &on_message);
    discord_set_on_command(client, "ping", ping);
    //discord_set_on_command(client, "debug", debug);
    discord_run(client);
}