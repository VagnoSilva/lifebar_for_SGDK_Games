#include <genesis.h>
#include "resources.h"
#include "lifebar.h"


int main(bool hardReset) {
    SYS_disableInts();
    VDP_init();

    // Inicializa a tela
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();


    SYS_enableInts();

   VDP_setWindowFullScreen();// Habilita o plano window

    PAL_setPalette(PAL3, lifebar_PAL.data, DMA);// Define a paltea utilizada

    loadLifeBarTiles(); // carrega os tiles da barra de vida

    // Aqui você pode desenhar a barra conforme o jogo roda, neste exemplo estou apenas pre carregando a barra na memoria
    drawLifeBar(WINDOW, 3, 2, 30, 60, 13, FALSE, FALSE);  // player 50%
    drawLifeBar(WINDOW, 3, 4, 9, 30, 3,  FALSE, TRUE);   // inimigo 30%
    drawLifeBar(WINDOW, 3, 6, 100, 100, 13, TRUE, TRUE);   // boss cheio

    //comando para apagar a barra
    //hideLifeBar(WINDOW, 3, 4, 10); //(plano onde esta a barra, posição X, posição Y, tamanho da barra em tiles)

    while (1) {

        // Atualiza o sistema
        SYS_doVBlankProcess();
    }

    return 0;
}
