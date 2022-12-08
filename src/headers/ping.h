#ifndef PING_H
#define PING_H

#include <concord/discord.h>

void ping(struct discord *client, const struct discord_message *this); 

void slashy_ping(struct discord *client, const struct discord_interaction *event);

#endif /* PING_H */
