#include "fox.h"
#include "fighter.h"
#include "display.h"
#include "projectiles.h"
#include <PA9.h>
#include <vector>
using std::vector;

//constructor
Fox::Fox(int num, vector<Fighter*> *listplayers, Display *disp, bool AI) : Fighter(num,listplayers,disp,"fox",AI) {
	weight = .910;
	w2value  = 3.41;
	jumpspeed = 8.5;
	doublejumpspeed = 5;
	shieldstr = 64;
	runspeed = 5;
	handx = 42;
	handy = 11;
	MYCHAR = FOX;
	series = "starfox";
	topside = 10;
	bottomside = 45;
	rightside = 45;
	leftside = 25;
	gravity = 2.5;
	jumpmax = 2;
	initPalettes();
	initFrames();
	initSprite();
	idle();
} // initializes all of the variables
// initializers
void Fox::initSounds() {
	int alreadymade = 0;
	for(int n = 0; n < charnum; n++) {
		if(players[n] -> MYCHAR == MYCHAR) alreadymade++;
	}
	if(alreadymade == 0) {
		PA_FatLoadSfx("foxfsmash", "foxfsmash");
		PA_FatLoadSfx("foxbup", "foxbup");
		PA_FatLoadSfx("foxdair", "foxdair");
		PA_FatLoadSfx("foxjab", "foxjab");
		PA_FatLoadSfx("foxdashatk", "foxdashatk");
		PA_FatLoadSfx("foxbdown", "foxbdown");
		PA_FatLoadSfx("foxbneut", "foxbneut");
		PA_FatLoadSfx("foxbside", "foxbside");
		PA_FatLoadSfx("foxutilt", "foxutilt");
	}
}
void Fox::initPalettes() {
	palettes.push_back("fox");
	palettes.push_back("fox");
	palettes.push_back("fox");
	palettes.push_back("fox");
}
// sounds
void Fox::playsound(int sndnum) {
	if(sndnum == SMASHRIGHT || sndnum == SMASHLEFT) PA_FatPlaySfx("foxfsmash");
	if(sndnum == DAIR) PA_FatPlaySfx("foxdair");
	if(sndnum == JAB) PA_FatPlaySfx("foxjab");
	if(sndnum == DASHATTACK) PA_FatPlaySfx("foxdashatk");
	if(sndnum == UTILT) PA_FatPlaySfx("foxutilt");
}
// actions
void Fox::bside() {

}
void Fox::bup() {

}
void Fox::bdown() {

}
void Fox::bneut() {

}
void Fox::fthrow() {

}
void Fox::bthrow() {

}
void Fox::uthrow() {


}
void Fox::dthrow() {

}
void Fox::jaywalk() {

}
Fox::~Fox() {
	allatkbox.clear();
	alldefbox.clear();
	PA_DeleteSprite(MAIN_SCREEN, SPRITENUM);
	PA_FatFreeSprite(MYCHAR);
}