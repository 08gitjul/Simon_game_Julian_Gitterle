#include <Arduino.h>
#include "helper.h"
#include <stdlib.h>

void game::init(uint8_t (&_button_list)[4], uint8_t db_time, uint8_t (&_press_order)[100])
{
    for (int i = 0; i < 4; i++)
    {
        button_liste[i] = _button_list[i];
    }
    for (int i = 0; i < 100; i++)
    {
        press_order[i] = _press_order[i];
    }
}
void game::poll()
{
    pressed_right = false;
    for (int i = 0; i < 4; i++)
    {
        st_fl[i] = false;
    }
    if (millis() - last_db > debounce_time)
    {
        for (int i = 0; i < 4; i++)
        {
            vorher[i] = in[i], vorher_out[i] = out[i];
            in[i] = digitalRead(button_liste[i]);
            if (in[i] == vorher[i])
            {
                out[i] = in[i];
            }
            if (out[i] && !vorher_out[i])
            {
                st_fl[i] = true;
                Serial.println(i);
            }
        }
        last_db = millis();
    }
    if ((st_fl[0] == false) && (st_fl[1] == false) && (st_fl[2] == false) && (st_fl[3] == false))
    {
    }
    else if (st_fl[3-press_order[counter]] == true)
    {
        counter++;
    }
    else
    {
        right_until_now = false;
        Serial.println("GAME OVER");
        Serial.println(3-press_order[counter]);
        while (!right_until_now)
        {
        }
    }
    if(counter > level_counter)
    {
        counter = 0;
        pressed_right = true;
        level_counter++;
    }
}
void lamps::init(uint8_t (&_led_list)[4], uint8_t (&_press_order)[100], bool &_pressed_right)
{
    pressed_right_adress = &_pressed_right;
    for (int i = 0; i < 4; i++)
    {
        led_liste[i] = _led_list[i];
    }
    for (int i = 0; i < 100; i++)
    {
        press_order[i] = _press_order[i];
    }
}
void lamps::poll()
{
    pressed_right = *pressed_right_adress;
    if (pressed_right)
    {
        for (int i = 0; i < counter; i++)
        {
            delay(400);
            digitalWrite(press_order[i] + 6, HIGH);
            // Serial.println(press_order[i] + 6);
            delay(1000);
            digitalWrite(press_order[i] + 6, LOW);
        }
        delay(200);
        for (int i = 0; i < 4; i++)
        {
            digitalWrite(i + 6, HIGH);
        }
        delay(300);
        for (int i = 0; i < 4; i++)
        {
            digitalWrite(i + 6, LOW);
        }
        counter++;
    }
}