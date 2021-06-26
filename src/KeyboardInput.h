#ifndef __KEYBOARDINPUT_H
#define __KEYBOARDINPUT_H

struct KeyboardInput {
    bool key_up = false;
    bool key_down = false;
    bool key_left = false;
    bool key_right = false;
    bool key_space = false;
    bool key_shift = false;

    void reset() {
        key_up = false;
        key_down = false;
        key_left = false;
        key_right = false;
        key_space = false;
        key_shift = false;
    }
};

#endif