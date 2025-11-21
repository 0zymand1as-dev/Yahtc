#include "../Yahtc/Yahtc.h"
#include <ncurses.h>


#define MAX_STR 200
#define MAX_ROLLS 3
typedef struct {
    char* name[MAX_STR + 1];
} PlayerMenu;
 

/*
 This is the callback for the menu. This signature is exact
 The state is considered as immutable, hence const. 
 Yes you could access the cups via the state and shit like that, but the idea is that you only modify the cups
*/
// This signature should be in the framework file
enum Hands afterRollUpdateMenu(const State* state, Cup* cup, void* player_name) {
    return;
}

// Another function that should be i the barebones framework file
void afterPlayerUpdateMenu(const State* state, void* info) {
    return;
}

int main(void) {
    
    // Setup the display
    
    initscr();			/* Start curses mode. From now on this only terminal IO is thru curses 		  */
    printw("Hello World !!!");	/* Print Hello World		  */
    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    endwin(); // Explictily clears the screen and closes out ncurses, (assuming you dont have multiple windows)
        

    // Setup the game
    State* game;
    srand(time(NULL));  // The game doesnt seed rng by default
    Rules rules = {
        .players_count = 2,
        .max_round = 13,
        .winner_score = 1000,
        .rerolls = MAX_ROLLS,
        .dices_count = 5,
        .dices_faces = 6,
        .sstraight_count = 4,
        .lstraight_count = 5,
        .upper_bonus_req = 63,
        .upper_bonus_amo = 35,
        .extra_yahtzee_bonus = 100,
        .full_house_points = 25,
        .sstraight_points = 30,
        .lstraight_points = 40,
        .yahtzee_points = 50
    };

    // This is player information which is just for the menu to use. Later we assign each player to a particular index in the game state
    // Then, for each players turn, the menu function will be called with this passed into it
    PlayerMenu player_A = {
        .name = "test",
    };
    
    PlayerMenu player_B = {
        .name = "test2",
    };
    


    // There are really 3 phases that are important to display menus: inbetween turns, during the 3 rolls, during scoring sheet
    // game_next is the menu inbetween turns
    // game_round is used after 
    // T
    PlayerMenuHandler ncursesInfo = {
        .function = afterRoundUpdateMenu,
        .info = NULL // This is always passed to the callback, so its more global than the player information
    };


    // I think this pretty much just allocs the game nd does background stuff
    game = game_init(&rules); 

    // Since the callback to update the menu is called internally by the api, all the information of the player at a specific index
    // has to be stored in the game state. Now when the game updates its state and is ready for the menu, it an pass information
    // abut the players to the callback
    game_sit_player(game, 0, &player_A);  // The game need a callback
    game_sit_player(game, 0, &player_B);  // The game need a callback
    
    // Game loop
    game_start(game, &ncursesInfo); // This will call menu?

    while (1) {
        if (game_done(game, NULL)) {  // Why would i ever need to pass the menu info to this? I can just do menu stuff outside the function
            break;
        }

        // Processing all 3 rolls for the current player
        game_round(game, NULL); // The menu parameter is only if you want a special menu to run after the player finished their rolls
        game_next(game, &ncursesInfo);  // This advances to the next player
    }

    // Forevver:
    // If quid flag: quit
    // game_next()
    

    // Exit
}
