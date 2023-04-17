/*

 Created by Abhilekh Gautam Apr 17, 2023

 Implementation of the boundary fill algorithm using
 recursive approach

*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Represents mouse position.
struct MousePosition{
    int x;
    int y;
};

class Maze: public olc::PixelGameEngine{
    std::vector<MousePosition> mouse_positions;
    olc::Pixel fill_color = olc::CYAN; // color to be filled with

public:
    Maze() {
        sAppName = "Boundary Fill Algorithm";
    }

    // TODO: detect touch outside the boundary
    // program crashes if the mouse is clicked outside the boundary.
    // recursive boundary fill algorithm.
    void boundary_fill(int x, int y, olc::Pixel fill, olc::Pixel boundary){
            olc::Pixel current = GetDrawTarget()->GetPixel(x, y);
            if (current != boundary && fill != boundary && fill != current) {
                Draw(x, y,fill);
                boundary_fill(x, y + 1, fill, boundary);
                boundary_fill(x, y - 1, fill, boundary);
                boundary_fill(x + 1, y, fill, boundary);
                boundary_fill(x - 1, y, fill, boundary);
            }
    }

    bool OnUserCreate() override{
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::WHITE);

        // Draw Boundary Strips
        for (int x = 10; x < ScreenWidth(); x = x + 20){
            for (int y = 10; y < ScreenHeight(); y = y + 20){
                DrawLine(x, y, ScreenWidth() - x, y, olc::BLACK);
                DrawLine(x, y, x, ScreenHeight() - x, olc::BLACK);
            }
        }
        // Boundary Strip ends here.

        // add clicked mouse position to vector
        if (GetMouse(0).bHeld){
                MousePosition mousePosition{GetMouseX(), GetMouseY()};
                mouse_positions.emplace_back(mousePosition);
        }

        for (auto elt: mouse_positions) {
            boundary_fill(elt.x, elt.y, fill_color, olc::BLACK);
        }
        return true;
    }
};

int main() {
    Maze my_maze;

    if(my_maze.Construct(400,400,4,4))
        my_maze.Start(); // start the game engine

    return 0; // my happy compiler :)
}
