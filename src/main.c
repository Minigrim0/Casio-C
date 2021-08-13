#include <stdlib.h>
#include <gint/display.h>
#include <gint/keyboard.h>

typedef struct {
    const bopti_image_t *image;
    const bopti_image_t *image_rot;
    const char* name;
} Component;

void loadComponents(Component **components){
    extern bopti_image_t vertical_self;
    extern bopti_image_t horizontal_self;
    extern bopti_image_t vertical_capa;
    extern bopti_image_t horizontal_capa;
    extern bopti_image_t vertical_resistor;
    extern bopti_image_t horizontal_resistor;

    *components = (Component*) malloc(3 * sizeof(Component));

    Component self = {&vertical_self, &horizontal_self, "self"};
    *components[0] = self;
    Component capa = {&vertical_capa, &horizontal_capa, "capa"};
    *components[1] = capa;
    Component resistor = {&vertical_resistor, &horizontal_resistor, "resistor"};
    *components[2] = resistor;
}

int drawUI(int cursor_position, Component* components){
    short int x = 0;

    for(x=0;x<3;x=x+1){
        drect_border(106, x*21, 127, (x*21)+21, C_WHITE, 1, C_BLACK);
        dprint(107, x+1, C_BLACK, components[x].name);
        // dimage(107, x+1, components[x].image);
    }
    return 0;
}

int main(void){
    extern font_t font;
    Component* components = NULL;

    dfont(&font);

    loadComponents(&components);
    dclear(C_WHITE);
    dprint(107, 0, C_BLACK, components[0].name);
    dprint(107, 15, C_BLACK, components[1].name);
    dprint(107, 30, C_BLACK, components[2].name);
    dupdate();
    getkey();

    // drawUI(0, components);

    // dupdate();
    // getkey();

    free(components);
    return 1;
}
