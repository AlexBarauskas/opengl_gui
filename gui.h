#include "glcontroller.h"
#include <string>

using std::string;
class GUIObj : public GraphicsObj
{
 public:
  virtual void keyboard(unsigned char, int, int) {};
  virtual void keyspecial(int, int, int) {};
  virtual void mouse(int, int, int, int) {};
  virtual void show() {};
};

class TextInput : public GraphicsObj
{
  int x,y; // Позиция верхнего левого угла
  int h,w; // Высота и ширина
  short int * background_color; // цвет фона
  short int * border_color; // цвет границы
  short int * color; // цвет текста
  short int border_width; // ширина границы
  short int * padding; // внутренняя граница

  bool focus; //установлен ли фокус на элемент
  string value;
  short int cursor_position;

  int inner_height();
  int inner_width();

 public:
  TextInput();
  void show();
  void keyboard( unsigned char, int, int);
  void mouse(int, int, int, int);
  void keyspecial(int, int, int);
  ~TextInput();
};


