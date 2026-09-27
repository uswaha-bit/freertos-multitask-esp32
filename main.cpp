#include <Arduino.h>
#include <stdio.h>

#define FAST_LED_PIN 2
#define SLOW_LED_PIN 4

void fastBlinkTask(void *pvParameters) {
  pinMode(FAST_LED_PIN, OUTPUT);
  bool ledState = false;

  while (true) {
    ledState = !ledState;
    digitalWrite(FAST_LED_PIN, ledState);
    printf("Fast task: LED %s\n", ledState ? "ON" : "OFF");
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void slowBlinkTask(void *pvParameters) {
  pinMode(SLOW_LED_PIN, OUTPUT);
  bool ledState = false;

  while (true) {
    ledState = !ledState;
    digitalWrite(SLOW_LED_PIN, ledState);
    printf("Slow task: LED %s\n", ledState ? "ON" : "OFF");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  printf("Starting FreeRTOS multi-task LED demo\n");

  xTaskCreate(fastBlinkTask, "fastBlinkTask", 2048, NULL, 5, NULL);
  xTaskCreate(slowBlinkTask, "slowBlinkTask", 2048, NULL, 5, NULL);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}