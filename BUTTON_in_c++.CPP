#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
class Demo{
    public:
	void sayHi(){
	   cout<<"\nHi";	
	}
	void sayHello(){
	   cout<<"\nHello";	
	}
};
class Button{
    private:
      int counter;
    public:
      Button(){
	 counter=0;
      }
      void reset(){
	   counter=0;
      }
      void Property(char [], int, int, int, int, int, int, int, int, int, int, int);
      void Fbutton(Demo *st,void (*)(Demo *) ,char [], int, int, int, int, int, int, int, int, int, int, int);
      void Nbutton(void (*)(int) ,char [], int, int, int, int, int, int, int, int, int, int, int);
      int getXY(int *, int *);

};
void Button::Property(char text[], int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize)
{
     int textX=x+(((x+length)-x)/4);
     int textY=y+(((y+breath)-y)/4);
     setcolor(border);
     rectangle(x, y, (length+x), (breath+y));
     setfillstyle(fillStyle,fillInside);
     floodfill(length/2+x, breath/2+y,border);
     settextstyle(font,direction,fontSize);
     setcolor(fontColor);
     outtextxy(textX,textY,text);
}
void Button::Fbutton(Demo *st,void (*func)(Demo *),char text[], int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize)
{
    int mouseX,mouseY;
    if(counter==0)
    {
	 Property(text,x,y,length,breath,border,fillInside,fillStyle,fontColor,font,direction,fontSize);
	 counter++;
    }
    if(getXY(&mouseX, &mouseY)==1)
    {
	  if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) )
	  {
		 setcolor(border-1);
		 rectangle(x,y,(x+length),(y+breath));
		 delay(50);
		 setcolor(border);
		 rectangle(x,y,(x+length),(y+breath));
		 delay(60);
		 (*func)(st);
	  }
    }
}
void Button::Nbutton(void (*func)(int ),char text[], int x, int y, int length, int breath, int border,int fillInside, int fillStyle, int fontColor, int font, int direction, int fontSize)
{
    int mouseX,mouseY;
    if(counter==0)
    {
	 Property(text,x,y,length,breath,border,fillInside,fillStyle,fontColor,font,direction,fontSize);
	 counter++;
    }
    if(getXY(&mouseX, &mouseY)==1)
    {
	  if(mouseX >= x && mouseX <= (x+length) && mouseY >= y && mouseY <= (y+breath) )
	  {
		 setcolor(border-1);
		 rectangle(x,y,(x+length),(y+breath));
		 delay(50);
		 setcolor(border);
		 rectangle(x,y,(x+length),(y+breath));
		 delay(60);
		 (*func)(0);
	  }
    }
}
int Button::getXY(int *x,int *y)
{
     union REGS i,o;
     i.x.ax=1;
     int86(0x33,&i,&o);
     i.x.ax=3;
     int86(0x33,&i,&o);
     *x=o.x.cx;
     *y=o.x.dx;
     return o.x.bx;
}
void sayHi(Demo *a){
     a->sayHi();
}
void sayHello(Demo *a){
     a->sayHello();
}
void main()
{
     Button b[2];
     Demo d;
     int gd=DETECT,gm;
     clrscr();
     initgraph(&gd,&gm,"C:\\TC\\BGI");
     while(!kbhit()){
	b[0].Fbutton(&d,&sayHi,"Perss Me", 270, 100, 100, 35, 15, 12, 1, 6, 2, 0, 4);
	b[1].Fbutton(&d,&sayHello,"Press Me", 400, 100, 100, 35, 15, 12, 1, 6, 2, 0, 4);
    }
     getch();
}
