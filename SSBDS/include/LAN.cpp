#include <MessageQueue.h>
#include <802.11.h>
#include <lobby.h>
// DS <-> DS

#define ROOM_NAME "SSBDS"
#define MAX_PLAYERS 2
#define GAME_CODE 558
#define GAME_VER 0

char dat[10];
bool lobbyinited = false;
int playernumber = -1;

void customVBL(void) {
	IPC_RcvCompleteCheck();
	LOBBY_Update();
	AS_SoundVBL();
}

void receive(unsigned char *data, int length, LPLOBBY_USER from) {
	if(playernumber == 1) {
		PA_SetSpriteXY(MAIN_SCREEN, players[0] -> SPRITENUM, (int)data[0], (int)data[1]);
		PA_SetSpriteAnimFrame(MAIN_SCREEN, players[0] -> SPRITENUM, (int)data[2]);
	}
}

void LAN() {
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	PA_InitText(MAIN_SCREEN, 0);
	PA_SetTextCol(MAIN_SCREEN, 31, 31, 31);

	if(!IPC_Init()) {
		PA_OutputText(MAIN_SCREEN, 0, 0, "IPC INIT FAILED");
		while(true) {}
	}
	IPC_SetChannelCallback(0, &LWIFI_IPC_Callback);
	PA_VBLFunctionInit(customVBL);
	// inits/preps DS <-> DS

	PA_OutputText(MAIN_SCREEN, 1, 3, "Start Game = Start/nJoin Game = Select");

	fadeIn();

	while(playernumber == -1) {
		if(!lobbyinited) {
			LOBBY_Init();
			LOBBY_SetStreamHandler(0x0001, &receive);
			lobbyinited = true;
		} // inits liblobby
		else if(Pad.Newpress.Start) {
			playernumber = 0;
			LOBBY_SetOwnName("Host");
			LOBBY_CreateRoom(ROOM_NAME, MAX_PLAYERS, GAME_CODE, GAME_VER);
		} // creates a new game
		else if(Pad.Newpress.Select) {
			playernumber = 1;
			LOBBY_SetOwnName("Client");
			LOBBY_JoinRoom(LOBBY_GetRoomByGame(0, GAME_CODE));
		} // joins a created game
		PA_WaitForVBL();
	}
	
	int max = LOBBY_GetNumberOfKnownUsers();
	PA_OutputText(MAIN_SCREEN, 1, 3, "                                         ");
	PA_OutputText(MAIN_SCREEN, 1, 4, "                                         ");
	PA_OutputText(MAIN_SCREEN, 1, 3, "Waiting for connection");
	while(max < 1) {
		max = LOBBY_GetNumberOfKnownUsers();
		PA_WaitForVBL();
	}
	
	players.push_back(new Kirby(512/2 -96 -32, 256/3 -32, 1));
	Stage stage = setStage("finaldestination");
	PA_InitText(MAIN_SCREEN, 1); // inits text on the main screen (displays time)
	PA_SetTextCol(MAIN_SCREEN, 31, 31, 31); // text color = white

	while(true) {
		if(playernumber == 0) {
			players[0] -> act();
			dat[0] = (char)(players[0] -> x);
			dat[1] = (char)(players[0] -> y);
			dat[2] = PA_GetSpriteAnimFrame(MAIN_SCREEN, players[0] -> SPRITENUM);
			LOBBY_SendToUser(LOBBY_GetUserByID(0), 0x0001, (unsigned char *)dat, 10);
		}		
		scrollScreen();
		PA_WaitForVBL();
	}
}

