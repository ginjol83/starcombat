#include <gb/gb.h>

#include <..\projects\StarCombat\Libreries\backgrounds.h>


void plot_background_image(unsigned char *tile_data, unsigned char *map_data){
   set_bkg_data(0, 0, tile_data);
   set_bkg_tiles(0, 0, 20, 18, map_data);
   SHOW_BKG;
   DISPLAY_ON;
}

void plot_intro_image(unsigned char *tile_data, unsigned char *map_data){
   set_bkg_data(0, 0, tile_data);
   set_bkg_tiles(0, 0, 20, 18, map_data);
   SHOW_BKG;
   DISPLAY_ON;
   delay(5000);
   //clscr();
}