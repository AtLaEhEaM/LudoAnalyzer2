#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum Color {
    Red, Green, Blue, Yellow
};

std::string ColorToString(Color c) {
    switch (c) {
    case Red: return "Red";
    case Green: return "Green";
    case Blue: return "Blue";
    case Yellow: return "Yellow";
    }
    return "Unknown";
}

class Pieces {
private:
    Color pieceColor;

public:
    Pieces() : pieceColor(Red) {}
    Pieces(Color c) : pieceColor(c) { OnStart(c); }

    int location = 0;
    int BoardLocation = 0;
    bool canMove = false;
    bool hasWon = false;

    void OnStart(Color c) {
        switch (c) {
        case Red:
            BoardLocation = 14;
            break;
        case Yellow:
            BoardLocation = 40;
            break;
        case Green:
            BoardLocation = 27;
            break;
        case Blue:
            BoardLocation = 1;
            break;
        }
    }

    Color GetColor() const {
        return pieceColor;
    }
};

bool IsUnkillableSquare(int loc) {
    int unkillableSquares[] = { 1, 9, 14, 22, 27, 32, 40, 47 };
    for (int val : unkillableSquares) {
        if (loc == val) return true;
    }
    return false;
}

void CheckPiece(std::vector<Pieces>& pieces, int index) {
    for (int i = 0; i < pieces.size(); i++) {
        if (i != index && pieces[i].BoardLocation == pieces[index].BoardLocation
            && pieces[i].canMove && !IsUnkillableSquare(pieces[i].BoardLocation)) {
            pieces[i].BoardLocation = 0;
            pieces[i].location = 0;
            pieces[i].canMove = false;
        }
    }
}

void CheckWin(std::vector<Pieces>& pieces, int index) {
    if (pieces[index].location >= 57) {
        pieces[index].hasWon = true;
    }
}

void StartGame(std::vector<Pieces>& pieces) {
    for (int i = 0; i < 4; i++) {
        pieces.push_back(Pieces(Red));pieces.push_back(Pieces(Blue));
        pieces.push_back(Pieces(Yellow));
        pieces.push_back(Pieces(Green));
        
    }
}

bool TeamHasWon(std::vector<Pieces>& pieces, Color c) {
    int count = 0;
    for (const auto& p : pieces) {
        if (p.GetColor() == c && p.hasWon) count++;
    }
    return count == 4;
}

int main() {
    srand((unsigned)time(0));

    const int X = 1000;

    int outFirstCount[4] = { 0 };
    int winCount[4] = { 0 };
    int outFirstAndWinCount[4] = { 0 };
    long long totalMoves = 0;

    for (int run = 0; run < X; run++) {
        std::vector<Pieces> pieces;
        StartGame(pieces);

        int totalTurns = 0;
        bool complete = false;
        Color winner;
        bool firstMoveFound = false;
        Color firstMover = Red;

        while (!complete) {
            for (Color currentColor : {Red, Yellow, Green, Blue}) {
                totalTurns++;

                std::vector<int> movableIndexes;
                for (int i = 0; i < pieces.size(); i++) {
                    if (pieces[i].GetColor() == currentColor && (pieces[i].canMove || pieces[i].location == 0)) {
                        movableIndexes.push_back(i);
                    }
                }

                if (movableIndexes.empty()) continue;

                int choice = movableIndexes[rand() % movableIndexes.size()];
                Pieces& piece = pieces[choice];

                int roll = (rand() % 6) + 1;

                if (!piece.canMove) {
                    if (roll == 6) {
                        piece.canMove = true;
                        piece.BoardLocation++;
                        piece.location++;

                        if (!firstMoveFound) {
                            firstMover = currentColor;
                            firstMoveFound = true;
                        }
                    }
                }
                else {
                    piece.BoardLocation += roll;
                    piece.location += roll;
                    CheckWin(pieces, choice);
                    CheckPiece(pieces, choice);
                }

                if (TeamHasWon(pieces, currentColor)) {
                    winner = currentColor;
                    complete = true;
                    break;
                }
            }
        }

        outFirstCount[firstMover]++;
        winCount[winner]++;
        if (firstMover == winner) outFirstAndWinCount[winner]++;
        totalMoves += totalTurns;
    }

    std::ofstream summaryFile("ludo_summary4.txt");
    summaryFile << "Simulated " << X << " games\n\n";

    float winratio;

    summaryFile << "Color Stats:\n";
    for (int c = 0; c < 4; c++) {
        summaryFile << ColorToString((Color)c) << ":\n";
        summaryFile << "  Got out first: " << outFirstCount[c] << "\n";
        summaryFile << "  Won: " << winCount[c] << "\n";
        summaryFile << "  Got out first AND won: " << outFirstAndWinCount[c] << "\n";
        winratio = (static_cast<float>(winCount[c]) / X) * 100;
        summaryFile << "  Average: " << winratio << "\n\n";
    }

    double avgMoves = (double)totalMoves / X;
    summaryFile << "Average number of moves per game: " << avgMoves << "\n";

    summaryFile.close();

    std::cout << "Simulation complete. Summary written to yes ludo_summary.txt\n";

    return 0;
}
