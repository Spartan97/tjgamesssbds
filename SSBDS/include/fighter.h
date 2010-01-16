#ifndef FIGHTER_H
#define FIGHTER_H

#define RIGHT 1 //"right"
#define LEFT (-1) //"left"

#define GLOBALGRAVITY 2.0

#include <PA9.h>
#include "hitbox.h"
#include "knockback.h"
#include "circle.h"
#include "stage.h"
#include "effect.h"
#include "display.h"
#include <string>
using std::string;

static const int LAND = 0, SHIELD = 1, ROLL = 2, DODGE = 3, AIRDODGE = 4, CROUCH = 5, FALL = 6, IDLE = 7, RUN = 8, SHORTHOP = 9, JUMP = 10, DOUBLEJUMP = 11, JAB = 12, DASHATTACK = 13, FTILT = 14, UTILT = 15, DTILT = 16, CHARGELEFT = 17, CHARGERIGHT = 18, CHARGEUP = 19, CHARGEDOWN = 20, SMASHLEFT = 21, SMASHRIGHT = 22, SMASHUP = 23, SMASHDOWN = 24, FAIR = 25, BAIR = 26, UAIR = 27, DAIR = 28, NAIR = 29, STUN = 30, SLIDE = 31, HANG = 32, GRABBED = 33, GRAB = 34, GRABATK = 35, FTHROW = 36, BTHROW = 37, UTHROW = 38, DTHROW = 39, DEAD = 40, BNEUT = 41, BSIDE = 42, BUP = 43, BDOWN = 44, WALK = 45;
static const int ATTACK = -1, AIRATTACK = -2, AIRLAG = -3, TILTLAG = -4, RELEASED = -5, RELEASE = -6, HOLD = -7;
// shortcuts for actions

/// Fighter class keeps track of a single player in the game.

/// It is subclassed for more specific behavior, various methods
/// are overrriden by it's subclasses.
class Fighter {
	public:
		//constructor
		Fighter(int num, vector<Fighter*> *listplayers, Display *disp, string n, bool AI = false);
		// variables
		spriteanim tempanim;
		double traction, airresistance, grabatkdamage, DIval;
		double walkspeed;
		double rollspeed;
		bool iswalking;
		bool jabagain;
		double shorthopheight;
		double jumpheight; ///< stores how high a fighter can jump off of the ground. Overwritten by subclasses
		double doublejumpheight; ///< stores how high a fighter can jump from midair. Overwritten by subclasses
		double w1;
		double w2;
		double shieldstr;
		bool shieldbroken;
		int shieldx, shieldy;
		int myledge;
		double runspeed;
		double acceleration;
		int invincibility;
		int ledgewait;
		int freezelen;
		int hangtime;
		int handx, handy, hangx, hangy;
		bool CAPE;
		bool ABSORB;
		bool COUNTER;
		bool PERMAFALL;
		int respawntimer;
		int airdodgecount;
		int effectwait;
		int MYCHAR;
		int chargecount;
		int lasthitby;
		vector<Hitbox> allatkbox;
		vector<Hitbox> alldefbox;
		int leftside, rightside, topside, bottomside;
		bool isCPU;
		bool isdead;
		int SPRITENUM;
		double gravity;
		int jumpmax;
		double x, y, startx, starty;
		double lastx, lasty;
		double dx, dy;
		int direction;
		int action;
		bool aerial;
		int delay, jumpcount, startlag, landinglag, tiltlag, airlag, lcancel, hitstun;
		double fastfall, DI;
		Knockback k;
		double kx, ky;
		double percentage;
		Stage *stage;
		double ymomentum;
		int momentumtime;
		int charnum;
		string name;
		string series;
		vector<int> startframes;
		vector<int> endframes;
		vector<int> framespeeds;
		vector<Fighter*> players;
		vector<Effect> effects;
		vector<const char*> palettes;
		Fighter* grabbedenemy;
		Fighter* grabbedby;
		int grabtimeleft;
		Display *display;
		// virtual methods
		void initDefbox();
		void initAtkbox();
		void initSprite();
		int cpu_getTarget();
		int cpu_target;
		double cpu_target_distance;
		void cpu_obeyRules();
		virtual void actCPU();
		virtual void act();
		void actAir();
		void actGround(); ///< acts on the ground based on key presses
		virtual double cpu_specialweight();
		virtual void cpu_dospecial();
		virtual void bside();
		virtual void bup();
		virtual void bdown();
		virtual void bneut();
		virtual void uthrow();
		virtual void dthrow();
		virtual void bthrow();
		virtual void fthrow();
		virtual void initPalettes();
		void initFrames();
		void release(int dir);
		void released(int dir);
		void grabbed(int otherx, int othery);
		void grab();
		void hold(int d = 300);
		void grabattack();
		void land();
		void shield();
		void roll(int dir = 0);
		void tech();
		void rollUp();
		void attackUp();
		void jumpUp();
		void dodge();
		void airdodge();
		void crouch();
		void fall();
		void permafall();
		void idle();
		void walk(int d = 0);
		void run(int d = 0);
		void shorthop();
		void jump();
		void doubleJump();
		void jab();
		void dashAttack();
		void ftilt();
		void utilt();
		void dtilt();
		void chargeleft();
		void chargeright();
		void chargeup();
		void chargedown();
		void smashleft();
		void smashright();
		void smashup();
		void smashdown();
		void fair();
		void bair();
		void uair();
		void dair();
		void nair();
		void stun();
		void freeze(int duration);
		void slide();
		void hang();
		virtual void jabatk();
		// Sound playing
		virtual void initSounds();
		virtual void playsound(int sndnum);
		// constant methods
		void setStage(Stage *s);
		int getHitstun();
		double getDamagePercent();
		void takeDamage(Circle other, int mult, int hitter, int charge);
		Fighter* checkHits(Fighter* other);
		Hitbox getAtkbox();
		virtual Hitbox getDefbox(int framenum);
		Circle createAtkbox(double extrax, double extray, double radius, Knockback k, double damage, int prior = 0);
		void airAttack();
		void airAttackStylus();
		void smashAttack();
		void move(); ///< moves the sprite
		virtual void jaywalk();
		void setDirection(int rl = 0); ///< flips the direction of the sprite if necessary
		virtual void directionalInfluence(double dx = 0); ///< acts in the air based on key presses
		bool checkForDeath();
		void respawn();
		void beDead();
		int onFloor();
		bool ledgenotinuse(int lnum);
		bool checkLedgeCollision();
		bool checkFloorCollision();
		bool checkWallCollision();
		bool checkCeilingCollision();
		void scroll(double scrollx, double scrolly);
		virtual ~Fighter();
};

#endif
