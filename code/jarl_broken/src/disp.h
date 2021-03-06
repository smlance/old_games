#ifndef DISP_H
#define DISP_H

class Display
{
	private:
		Surface *			window;
		svector<Surface *>	img_list;
		svector<Font *>		font_list;

	public:
		Display();
		~Display();
		void 	init();
		void	init_fonts();
		void 	load_gfx();
		void 	refresh();
		void	render();
		Uint32 	get_pixel32(int, int, Surface *);
		// overload apply function for defaulting to window
		void 	apply_surface(int, int, Surface *, Rect *);
		void 	apply_surface(int, int, Surface *, Rect *, Surface *);
		Surface *load_img(sstring);
		void	update_cam(int, int);
};

class Font
{
	private:
		Surface *			font;
		svector <Rect>		chars;
		int 				new_line, space;

	public:
		Font();
		~Font();
		void 	load_font(sstring);
		void 	disp_text(int, int, sstring);
};

class Camera
{
	private:
		Rect 	viewer;

	public:
		Camera();
		~Camera();
		void init();
		void set_pos(int, int);
		Rect *get_viewer();
};

#endif // DISPLAY_H
