#include <Arduino.h>

struct game
{
  uint8_t level = 1;
  uint8_t press_order[100];
  uint8_t random_num;
  uint8_t debounce_time;
  long int last_run = 0;
  uint8_t button_liste[4];
  unsigned long last_db = 0;
  int counter = 0;
  int level_counter = 0;
  bool right_until_now = true;
  bool stop = false;
  bool pressed_right = true;
  bool st_fl[4] = {false, false, false, false};
  bool in[4];
  bool out[4] = {false, false, false, false};
  bool vorher[4] = {false, false, false, false};
  bool vorher_out[4] = {false, false, false, false};

  void init(uint8_t (&_button_list)[4], uint8_t, uint8_t (&_press_order)[100]);
  void poll();
};

struct lamps
{
  uint8_t led_liste[4];
  uint8_t button_liste[4];
  uint8_t press_order[100];
  bool lamps_finished = false;
  int counter = 1;
  bool pressed_right;
  bool *pressed_right_adress;

  void init(uint8_t (&_led_list)[4], uint8_t (&_press_order)[100], bool &_pressed_right);
  void poll();
};