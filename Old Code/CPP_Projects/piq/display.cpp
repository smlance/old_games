#include "main.h"

Display::Display() {

}



void Display::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	putenv((char*)"SDL_VIDEO_CENTERED=1"); // ?
	
	if (FULLSCREEN) {
	display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_FULLSCREEN | 
	SDL_SWSURFACE | SDL_DOUBLEBUF);
	} else {
	display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	}
	
	SDL_WM_SetCaption("ninto", NULL);
	
	image_list_size = 1000;
	image_list.resize(image_list_size);
	load_all_images();
	
	init_font();
	
	view = new Camera;
}



Display::~Display() {
	SDL_FreeSurface(display);
	display = NULL;
	
	for (int i = 0; i < image_list_size; i++) {
		if (image_list[i]) {
			SDL_FreeSurface(image_list[i]);
			image_list[i] = NULL;
		}
	}
	
	delete font;
	font = NULL;
	
	delete view;
	view = NULL;
	
	SDL_Quit();
	
	std::cout << "Display deleted successfully!" << std::endl;
}



void Display::init_font() {
	font = new Font();
	
	font->set_display(this);
	
	font->build_font(image_list[999]);
}



void Display::refresh() {	// updates happen. display is flipped once at end of each frame.
	SDL_Flip(display);
}



SDL_Surface *Display::load_image(std::string filename)
{
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	loaded_image = IMG_Load(filename.c_str());
	
	if (loaded_image)
	{
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);
		
		if (optimized_image)
		{
			SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB
				(optimized_image->format, 0, 0xFF, 0xFF));
		}
	}
	
	return optimized_image;
}



void Display::apply_surface(int x, int y, SDL_Surface *source, SDL_Rect *clp)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clp, display, &offset);
}



SDL_Surface *Display::load_image_from_ID(int ID, int state_ID) {
	if (ID == -1) 		return image_list[10];		// bg space
	else if (ID == 1) 	return image_list[1];		// player
	else if (ID == 101)	return image_list[101];
	else if (ID == 102)	return image_list[102];
	else if (ID == 0)	return image_list[0];
	else 				return image_list[ID + state_ID];
	
	return NULL;
}



void Display::load_all_images() {
	for (int i = 0; i < image_list_size; i++) {
		image_list[i] = NULL;
	}

	//assert(image_list[300]);
	image_list[0]	=	load_image("./gfx/mk01.png"); // temp bg
	image_list[1] 	= 	load_image("./gfx/player.png");
	image_list[10] 	= 	load_image("./gfx/16x16_bg.png");
	image_list[101]	= 	load_image("./gfx/tile.png");
	image_list[102]	=	load_image("./gfx/light_tile.png");
	image_list[999]	=	load_image("./gfx/font002_black.png");
	
	load_image_sheet(300, 1, 3/*, (char*)filename*/);
}



void Display::load_image_sheet(int cell, int rows, int cols) {
	SDL_Rect 	frames[rows*cols];
	SDL_Surface frame_surf[rows*cols];
	SDL_Surface *file = (load_image("./gfx/idleanimation.png"));
	Uint32 bg_color = SDL_MapRGB((file)->format, 0, 0xFF, 0xFF);
	
	int cell_width = file->w / cols;
	int cell_height = file->h / rows;
	
	int top = cell_height;
	int base = cell_height;
	
	int current_frame = 0;
	
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			frames[current_frame].x = cell_width * c;
			frames[current_frame].y = cell_height * r;
			
			frames[current_frame].w = cell_width;
			frames[current_frame].h = cell_height;
			
	     	for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
            {
                for( int pixel_row = 0; pixel_row < cell_height; pixel_row++ )
                {
                    int pixel_x = ( cell_width * c ) + pixel_col;
                    int pixel_y = ( cell_height * r ) + pixel_row;

                    //If a non colorkey pixel is found
                    if( get_pixel32( pixel_x, pixel_y, file ) != bg_color )
                    {
                        //Set the x offset
                        frames[ current_frame ].x = pixel_x;

                        //Break the loops
                        pixel_col = cell_width;
                        pixel_row = cell_height;
                    }
                }
            }
			
			for( int pixel_col_w = cell_width - 1; pixel_col_w >= 0; pixel_col_w-- )
            {
                for( int pixel_row_w = 0; pixel_row_w < cell_height; pixel_row_w++ )
                {
                    int pixel_x = ( cell_width * c ) + pixel_col_w;
                    int pixel_y = ( cell_height * r ) + pixel_row_w;

                    if( get_pixel32( pixel_x, pixel_y, file ) != bg_color )
                    {
                        //Set the width
                       frames[current_frame ].w = ( pixel_x - frames[current_frame ].x ) + 1;

                        //Break the loops
                        pixel_col_w = -1;
                        pixel_row_w = cell_height;
                    }
                }
            }
            
            for( int pixel_row = 0; pixel_row < cell_height; pixel_row++ )
            {
                //Go through pixel columns
                for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
                {
                    //get_ the pixel offsets
                    int pixel_x = ( cell_width * c ) + pixel_col;
                    int pixel_y = ( cell_height * r ) + pixel_row;

                    //If a non colorkey pixel is found
                    if( get_pixel32( pixel_x, pixel_y, file ) != bg_color )
                    {
                        //If new top is found
                        if( pixel_row < top )
                        {
                            top = pixel_row; std::cout << top << std::endl;
                            frames[ current_frame ].y += top;
        					frames[ current_frame ].h -= top;
                        }

                        //Break the loops
                        pixel_col = cell_width;
                        pixel_row = cell_height;
                    }
                }
            }
            
         	for( int pixel_row = cell_height - 1; pixel_row >= 0; pixel_row-- )
                {
                    //Go through pixel columns
                    for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
                    {
                        //get_ the pixel offsets
                        int pixel_x = ( cell_width * c ) + pixel_col;
                        int pixel_y = ( cell_height * r ) + pixel_row;

                        //If a non colorkey pixel is found
                        if( get_pixel32( pixel_x, pixel_y, file ) != bg_color )
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
    for( int t = 0; t < rows*cols; t++ )
    {
        frames[ t ].y = top + 1; 	/* this is the fix for the weird collison crap. maybe to avoid
        							 * this, remake the sprite file with different height/trans.
        							 * buffers?
        							 */
        frames[ t ].h -= top;
    }
	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	
	for (int i = 0; i < rows*cols; i++) {
		// create temporary surface with no transparency setttings (first parameter)
		SDL_Surface *surf = SDL_CreateRGBSurface(0,frames[i].w,frames[i].h,32,
		0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000); // XXX FIND OUT ABOUT ORDER
		//Uint32(0x000000ff), Uint32(0x0000ff00),Uint32(0x00ff0000), Uint32(0xff000000));
		// yes, all the later Uint32 parameters are necessary :(
		
		// blit picture with correct clipping to new surface
		SDL_BlitSurface((file), &frames[i], (surf), &offset); // might as well nullify offset
		
		// store the temporary surface in the permanent location in the list
		image_list[cell + i] = surf;
		
		// nullify the pointer (freeing it also frees image_list[]
		//SDL_FreeSurface(surf);
		surf = NULL;
		//assert(image_list[cell + i]);
	}
	
	
}



void Display::apply_text(int x, int y, std::string text) {
	font->show_text(x, y, text);
}



Camera *Display::get_cam() {
	return view;
}



Camera::Camera() {
	viewer.x = 0;
	viewer.y = 0;
	viewer.w = SCREEN_WIDTH;
	viewer.h = SCREEN_HEIGHT;
}



Camera::~Camera() {
	
}



SDL_Rect *Camera::get_viewer() {
	return &viewer;
}



Font::Font()
{
    //initialize variables
    font_file = NULL;
    new_line = 0;
    space = 0;
}

Font::~Font() {

}

Font::Font( SDL_Surface *surface, Display *display_in )
{
    //Build the font
    build_font( surface );
    display_in = display;
}

void Font::build_font( SDL_Surface *surface )
{
	font_file = surface;
    //If surface is NULL
    if( surface == NULL )
    {
        return;
    }

    //Set the background color
    Uint32 bg_color = SDL_MapRGB( font_file->format, 0, 0xFF, 0xFF  );

    //Set the cell dimensions
    int cell_width = font_file->w / 26;	// for each letter (but this won't work because not evenly spaced)
    int cell_height = font_file->h / 1;	// only one row

    //New line variables
    int top = cell_height;
    int base_a = cell_height;

    //The current character we're setting
    int current_char = 0;

    //Go through the cell rows
    for( int rows = 0; rows < 1; rows++ )
    {
        //Go through the cell columns
        for( int cols = 0; cols < 26; cols++ )
        {
            //Set the character offset
            chars[ current_char ].x = cell_width * cols;
            chars[ current_char ].y = cell_height * rows;

            //Set the dimensions of the character
            chars[ current_char ].w = cell_width;
            chars[ current_char ].h = cell_height;

            //Find Left Side
            //Go through pixel columns
            for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
            {
                //Go through pixel rows
                for( int pixel_row = 0; pixel_row < cell_height; pixel_row++ )
                {
                    //get_ the pixel offsets
                    int pixel_x = ( cell_width * cols ) + pixel_col;
                    int pixel_y = ( cell_height * rows ) + pixel_row;

                    //If a non colorkey pixel is found
                    if( get_pixel32( pixel_x, pixel_y, font_file ) != bg_color )
                    {
                        //Set the x offset
                        chars[ current_char ].x = pixel_x;

                        //Break the loops
                        pixel_col = cell_width;
                        pixel_row = cell_height;
                    }
                }
            }

            //Find Right Side
            //Go through pixel columns
            for( int pixel_col_w = cell_width - 1; pixel_col_w >= 0; pixel_col_w-- )
            {
                //Go through pixel rows
                for( int pixel_row_w = 0; pixel_row_w < cell_height; pixel_row_w++ )
                {
                    //get_ the pixel offsets
                    int pixel_x = ( cell_width * cols ) + pixel_col_w;
                    int pixel_y = ( cell_height * rows ) + pixel_row_w;

                    //If a non colorkey pixel is found
                    if( get_pixel32( pixel_x, pixel_y, font_file ) != bg_color )
                    {
                        //Set the width
                        chars[ current_char ].w = ( pixel_x - chars[ current_char ].x ) + 1;

                        //Break the loops
                        pixel_col_w = -1;
                        pixel_row_w = cell_height;
                    }
                }
            }

            //Find Top
            //Go through pixel rows
            for( int pixel_row = 0; pixel_row < cell_height; pixel_row++ )
            {
                //Go through pixel columns
                for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
                {
                    //get_ the pixel offsets
                    int pixel_x = ( cell_width * cols ) + pixel_col;
                    int pixel_y = ( cell_height * rows ) + pixel_row;

                    //If a non colorkey pixel is found
                    if( get_pixel32( pixel_x, pixel_y, font_file ) != bg_color )
                    {
                        //If new top is found
                        if( pixel_row < top )
                        {
                            top = pixel_row;
                        }

                        //Break the loops
                        pixel_col = cell_width;
                        pixel_row = cell_height;
                    }
                }
            }

            //Find Bottom of A
            if( current_char == 'A' )
            {
                //Go through pixel rows
                for( int pixel_row = cell_height - 1; pixel_row >= 0; pixel_row-- )
                {
                    //Go through pixel columns
                    for( int pixel_col = 0; pixel_col < cell_width; pixel_col++ )
                    {
                        //get_ the pixel offsets
                        int pixel_x = ( cell_width * cols ) + pixel_col;
                        int pixel_y = ( cell_height * rows ) + pixel_row;

                        //If a non colorkey pixel is found
                        if( get_pixel32( pixel_x, pixel_y, font_file ) != bg_color )
                        {
                            //Bottom of a is found
                            base_a = pixel_row;

                            //Break the loops
                            pixel_col = cell_width;
                            pixel_row = -1;
                        }
                    }
                }
            }

            //Go to the next character
            current_char++;
        }
    }

    //Calculate space
    space = cell_width / 2;

    //Calculate new line
    new_line = base_a - top;

    //Lop off excess top pixels
    for( int t = 0; t < 26; t++ )
    {
        chars[ t ].y += top;
        chars[ t ].h -= top;
    }
}

void Font::set_display(Display *disp) {
	display = disp;
}

void Font::show_text( int x, int y, std::string text)
{
    //Temp offsets
    int X = x, Y = y;

    //If the font has been built
    if( font_file != NULL )
    {
        //Go through the text
        for( int show = 0; text[ show ] != '\0'; show++ )
        {
            //If the current character is a space
            if( text[ show ] == ' ' )
            {
                //Move over
                X += space;
            }
            //If the current character is a newline
            else if( text[ show ] == '\n' )
            {
                //Move down
                Y += new_line;

                //Move back
                X = x;
            }
            else
            {
                //get_ the ASCII value of the character
                int ascii = (unsigned char)text[ show ];
                
                if (ascii < 65) exit(1);	// this would cause a segfault
                else if (ascii > 96 && ascii < 123) ascii -= 32;	// this capitalizes all chars

                //Show the character XXX (for camera) XXX
                display->apply_surface( X, Y, font_file, &chars[ ascii - 65 ] );
                //i.e. make a camera function in the display class XXX

                //Move over the width of the character with one pixel of padding
                X += chars[ ascii - 65 ].w + 1;
                // XXX NOTE: if lowercase chars are used, segfault will occur. XXX
            }
        }
    }
}



int Font::get_pixel_width(std::string text) {
	int width = 0;
	
	for (int ch = 0; text[ch] != '\0'; ch++) {
		if (text[ch] == ' ') {
			width += space;
		} else {
			int ascii = (unsigned char)text[ch];
			
            if (ascii < 65) exit(1);	// this would cause a segfault
            else if (ascii > 96 && ascii < 123) ascii -= 32;	// this capitalizes all chars
            
            width += chars[ascii-65].w + 1; // + 1 = padding
		}
	}
	
	return width;
}



Menu::Menu() {

}



void Menu::initialize(std::string title_in, int num_opts_in, ...) {
	title = title_in;
	
	va_list arguments;
	
	options.resize(num_opts_in);
	
	va_start(arguments, num_opts_in);
	for (int i = 0; i < num_opts_in; i++) {
		options[i] = va_arg(arguments, char*);
	}
	va_end(arguments);
	
	num_opts = num_opts_in;
	
	current_option = 0;
	
}



void Menu::handle_input(SDL_Event event) {
	SDLKey input = event.key.keysym.sym;
	int current_state = game.get_state();
	
	// why is game state stuff handled by the menu? whevs. 
	// main menu functionality
	if (event.type == SDL_KEYDOWN && event.type != SDL_KEYUP) { 	// only do for key presses, not releases
		if (input == SDLK_z) {
			if (current_option == 0) { 	// play
				game.change_state(1);
			}
			else if (current_option == 1) {
				game.change_state(2); 	// editor
			}
			else if (current_option == 2) {
				game.change_state(-1);
				output("test");
			}
			
		}
		else if (input == SDLK_UP) {
			current_option -= 1;
			if (current_option < 0)
				current_option = num_opts - 1;
		}
		else if (input == SDLK_DOWN) {
			current_option += 1;
			if (current_option > num_opts - 1)
				current_option = 0;
		}
	}
	
}



void Menu::show_back() {
	display.apply_surface(0, 0, display.load_image_from_ID(0, 0), NULL);
}



void Menu::print() {
	int x_pos = 16;
	int y_pos = 64 /* + height_of_title */;
	
	display.apply_text(x_pos + 16, y_pos - 48, title);
	
	for (int i = 0; i < num_opts; i++) {
		display.apply_text(x_pos, y_pos, options[i]);
		
		if (i == current_option) {
			display.apply_surface(x_pos + display.get_font()->get_pixel_width(options[i]) + 4, 
			y_pos, 
				display.load_image_from_ID(300, 0), NULL);
		}
		
		y_pos += 16;
	}
}



Font *Display::get_font() {
	return font;
}



Menu::~Menu() {

}
