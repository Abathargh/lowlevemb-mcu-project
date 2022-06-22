#ifndef LOGGER_H_
#define LOGGER_H_

/************************************************************************/
/* Includes                                                             */
/************************************************************************/

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define BAUD_9600  103
#define BAUD_38400 25

/************************************************************************/
/* Typedefs                                                             */
/************************************************************************/

typedef enum {
  BAUD_RATE_9600  = BAUD_9600,
  BAUD_RATE_38400 = BAUD_38400
} baudrate_t;

typedef enum {
  USART_0,
  USART_1,
  USART_2,
  USART_3,
} usart_t;

/************************************************************************/
/* Public functions                                                     */
/************************************************************************/

void logger_init(usart_t usart, baudrate_t baud);
void print_error(const char *msg);

#endif
