#include "SDL.h"
#include<string>
#include"canvas.h"
#include "image.h"
#include "scene.h"
#include "FreeImage.h"
#include "matrix.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

void test()
{
	SDL_LoadBMP("");
	//源,目的
	//SDL_BlitSurface(hello,NULL,screen,NULL);
	//更新窗口
	//SDL_Flip(screen);
	SDL_Delay(2000);
	//释放已加载的图像
	//SDL_FreeSurface(hello);

}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadImage = SDL_LoadBMP(filename.c_str());
	if (loadImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadImage);
		SDL_FreeSurface(loadImage);
		Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0,0xff,0xff);
		//仅当blit这个表面的时候才使用关键色
		SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
	}
	return optimizedImage;
}
void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source,NULL,destination,&offset);
}

void clean_up()
{
	SDL_Quit();
}

Uint32 get_pixel32(SDL_Surface *surface,int x,int y)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y*surface->w)+x];
}

void put_pixel32(SDL_Surface *surface,int x,int y,Uint32 pixel)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[(y*surface->w)+x] = pixel;
}

/*
int main(int argc,char* args[])
{
	bool quit = false;
	SDL_Event event;
	SDL_Surface* hello = nullptr;
	SDL_Surface* screen = nullptr;
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return 1;
	}
	//一像素32位
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
//	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	SDL_WM_SetCaption("Engine",NULL);
	while (quit == false)
	{

		if (SDL_MUSTLOCK(screen))
		{
			SDL_LockSurface(screen);
		}

		Uint32 *pixels = (Uint32 *)screen->pixels;
		Canvas* canvas = new Canvas((uint32_t *)screen->pixels,SCREEN_WIDTH,SCREEN_HEIGHT);
	//	canvas->drawLine(Vertex2(Vector2(100, 100), Color(100, 2, 44, 5)), Vertex2(Vector2(100, 300), Color(100, 2, 44, 5)));
	//	canvas->drawTriangle(Vertex2(Vector2(100, 100), Color(100, 2, 44, 5)), Vertex2(Vector2(100, 300), Color(100, 2, 44, 5)),Vertex2(Vector2(400,200),Color(200,100,200,4)));
		Image* image = new Image("D:\\vs2015\\MyCode\\SimpleEngine\\SimpleEngine\\image.txt");
		canvas->loadImage(*image,Vector2(200,200));
		if (SDL_MUSTLOCK(screen))
		{
			SDL_UnlockSurface(screen);
		}

		while (SDL_PollEvent(&event))
		{
			SDL_Flip(screen);
			if (event.type == SDL_QUIT)
			{
				quit = true;
				delete canvas;
				delete image;
			}
		}
	}
	clean_up();
	return 0;
}
*/

int main(int argc, char* args[]){
	FreeImage_Initialise();
	Scene::render();
	FreeImage_DeInitialise();
	return 0;
}
