#include "shape.h"
#include "shape_editor_resource.h"

class MyEditor {
private:
	MyEditor() {};
	MyEditor(const MyEditor&);
public:
	int x1, y1, x2, y2;
	static MyEditor& getInstance() { 
		static MyEditor instance; 
		return instance; 
	}
	~MyEditor();
	void Start(Shape *);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
	std::string GetString();
};

extern Shape** pcshape;
extern int c;
