#ifndef EDITOR_H
#define EDITOR_H

class Editor {
	private:
	Area 	*area;
	int		active_block_ID;
	std::vector <std::string> current_text;
	int 	active_block_x;
	int 	active_block_y;
	
	struct x_y {
		int x;
		std::string x_string;
		int y;
		std::string y_string;
	} size;
	
	public:
	Editor();
	~Editor();
	
	int update();
	x_y prompt_size();
	void init(int, int);
	void show_back();
	void print();
	int read_input();
	
	Area *get_area();
};

#endif
