#include "main.h"
//#include "glcontroller.cpp"
#include "gui.h"

GLController *controller;

int main(int argc, char* argv[])
{
  /*Base information by run application*/
  printf("Run application %s\n",argv[0]);
  if(argc>1)
    {
      printf("Number arguments: %i\n",argc-1);
      for(int i=1;i<argc;i++)
	{
	  printf("%s\n",argv[i]);
	}
    }

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  controller = new GLController(400, 400, 2);

  TextInput * ti1, * ti2;
  ti1 = new TextInput();
  ti2 = new TextInput();
  ti1->set_position(100,100);
  ti2->set_position(100,300);
  controller->add_obj(ti1);
  controller->add_obj(ti2);  

  glutDisplayFunc( display );
  glutKeyboardFunc( keyboard );
  //glutIdleFunc( display );
  glutReshapeFunc( resize );
  glutMouseFunc( mouse );
  glutMotionFunc( motion );
  glutSpecialFunc(keySpecial);
  controller->init();


  glutMainLoop();

}

void display()
{
  if(controller)
    {controller->display();}
}

void keyboard ( unsigned char b, int x, int y)
{
  if(controller)
    {controller->keyboard(b,x,y);}
}

void resize(int w, int h)
{
  if(controller)
    {controller->resize(w,h);}
}

void mouse(int b, int s, int x, int y)
{
  if(controller)
    {controller->mouse(b, s, x, y);}
}

void motion(int x, int y)
{
  if(controller)
    {controller->motion(x,y);}
}


void keySpecial (int key, int x, int y) 
{  
  if(controller)
    {controller->keyspecial(key,x,y);}
}  
