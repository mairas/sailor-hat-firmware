#include "digital_io.h"

#include <avr/io.h>

#include "globals.h"

volatile uint8_t port_a_mode = DDRA;
volatile uint8_t port_a_state = PORTA;

volatile uint8_t port_b_mode = DDRB;
volatile uint8_t port_b_state = PORTB;

bool read_portA(int pin) { return PINA & (1 << pin); }

bool read_portB(int pin) { return PINB & (1 << pin); }

void update_port(volatile uint8_t* port_state, uint8_t pin, bool value) {
  if (value) {
    *port_state |= 1 << pin;
  } else {
    *port_state &= ~(1 << pin);
  }
}

void set_en5v_pin(bool state) { update_port(&port_a_state, EN5V_PIN, state); }

void set_port_mode(volatile uint8_t* port_a_mode, volatile uint8_t* port_b_mode,
                   int port, int pin, bool output) {
  auto port_mode = port ? port_b_mode : port_a_mode;
  if (output) {
    *port_mode |= 1 << pin;
  } else {
    *port_mode &= ~(1 << pin);
  }
}
