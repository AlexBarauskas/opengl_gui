/* Заголовочный файл для контроллера основного цикла  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>	
#include <GL/glu.h>

#include <vector>
#include <string>
#include <cstring>
//#define vector<GraphicsObj*> listGraphics;
#define KEY_ESCAPE 27
using std::vector;
using std::string;

// Для последнего сохранения события мыши
typedef struct {
  int button;
  int state;
  int x;
  int y;
} mouseEvent;


class GraphicsObj{
 public:
  //GraphicsObj(){};
  virtual void keyboard(unsigned char, int, int)=0;
  virtual void keyspecial(int, int, int)=0;
  virtual void mouse(int, int, int, int)=0;
  virtual void show()=0;

  //~GraphicsObj(){};
};


// класс Observer отвечает за положение наблюдателя сцены
class Observer
{
  short int d;    // Размерность системы координат
  short int type; // Тип координат положения наблюдателя
                  // 0 - декартовы
                  // 1 - сферические
  float *x;       // Позиция наблюдателя
                  // Для декартовых [x_1, x_2, ...], для сферических [phi, psi, ... , r]
  float *v;       // Точка куда смотрит наблюдатель (фокус еаблюдателя)
  float *z;       // Вертикать наблюдателя

 public:
  Observer(int);
  void set_type(short int);
  void set_x(float*);
  void set_v(float*);
  void set_z(float*);
  int set_look_at();
  ~Observer();
};


class GLController
{
  short int d;    // Размерность системы координат

  int width;      // ширина окна
  int height;     // высота окна
  int aspect;     // отношение сторон окна

  vector<GraphicsObj*> graphicsObjects;
  Observer *observer;
  mouseEvent mevent;


 public:
  GLController(int w,int h, short int d);
  void init();

  void add_obj(GraphicsObj*);
  void resize(int w, int h);
  void keyboard ( unsigned char key, int mousePositionX, int mousePositionY );
  void keyspecial ( int key, int mousePositionX, int mousePositionY );
  void display();
  void mouse(int button, int state, int x, int y);
  void motion(int y, int x);
  
  ~GLController();
};
