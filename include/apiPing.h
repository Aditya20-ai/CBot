#ifndef APIPING_H
#define APIPING_H

#include <concord/discord.h>

void apiPing(struct discord *client, const struct discord_message *this); 
void slashy_ping(struct discord *client, const struct discord_interaction *this);

#endif /* PING_H */
