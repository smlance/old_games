#include "libtcod.hpp"

int main(){
	TCODConsole::intRoot(80, 50,"Libtcod Hello World");
	TCODConsole::root->printCenter(40, 25,TCOD_BKGND_NONE,"libtcod says: \"Hello, world!\"");
	TCODConsole::flush();
	TCODConsole::waitForKeyPress(TRUE);
}
