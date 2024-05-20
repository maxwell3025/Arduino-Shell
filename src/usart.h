
// Must be run before any other usart-related commands
void usart_init();

// Transmit a single byte to the terminal
void usart_transmit(unsigned char c);

// Read a single byte from the terminal(blocking)
unsigned char usart_receive();

// Send a string stored in flash memory
void usart_transmit_flash_string(char *str);

// Send a string stored in SRAM
void usart_transmit_string(char *str);

void usart_transmit_hex_number(unsigned int x);
