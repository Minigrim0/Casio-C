#include <stdlib.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/std/stdio.h>
#include <math.h>

static int tag_size = 0;
static int set_index = 0;
static int offset_size = 0;

long unsigned int read_int(const char* prompt) {
    long unsigned int val = 0;
    char buff[25];
    int key = 0;
    int add = -1;
    do {
        dclear(C_WHITE);
        snprintf(buff, 25, "%d", val);
        dtext(0, 0, C_BLACK, prompt);
        dtext(0, 10, C_BLACK, buff);
        dupdate();
        key = getkey().key;
        if (key == KEY_EXE) {
            return val;
        } else if (key == KEY_DEL) {
            val = val / 10;
        }

        add = keycode_digit(key);
        if(add != -1) {
            val = val * 10 + add;
        }
    } while (1);
}

long unsigned int read_hex(const char* prompt) {
    long unsigned int val = 0;
    char buff[25];
    int key = 0;
    int add = -1;
    do {
        dclear(C_WHITE);
        snprintf(buff, 25, "%x", val);
        dtext(0, 0, C_BLACK, prompt);
        dtext(0, 10, C_BLACK, buff);
        dupdate();
        key = getkey().key;
        if (key == KEY_EXE) {
            return val;
        } else if (key == KEY_DEL) {
            val = val / 16;
        }

        add = keycode_digit(key);
        if(add == -1) {
            add = keycode_function(key);
            add = add != -1 ? add + 9 : -1;
        }

        if(add != -1) {
            val = val * 16 + add;
        }
    } while (1);
}

int main(void){
    extern font_t font;
    dfont(&font);

    dclear(C_WHITE);
    tag_size = read_int("Tag size");
    set_index = read_int("Set index size");
    offset_size = read_int("Offset size");
    int assoc = read_int("Associativity");

    int cache_size_bytes = assoc * pow(2, set_index + offset_size);
    int block_size_bytes = pow(2, offset_size);
    char cache_size_str[25];
    char block_size_str[25];

    dclear(C_WHITE);
    snprintf(cache_size_str, 25, "Cache size: %d bytes", cache_size_bytes);
    snprintf(block_size_str, 25, "Block size: %d bytes", block_size_bytes);
    dtext(0, 0, C_BLACK, cache_size_str);
    dtext(0, 10, C_BLACK, block_size_str);
    dtext(0, 20, C_BLACK, "Press EXE to continue");
    dupdate();
    getkey();

    int key = 0;
    char value_str[25];
    do {
        long unsigned int val = read_hex("Hex Value to cut");

        int tag_mask = (1 << tag_size) - 1;
        int set_mask = (1 << set_index) - 1;
        int offset_mask = (1 << offset_size) - 1;

        int tag = (val >> (set_index + offset_size)) & tag_mask;
        int set = (val >> offset_size) & set_mask;
        int offset = val & offset_mask;

        char tag_str[25];
        char set_str[25];
        char offset_str[25];

        dclear(C_WHITE);
        snprintf(value_str, 25,  "v: %21x", val);
        snprintf(tag_str, 25,    "Tag   : %10x, %10d", tag, tag);
        snprintf(set_str, 25,    "Set   : %10x, %10d", set, set);
        snprintf(offset_str, 25, "Offset: %10x, %10d", offset, offset);

        dtext(0, 10, C_BLACK, tag_str);
        dtext(0, 10, C_BLACK, tag_str);
        dtext(0, 20, C_BLACK, set_str);
        dtext(0, 30, C_BLACK, offset_str);
        dtext(0, 55, C_BLACK, "any to continue, DEL to exit");
        dupdate();
        key = getkey().key;
    } while (key == KEY_DEL);

    return 0;
}
