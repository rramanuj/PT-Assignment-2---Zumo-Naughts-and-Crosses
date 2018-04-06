Naughts and Zumos, our robotic spin on the well known tic-tac-toe game. A naughts and crosses inspired game using Zumos, Arduino, Processing, Xbees, a website using MongoDB, a twitter feed using a Raspberry Pi, 2 sheets of card and some crayons.

For this project we had a range of different technologies at our disposal to achieve a goal of our choosing. After pitching a couple of ideas, we opted to use Zumos to robotically visualise a game of naughts and crosses. This is done by a position on the 3 x 3 board being selected via the Processing GUI, then using the current position, direction and destination, the Zumo navigates to the desired square. Consequently this updates the state of the game and if a win or a draw occurs, the players are notified and the game ends. This is followed by the website and twiter feed being updated.

In this current version this only works for two different finished states, which is a draw and a win, with fixed moves to get to those states, regardless of what you press on the GUI. The preprogrammed moves are done through information/coordinates that are given to the navigateZumo() function within arduino, as we could not correctly pass through the information from Processing to be used in Arduino. 

The twitter bot works from the Raspberry Pi's localhost as the version of MongoDB native to Raspberry Pis is not a version that works with mLab, however the scripts are fully functional and tweet an unparsed section of the JSON object fed back from MongoDB (as you can't parse JSON in Python) needing only a change to the source of the database for them to work. The contents of the MongoDB needs to have a index for the day, to be incremented with each win game ("day": n) and an index for the tweet contents ("tweet" :"n"). As the remote database needs to be set up, there is no need for us to give you any permission to access it. As this is the case, the database connection needs to be refactored within the .py file containing the twitter bot code.

All sections of the code and project should work properly upon opening and not need any prior passwords/connections to test/function.

By Jamie Pounds, Mark Scholefield, Rasesh Ramanuj
