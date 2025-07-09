This C++ program simulates a simplified Ludo game between four colors: Red, Yellow, Green, and Blue.

Features
16 pieces total (4 per color)

Each color moves in turn, selecting a valid movable piece

Dice rolling with 6 unlocking pieces onto the board

Kills opponents on non-unkillable squares

Unkillable safe squares: 1, 9, 14, 22, 27, 32, 40, 47

Win condition: 4 pieces of a color reach position 57

Simulation Mode
Runs multiple games automatically (e.g., 500,000 times)

Tracks statistics:

Number of times each color moved out first

Number of wins per color

Number of times a color both got out first and won

Average number of moves per game

Saves results to a text file

Usage
Compile with a C++ compiler supporting C++11 or newer.

Edit main() to set desired number of simulations.

Run the executable; results will appear in ludo_summary.txt.

Note
Turn order is color-by-color in fixed sequence (Red, Yellow, Green, Blue), which may introduce minor bias over many runs. Randomizing the order per round can reduce this effect.
