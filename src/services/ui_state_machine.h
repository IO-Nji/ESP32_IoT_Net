#ifndef UI_STATE_MACHINE_H
#define UI_STATE_MACHINE_H
#include <stdint.h>
#include "src/hal/hal_button.h"

// UI Screens
typedef enum {
    UI_SCREEN_HOME = 0,
    UI_SCREEN_SENSOR,
    UI_SCREEN_NETWORK,
    UI_SCREEN_COUNT
} UIScreen;

// UI Event Types
typedef enum {
    UI_EVENT_NONE = 0,
    UI_EVENT_SELECT,
    UI_EVENT_UP,
    UI_EVENT_DOWN,
    UI_EVENT_BACK
} UIEventType;

// UI Event
typedef struct {
    UIEventType type;
} UIEvent;

// Event Queue
#define UI_EVENT_QUEUE_SIZE 8
extern UIEvent uiEventQueue[UI_EVENT_QUEUE_SIZE];
extern uint8_t uiEventQueueHead;
extern uint8_t uiEventQueueTail;

void ui_state_machine_init();
void ui_state_machine_handle_event(const UIEvent* event);
void ui_event_queue_push(UIEventType type);
UIEvent ui_event_queue_pop();
UIScreen ui_state_machine_get_screen();

#endif // UI_STATE_MACHINE_H
