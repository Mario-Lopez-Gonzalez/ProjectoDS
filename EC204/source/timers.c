/**********************************************************
 * timers.c
 **********************************************************/

/* 
 * Añadir los includes que sean necesarios
 **/
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"
#include "backgrounds.h"
#include "keypad_screen.h"

/**
 *Variables para el documento
**/
int only=10;
int alien_color=0;
int layer=1;
extern int ticks;
extern int timer;
extern t_crab crab_pos[crabs];
extern t_shoot shoot_pos;
extern int shoot_layer;
int i;
int j;
int x;
int y=0;
int a;
int left=1;
int right=0;
int max;
int min;
int fast;
int score=0;
extern int state;
extern int shoot_present;
int delete=0;
extern int crabs_alive;
int w=0;
int found;
int anim_counter=0;
int dif=0;
int cd=0;
/* 
 * Rutina de atención a la interrupción del temporizador
 **/
void timer_handler() {
	ticks++;//vital
	if(score%500==0&&cd)
	{
	dif+=4;
	cd=0;
	}
	if(cd==0&&score%500!=0)
	cd++;
	if(ticks%45==0)
	{
switch(state)
{
	 case 0://home screen
	 background_home();
	 break;
	 case 2:
	 background_playing();
	 break;
 	 case 3:
	 background_gameover();
	 break;
	 case 12:
	 background_playing();
	 break;
	 default:
	 break;
}

	}
switch(state){
case 3:
	if(only){
iprintf("\x1b[12;00H                                              ");
iprintf("\x1b[16;00H                                              ");
iprintf("\x1b[17;00H                                              ");
iprintf("\x1b[18;00H                                              ");
only--;
}
break;
case 12:
	if(ticks%60==0)
	{	
	timer++;                                       
	iprintf("\x1b[19;00H TIMER: %d",timer);
	}
	if(screen_pos_x()!=0&&screen_pos_y()!=0){
	display_crab_alien(layer,screen_pos_x()+8,screen_pos_y()+8);
	layer++;
	if(layer>50)
	layer=1;
	}
break;
case 2:
	if(ticks%60==0)
	{	
	timer++;                                       
	iprintf("\x1b[19;00H TIMER: %d",timer);
	}
	if(ticks%(120-dif)==0)
{
	if(anim_counter)
	anim_counter--;
	else
	anim_counter++;
	move_crabs();
	if(crabs_alive<crabs)
	respawn();
}
	if(max_y()>175)
	state=3;
	if(shoot_pos.y<=2)
	shoot_miss();
	else
	move_shoot();
	if(shoot_present)
	hitbox();
	iprintf("\x1b[16;00H Touchscreen x= %d  ",screen_pos_x());
	iprintf("\x1b[17;00H Touchscreen y= %d  ",screen_pos_y());
	break;
default:
	break;
}
	
} // timer_handler()

void move_crabs(){
i=0;
	for(i;i<crabs;i++){
	if(left){
	if(crab_pos[i].anim==1){
	switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].x-=16;
	switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].anim=2;}
	else{
	if(crab_pos[i].anim==2){
	switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].x-=16;
	switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].anim=1;}
	}
	}
	if(right){
	if(crab_pos[i].anim==1){
	switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].x+=16;
	switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].anim=2;}
	else{
	if(crab_pos[i].anim==2){
	switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].x+=16;
	switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	crab_pos[i].anim=1;}
	}
	}
	}
	max=max_x();
	min=min_x();
	if(max>224){
	left=1;
	right=0;
	all_down();
	}
	if(min<16)
	{
	left=0;
	right=1;
	all_down();
	}
}

int max_x(){
	int max=0;
	i=0;
	for(i;i<crabs;i++){
	if(crab_pos[i].x>max&&crab_pos[i].anim!=0)
	max=crab_pos[i].x;
	}
	return max;
}

int max_y(){
	int max=0;
	i=0;
	for(i;i<crabs;i++){
	if(crab_pos[i].y>max&&crab_pos[i].anim!=0)
	max=crab_pos[i].y;
	}
	return max;
}

int min_x(){
	int min=999;
	i=0;
	for(i;i<crabs;i++){
	if(crab_pos[i].x<min&&crab_pos[i].anim!=0)
	min=crab_pos[i].x;
	}
	return min;
}

void all_down(){
	i=0;
	for(i;i<crabs;i++){
	if(crab_pos[i].anim==1)
	{
	 switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
	}
	 crab_pos[i].y+=16;
	 if(right)
	 crab_pos[i].x+=16;
	 if(left)
	 crab_pos[i].x-=16;
	 switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	}
	if(crab_pos[i].anim==2)
	{
	 switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			remove_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			remove_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		default:
		break;
	}
	 crab_pos[i].y+=16;
	 if(right)
	 crab_pos[i].x+=16;
	 if(left)
	 crab_pos[i].x-=16;
	 switch(crab_pos[i].sprite)
	{
		case 1:
			display_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 2:
			if(crab_pos[i].hits==0)
			display_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			else
			display_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					display_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					display_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					display_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				default:
				break;
			}
		default:
		break;
	}
	}
}
}

void background_playing(){
if(j)
	 {display_back02();
	 j=0;}
	 else
	 {display_back03();
	 j++;}
}

void background_home(){
if(j)
	 {display_back00();
	 j=0;}
	 else
	 {display_back01();
	 j++;}
}

void background_gameover(){
if(j)
	 {display_back00();
	 j=0;}
	 else
	 {display_back04();
	 j++;}
}

void shoot_miss(){
if(shoot_pos.anim==1)
		remove_projectile(125,shoot_pos.x,shoot_pos.y);
		else
		if(shoot_pos.anim==2)
		remove_projectile_2(125,shoot_pos.x,shoot_pos.y);
		shoot_pos.anim=0;
		shoot_present=0;
}

void move_shoot(){
if(shoot_pos.anim==1){
	remove_projectile(125,shoot_pos.x,shoot_pos.y);
	shoot_pos.y-=5;
	display_projectile_2(125,shoot_pos.x,shoot_pos.y);
	shoot_pos.anim=2;
	}
	else
	 if(shoot_pos.anim==2){
	remove_projectile_2(125,shoot_pos.x,shoot_pos.y);
	shoot_pos.y-=5;
	display_projectile(125,shoot_pos.x,shoot_pos.y);
	shoot_pos.anim=1;
	}
}

void respawn()
{
if(crabs_alive<=crabs)
	{
	w=0;
	found=0;
	while(!found)
	{
	if(crab_pos[w].anim==0)
	found=1;
	else
	w++;
	}
	if(crabs_alive!=0)
{
	while(found){
	x=((rand()%12)+2)*16;//72 espacios
        a=0;
     for(a;a<crabs;a++)
     {
	if(a==w&&w!=crabs-1)
	a++;
	if(x-15<=crab_pos[a].x&&crab_pos[a].x<=x+15)
	 found=0;
     }}}}
	switch(rand()%3+1)
	{
		case 1:
		crab_pos[w].sprite=1;
		break;
		case 2:
		if(dif>=20)
		crab_pos[w].sprite=2;
		break;
		case 3:
		if(dif>=40)
		crab_pos[w].sprite=3;
		break;
		default:
		break;
	}
      crab_pos[w].hits=0;
      crab_pos[w].x=x;
      crab_pos[w].y=y;
      crab_pos[w].anim=anim_counter+1;
      if(anim_counter)
      switch(crab_pos[w].sprite)
	{
		case 1:
			display_crab_alien_2(w,x,y);
		break;
		case 2:
			display_squid_alien_2(w,x,y);
		break;
		case 3:
			display_octo_alien_2(w,x,y);
		break;
		default:
		break;
	}
      else
      switch(crab_pos[w].sprite)
	{
		case 1:
			display_crab_alien(w,x,y);
		break;
		case 2:
			display_squid_alien(w,x,y);
		break;
		case 3:
			display_octo_alien(w,x,y);
		break;
		default:
		break;
	}
      crabs_alive++;
}

void hitbox()
{
{ //HITBOX START
	delete=0;
	i=0;
	for(i;i<crabs&&!delete;i++){
	if(shoot_pos.y+4<=crab_pos[i].y+16&&shoot_pos.y+4>=crab_pos[i].y&&(shoot_pos.x+7>=crab_pos[i].x&&shoot_pos.x+7<=crab_pos[i].x+16)&&(shoot_pos.x+9>=crab_pos[i].x&&shoot_pos.x+9<=crab_pos[i].x+16)&&crab_pos[i].anim!=0)
	{
	if(crab_pos[i].anim==1)
	switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien(i,crab_pos[i].x,crab_pos[i].y);
			crab_pos[i].anim=0;
			crabs_alive--;
		break;
		case 2:
			if(crab_pos[i].hits==0)
			{remove_squid_alien(i,crab_pos[i].x,crab_pos[i].y);
			crab_pos[i].hits=1;
			display_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);}
			else
			{remove_squid_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
			crab_pos[i].hits=2;
			crab_pos[i].anim=0;
			crabs_alive--;}
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=1;
					display_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 1:
					remove_octo_alien_hit(i,crab_pos[i].x,crab_pos[i].y);
					display_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=2;
				break;
				case 2:
					remove_octo_alien_hit_2(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=3;
					crab_pos[i].anim=0;
					crabs_alive--;
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	else
	 if(crab_pos[i].anim==2)
	 switch(crab_pos[i].sprite)
	{
		case 1:
			remove_crab_alien_2(i,crab_pos[i].x,crab_pos[i].y);

			crab_pos[i].anim=0;
			crabs_alive--;
		break;
		case 2:
			if(crab_pos[i].hits==0)
			{remove_squid_alien_2(i,crab_pos[i].x,crab_pos[i].y);
			crab_pos[i].hits=1;
			display_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);}
			else
			{remove_squid_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
			crab_pos[i].hits=2;
			crab_pos[i].anim=0;
			crabs_alive--;}
		break;
		case 3:
			switch(crab_pos[i].hits)
			{
				case 0:
					remove_octo_alien_2(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=1;
				break;
				case 1:
					remove_octo_alien_2_hit(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=2;
					display_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
				break;
				case 2:
					remove_octo_alien_2_hit_2(i,crab_pos[i].x,crab_pos[i].y);
					crab_pos[i].hits=3;
					crab_pos[i].anim=0;
					crabs_alive--;
				break;
				default:
				break;
			}
		break;
		default:
		break;
	}
	score+=100;
	shoot_miss();
	shoot_pos.anim=0;
	shoot_present=0;
	iprintf("\x1b[12;00H SCORE: %d   ",score);
	delete=1;
}
}
} //hitbox end
}
