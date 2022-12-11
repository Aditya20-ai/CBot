#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <time.h>

time_t discordSnowflakeToUnixMs(long int discord_snowflake);
time_t currentTimestamp();

#endif /* TIMESTAMP_H */
