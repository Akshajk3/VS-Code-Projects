#include "cart.h"

typedef struct
{
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    rom_header *header;
} cart_context;

static cart_context ctx;

static const char *ROM_TYPES[] = 
{
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???"
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???"
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY"
};

static const char *LIC_CODE[0xA5] = 
{
    "None",
    "Nintendo R&D1",
    "Capcom",
    "Electronic Arts",
    "Hudson Soft",
    "b-ai",
    "kss",
    "pow",
    "PCM Complete",
    "san-x",
    "Kemco Japan",
    "seta",
    "Viacom",
    "Nintendo",
    "Bandai",
    "Ocean/Acclaim",
    "Konami",
    "Hector",
    "Taito",
    "Hudson",
    "Branpresto",
    "Ubi Soft",
    "Atlus",
    "Malibu",
    "angel",
    "Bullet-Proof",
    "irem",
    "Absolute",
    "Acclaim",
    "Activision",
    "American sammy",
    "Konami",
    "Hi tech entertainment",
    "LJN",
    "Matchbox",
    "Mattel",
    "Milton Bradley",
    "Titus",
    "Virgin",
    "LucasArts",
    "Ocean",
    "Electronic Arts",
    "Infogrames",
    "Interplay",
    "Broderbund",
    "sculptured",
    "sci",
    "THQ",
    "Accolade",
    "misawa",
    "lozc",
    "Tokuma Shoten Intermedia'",
    "Tsukusa Original",
    "Chunsoft",
    "Video System",
    "Ocean/Acclaim",
    "Varie",
    "Yonezawa/s’pal",
    "Kaneko",
    "Pack in soft",
    "Konami (Yu-Gi-Oh!)"
};

const char* cart_lic_name()
{
    if(ctx.header->new_lic_code <= 0xA4)
    {
        return LIC_CODE[ctx.header->lic_code];
    }

    return "UNKNOWN";
}

const char* cart_type_name()
{
    if(ctx.header->type <= 0x22)
    {
        return ROM_TYPES[ctx.header->type];
    }

    return "UNKNOWN";
}

bool cart_load(char* cart)
{
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    FILE* fp = fopen(cart, "r");

    if(!fp)
    {
        printf("Failed to open: %s\n", cart);
        return false;
    }

    printf("Opened: %s\n", ctx.filename);

    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);

    rewind(fp);

    ctx.rom_data = (u8*)malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    ctx.header = (rom_header *)(ctx.rom_data + 0x100);
    ctx.header->title[15] = 0;

    printf("Cartridge Loaded:\n");
    printf("\t Title     :  %s\n", ctx.header->title);
    printf("\t Type      :  %2.2x (%s)\n", ctx.header->type, cart_type_name());
    printf("\t ROM Size  :  %d KB\n", 32 << ctx.header->rom_size);
    printf("\t RAM Size  :  %2.2x\n", ctx.header->ram_size);
    printf("\t LIC Code  :  %2.2x  (%s)\n", ctx.header->lic_code, cart_lic_name());
    printf("\t ROM Vers  :  %2.2x\n", ctx.header->version);

    u16 x = 0;
    for(u16 i=0x0134; i <= 0x014C; i++)
    {
        x = x - ctx.rom_data[i] - 1;
    }

    printf("\t Checksum  : %2.2x (%s)\n", ctx.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");

    return true;
}