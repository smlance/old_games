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
	void	initFonts();
	void 	loadGfx();
	void 	refresh();
	void	render();
	Uint32 	getPixel32(int, int, Surface *);
	// overload apply function for defaulting to window
	void 	applySurface(int, int, Surface *, Rect *);
	void 	applySurface(int, int, Surface *, Rect *, Surface *);
	Surface *loadImg(sstring);
	void	updateCam(int, int);
	sstring	concatenateString(int, ...);
	const char *intToConstChar(int);
	//template <typename Head, typename... Tail>
	//static void concatenateString(std::ostream&);
	
	//static void concatenateString(std::ostream&, const Head&, const Tail&...);
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
	void 	loadFont(sstring);
	void 	dispText(int, int, sstring);
};

class Camera
{
private:
	Rect 	viewer;

public:
	Camera();
	~Camera();
	void init();
	void setPos(int, int);
	Rect *getViewer();
};

#endif // DISPLAY_H
