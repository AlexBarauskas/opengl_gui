#include <stdio.h>
#include <stdlib.h>
#include "gui.h"

TextInput::TextInput()
{
  this->x = 10;
  this->y = 10;
  this->w = 100;
  this->h = 20;
  this->background_color = new short int(3);
  this->border_color = new short int(3);
  this->color = new short int(3);
  this->padding = new short int(4);
  for(int i=0; i<3; i++)
    {
      this->background_color[i]=200;
      this->border_color[i]=50;
      this->color[i]=0;
    }
  this->padding[0] = 2; //левая граница
  this->padding[1] = 0; //верх
  this->padding[2] = 2; //право
  this->padding[3] = 2; //низ


  this->border_color[1]=255;
  this->color[1]=255;
  this->border_width = 2;
  this->focus = false;
  this->cursor_position = 0;
}

int TextInput::inner_height()
{
  return this->h + this->padding[1] + this->padding[3] + 2*this->border_width;
}

int TextInput::inner_width()
{
  return this->w + this->padding[0] + this->padding[2] + 2*this->border_width;
}


void TextInput::show(){

  
  //glMatrixMode(GL_PROJECTION);	
  //glLoadIdentity();				

  glColor3ub(this->border_color[0], this->border_color[1], this->border_color[2]);
  //glColor3f(0,1,1);
  glLineWidth(this->border_width);
  glBegin(GL_LINE_LOOP);
  glVertex2i(this->x, this->y);
  glVertex2i(this->x + this->inner_width(), this->y);
  glVertex2i(this->x + this->inner_width(), this->y+this->inner_height());
  glVertex2i(this->x, this->y+this->inner_height());
  glEnd();
  /*
  glViewport(this->x, this->y, this->x + this->inner_width(), this->y + this->inner_height());
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(this->x, this->x + this->inner_width(), this->y, this->y + this->inner_height());
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  */
  glColor3ub(this->color[0], this->color[1], this->color[2]);
  //glRasterPos2f(this->x + this->padding[0], this->y + this->padding[3]);
  glRasterPos2f(this->x + this->padding[0] + this->border_width, this->y + this->padding[3] + this->border_width);
  short int dx=0;
  for (int i=0; i <= this->value.size(); i++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->value[i]);
      dx += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, this->value[i]);
      if(i+1 == this->cursor_position && this->focus){
	glColor3ub(this->color[0]/2, this->color[1]/2, this->color[2]/2);
	glBegin(GL_LINES);
	glVertex2i(this->x + dx + 1 + this->padding[0] + this->border_width, this->y + this->padding[3] + this->border_width);
	glVertex2i(this->x + dx + 1 + this->padding[0] + this->border_width, this->y + 18 + this->padding[3] + this->border_width);

	glEnd();
      }
    }
  if(!this->value.size() &&  this->focus)
    {
      glColor3ub(this->color[0]/2, this->color[1]/2, this->color[2]/2);
      glBegin(GL_LINES);
	glVertex2i(this->x + 1 + this->padding[0] + this->border_width, this->y + this->padding[3] + this->border_width);
	glVertex2i(this->x + 1 + this->padding[0] + this->border_width, this->y + 18 + this->padding[3] + this->border_width);
      glEnd();
    }
}

void TextInput::mouse(int button, int state, int x, int y)
{
  if(x>this->x && x<this->x+this->w && y>this->y && y<this->y+this->h)
    {
      this->focus = true;
    }
  else
    {
      this->focus = false;      
    }
}

void TextInput::keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
  if(this->focus)
    {
      if(key>='0' && key<='9' || key>='a' && key<='z' || key>='A' && key<='Z')
	{
	  this->value.insert(this->cursor_position,1, key);
	  this->cursor_position++;
	}
      else if(key==8){
	if(this->value.size())
	  {
	  if(this->cursor_position)
	    { 
	      this->value.erase(this->cursor_position-1,1);
	      this->cursor_position--;
	    }
	  }
      }
    }
  
}

void TextInput::keyspecial(int key, int mousePositionX, int mousePositionY){
  if(this->focus)
    {
      if(key == 100 && this->cursor_position>0)
	{
	  this->cursor_position--;	    
	}
      else if(key == 102 && this->cursor_position < this->value.size()){
	this->cursor_position++;
      }
    }
  printf("%i %i %i %i\n", key, mousePositionX, mousePositionY, this->focus);
}

TextInput::~TextInput()
{
  delete [] this->border_color;
  delete [] this->background_color;
}

