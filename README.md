# PT-Assignment-2---Zumo-Naughts-and-Crosses
Naughts and Crosses game created using Zumo robots.

to-do list:

1. Build a GUI with...
		a virtual N&C board (probably just 9 hard-coded buttons representing a square each, but maybe a 2d array of buttons? That way could expand to bigger sizes? I dunno)
		some kind of output to player (maybe player registration on start, so we can use names and shit?)

2. Write code so...
		Click a square-button and the Zumo moves there on the actual board, sets button text/image to X/O depending on whose turn
		Guessing the Zumo will just go there from wherever it was last sent, so need to have some kind of class that works out how many vert & horz lines it needs to cross to arrive at selected square
		Once we've got that, just re-purpose the border-detect code so that it keeps moving until it's detected however many borders that aren't edges of the board
		On every completed move, need a method that checks for winning combinations of X/Os. Shouldn't be too bad, I think there's even an AAF lab where we did JS N&C that will use the algorithm we need

Don't know if you guys have any other ideas you wanna add in, but think this stuff covers everything. Probably need to build our GUI first so we have a way that we can start testing our code once it's written.
