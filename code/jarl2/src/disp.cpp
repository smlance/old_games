#include "main.h"

Display::Display()
{

}

Display::~Display()
{
	// free screen and nullify pointer
	SDL_FreeSurface(window);
	window = NULL;

	// free images and nullify pointers
	for (unsigned int i = 0; i < img_list.size(); i++)
	{
		SDL_FreeSurface(img_list[i]);
		img_list[i] = NULL;
	}
	// nullify pointers to fonts
	for (unsigned int i = 0; i < font_list.size(); i++)
	{
		font_list[i] = NULL;
	}

	// safely quit
	SDL_Quit();
}

void Display::refresh()
{
	SDL_Flip(window);
}

Uint32 Display::getPixel32(int x, int y, Surface *surface)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

void Display::init()
{
	// init SDL, center window, create window
	SDL_Init(SDL_INIT_EVERYTHING);
	putenv((char*)"SDL_VIDEO_CENTERED=1");
	window = SDL_SetVideoMode(VIDEO_MODE);
	SDL_WM_SetCaption("Jarl", NULL);

	// arbitrary large list size for storing images
	img_list.resize(1000);
	loadGfx();

	// initialize fonts
	font_list.resize(1);
	initFonts();
}

void Display::updateCam(int x, int y)
{
	// x and y come in as player coordinates
	int pixel_x = x * TILE_SIDE;
	int pixel_y = y * TILE_SIDE;
	// pan variables are used for centering the player as he moves
	int pan_x = pixel_x - (GAME_WIDTH / 2);
	// add (TILE_SIDE / 2) so that we see full tiles at top and bottom
	// (without it, top and bottom are split in half)
	int pan_y = pixel_y + (TILE_SIDE / 2) - (GAME_HEIGHT / 2);

	/* ADJUST THE PAN VALUES
	 * only set the position to the new values if the resulting values are between
	 * 0 and the SCREEN_W/H!
	 * subtract half a SCREEN_WIDTH and HEIGHT from player's positions to obtain
	 * the coordinates of the cam.
	 */
	if (pan_x < 0)
		pan_x = 0;

	if (pan_x >= GAME_WIDTH)
		pan_x = pixel_x - abs(pixel_x - GAME_WIDTH) - TILE_SIDE;

	if (pan_y < 0)
		pan_y = 0;

	if (pan_y >= GAME_HEIGHT)
		pan_y = pixel_y - abs(pixel_y - GAME_HEIGHT) - TILE_SIDE;

	// finally, set the camera position
	camera.setPos(pan_x, pan_y);
}

void Display::initFonts()
{
	font_list[0] = new Font;
	font_list[0]->loadFont(TXT_PATH);
}

void Display::applySurface(int x, int y, Surface *source, Rect *clip)
{
	// by default (if destination not given), draw to window
	applySurface(x, y, source, clip, window);
}

void Display::applySurface(int x, int y, Surface *source, Rect *clip,
                           Surface *dest)
{
	// set up rectangle with dimensions
	// offset is for (x, y) position of box
	// clipping is for displaying only part of the source at the position
	Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, dest, &offset);
}

/*template <typename Head, typename... Tail>

//static void Display::concatenateString(std::ostream& out)
{

}

static void Display::concatenateString(std::ostream& out, const Head& head, const Tail&... tail)
{
  out << head;
  concatenateString(out, tail...);
}*/
sstring Display::concatenateString(int count, ...)
{
	va_list ap;
	std::stringstream stream;
	
	va_start(ap, count);
	for (int i = 0; i < count; i++)
	{
		stream << va_arg(ap, const char *);
	}
	va_end(ap);
	
	return stream.str();
}

void Display::render()
{
	// update the camera position so we know what to draw
	updateCam(game.getEnt(0)->getX(), game.getEnt(0)->getY());
	int cam_x = camera.getViewer()->x;
	int cam_y = camera.getViewer()->y;
	// convert pixel (cam_) coordinates to game (tile-sized) coordinates
	int game_x = cam_x / TILE_SIDE;
	int game_y = cam_y / TILE_SIDE;

	// render tiles
	// only draw tiles that are within our camera bounds!
	// (this is why we use game_x and game_y)
	for (unsigned int i = game_x; i < game_x + TILE_COLS; i++)
	{
		for (unsigned int j = game_y; j < game_y + TILE_ROWS; j++)
		{
			// display the lowest entity id in the stack/list of entities (tiles/items/doors)
			// in this position
			int id_orig = game.getArea()->getTile(i, j)->getID();
			if ( !( game.getArea()->getTile(i, j)->getVisible() ) )
			{
				applySurface(i*TILE_SIDE - cam_x, j*TILE_SIDE - cam_y,
				             img_list[BLACK_SPACE], NULL);
			}
			else
			{

				applySurface(i*TILE_SIDE - cam_x, j*TILE_SIDE - cam_y,
				             img_list[id_orig], NULL);

				
				// check for any other entities that need to be printed on top of this cell
				for (unsigned int k = 0;
				        k < game.getArea()->getTile(i, j)->getEntListSize();
				        k++)
				{
					// if they exist
					if (game.getArea()->getTile(i, j)->getEnt(k))
					{
						// grab their ids, print them (then go up and do checks for as large
						// as the list is; i.e., continue)
						int id = game.getArea()->getTile(i, j)->getEnt(k)->getID();
						applySurface(i*TILE_SIDE - cam_x, j*TILE_SIDE - cam_y,
						             img_list[id], NULL);

					}
				}
			}
		}
	}

	// render entities
	// only draw entities within bounds!
	for (unsigned int i = 0; i < game.getEntListSize(); i++)
	{
		if (game.getEnt(i))
		{
			int x_ = game.getEnt(i)->getX();
			int y_ = game.getEnt(i)->getY();
			int id_ = game.getEnt(i)->getID();
			// if the coordinates of the entity fit within our cam boundaries
			if (x_ >= game_x && x_ < game_x + TILE_COLS
			        && y_ >= game_y && y_ < game_y + TILE_ROWS
			        && ( game.getArea()->getTile(x_, y_)->getVisible() ) )
			{
				// display it
				applySurface(x_*TILE_SIDE - cam_x, y_*TILE_SIDE - cam_y,
				             img_list[id_], NULL);
	
			}
		}
	}

	// render texts
	/* TODO: functionize all of this
	In other words, make a function that can concatonate as many items together as you want...
	*/
	sstring txt = concatenateString(2, "Health: ", intToConstChar(game.getEnt(0)->hp));
	font_list[0]->dispText(GAME_WIDTH, 0, txt);
	txt = concatenateString(2, "Attack: ", intToConstChar(game.getEnt(0)->atk));
	font_list[0]->dispText(GAME_WIDTH, 16, txt);
	txt = concatenateString(2, "Defense: ", intToConstChar(game.getEnt(0)->def));
	font_list[0]->dispText(GAME_WIDTH, 32, txt);
}


const char *Display::intToConstChar(int int_in)
{
	std::stringstream convert; // stringstream used for the conversion
	convert << int_in;//add the value of Number to the characters in the stream
	//return convert.str();//set Result to the content of the stream
	const char *retval;
	//snprintf(retval, "%s", convert);
	
	return convert.str().c_str();
}

Surface *Display::loadImg(sstring path)
{
	// init surfaces
	Surface *loaded_image = NULL;
	Surface *optimized_image = NULL;
	loaded_image = IMG_Load(path.c_str());

	// 'if's are for checking against errors
	// -> if loaded image exists/is valid
	if (loaded_image)
	{
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);

		// remove pink (FF00FF) background, make transparent
		if (optimized_image)
		{
			// makes all of the RGBs of FF00FF on opt_img transparent
			SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB
			                (optimized_image->format, 0xFF, 0, 0xFF));
		}
	}

	return optimized_image;
}

void Display::loadGfx()
{
	// initialize list
	for (unsigned int i = 0; i < img_list.size(); i++)
	{
		img_list[i] = NULL;
	}

	// load sprite sheet into a surface
	Surface *file = loadImg(GFX_PATH);
	// calculate number of rows and cols
	int rows = file->h / TILE_SIDE;
	int cols = file->w / TILE_SIDE;
	// cell of img_list to start placing surfaces in
	int cell = 0;

	Rect 	frames[rows*cols];
	Surface frame_surf[rows*cols];

	// get bg color (transparent)
	Uint32 bg_color = SDL_MapRGB((file)->format, 0xFF, 0, 0xFF);

	// get dimensions of each cell
	int cell_width = file->w / cols;
	int cell_height = file->h / rows;

	// demark top and bottom positions
	int top = cell_height;
	int base = cell_height;

	int current_frame = 0;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			// get dimensions and position of this cell's rectangle
			frames[current_frame].x = cell_width * c;
			frames[current_frame].y = cell_height * r;

			frames[current_frame].w = cell_width;
			frames[current_frame].h = cell_height;

			for (int pixel_col = 0; pixel_col < cell_width; pixel_col++)
			{
				for (int pixel_row = 0; pixel_row < cell_height; pixel_row++)
				{
					int pixel_x = (cell_width * c) + pixel_col;
					int pixel_y = (cell_height * r) + pixel_row;

					// if we get the transparent color (?)
					if(getPixel32(pixel_x, pixel_y, file) != bg_color)
					{
						// set new width for this cell
						frames[current_frame].x = pixel_x;

						// break out of these nested for loops
						pixel_col = cell_width;
						pixel_row = cell_height;
					}
				}
			}

			for (int pixel_col_w = cell_width - 1; pixel_col_w >= 0; pixel_col_w--)
			{
				for (int pixel_row_w = 0; pixel_row_w < cell_height; pixel_row_w++)
				{
					int pixel_x = (cell_width * c) + pixel_col_w;
					int pixel_y = (cell_height * r) + pixel_row_w;

					if(getPixel32(pixel_x, pixel_y, file) != bg_color)
					{
						//Set the width
						frames[current_frame].w = (pixel_x - frames[current_frame].x) + 1;

						//Break the loops
						pixel_col_w = -1;
						pixel_row_w = cell_height;
					}
				}
			}

			for (int pixel_row = 0; pixel_row < cell_height; pixel_row++)
			{
				//Go through pixel columns
				for (int pixel_col = 0; pixel_col < cell_width; pixel_col++)
				{
					//get_ the pixel offsets
					int pixel_x = (cell_width * c) + pixel_col;
					int pixel_y = (cell_height * r) + pixel_row;

					//If a non colorkey pixel is found
					if(getPixel32(pixel_x, pixel_y, file) != bg_color)
					{
						//If new top is found
						if(pixel_row < top)
						{
							top = pixel_row;
							frames[current_frame].y += top;
							frames[current_frame].h -= top;
						}

						//Break the loops
						pixel_col = cell_width;
						pixel_row = cell_height;
					}
				}
			}

			for (int pixel_row = cell_height - 1; pixel_row >= 0; pixel_row--)
			{
				//Go through pixel columns
				for (int pixel_col = 0; pixel_col < cell_width; pixel_col++)
				{
					//get_ the pixel offsets
					int pixel_x = (cell_width * c) + pixel_col;
					int pixel_y = (cell_height * r) + pixel_row;

					//If a non colorkey pixel is found
					if(getPixel32(pixel_x, pixel_y, file) != bg_color)
					{
						//Bottom of a is found
						base = pixel_row;

						//Break the loops
						pixel_col = cell_width;
						pixel_row = -1;
					}
				}
			}

			current_frame++;
		}
	}

	// get rid of excess top and bottom bits (transparent)
	for (int t = 0; t < rows*cols; t++)
	{
		frames[t].y += top;
		frames[t].h -= top;
	}

	Rect offset;
	offset.x = 0;
	offset.y = 0;

	for (int i = 0; i < rows*cols; i++)
	{
		// create temporary surface with no transparency setttings (first parameter)
		Surface *surf = SDL_CreateRGBSurface(0,frames[i].w,frames[i].h,32,
		                                     0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		// yes, all the later Uint32 parameters are necessary :(

		// blit picture with correct clipping to new surface
		SDL_BlitSurface((file), &frames[i], (surf), &offset);
		// offset necessary? XXX

		// store the temporary surface in the permanent location in the list
		img_list[cell + i] = surf;
		// nullify the pointer (don't do a FreeSurface)
		surf = NULL;
	}
}
