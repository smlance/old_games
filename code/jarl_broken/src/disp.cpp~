#include "main.h"

Display::Display()
{
	// init SDL, center window, create window
	SDL_Init(SDL_INIT_EVERYTHING);
	putenv( (char*)"SDL_VIDEO_CENTERED=1" );
	window = SDL_SetVideoMode(VIDEO_MODE);
	SDL_WM_SetCaption("jarl", NULL);

	// arbitrary large list size for storing images
	img_list.resize(1000);
	load_gfx();

	// initialize fonts
	font_list.resize(1);
	init_fonts();
}

Display::~Display()
{
	/* XXX Check if the pointers are non-NULL before freeing? XXX */
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

Uint32 Display::get_pixel32(int x, int y, Surface *surface)
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
	SDL_WM_SetCaption("jarl", NULL);

	// arbitrary large list size for storing images
	img_list.resize(1000);
	load_gfx();

	// initialize fonts
	font_list.resize(1);
	init_fonts();
}

void Display::update_cam(int x, int y)
{
	// x and y come in as player coordinates
	int pixel_x = x * TILE_SIDE;
	int pixel_y = y * TILE_SIDE;
	// pan variables are used for centering the player as he moves
	int pan_x = pixel_x - (GAME_WIDTH / 2);
	// add (TILE_SIDE / 2) so that we see full tiles at top and bottom
	// (without it, top and bottom are split in half)
	int pan_y = pixel_y + (TILE_SIDE / 2) - (GAME_HEIGHT / 2);

	 ADJUST THE PAN VALUES
	 * only set the position to the new values if the resulting values are between
	 * 0 and the SCREEN_W/H!
	 * subtract half a SCREEN_WIDTH and HEIGHT from player's positions to obtain
	 * the coordinates of the cam.
	 *
	if (pan_x < 0)
		pan_x = 0;
		
	if (pan_x >= GAME_WIDTH)
		pan_x = pixel_x - abs(pixel_x - GAME_WIDTH) - TILE_SIDE;
		
	if (pan_y < 0)
		pan_y = 0;
		
	if (pan_y >= GAME_HEIGHT)
		pan_y = pixel_y - abs(pixel_y - GAME_HEIGHT) - TILE_SIDE;

	// finally, set the camera position
	camera.set_pos(pan_x, pan_y);
}

void Display::init_fonts()
{
	font_list[0] = new Font;
	font_list[0]->load_font(TXT_PATH);
}

void Display::apply_surface(int x, int y, Surface *source, Rect *clip)
{
	// by default (if destination not given), draw to window
	apply_surface(x, y, source, clip, window);
}

void Display::apply_surface(int x, int y, Surface *source, Rect *clip,
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

void Display::render()
{
	// update the camera position so we know what to draw
	update_cam(game.get_ent(0)->get_x(), game.get_ent(0)->get_y());
	int cam_x = camera.get_viewer()->x;
	int cam_y = camera.get_viewer()->y;
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
			int id_orig = game.get_area()->get_tile(i, j)->get_id();
			apply_surface(i*TILE_SIDE - cam_x, j*TILE_SIDE - cam_y,
				img_list[id_orig], NULL);
			
			// check for any other entities that need to be printed on top of this cell
			for (unsigned int k = 0;
				k < game.get_area()->get_tile(i, j)->get_ent_list_size();
				k++)
			{
				// if they exist
				if (game.get_area()->get_tile(i, j)->get_ent(k))
				{
					// grab their ids, print them (then go up and do checks for as large
					// as the list is; i.e., continue)
					int id = game.get_area()->get_tile(i, j)->get_ent(k)->get_id();
			
					apply_surface(i*TILE_SIDE - cam_x, j*TILE_SIDE - cam_y,
			    		img_list[id], NULL);
			    }
			}
		}
	}

	// render entities
	// only draw entities within bounds!
	for (unsigned int i = 0; i < game.get_ent_list_size(); i++)
	{
		if (game.get_ent(i))
		{
			int x_ = game.get_ent(i)->get_x();
			int y_ = game.get_ent(i)->get_y();
			int id_ = game.get_ent(i)->get_id();
			// if the coordinates of the entity fit within our cam boundaries
			if (x_ >= game_x && x_ < game_x + TILE_COLS
			&& y_ >= game_y && y_ < game_y + TILE_ROWS)
			{
				// display it
				apply_surface(x_*TILE_SIDE - cam_x, y_*TILE_SIDE - cam_y,
			              	img_list[id_], NULL);
			}
		}
	}

	// render texts
	sstring text = "Welcome. ;)";
	font_list[0]->disp_text(GAME_WIDTH, 0, text);
}

Surface *Display::load_img(sstring path)
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

void Display::load_gfx()
{
	// initialize list
	for (unsigned int i = 0; i < img_list.size(); i++)
	{
		img_list[i] = NULL;
	}

	// load sprite sheet into a surface
	Surface *file = load_img(GFX_PATH);
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
					if(get_pixel32(pixel_x, pixel_y, file) != bg_color)
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

					if(get_pixel32(pixel_x, pixel_y, file) != bg_color)
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
					if(get_pixel32(pixel_x, pixel_y, file) != bg_color)
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
					if(get_pixel32(pixel_x, pixel_y, file) != bg_color)
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
