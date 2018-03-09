# PT-Assignment-2---Zumo-Naughts-and-Crosses
Naughts and Crosses game created using Zumo robots.

to-do list:

0. ADD JAMIE TO THE BASTARDIN' REPO!!!!! ---- Hi guys :3

1. Build a GUI with...
		a virtual N&C board (probably just 9 hard-coded buttons representing a square each, but maybe a 2d array of buttons? That way could expand to bigger sizes? I dunno)
		some kind of output to player (maybe player registration on start, so we can use names and shit?)

2. Write code so...
		Click a square-button and the Zumo moves there on the actual board, sets button text/image to X/O depending on whose turn
		Guessing the Zumo will just go there from wherever it was last sent, so need to have some kind of class that works out how many vert & horz lines it needs to cross to arrive at selected square
		Once we've got that, just re-purpose the border-detect code so that it keeps moving until it's detected however many borders that aren't edges of the board
		Zumo will need to know what direction it's facing so it can turn the right way before it starts moving.
		Look at installing Zumo Compass and treating the board as N/E/S/W
		Deal with other Zumo blocking path. Options are:
							Figure out a route around the other Zumo
							Switch LED colours and have other Zumo continue the move
		On every completed move, need a method that checks for winning combinations of X/Os. Shouldn't be too bad, I think there's even an AAF lab where we did JS N&C that will use the algorithm we need

3. Physical Board...
		Put together a 3x3 board, edge of the board needs to be a different shade to the actual lines on the board, so Zumo interacts differently depending on threshold.

4. Raspberry Pi...
		Tweet some shit about moves and winners, maybe see how this goes but prioritize other stuff if this is long?

Don't know if you guys have any other ideas you wanna add in, but think this stuff covers everything. Probably need to build our GUI first so we have a way that we can start testing our code once it's written.

METHODS:
	Move checking algorithm (cases) - Sesh
	Globals for coordinates & orientation, methods to update after move - Mark
	Check if square has been marked
	Check for other Zumo in square
	Nudge other Zumo and switch sides
