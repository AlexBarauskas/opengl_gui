#include "glcontroller.h"

Observer::Observer(int  dimension)
{
  this->d = dimension;
  this->x = new float(dimension);
  this->v = new float(dimension);
  this->z = new float(dimension);
  for(int i=0;i<dimension;i++)
    {
      this->x[i]=this->v[i]=this->z[i]=0;
    }
  this->type = 1;
  if(this->d==3)
    this->z[3]=1;
}

Observer::~Observer()
{
  delete [] this->x;
  delete [] this->v;
  delete [] this->z;
}

void Observer::set_type(short int type)
{
  this->type = type;
}

void Observer::set_x(float *x)
{
  for(int i=0;i<this->d;i++)
    {
      this->x[i]=x[i];
    }  
}

void Observer::set_v(float *v)
{
  for(int i=0;i<this->d;i++)
    {
      this->v[i]=v[i];
    }  
}

void Observer::set_z(float *z)
{
  for(int i=0;i<this->d;i++)
    {
      this->z[i]=z[i];
    }  
}

int Observer::set_look_at()
{
  if(this->d != 3)
    {
      return 0;
    }
  if(this->type == 0)
    {
      gluLookAt(x[0],x[1],x[2], v[0],v[1],v[2], z[0],z[1],z[2]);
    }
  else if(this->type == 0)
    {
      float x1,x2,x3;
      x1 = x[2] * sin(x[1])*(sin(x[0])+cos(x[0]));
      x2 = x[2] * sin(x[1])*(sin(x[0])-cos(x[0]));
      x3 = x[2] * cos(x[1]);
      gluLookAt(x1,x2,x3, v[0],v[1],v[2], z[0],z[1],z[2]);
    }
  return 1;
}



GLController::GLController(int w,int h, short int d)
{
  this->width = w;
  this->height = h;
  this->d=d;
  this->observer = new Observer(d);
  if(this->d == 3)
    {
      float *x=new float(3);
      x[0] = 3.14/4.0;
      x[1] = 3.14/4.0;
      x[2] = 6;
      this->observer->set_x(x);
      this->mevent.button = -1;
    }
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowSize(this->width, this->height);
  glutCreateWindow("GL_Controller");
  
}

void GLController::init()
{
  //glMatrixMode(GL_PROJECTION);						
  //glViewport(0, 0, this->width, this->height);
  //glMatrixMode(GL_PROJECTION);	
  //glLoadIdentity();				

  if(this->d == 3)
    {
      GLfloat aspect = (GLfloat) this->width / this->height;
      gluPerspective(45, aspect, 1.0f, 500.0f);
      glMatrixMode(GL_MODELVIEW);		
      glShadeModel( GL_SMOOTH );
      glClearDepth( 1.0f );			
      glEnable( GL_DEPTH_TEST );
      glDepthFunc( GL_LEQUAL );
      glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

      GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
      GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
      GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
      glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
      glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
      glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
      glEnable( GL_LIGHT0 );
      glEnable( GL_COLOR_MATERIAL );
      glShadeModel( GL_SMOOTH );
      glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
      glDepthFunc( GL_LEQUAL );
      glEnable( GL_DEPTH_TEST );
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0); 
    }
  if(this->d == 2){
    glEnable( GL_LINE_SMOOTH );
    //glMatrixMode (GL_PROJECTION);
    //glLoadIdentity ();
    glViewport(0, 0, this->width, this->height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, this->width, 0, this->height);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
  }
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

GLController::~GLController()
{}

void GLController::keyboard ( unsigned char key, int mousePositionX, int mousePositionY )
{ 
  for (int i = 0; i!=this->graphicsObjects.size(); ++i)
    {
      this->graphicsObjects[i]->keyboard(key, mousePositionX, mousePositionY);
    }

  switch ( key ) 
    {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;      
    default:      
      break;
    }
  
  this->display();
}

void GLController::keyspecial (int key, int mousePositionX, int mousePositionY )
{ 
  for (int i = 0; i!=this->graphicsObjects.size(); ++i)
    {
      this->graphicsObjects[i]->keyspecial(key, mousePositionX, mousePositionY);
    }
  this->display();
}

void GLController::resize(int w, int h)
{
  this->width=w;
  this->height=h;
  this->init();
}

void GLController::mouse(int button, int state, int x, int y)
{
  //printf("button:%i; state:%i; x:%i; y:%i\n", button, state, x, y);
  mevent.button = button;
  mevent.state = state;
  mevent.x = x;
  mevent.y = y;
  for (int i = 0; i!=this->graphicsObjects.size(); ++i)
    {
      this->graphicsObjects[i]->mouse(button, state, x, this->height-y);
    }
  this->display();
}

void GLController::display()
{
    glViewport(0, 0, this->width, this->height);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    gluOrtho2D(0, this->width, 0, this->height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
  //glLoadIdentity();
  this->observer->set_look_at();

  for (int i = 0; i!=this->graphicsObjects.size(); ++i)
    {
      this->graphicsObjects[i]->show();
    }

  glutSwapBuffers();
}

void GLController::motion(int y, int x)
{}

void GLController::add_obj(GraphicsObj* obj){
  this->graphicsObjects.push_back(obj);
}
