#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "DEBUG_PORT";

void app_main(void)
{
    ESP_LOGI(TAG, "=== ESP-IDF Debug Port Started ===");
    ESP_LOGI(TAG, "Type something in the terminal and press Enter...");

    char buffer[128];
    int index = 0;

    while (1) {
        // Read 1 character from the serial/debug port
        int c = getchar();

        // getchar() returns EOF if no character is available
        if (c != EOF) {
            // Process line when Enter ('\n' or '\r') is pressed
            if (c == '\n' || c == '\r') {
                if (index > 0) {
                    buffer[index] = '\0'; // Null-terminate string

                    // Send received message back via debug port
                    ESP_LOGI(TAG, "Received message: %s", buffer);

                    // Reset buffer index
                    index = 0;
                }
            } else {
                // Add character to buffer (prevent overflow)
                if (index < sizeof(buffer) - 1) {
                    buffer[index++] = (char)c;
                }
            }
        }

        // Short delay to prevent watchdog timer triggers
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}