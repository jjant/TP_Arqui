void chat_program() {
  char command[BUFFER_SIZE] = { 0 };
  uint16_t current_index = 0;
  int c;

  while(1) {
    char ** args = malloc(MAX_ARGS * sizeof (char *));
    for(int i = 0; i < MAX_ARGS; i++) {
      void * aux = malloc(MAX_ARG_LEN);
      args[i] = (char *) aux;
    }

    print_chat_icon(0);

    while((c = getchar()) != '\n') {
      if(c == BACKSPACE) {
        if (!current_index) continue;
        putc(BACKSPACE);
        command[--current_index] = 0;
      }
      else if (c == ESC) set_keyboard_language(0);
      else if (c) putc(command[current_index++] = c);
    }
    command[current_index++] = 0;

    if (parse_input(command, args)) {
      private_line(args[0]);
      execute_program(programs, args);
    } else {
      putc('\n');
    }

    current_index = 0;
  }
}

void talk_program(uint8_t user) {
  uint16_t current_index = 0;
  int c;

  while(1) {
    char * message = malloc(MAX_MESSAGE_LEN);
    print_chat_icon(USUARIO);

    while((c = getchar()) != '\n') {
      if(c == BACKSPACE) {
        if (!current_index) continue;
        putc(BACKSPACE);
        message[--current_index] = 0;
      }
      else if (c == ESC) return;
      else if (c) putc(message[current_index++] = c);
    }

    message[current_index++] = 0;
    send_message(message, user);
    current_index = 0;
  }
}

void receive_program() {
  char * message = malloc(MAX_MESSAGE_LEN);
  uint8_t user;
  while((user = unread_message(&message)) == NO_MESSAGES) {
    print_chat_icon(user);
    printf("%s\n", message);
  }
}

void print_chat_icon(uint8_t user) {
  uint8_t color;
  
  if (user == USUARIO) {
    color = set_color(10);
    printf(" TU %c ", 26);
  } else {
    color = set_color(user + 5);
    printf(" USUARIO %d %c ", user, 26);
  }

  set_color(color);
}

char ** parse_input(char * kb_buffer, char ** args) {
  int k = 0;
  char * current = args[0];
  uint8_t in_string = 0;

  if (strlen(kb_buffer) == 0) return 0;

  while(*kb_buffer) {
    if (k > 0 && *kb_buffer == '\'')
      in_string = in_string ? 0 : 1;
    if(*kb_buffer != ' ' || in_string && *kb_buffer == ' ') {
      *current = *kb_buffer;
      current++;
    } else if (!in_string) {
      *current = '\0';
      k++;
      current = args[k];
    }

    kb_buffer++;
  }

  *current = '\0';
  return args;
}