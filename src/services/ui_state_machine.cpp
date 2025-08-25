#include "src/services/ui_state_machine.h"

UIEvent uiEventQueue[UI_EVENT_QUEUE_SIZE];
uint8_t uiEventQueueHead = 0;
uint8_t uiEventQueueTail = 0;

static UIScreen currentScreen = UI_SCREEN_HOME;

void ui_state_machine_init() {
    currentScreen = UI_SCREEN_HOME;
    uiEventQueueHead = 0;
    uiEventQueueTail = 0;
}

void ui_state_machine_handle_event(const UIEvent* event) {
    switch (event->type) {
        case UI_EVENT_SELECT:
            if (currentScreen == UI_SCREEN_HOME) currentScreen = UI_SCREEN_SENSOR;
            else if (currentScreen == UI_SCREEN_SENSOR) currentScreen = UI_SCREEN_NETWORK;
            else if (currentScreen == UI_SCREEN_NETWORK) currentScreen = UI_SCREEN_HOME;
            break;
        case UI_EVENT_UP:
            currentScreen = (UIScreen)((currentScreen + UI_SCREEN_COUNT - 1) % UI_SCREEN_COUNT);
            break;
        case UI_EVENT_DOWN:
            currentScreen = (UIScreen)((currentScreen + 1) % UI_SCREEN_COUNT);
            break;
        case UI_EVENT_BACK:
            currentScreen = UI_SCREEN_HOME;
            break;
        default:
            break;
    }
}

void ui_event_queue_push(UIEventType type) {
    uint8_t nextTail = (uiEventQueueTail + 1) % UI_EVENT_QUEUE_SIZE;
    if (nextTail != uiEventQueueHead) {
        uiEventQueue[uiEventQueueTail].type = type;
        uiEventQueueTail = nextTail;
    }
}

UIEvent ui_event_queue_pop() {
    UIEvent event = { UI_EVENT_NONE };
    if (uiEventQueueHead != uiEventQueueTail) {
        event = uiEventQueue[uiEventQueueHead];
        uiEventQueueHead = (uiEventQueueHead + 1) % UI_EVENT_QUEUE_SIZE;
    }
    return event;
}

UIScreen ui_state_machine_get_screen() {
    return currentScreen;
}
