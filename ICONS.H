#include <alloc.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include<dos.h>
struct BMP
{
 char Type[2]; //File type. Set to "BM".
unsigned long Size; //Size in BYTES of the file.
unsigned long Reserved; //Reserved. Set to zero.
unsigned long OffSet; //Offset to the data.
unsigned long headsize; //Size of rest of header. Set to 40.
unsigned long Width; //Width of bitmap in pixels.
unsigned long Height; // Height of bitmap in pixels.
unsigned int Planes; //Number of Planes. Set to 1.
unsigned int BitsPerPixel; //Number of Bits per pixels.
unsigned long Compression; //Compression. Usually set to 0.
unsigned long SizeImage; //Size in bytes of the bitmap.
unsigned long XPixelsPreMeter; //Horizontal pixels per meter.
unsigned long YPixelsPreMeter; //Vertical pixels per meter.
unsigned long ColorsUsed; //Number of colors used.
unsigned long ColorsImportant; //Number of "important" colors.
};
int ShowBMP(int x, int y, char* FileName)
{
int b,a;
struct BMP Obj;
unsigned char* Datas;
int in=0;
unsigned char c=0;
FILE * fp;
fp = fopen(FileName,"rb");
x=1; y=1;
if(!fp)
 {
 printf("Error : Unable to open file ..");

 }
 fread(&Obj, sizeof(Obj), 1, fp);
 if(Obj.BitsPerPixel!=4) // This isn't a 16 color bmp we can read;
 {
  fclose(fp);
  printf("Error : File format not supported ..");

 };
  fseek(fp,Obj.OffSet,SEEK_SET);
  Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
  for(b=Obj.Height;b>=0;b--)
   {
   fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
   c=0; in=0;
   for(a=0;a<=Obj.Width;a+=2)
   {
    c = (Datas[in] | 0x00) >>4;
    putpixel(a+x,b+y,c);
    c = (Datas[in] | 0xF0) & 0x0F;
    putpixel(a+1+x,b+y,c); in++;
   }
  }
 free (Datas);
 fclose(fp);
 return 1;
}

void fillcoloricon(int x,int y,int stat)
{
struct fillsettingstype far *old;getfillsettings(old);
rectangle(x+0,y+0,x+30,y+30);
	if(stat==3)
	{
	setfillstyle(SOLID_FILL,BLUE);

	}
	else
	{
	setfillstyle(SOLID_FILL,BLACK);

	}
bar(x+1,y+1,x+29,y+29);
line(x+13,y+27,x+27,y+22);
line(x+13,y+27,x+8,y+10);
line(x+27,y+22,x+22,y+5);
line(x+22,y+5,x+8,y+10);
setfillstyle(0,0);
sector(x+8,y+10,25,180,5,4);
line(x+3,y+10,x+6,y+25);
line(x+6,y+25,x+8,y+10);
if(stat==3)
setcolor(BLUE);
else
setcolor(0);
line(x+8,y+10,x+1,y+10);
setfillstyle(old->pattern,old->color);
}
void pencilicon(int x,int y,int stat)
{
	struct fillsettingstype far *old;getfillsettings(old);
	setcolor(WHITE);
	rectangle(x+0,y+0,x+30,y+30);
	if(stat==1)
	{
	setfillstyle(SOLID_FILL,BLUE);

	}
	else
	{
	setfillstyle(SOLID_FILL,BLACK);

	}
bar(x+1,y+1,x+29,y+29);
	line(x+8,y+19,x+22,y+5);
	line(x+9,y+20,x+23,y+6);
	line(x+10,y+21,x+24,y+7);
	line(x+11,y+22,x+25,y+8);
	line(x+25,y+8,x+22,y+5);
	line(x+8,y+19,x+11,y+22);
	line(x+8,y+19,x+5.5,y+24.5);
	line(x+5.5,y+24.5,x+11,y+22);
	line(x+22,y+5,x+23,y+4);
	line(x+23,y+4,x+26,y+7);
	line(x+26,y+7,x+25,y+8);
	setfillstyle(old->pattern,old->color);
	//line(70,220,80,240);
}
void brushicon(int x,int y,int stat)
{
	struct fillsettingstype far *old;
	getfillsettings(old);
	setcolor(WHITE);
	rectangle(x+0,y+0,x+30,y+30);
	if(stat==2)
	{
	setfillstyle(SOLID_FILL,BLUE);
	}
	else
	setfillstyle(SOLID_FILL,BLACK);
	bar(x+1,y+1,x+29,y+29);
	//line(x+80,y+190,x+220,y+50);
	line(x+9,y+20,x+23,y+6);
	//line(x+100,y+210,x+240,y+70);
	line(x+11,y+22,x+25,y+8);
	line(x+23,y+6,x+25,y+8);
	line(x+9,y+20,x+11,y+22);

	setfillstyle(SOLID_FILL,15);

	circle(x+8,y+23,3);
	floodfill(x+9,y+22,15);
	setfillstyle(old->pattern,old->color);

}
/*void main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
brushicon(0,0,0);
//ShowBMP(50,50,"BRUSH1.bmp");
getch();
} */
