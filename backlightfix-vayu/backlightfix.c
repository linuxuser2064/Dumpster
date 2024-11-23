#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define BRIGHTNESS_FILE "/sys/class/backlight/backlight/brightness"
#define POLL_INTERVAL_MS 10

// Function to sleep for a specified number of milliseconds
void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

// Function to read the current brightness value
long read_brightness() {
    FILE *file = fopen(BRIGHTNESS_FILE, "r");
    if (!file) {
        perror("Error opening brightness file");
        return -1;
    }

    long value = -1;
    if (fscanf(file, "%ld", &value) != 1) {
        fprintf(stderr, "Failed to read brightness value.\n");
    }
    fclose(file);
    return value;
}

// Function to write a new brightness value
void write_brightness(long value) {
    FILE *file = fopen(BRIGHTNESS_FILE, "w");
    if (!file) {
        perror("Error opening brightness file for writing");
        return;
    }

    fprintf(file, "%ld", value);
    fclose(file);
}

int main() {
//    printf("Polling %s every 16ms for changes...\n", BRIGHTNESS_FILE);

    long last_value = read_brightness();
    if (last_value == -1) {
        return EXIT_FAILURE; // Exit if unable to read the initial value
    }

    while (1) {
        sleep_ms(POLL_INTERVAL_MS);

        long current_value = read_brightness();
        if (current_value == -1) {
            continue; // Skip iteration if reading fails
        }

        // If the value has changed, process it
        if (current_value != last_value) {
//            printf("Detected change in brightness: %ld -> %ld\n", last_value, current_value);
            long new_value = current_value * 16;
            write_brightness(new_value);
//            printf("Updated brightness to: %ld\n", new_value);
            last_value = new_value; // Update last_value to prevent re-triggering
        }
    }

    return EXIT_SUCCESS;
}

