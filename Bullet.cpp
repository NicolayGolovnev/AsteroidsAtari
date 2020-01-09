#include "Bullet.h"

Bullet::Bullet()
{
    name="bullet";
}

void  Bullet::update()
{
    dx=cos(angle*DEGtoRAD)*6;
    dy=sin(angle*DEGtoRAD)*6;
    // angle+=rand()%7-3;  /*try this*/
    x+=dx;
    y+=dy;

    if (x>W || x<0 || y>H || y<0) life=0;
}
