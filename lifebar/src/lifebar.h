#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <genesis.h>
#include "resources.h"  // onde está o extern const TileSet lifebar;

#define TILE_LIFEBAR_BASE  1984 //define a posição na vram

// Índices dos tiles dentro do tileset
enum {
    LIFEBAR_BOSS_CLEAR = 0,
    LIFEBAR_CLEAR = 0,
    LIFEBAR_BOSS_EMPTY = 1,
    LIFEBAR_EMPTY = 1,
    LIFEBAR_FULL,
    LIFEBAR_25,
    LIFEBAR_50,
    LIFEBAR_75,
    LIFEBAR_BOSS_FULL,
    LIFEBAR_BOSS_25,
    LIFEBAR_BOSS_50,
    LIFEBAR_BOSS_75,
    LIFEBAR_END_PLAYER,
    LIFEBAR_END_ENEMY
};

// Paleta usada para a barra de vida (mude se necessário)
#define LIFEBAR_PALETTE PAL3

// Carrega os tiles da barra de vida na VRAM
static inline void loadLifeBarTiles()
{
    VDP_loadTileSet(&lifebar, TILE_LIFEBAR_BASE, DMA);
}

// Desenha uma barra de vida horizontal com tamanho variável + terminal
static inline void drawLifeBar(u16 plan, u16 x, u16 y, u16 currentLife, u16 maxLife, u8 length, bool isBoss, bool isEnemy)
{
    if (maxLife == 0 || length == 0) return;

    u16 percent = (currentLife * 100) / maxLife;
    u8 filled = (percent * length) / 100;
    u8 remainder = (percent * length) % 100;

    for (u8 i = 0; i < length; i++)
    {
        u16 tileIndex;

        if (i < filled) {
            tileIndex = isBoss ? LIFEBAR_BOSS_FULL : LIFEBAR_FULL;
        } else if (i == filled) {
            if (remainder >= 75) tileIndex = isBoss ? LIFEBAR_BOSS_75 : LIFEBAR_75;
            else if (remainder >= 50) tileIndex = isBoss ? LIFEBAR_BOSS_50 : LIFEBAR_50;
            else if (remainder >= 25) tileIndex = isBoss ? LIFEBAR_BOSS_25 : LIFEBAR_25;
            else tileIndex = isBoss ? LIFEBAR_BOSS_EMPTY : LIFEBAR_EMPTY;
        } else {
            tileIndex = isBoss ? LIFEBAR_BOSS_EMPTY : LIFEBAR_EMPTY;
        }

        VDP_setTileMapXY(plan, TILE_ATTR_FULL(LIFEBAR_PALETTE, TRUE, FALSE, FALSE, TILE_LIFEBAR_BASE + tileIndex), x + i, y);
    }

    // Terminal no final da barra
    u16 tileEnd = isEnemy ? LIFEBAR_END_ENEMY : LIFEBAR_END_PLAYER;
    VDP_setTileMapXY(plan, TILE_ATTR_FULL(LIFEBAR_PALETTE, TRUE, FALSE, FALSE, TILE_LIFEBAR_BASE + tileEnd), x + length, y);
}



// Esconde a barra de vida sobrescrevendo com tiles vazios
static inline void hideLifeBar(u16 plan, u16 x, u16 y, u8 length)
{
    for (u8 i = 0; i < length + 1; i++)  // +1 para o terminal
    {
        VDP_setTileMapXY(plan, TILE_ATTR_FULL(LIFEBAR_PALETTE, FALSE, FALSE, FALSE, TILE_LIFEBAR_BASE + LIFEBAR_CLEAR), x + i, y);
    }
}

#endif // LIFEBAR_H
