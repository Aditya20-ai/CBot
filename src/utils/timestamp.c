#include <time.h>
#include <stdio.h>
#define DISCORD_EPOCH 1420070400000
#define CLOCK_REALTIME 0

time_t discordSnowflakeToUnixMs(long int discord_snowflake) {
    time_t discord_snowflake_time = discord_snowflake >> 22;
    time_t discord_snowflake_time_ms = discord_snowflake_time + DISCORD_EPOCH;
    return discord_snowflake_time_ms;
}

time_t currentTimestamp() {
    // Returns the current timestamp in milliseconds
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    time_t exact_time_t = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    return exact_time_t;
}


