#ifndef DISPLAY_H
#define DISPLAY_H

class Camera {
	private:
	int 		x, y;
	SDL_Rect 	viewer;
	
	public:
	Camera();
	~Camera();
	
	SDL_Rect *get_viewer();
};



class Display {
	private:
	SDL_Surface *display;
	Font		*font;
	int 		image_list_size;
	std::vector<SDL_Surface *> image_list;
	Camera		*view;
	
	public:
	Display();
	~Display();
	
	void		initialize();
	SDL_Surface *load_image(std::string filename);
	void 		apply_surface(int x, int y, SDL_Surface* source, SDL_Rect* clp);
	void 		refresh();
	SDL_Surface *load_image_from_ID(int ID, int state);
	void 		apply_text(int x, int y, std::string text);
	void		init_font();
	void		load_all_images(); 
	Camera		*get_cam();
	void		load_image_sheet(int, int, int);
	Font		*get_font();
	
	Uint32 	get_pixel32( int x, int y, SDL_Surface *surface ) {
    	Uint32 *pixels = (Uint32 *)surface->pixels;
	    return pixels[ ( y * surface->w ) + x ];
	}
	
};



class Font
{
    private:
    //The font surface
    SDL_Surface *font_file;
    Display 	*display;

    //The individual characters in the surface
    SDL_Rect chars[ 26 ];

    //Spacing Variables
    int new_line, space;

    public:
    //The default constructor
    Font();
    ~Font();
    
    Font(SDL_Surface *surface, Display *display);
    
    void 	set_display(Display *disp); // ?
    void 	build_font( SDL_Surface *surface );
    void 	show_text( int x, int y, std::string text);
	int		get_pixel_width(std::string text);
	
    Uint32 	get_pixel32( int x, int y, SDL_Surface *surface ) {
    	Uint32 *pixels = (Uint32 *)surface->pixels;
	    return pixels[ ( y * surface->w ) + x ];
	}
};



class Menu {
	private:
	std::vector<std::string> options;
	std::string	title;
	int num_opts;
	int current_option;
	
	public:
	Menu();
	~Menu();
	
	void initialize(std::string title_in, int num_opts_in, ...);
	void show_back();
	void print();
	void handle_input(SDL_Event event);
};

#endif
