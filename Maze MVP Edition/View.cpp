#include "View.h"



View::View() {}


void View::setFPS(float FPS) { this->FPS = FPS; }
float View::getFPS() { return FPS; }

std::set<char> View::getUserInput() {
    std::set<char> keysPressed;

    if (GetAsyncKeyState('W') & 0x8000) {
        keysPressed.insert('W');
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        keysPressed.insert('A');
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        keysPressed.insert('S');
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        keysPressed.insert('D');
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        keysPressed.insert(VK_LEFT);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        keysPressed.insert(VK_RIGHT);
    }

    if (GetAsyncKeyState('R') & 0x8000) {
        keysPressed.insert('R');
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        keysPressed.insert(VK_ESCAPE);
    }

    return keysPressed;
}

void View::setWidth(int WIDTH) {
    this->WIDTH = WIDTH;
}
int View::getWidth() {
    return WIDTH;
}

void View::setHeight(int HEIGHT) {
    this->HEIGHT = HEIGHT;
}
int View::getHeight() {
    return HEIGHT;
}

void View::initScreen() {
    screen = new wchar_t[WIDTH * HEIGHT];
    console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(console);
    painted = 0;
}
void View::updateConsole() {

    WriteConsoleOutputCharacterW(console, screen, WIDTH * HEIGHT, { 0,0 }, &painted);
}
void View::setCharPixel(int y, int x, short charPixel ) {
    wchar_t wcharShade = static_cast<wchar_t>(charPixel);
    screen[y * WIDTH + x] = wcharShade;
}