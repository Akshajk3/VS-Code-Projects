#ifndef MEMORY_H
#define MEMORY_H

uint8_t mem[] = {
 0x21, 0x0a, 0x00, //ld hl, ??
 0x0e, 0x00, //ld c, 0
 0x06, 0x0c, //ld b, 12
 0xed, 0xb3, //otir
 0x76, //halt
 'H','e','l','l','o', ' ','W','o','r','l','d','\n'
};

#endif