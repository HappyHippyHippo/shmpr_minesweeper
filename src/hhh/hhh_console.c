#include <hhh/hhh_console.h>
#include <hhh/hhh_error.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* macro definition for console clearing */
#ifdef _WIN32
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

/* macro definition for input buffer clear */
#define CLEAR_INPUT while (getchar() != '\n') /*void*/

/* macro definition of buffer size */
#define INPUT_BUFFER_SIZE 256

int console_clear(void) {
  /* clear the console */
  CLEAR_SCREEN;

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_option(char * readed, char * options, const char * message, ...) {
  char buffer[INPUT_BUFFER_SIZE];
  int ok = 0, i = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL || options == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input */
    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == buffer && buffer[0] != '\n') {
      /* store the option inserted */
      *readed = buffer[0];

      /* validate cycle */
      i = 0;
      while (*(options + i) != 0 && !ok) {
        /* check if the inserted option is equal to the iterated valid option */
        ok = (*readed == *(options + i));

        /* increment the option to be checked */
        i++;
      }

      /* check if the value is not a valid value */
      if (!ok) {
        /* remove the '\n' readed by the fgets function */
        buffer[strlen(buffer) - 1] = '\0';

        /* message that the value was not accepted */
        printf("valor inválido : %s\n", buffer);
      }
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_string(char * readed, size_t buffer_size, const char * message, ...) {
  int ok = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input and check if the inserted string is not empty */
    ok = fgets(readed, buffer_size, stdin) == readed && readed[0] != '\n';

    /* check if the value is not a valid value */
    if (!ok) {
      /* message that the value was not accepted */
      printf("valor inválido\n");
    } else {
      /* remove the '\n' readed by the fgets function */
      readed[strlen(readed) - 1] = '\0';
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_int(int * readed, const char * message, ...) {
  char buffer[INPUT_BUFFER_SIZE];
  int ok = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input */
    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == buffer && buffer[0] != '\n') {
      /* read the inserted number */
      if ((ok = sscanf(buffer, "%d", readed)) == 0) {
        /* remove the '\n' readed by the fgets function */
        buffer[strlen(buffer) - 1] = '\0';

        /* message that the value was not accepted */
        printf("valor inválido : %s\n", buffer);
      }
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_int_limit(int * readed, int min, int max, const char * message, ...) {
  char buffer[INPUT_BUFFER_SIZE];
  int ok = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL || min > max) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input */
    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == buffer && buffer[0] != '\n') {
      /* read the inserted number */
      if ((ok = sscanf(buffer, "%d", readed)) == 1) {
        /* validate the number limit values */
        ok = *readed >= min && *readed <= max;
      }

      /* check if the value is not a valid value */
      if (!ok) {
        /* remove the '\n' readed by the fgets function */
        buffer[strlen(buffer) - 1] = '\0';

        /* message that the value was not accepted */
        printf("valor inválido : %s\n", buffer);
      }
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_double(double * readed, const char * message, ...) {
  char buffer[INPUT_BUFFER_SIZE];
  int ok = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input */
    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == buffer && buffer[0] != '\n') {
      /* read the inserted number */
      if ((ok = sscanf(buffer, "%lf", readed)) == 0) {
        /* remove the '\n' readed by the fgets function */
        buffer[strlen(buffer) - 1] = '\0';

        /* message that the value was not accepted */
        printf("valor inválido : %s\n", buffer);
      }
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_double_limit(double * readed, double min, double max, const char * message, ...) {
  char buffer[INPUT_BUFFER_SIZE];
  int ok = 0;
  va_list vl;

  /* argument check */
  if (readed == NULL || message == NULL || min > max) {
    return ERROR_INVALID_ARGUMENT;
  }

  /* request cycle */
  do {
    /* check if is to present a request message */
    if (message != NULL) {
      /* get/start the variadic arguments reading */
      va_start(vl, message);

      /* request message presentation */
      vprintf(message, vl);
      fflush(stdout);

      /* end the variadic arguments reading */
      va_end(vl);
    }

    /* read input */
    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == buffer && buffer[0] != '\n') {
      /* read the inserted number */
      if ((ok = sscanf(buffer, "%lf", readed)) == 1) {
        /* validate the number limit values */
        ok = *readed >= min && *readed <= max;
      }

        /* check if the value is not a valid value */
        if (!ok) {
          /* remove the '\n' readed by the fgets function */
          buffer[strlen(buffer) - 1] = '\0';

          /* message that the value was not accepted */
          printf("valor inválido : %s\n", buffer);
        }
    }
  } while (!ok);

  /* signal successful operation */
  return ERROR_OK;
}

int console_read_enter(const char * message, ...) {
  va_list vl;

  /* check if is to present a request message */
  if (message != NULL) {
    /* get/start the variadic arguments reading */
    va_start(vl, message);

    /* request message presentation */
    vprintf(message, vl);
    fflush(stdout);

    /* end the variadic arguments reading */
    va_end(vl);
  }

  /* clear the input buffer */
  CLEAR_INPUT;

  return ERROR_OK;
}
