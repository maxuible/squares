#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdlib.h>
#include <time.h>

#define WINDOW_HEIGHT  900
#define WINDOW_WIDTH 1600

static void drawRect(u8* buffer, i32 bufferWidth, i32 x, i32 y, i32 w, i32 h, u8 color[4]) {
    i32 x1 = x;
    i32 y1 = y;

    for(x = x1; x < w + x1; x++) {
        for(y = y1; y < h + y1; y++) {
            u32 index = (u32)y * (4 * (u32)bufferWidth) + (u32)x * 4;
            memcpy(&buffer[index], color, 4 * sizeof(u8));
        }
    }
}


static void subtractColor(u8* buffer) {
    for (int i = 1; i < (WINDOW_HEIGHT * WINDOW_WIDTH * 4); ++i) {
        if (buffer[i] > 0) { buffer[i] = buffer[i] - 1; }
    }

}

static void drawRandomRect(u8* buffer)
{
    u8 color[4] = {255, 0, 0, 255};

    int w = rand() % (WINDOW_WIDTH / 8);
    int h = rand() % (WINDOW_HEIGHT / 8);
//    int w = 1;
//    int h = 1;

    int x = rand() % (WINDOW_WIDTH  - w);
    int y = rand() % (WINDOW_HEIGHT - h);
    color[0] = rand() % 255;
    color[1] = rand() % 255;
    color[2] = rand() % 255;

    drawRect(buffer, WINDOW_WIDTH, x, y, w, h, color);

}

int main() {

    srand(time(NULL));
	RGFW_window* window = RGFW_createWindow("name", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (u16)(RGFW_windowCenter | RGFW_windowNoResize));
	//RGFWDEF RGFW_window* RGFW_createWindow(const char* name, i32 x, i32 y, i32 w, i32 h,  RGFW_windowFlags flags);
	RGFW_event event;

	RGFW_window_setExitKey(window, RGFW_escape);

    u8* buffer = (u8*)RGFW_ALLOC((u32)(WINDOW_WIDTH * WINDOW_HEIGHT * 4));


    RGFW_surface *surface =  RGFW_createSurface(buffer, WINDOW_WIDTH, WINDOW_HEIGHT, RGFW_formatRGBA8);

	while (RGFW_window_shouldClose(window) == RGFW_FALSE) {

        drawRandomRect(buffer);
//        drawRect(buffer, WINDOW_WIDTH, 0, 0, 100, 100, color2);
        subtractColor(buffer);
		while (RGFW_window_checkEvent(window, &event)) {
			if (event.type == RGFW_quit)
				break;
		}
        RGFW_window_blitSurface(window, surface);
	}

	RGFW_window_close(window);
}
