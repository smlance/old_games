#include "main.h"

Font::Font() 	{ }
Font::~Font()
{
	SDL_FreeSurface(font);
}

// have it put together string? or pass constructed string to it?
// also, have it return a surface?
void Font::dispText(int x, int y, sstring txt)
{
	// surface letters and numbers are applied to
	//Surface *txt_surface;
	//txt_surface->w = 400;
	//txt_surface->h = 400;

	//Temp offsets
	int X = x, Y = y;
	//If the font has been built
	if(font != NULL)
	{
		//Go through the text
		for(int show = 0; txt[show] != '\0'; show++)
		{
			//If the current character is a space
			if(txt[show] == ' ')
			{
				//Move over
				X += space;
			}
			//If the current character is a newline
			else if(txt[show] == '\n')
			{
				//Move down
				Y += new_line;
				//Move back
				X = x;
			}
			else
			{
				//get the ASCII value of the character
				int ascii = (unsigned char)txt[show];
				display.applySurface(X, Y, font, &chars[ascii]/*, txt_surface*/);
				//Move over the width of the character with one pixel of padding
				X += chars[ascii].w + 1;
			}
		}
	}
	//display.applySurface(X, Y, txt_surface, NULL);

}

void Font::loadFont(sstring font_file)
{
	font = display.loadImg(font_file);

	//Set the background color
	Uint32 bg_color = SDL_MapRGB(font->format, 0xFF, 0, 0xFF );

	//Set the cell dimensions
	int cell_width = SQ_TXT_SIDE;
	int cell_height = SQ_TXT_SIDE;
	int n_rows = font->h / SQ_TXT_SIDE;
	int n_cols = font->w / SQ_TXT_SIDE;
	chars.resize(n_rows*n_cols);

	//New line variables
	int top = cell_height;
	int base_a = cell_height;

	//The current character we're setting
	int current_char = 0;

	//Go through the cell rows
	for(int rows = 0; rows < n_rows; rows++)
	{
		//Go through the cell columns
		for(int cols = 0; cols < n_cols; cols++)
		{
			//Set the character offset
			chars[current_char].x = cell_width * cols;
			chars[current_char].y = cell_height * rows;

			//Set the dimensions of the character
			chars[current_char].w = cell_width;
			chars[current_char].h = cell_height;

			//Find Left Side
			//Go through pixel columns
			for(int pixel_col = 0; pixel_col < cell_width; pixel_col++)
			{
				//Go through pixel rows
				for(int pixel_row = 0; pixel_row < cell_height; pixel_row++)
				{
					//get_ the pixel offsets
					int pixel_x = (cell_width * cols) + pixel_col;
					int pixel_y = (cell_height * rows) + pixel_row;

					//If a non colorkey pixel is found
					if(display.getPixel32(pixel_x, pixel_y, font) != bg_color)
					{
						//Set the x offset
						chars[current_char].x = pixel_x;

						//Break the loops
						pixel_col = cell_width;
						pixel_row = cell_height;
					}
				}
			}

			//Find Right Side
			//Go through pixel columns
			for(int pixel_col_w = cell_width - 1; pixel_col_w >= 0; pixel_col_w--)
			{
				//Go through pixel rows
				for(int pixel_row_w = 0; pixel_row_w < cell_height; pixel_row_w++)
				{
					//get_ the pixel offsets
					int pixel_x = (cell_width * cols) + pixel_col_w;
					int pixel_y = (cell_height * rows) + pixel_row_w;

					//If a non colorkey pixel is found
					if(display.getPixel32(pixel_x, pixel_y, font) != bg_color)
					{
						//Set the width
						chars[current_char].w = (pixel_x - chars[current_char].x) + 1;

						//Break the loops
						pixel_col_w = -1;
						pixel_row_w = cell_height;
					}
				}
			}

			//Find Top
			//Go through pixel rows
			for(int pixel_row = 0; pixel_row < cell_height; pixel_row++)
			{
				//Go through pixel columns
				for(int pixel_col = 0; pixel_col < cell_width; pixel_col++)
				{
					//get_ the pixel offsets
					int pixel_x = (cell_width * cols) + pixel_col;
					int pixel_y = (cell_height * rows) + pixel_row;

					//If a non colorkey pixel is found
					if(display.getPixel32(pixel_x, pixel_y, font) != bg_color)
					{
						//If new top is found
						if(pixel_row < top)
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
			if(current_char == 'A')
			{
				//Go through pixel rows
				for(int pixel_row = cell_height - 1; pixel_row >= 0; pixel_row--)
				{
					//Go through pixel columns
					for(int pixel_col = 0; pixel_col < cell_width; pixel_col++)
					{
						//get_ the pixel offsets
						int pixel_x = (cell_width * cols) + pixel_col;
						int pixel_y = (cell_height * rows) + pixel_row;

						//If a non colorkey pixel is found
						if(display.getPixel32(pixel_x, pixel_y, font) != bg_color)
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
	for(int t = 0; t < n_rows*n_cols; t++)
	{
		chars[t].y += top;
		chars[t].h -= top;
	}
}
