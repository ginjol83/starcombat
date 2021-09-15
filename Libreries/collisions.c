#include <..\projects\StarCombat\Libreries\collisions.h>
/*Check if two rectangles from x1,y1, and extending out h1, h2, 
 overlap with another, x2,y2, and extending out w2, h2*/
int collisionCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		return 1;
	} else {
		return 0;
	}
}