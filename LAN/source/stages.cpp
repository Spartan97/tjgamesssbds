#include "stages.h"
#include "stage.h"
const int FINALDESTINATION = 1, POKEMONSTADIUM = 2, CASTLESIEGE = 3, CORNERIA = 4;
// stage shortcuts just like character shortcuts

FinalDestination::~FinalDestination() {}
FinalDestination::FinalDestination() { Initialize(); }
void FinalDestination::Initialize() {
	name = "finaldestination";
	width = 512;
	height = 256;
	topdeath = 0-192;
	leftdeath = 0-128;
	rightdeath = 512+128;
	bottomdeath = 256;
	spawnx.push_back(512/2 -32 -64);
	spawnx.push_back(512/2 -32 +64);
	spawnx.push_back(512/2 -32 -64 -64);
	spawnx.push_back(512/2 -32 +64 +64);
	spawny.push_back(256/3 -32);
	spawny.push_back(256/3 -32);
	spawny.push_back(256/3 -32);
	spawny.push_back(256/3 -32);
	floors.push_back(Floor(64, 132, 512-64-64, false));
	walls.push_back(Wall(96, 132, 248-132, "left"));
	walls.push_back(Wall(512-96, 132, 248-132, "right"));
	ceilings.push_back(Ceiling(64, 132, 512-64-64));
	ledges.push_back(Ledge(64, 132, "left"));
	ledges.push_back(Ledge(512-64, 132, "right"));
	songnames.push_back("Final Destination");
	songnames.push_back("Final Destination");
	songartists.push_back("Super Smash Bros. Brawl");
	songartists.push_back("Super Smash Bros. Melee");
	songs.push_back("SSBDS_Files/music/stages/finaldestination1.mp3");
	songs.push_back("SSBDS_Files/music/stages/finaldestination2.mp3");
} // initializes all the variables for final destination
PokemonStadium::~PokemonStadium() {}
PokemonStadium::PokemonStadium() { Initialize(); }
void PokemonStadium::Initialize() {
	name = "pokemonstadium";
	width = 512;
	height = 256;
	topdeath = 0-192;
	bottomdeath = 256;
	leftdeath = 0-128;
	rightdeath = 512+128;
	spawnx.push_back(512/2 -32 -64);
	spawnx.push_back(512/2 -32 +64);
	spawnx.push_back(512/2 -32 -64 -64);
	spawnx.push_back(512/2 -32 +64 +64);
	spawny.push_back(256/3 -64);
	spawny.push_back(256/3 -64);
	spawny.push_back(256/3 -64);
	spawny.push_back(256/3 -64);
	floors.push_back(Floor(42, 154, 512-42-42, false));
	floors.push_back(Floor(128, 110, 190-128, true));
	floors.push_back(Floor(324, 110, 386-324, true));
	walls.push_back(Wall(50, 154, 216-154, "left"));
	walls.push_back(Wall(512-50, 154, 216-154, "right"));
	ceilings.push_back(Ceiling(42, 216, 512-42-42));
	ledges.push_back(Ledge(42, 154, "left"));
	ledges.push_back(Ledge(512-42, 154, "right"));
	songnames.push_back("Pokemon Gym / Evolution");
	songnames.push_back("Battle Theme");
	songnames.push_back("Lugia's Song");
	songartists.push_back("Pokemon Red/Blue/Yellow");
	songartists.push_back("Pokemon Gold/Silver/Crystal");
	songartists.push_back("Pokemon 2000");
	songs.push_back("SSBDS_Files/music/stages/pokemonstadium1.mp3");
	songs.push_back("SSBDS_Files/music/stages/pokemonstadium2.mp3");
	songs.push_back("SSBDS_Files/music/stages/pokemonstadium3.mp3");
} // initializes the pokemon stadium stage
CastleSiege::~CastleSiege() {}
CastleSiege::CastleSiege() { Initialize(); }
void CastleSiege::Initialize() {
	name = "castlesiege";
	width = 512;
	height = 384;
	topdeath = 0-192;
	bottomdeath = 384;
	leftdeath = 0-128;
	rightdeath = 512+128;
	spawnx.push_back(512/2 -32 -64);
	spawnx.push_back(512/2 -32 +64);
	spawnx.push_back(512/2 -32 -64 -64);
	spawnx.push_back(512/2 -32 +64 +64);
	spawny.push_back(384/3 -64);
	spawny.push_back(384/3 -64);
	spawny.push_back(384/3 -64);
	spawny.push_back(384/3 -64);
	floors.push_back(Floor(40, 344-128, 450-40, false));
	for(int n = 40; n < 202; n++) {
		floors[0].slopes.push_back(0);
	}
	for(int n = 202; n < 300; n++) {
		floors[0].slopes.push_back(-.25);
	}
	for(int n = 300; n < 451; n++) {
		floors[0].slopes.push_back(0);
	}
	// this floor is sloped
	floors.push_back(Floor(84, 288-128, 194-84, true));
	floors.push_back(Floor(302, 270-128, 408-302, true));
	walls.push_back(Wall(48, 350-128, 100, "left"));
	walls.push_back(Wall(442, 350-128, 100, "right"));
	songnames.push_back("Ike's Theme");
	songnames.push_back("Victory is Near");
	songartists.push_back("Fire Emblem 10: Radiant Dawn");
	songartists.push_back("Fire Emblem 9: Path of Radiance");
	songs.push_back("SSBDS_Files/music/stages/castlesiege1.mp3");
	songs.push_back("SSBDS_Files/music/stages/castlesiege2.mp3");
} // initializes Castle Siege
Corneria::~Corneria() {}
Corneria::Corneria() { Initialize(); }
void Corneria::Initialize() {
	name = "corneria";
	width = 512; height = 256;
	topdeath = 0-192;
	bottomdeath = 256;
	leftdeath = 0-128;
	rightdeath = 512+128;
	spawnx.push_back(512/2 -32 -64);
	spawnx.push_back(512/2 -32 +64);
	spawnx.push_back(512/2 -32 -64 -64);
	spawnx.push_back(512/2 -32 -64 +64);
	spawny.push_back(256/3 -96);
	spawny.push_back(256/3 -96);
	spawny.push_back(256/3 -96);
	spawny.push_back(256/3 -96);
	floors.push_back(Floor(106, 386-256, 140-106, false));			
	floors.push_back(Floor(30, 330-256, 368-30, false));
	for(int n = 30; n < 90; n++) {
		floors[1].slopes.push_back(-.25);
	}
	for(int n = 90; n < 214; n++) {
		floors[1].slopes.push_back(.10);
	}
	for(int n = 214; n < 260; n++) {
		floors[1].slopes.push_back(-.21);
	}
	for(int n = 260; n < 295; n++) {
		floors[1].slopes.push_back(-.8);
	}
	for(int n = 295; n < 369; n++) {
		floors[1].slopes.push_back(-.4);
	}
	floors.push_back(Floor(362, 341-256, 484-362, false));
	for(int n = 362; n < 408; n++) {
		floors[2].slopes.push_back(0);
	}
	for(int n = 408; n < 441; n++) {
		floors[2].slopes.push_back(-.2);
	}
	for(int n = 441; n < 485; n++) {
		floors[2].slopes.push_back(.38);
	}
	// 2 floors are sloped
	songnames.push_back("Main Theme");
	songnames.push_back("Fortuna");
	songartists.push_back("Star Fox");
	songartists.push_back("Star Fox Assault");
	songs.push_back("SSBDS_Files/music/stages/corneria1.mp3");
	songs.push_back("SSBDS_Files/music/stages/corneria2.mp3");
} // initializes Corneria