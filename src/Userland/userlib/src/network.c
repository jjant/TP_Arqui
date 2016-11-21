#include <network.h>

void send_message(uint8_t user, const char * message) {
  return;
}

char * read_message() {
  static uint8_t last_idx = 0;
  static uint8_t first_idx = 0;
  char * message = NULL;
  char ** messages = malloc( MESSAGES_BUFFER * sizeof(char *));

  if ((message = read_message_asm())) {
    messages[last_idx++] = message;
  }

  if (message = messages[first_idx]) {
    messages[first_idx++] = NULL;
    return message;
  }

  last_idx = last_idx % 100;
  first_idx = first_idx % 100;

  return NULL;
}