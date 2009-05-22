#include "kirby.h"
#include "fighter.h"
#include "display.h"
#include "projectiles.h"
#include <PA9.h>
#include <vector>
using std::vector;

//constructor
Kirby::Kirby(int num, vector<Fighter*> *listplayers, Display *disp, bool AI) : Fighter(num,listplayers,disp,"kirby",AI) {
	weight = 0.899;
	w2value  = -0.44;
	shieldstr = 64;
	runspeed = 3.5;
	handx = 24;
	handy = 18;
	MYCHAR = KIRBY;
	topside = 22;
	bottomside = 44;
	rightside = 41;
	leftside = 21;
	rockcount = 0;
	gravity = 3;
	jumpmax = 6;
	initPalettes();
	initFrames();
	initSprite();
	idle();
} // initializes all of the variables
// initializers
void Kirby::initSounds() {
	int alreadymade = 0;
	for(int n = 0; n < charnum; n++) {
		if(players[n] -> MYCHAR == KIRBY) alreadymade++;
	}
	if(alreadymade == 0) {
		PA_FatLoadSfx("kirbydoublejump", "kirbydoublejump");
		PA_FatLoadSfx("kirbydsmash", "kirbydsmash");
		PA_FatLoadSfx("kirbyfsmash", "kirbyfsmash");
		PA_FatLoadSfx("kirbyftilt", "kirbyftilt");
		PA_FatLoadSfx("kirbyjump", "kirbyjump");
		PA_FatLoadSfx("kirbyusmash", "kirbyusmash");
		PA_FatLoadSfx("kirbybside", "kirbybside");
		PA_FatLoadSfx("kirbybup1", "kirbybup1");
		PA_FatLoadSfx("kirbybup2", "kirbybup2");
	}
}
void Kirby::initPalettes() {
	palettes.push_back("kirbypink");
	palettes.push_back("kirbyblue");
	palettes.push_back("kirbyyellow");
	palettes.push_back("kirbygreen");
}
// sounds
void Kirby::playsound(int sndnum) {
	if(sndnum == DOUBLEJUMP) PA_FatPlaySfx("kirbydoublejump");
	if(sndnum == SMASHDOWN) PA_FatPlaySfx("kirbydsmash");
	if(sndnum == SMASHLEFT || sndnum == SMASHRIGHT) PA_FatPlaySfx("kirbyfsmash");
	if(sndnum == FTILT) PA_FatPlaySfx("kirbyftilt");
	if(sndnum == JUMP) PA_FatPlaySfx("kirbyjump");
	if(sndnum == SMASHUP) PA_FatPlaySfx("kirbyusmash");
}
// actions
void Kirby::bside() {
	if(action != BSIDE) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 178, 186, 15, ANIM_ONESHOT);
		PA_FatPlaySfx("kirbybside");
		delay = 60/15 * 9;
		setDirection();
		dx = 0;
		action = BSIDE;
	}
	else {
		if(delay == 1) {
			if(checkFloorCollision()) idle();
			else fall();
		}
	}
}
void Kirby::bup() {
	if(action != BUP) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 190, 199, 20, ANIM_ONESHOT);
		PA_FatPlaySfx("kirbybup1");
		aerial = true;
		delay = 60/20 * 10;
		dy = -6;
		dx = 0;
		fastfall = 0;
		DI = 0;
		setDirection();
		action = BUP;
	}
	else {
		if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 199) {
			PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 200, 200, 20, ANIM_LOOP, -1);
			PA_FatPlaySfx("kirbybup2");
			delay = 60/20 * 1;
			dy = 4;
		}
		else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 200) {
			if(!checkFloorCollision()) {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 200, 200, 20, ANIM_LOOP, -1);
				delay = 60/20 * 1;
				dy = 4;
			}
			else {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 201, 201, 20, ANIM_LOOP, -1);
				delay = 60/20 * 1;
				int directionmodifier = 1;
				if(direction ==RIGHT) directionmodifier = -1;
				Hitbox tempbox;
				tempbox.addCircle(createAtkbox(36, 805%64, 22, Knockback((-2*directionmodifier), -.5, 4), .3));
				tempbox.addCircle(createAtkbox(30, 794%63, 22, Knockback((-2*directionmodifier), -.5, 4), .3));
				tempbox.addCircle(createAtkbox(47, 812%64, 10, Knockback((-2*directionmodifier), -.5, 4), .3));
				((vector<Projectile>*)getProj())->push_back(Projectile(x, y, -5*directionmodifier, 0, 20, FINALCUTTER, charnum, tempbox, stage, display));
			}
		}
	}
}
void Kirby::bdown() {
	if(action != BDOWN) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 187, 188, 20, ANIM_LOOP, -1);
		delay = 60/20 * 2;
		dy = -gravity;
		dx = 0;
		action = BDOWN;
		rockcount = 250;
	}
	else {
		if(rockcount > 0) rockcount--;
		if(rockcount == 0 || custom_action(ACTION_SPECIAL, PAD_NEWPRESS)) {
			rockcount = -1;
			PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 203, 204, 20, ANIM_LOOP, -1);
			delay = 60/20 * 2;
			aerial = false;
			dx = 0;
		}
		else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 204) {
			if(checkFloorCollision()) idle();
			else fall();
		}
		else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 188) {
			if(!checkFloorCollision()) {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 189, 189, 20, ANIM_LOOP, -1);
				delay = 60/20 * 1;
				dy = 5;
			}
			else {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 189, 189, 20, ANIM_LOOP, -1);
				delay = 60/20*1;
				aerial = false;
			}
		}
		else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 189) {
			if(!checkFloorCollision()) {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 189, 189, 20, ANIM_LOOP, -1);
				delay = 60/20 * 1;
				dy = 5;
			}
			else {
				PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 189, 189, 20, ANIM_LOOP, -1);
				delay = 60/20*1;
			}				
		}
	}
}
void Kirby::bneut() {
	if(action != BNEUT) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 172, 172, 10, ANIM_LOOP, -1);
		delay = 60/10 * 1;
		setDirection();
		dx = 0;
		action = BNEUT;
	}
	else {
		if(custom_action(ACTION_SPECIAL, PAD_RELEASED)) {
			PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 176, 176, 10, ANIM_LOOP, -1);
			delay = 60/10 * 1;
		}
		else if(delay == 1 && (PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 172 || PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 174)) {
			PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 173, 174, 20, ANIM_LOOP, -1);
			delay = 60/20 * 2;
		}
		else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 176) {
			if(checkFloorCollision()) idle();
			else fall();
		}
	}
}
void Kirby::fthrow() {
	if(action != FTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 212, 218, 10, ANIM_LOOP, -1);
		playsound(FTHROW);
		delay = 60/10 * (218-212+1);
		action = FTHROW;
	}
	else if(delay <= 0) {
		int mult = -1;
		grabbedenemy -> k = Knockback(1, -2.5, 7);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int) (grabbedenemy -> k.length * 3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 6;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		fall();
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 212) {
		dx = 0;
		dy = 0;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 213) {
		dy = -8-gravity;
		aerial = true;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 214) {
		dy = -4-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 215) {
		dy = 0-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 216) {
		dy = 4-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 217) {
		dy = 8-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 218) {
		dx = 0;
		dy = -6-gravity;
	}
	if(grabbedenemy != NULL) {
		if(direction == RIGHT) grabbedenemy -> grabbed((int)(x+handx+dx), (int)(y+dy));
		else grabbedenemy -> grabbed((int)(x-handx+dx), (int)(y+dy));
	}	
}
void Kirby::bthrow() {
	if(action != BTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 219, 223, 10, ANIM_LOOP, -1);
		playsound(BTHROW);
		delay = 60/10 * (223-219+1);
		action = BTHROW;
	}
	else if(delay <= 0) {
		int mult = 1;
		grabbedenemy -> k = Knockback(1.25, -2.5, 7);
		if(direction == RIGHT) {
			mult = -1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 6;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		fall();
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 219) {
		if(direction == RIGHT) dx = -1.5;
		else dx = 1.5;
		dy = -8-gravity;
		aerial = true;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 220) {
		dy = 0-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 221) {
		dy = 8-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 222) {
		dy = 0;
		dx = 0;
		aerial = false;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 223) {
		dy = -4-gravity;
		if(direction == RIGHT) dx = -1.5;
		else dx = 1.5;
		aerial = true;
	}
	if(grabbedenemy != NULL) {
		if(direction == RIGHT) grabbedenemy -> grabbed((int)(x+handx+dx), (int)(y+dy));
		else grabbedenemy -> grabbed((int)(x-handx+dx), (int)(y+dy));
	}	
}
void Kirby::uthrow() {
	if(action != UTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 223, 226, 10, ANIM_LOOP, -1);
		playsound(UTHROW);
		delay = 60/10 * (226-223+1);
		action = UTHROW;
	}		
	else if(delay <= 0) {
		int mult = -1;
		grabbedenemy -> k = Knockback(.5, -3, 7);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 8;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		idle();
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 223) {
		dx = 0;
		dy = 0;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 224) {
		dy = -20-gravity;
		aerial = true;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 225) {
		dy = 20-gravity;
	}
	else if(PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 226) {
		aerial = false;
		dy = 0;
	}
	if(grabbedenemy != NULL) {
		if(direction == RIGHT) grabbedenemy -> grabbed((int)(x+handx+dx), (int)(y+dy));
		else grabbedenemy -> grabbed((int)(x-handx+dx), (int)(y+dy));
	}	
}
void Kirby::dthrow() {
	if(action != DTHROW) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 227, 228, 10, ANIM_LOOP, -1);
		playsound(DTHROW);
		delay = 60/10 * (228-227+1);
		action = DTHROW;
		if(direction == RIGHT) dx = 2;
		else dx = -2;
	}		
	else if(delay == 1 && (PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 228 || PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 227)) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 229, 230, 10, ANIM_LOOP, -1);
		delay = 60/10 * (230-229+1) * 5;
		dx = 0;
	}
	else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 230) {
		PA_StartSpriteAnimEx(MAIN_SCREEN, SPRITENUM, 231, 232, 10, ANIM_LOOP, -1);
		delay = 60/10 * (232-231+1);
		if(direction == RIGHT) dx = -2;
		else dx = 2;
	}
	else if(delay == 1 && PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM) == 232) {
		int mult = -1;
		grabbedenemy -> k = Knockback(.5, -2, 12);
		if(direction == RIGHT) {
			mult = 1;
		}
		grabbedenemy -> hitstun = (int)(grabbedenemy -> k.length*3 * (1+(grabbedenemy -> percentage/100)));
		grabbedenemy -> kx = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dx * mult;
		grabbedenemy -> ky = (1+(grabbedenemy -> percentage/100)) * grabbedenemy -> k.dy;
		grabbedenemy -> dx = grabbedenemy -> dy = grabbedenemy -> DI = grabbedenemy -> fastfall = 0;
		grabbedenemy -> percentage += 10;
		grabbedenemy -> stun();
		grabbedenemy -> lasthitby = charnum;
		grabbedenemy = NULL;
		idle();
	}
}
void Kirby::jaywalk() {
	int frame = PA_GetSpriteAnimFrame(MAIN_SCREEN, SPRITENUM);
	if(frame == 82 && direction == RIGHT) x += 8;
	if(frame == 82 && direction == LEFT) x -= 8;
}
Kirby::~Kirby() {
	allatkbox.clear();
	alldefbox.clear();
	PA_DeleteSprite(MAIN_SCREEN, SPRITENUM);
	PA_FatFreeSprite(MYCHAR);
}
