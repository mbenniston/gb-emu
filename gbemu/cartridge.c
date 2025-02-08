#include "cartridge.h"

#include <stdlib.h>
#include <string.h>

const char *cartidge_title(cartridge_t *rom) {
    return rom->title;
}

cartridge_type_e cartridge_type(cartridge_t *rom) {
    return rom->data[CARTRIDGE_TYPE_ADDRESS];
}

static void load_title(uint8_t *data, uint32_t length, char *title) {
    title[CARTRIDGE_TITLE_LENGTH + 1] = 0;
    if (length <= CARTRIDGE_TITLE_ADDRESS + CARTRIDGE_TITLE_LENGTH) {
        return;
    }
    memcpy(title, data + CARTRIDGE_TITLE_ADDRESS, CARTRIDGE_TITLE_LENGTH);
}

int cartridge_load(cartridge_t *rom, uint8_t *data, uint32_t data_length) {
    if (data_length < CARTRIDGE_MIN_LENGTH)
        return 0;
    rom->data = data;
    rom->data_length = data_length;
    load_title(data, data_length, rom->title);

    cartridge_type_e type = rom->data[CARTRIDGE_TYPE_ADDRESS];
    if (!mbc_create(&rom->mbc, type, rom->data, rom->data_length)) {
        return 0;
    }

    return 1;
}

void cartridge_destroy(cartridge_t *rom) {
    free(rom->data);
    mbc_destroy(&rom->mbc);
}

uint8_t cartridge_read(cartridge_t *rom, uint16_t address) {
    return mbc_read(&rom->mbc, address);
}

void cartridge_write(cartridge_t *rom, uint16_t address, uint8_t data) {
    mbc_write(&rom->mbc, address, data);
}
