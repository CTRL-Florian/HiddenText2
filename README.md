# HiddenText 2

This is a program that you can use to make some cool annimations. The project's name lies in a core mechanic of this program: You can show text, 
that's readable while playing the video (or just letting the program run). But becomes invisible the moment you pause it. 
Take a picture of your screen while running to verify this!
<br>

## Examples
Note that these are gifs. Whilst running the program, the object is more clear.
<br>

### Hidden square:
<p align="center">
  <img src="gifs/Square.gif" alt="Example picture" />
</p>


### Hidden text:
<p align="center">
  <img src="gifs/Text.gif" alt="Example picture" />
</p>


## How to execute
1) Clone git repository.
2) Open .sln file (Microsoft Visual Studio).
3) Build & Run.
<br><br>
The git repository contains the needed SDL library.
<br>

## How to customize the program
There's already four programs written in program.cpp. Select in the main class (HiddenText2.cpp) what program you want to run.
<br>
Each program should start with initializing SDL and creating a scene (default constructor or Scene(string name, int width, int height). 
It should also end with quitting SDL and destroying the scene (with it's correct method).
You can then create some variables you might need (e.g. making colors, sizes, ...) before starting a while loop. This while loop must contain a stop condition
(mostly the SDL_QUIT event), actions to apply on the scene, updating the scene... The actions you make on the scene only render if you update!
<br><br>

### Actions you can make on the scene are listed below:
<pre>
int getWidth()
    - Returns the width.
    
int getXCenter()
    - Returns the X coordinate of the center.
    
int getHeight()
    - Returns the height.

int getYCenter()
    - Returns the Y coordinate of the center.

SDL_Window* getWindow()
    - Returns the pointer to the scene's window.

SDL_Renderer* getRenderer()
    - Returns the pointer to the scene's renderer.
    
SDL_Texture* getBackground()
    - Returns the pointer to the scene's (background) texture.

bool drawRect(SDL_Rect rect)
bool drawRect(SDL_Rect rect, int r, int g, int b, int a)
    - Draw a rectangle on the window, using the rgba values (default is red).

bool fill()
bool fill(int r, int g, int b, int a)
    - Fill the window with the rgba based color (default is white) 
      Does not use the background texture.

bool drawFilledRect(SDL_Rect rect, int r, int g, int b, int a)
    - Draw a filled rectangle on the window, using the rgba values.

bool noisePixel()
bool noisePixel(SDL_Texture* tex, SDL_Rect rect)
    - Applies a black and white noise on the given texture (no alpha-value textures), 
      then adds it the the renderer.
  
bool noiseGray()
bool noiseGray(SDL_Texture* tex, SDL_Rect rect)
    - Applies a grayscale noise on the given texture (no alpha-value textures), 
      then adds it the the renderer.

bool noisePixelOnText(SDL_Texture* tex, int x, int y)
bool noisePixelOnText(SDL_Texture* tex, SDL_Rect rect)
    - Applies a black and white noise on the given (text) texture (alpha-value textures), 
      then adds it the the renderer.

SDL_Rect rectToCenter(SDL_Texture* tex) const
    - Returns a SDL_Rectangle that fits the texture and centers it on the window.

bool keepBackground()
    - Keeps the background this update cycle (background must be set, 
      note that the fill method doesnt set the background texture).

bool render(SDL_Texture* tex)
bool render(SDL_Texture* tex, SDL_Rect rect)
    - Render a given texture with a position and size (default is window size).

bool update()
bool update(bool clear)
    - Updates the window, renders everything that's been added the the renderer. 
      The bool determines of the renderer gets cleared after updating (default is true).
  
bool renderClear()
    - Clears the renderer.

bool SDLDestroy()
    - Destroys the background texture, renderer and window.
</pre>
<br>

### Other functions:
<pre>
void position(SDL_Rect& rect, int x, int y)
    - Reposition a rectangle given X and Y coordinates. Coordinates on top left corner of rectangle.
  
void positionCenter(SDL_Rect& rect, int x, int y)
    - Reposition a rectangle given X and Y coordinates. Coordinates on center of rectangle.
  
void move(SDL_Rect& rect, int x, int y)
    - Reposition a rectangle by adding X and Y values to the X and Y value of the rectangle.

void resize(SDL_Rect& rect, int m)
    - Multiply the size of a rectangle in the right and down direction.
  
void resize(SDL_Rect& rect, int w, int h)
    - Change the size of a rectangle. Rectangle will grow / shrink in the right and down direction.
  
void resizeAll(SDL_Rect& rect, int m)
    - Multiply the size of a rectangle in all directions.
  
void resizeAll(SDL_Rect& rect, int w, int h)
    - Change the size of a rectangle. Rectangle will grow / shrink in all directions.

SDL_Texture* textTexture(SDL_Renderer* r, const char* s, int size)
    - Returns a texture of the given string. Texture has alpha-values.
</pre>
<br>
