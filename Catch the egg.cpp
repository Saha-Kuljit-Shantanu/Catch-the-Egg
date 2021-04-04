# include "iGraphics.h"
# include<windows.h>
#include<mmsystem.h>
#include<math.h>


int read=-1,henx[3]={0,1},tim=200,et=110,et1=10,sec=1000,basket=1,un,te,hu,th,pause=0,mpause=0,iPlay=1,ptimer=0,eggtimer=0,newbx,
    bas_=1,brange=150,icount=0,bastimer=10,eggnum=0,perknum=0,score,atimer=10,ax=1300,ay=200,len=0,ft,lvflag=0;
double bx=670,stx=250,sty=450,heny[3]={495,395},load=40,eggdy=20,eggdx=0,dpy;
double vtx=stx+400,vty=sty-200,dtheta=0,d=0.3;
char s1[2]="0",s2[2]="3",s3[2]="0",s4[2]="0",dur[2],sread[3],ssc[8],spo[4],name[80]="";
char bg[20][40] ={"coverbg.bmp","gamebg.bmp","stick.bmp","lvlpointer.bmp","help 1.bmp","help 2.bmp","help 3.bmp","help 41.bmp","help 5.bmp","help 42.bmp"};
char henpic[3][20] ={"hen.bmp","hen.bmp","hen.bmp"};
char baspic[3][20] ={"basket0.bmp","basket1.bmp","basket2.bmp"};
char eggpic[20][20]={"egg.bmp","egg.bmp","egg.bmp","egg.bmp","egg.bmp","egg.bmp","egg.bmp","egg.bmp","egg.bmp","regg.bmp","regg.bmp","regg.bmp","regg.bmp","regg.bmp","gegg.bmp","poop.bmp","poop.bmp"};
char perks[10][40]={"plus.bmp","minus.bmp","elec.bmp","time.bmp"};
int point[20]={1,1,1,1,1,1,1,1,1,5,5,5,5,5,10,-10,-10};
//bool crowon=true;
//char** q;
typedef struct
{

    int eggx;
    int eggy;
    int view;
    char* epic;
    int eggtype;
    int iscore;
}_egg;
_egg e[100];
typedef struct
{
    int px;
    int py;
    int pnum;
    char* ppic;
    int view;
}_perk;
_perk p;
typedef struct
{
    int sscore;
    char naam[80];
}
savehs;
//savehs sc[12];
/*typedef struct
{
    int k;
}stru ;
stru tlv[3][3];*/
  /*  while(1)
            {
              k++;
              fprintf(fa,"%d ,%d ,%d ,%s",&Tt,&Ll,&sc[i][j][k].sscore,sc[i][j][k].naam);
              if(feof(fa))
                break;
            }
            fclose(fp);*/
            //tlv[i][j].k=2;
           /* for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                if((i ==ft-3) && (j ==atoi(sread)-1))
                {
                    tlv[i][j].k++;
                    sc[i][j][tlv[i][j].k].sscore=score;
                    strcpy(sc[i][j][tlv[i][j].k].naam, name);

                }
            }*/

FILE *fx;
FILE *fa;
FILE *fb;

/// read=-1 is loading page
/// read=0 is menu page
/// read=1 to 3 is game page
/// read=6 is Quit page
/// read=7 is duration page
/// read=8 is level completed page
/// read=9 is level selection page
/// read=10 is score saving prompt
/// read=11 to 15 is help page
/// read=16 is high score selection page
/// read=17 is no resume game viewer
/// read=18 to 26 is highscre viewing page
void sort_score(savehs* a,int n)
{
    int i,j,min_;
    for(j=n-1;j>0;j--)
    {
        min_ =0;
        for(i=0;i<=j-1;i++)
        {
            if(a[min_].sscore>a[i+1].sscore)
                min_ =i+1;
            else if(a[min_].sscore == a[i+1].sscore && stricmp(a[min_].naam,a[i+1].naam)<0)
                min_ =i+1;
            savehs t=a[j];
            a[j]=a[min_];
            a[min_]=t;

        }
    }
}

void reset()
{
    score=0;
    bas_=1;
    brange=150;
    et1=4000;
    ptimer=10;
    memset(name,0,sizeof(name));
    len=0;
    atimer=10;
    eggdx=0;
    henx[0]=0;
    henx[1]=1;
    vtx=stx+400;
    vty=sty-200;
    for(int i=0;i<=100;i++)
    {
        e[i].eggx=-20;
        e[i].eggy=-20;
    }
}
void vtm()
{
   if(pause ==0)
   {
        vtx=650+250*sin(dtheta);
        vty=250+250*(1-cos(dtheta));
        dtheta+=d;
        if(dtheta> 0.8 || dtheta<-0.8)
            d=-d;
   }
}
void peff()
{
      if(p.pnum == 0 && p.px>bx-45 && p.px<bx+brange-15 && p.py>50 && p.py<=120 && p.view ==1)
        {
            bas_=2;
            brange=250;
            PlaySound("neg.wav",NULL, SND_ASYNC);
            p.view =0;
        }
        if(p.pnum == 1 && p.px>bx-25 && p.px<bx+brange-15 && p.py>50 && p.py<=120 && p.view ==1)
        {
            bas_=0;
            brange=100;
            PlaySound("neg.wav",NULL, SND_ASYNC);
            p.view =0;
        }
        if (bas_==2 || bas_==0)
        {
            bastimer+=10;
            if(bastimer%4000 == 0)
            {
                bas_ =1;
                brange =150;
            }
        }
        if(p.pnum == 3 && p.px>bx-35 && p.px<bx+brange-10 && p.py>50 && p.py<=120 && p.view ==1)
        {
             if(s3[0]>='0' && s3[0]<'3')
             {
                 s3[0]+=3;
             }
             else
             {
                 s3[0]-=3;
                 s2[0]+=1;
             }
             p.view=0;
             PlaySound("neg.wav",NULL,SND_ASYNC);
        }
        if(p.pnum == 2 && p.px>bx-25 && p.px<bx+brange-20 && p.py>50 && p.py<=120)
        {
            et=300;
            PlaySound("neg.wav",NULL, SND_ASYNC);
        }
        if(et == 300)
        {
            et1+=10;
            if(et1>= 4000)
            {
               et =110;
               et1=10;
            }
        }

}

void pt()
{
    if(pause == 0)
         ptimer+=10;
}
void perkf()
{
         if(pause ==1)
            dpy =0;
        if(pause ==0)
            dpy =read*10;


            p.py-=dpy;
            iShowBMP2(p.px,p.py,perks[p.pnum],0);
           // peff();

}
void perk_pos()
{
//if(pause==0)
{
     pt();
     if(ptimer%6000 == 0)
      {
             p.px=400+rand()%600;
             p.py=700+rand()%200;
             int x =rand()%4;
             p.pnum=x;
             p.ppic=perks[x];
             p.view=1;

      }
      perkf();
}

}

void loading()
{
    load+=rand()%28;
}
void timpo()
{
    if (read >= 1 && read<=5 && pause==0)
    {
        un=atoi(s4);
        te=atoi(s3);
        hu=atoi(s2);

        if(!un && !te)
        {
            hu-=1;
            un=9;
            te=5;
        }
        else if(!un)
        {
            un=9;
            te--;
        }
        else un--;

        if(!un && !te && !hu)
        {
            read= 8;
            hu=atoi(dur);
        }

        itoa(un,s4,10);
        itoa(te,s3,10);
        itoa(hu,s2,10);
        icount++;
    }

}
void hen()
{
   if (read>=1 && read<=5 && pause==0)
   {
       if(henx[0]>-300 && henx[0]<300)
           henx[0]+=110-2*rand()%210;
       else if(henx[0]<-300)
           henx[0]+=2*rand()%210;
       else
           henx[0]-=2*rand()%210;


   }


}
void hen1()
{
   if (read>=1 && read<=5 && pause==0)
   {
       if(henx[1]>-300 && henx[1]<300)
           henx[1]+=110-rand()%210;
       else if(henx[1]<-300)
           henx[1]+=rand()%210;
       else
           henx[1]-=rand()%210;

   }

}

void eggt()
{
    if(pause ==0)
    {
        eggtimer+=10;
        atimer+=rand()%40;
    }
    if(pause ==1)
    {
        eggtimer=10;
        atimer+=0;
    }
}
void eggfall()
{
     if(atimer>6000 )
        {
            ax-=4*eggdx;
            if(pause==0);
                eggdx=10;
            if(pause ==1)
                eggdx=0;
            iShowBMP2(ax,ay,"leaf.bmp",0);
            if(atimer >= 7000)
            {
                atimer =10;
                ax=1300;
                eggdx=0;
            }
        }
    for(int i=0;i<100;i++)
    {

        if(pause == 0)
        {
            e[i].eggy-=eggdy;
            e[i].eggx-=eggdx;
        }
        if(e[i].eggy<70)
            e[i].view =0;
        if(e[i].view ==1)
        {

            iShowBMP2(e[i].eggx,e[i].eggy,eggpic[e[i].eggtype],0);

        }
        if(e[i].eggx>bx-25 && e[i].eggx<bx+brange-15 && e[i].eggy>50 && e[i].eggy<=80)
        {
             PlaySound("pos.wav",NULL, SND_ASYNC);
             if(pause ==0)
             score+=point[e[i].eggtype];
             iSetColor(255,0,0) ;
             itoa(point[e[i].eggtype],spo,10);
             itoa(score,ssc,10);
             iText(e[i].eggx,200,spo,GLUT_BITMAP_TIMES_ROMAN_24);

        }
    }


}

void egg()
{

     eggt();
     if(eggtimer%et == 0)
      {
         int hennum;
         eggnum=(eggnum+1)%100;
         hennum=rand()%read;
         int x;
         x=rand()%17;
         e[eggnum]={690+henx[hennum],heny[hennum],1,eggpic[x],x,point[x]};
      }
     // if(eggtimer%et == 0)
     // {
          iSetColor(255,255,255) ;
          iText(1200,620,ssc,GLUT_BITMAP_TIMES_ROMAN_24);

     // }
      eggfall();


}
void res_r()
{

    fx = fopen("abc.txt","r");
    fscanf( fx , "%d %d %d %d %d %d %d %d %d %d %d %d %d %lf %lf %d",&eggtimer,&ptimer,&bastimer,&un,&te,&hu,&iPlay,&score,&brange,&bas_,&eggnum,&henx[0],&henx[1],&vtx,&vty,&ft);
    fscanf( fx , "%lf %lf",&dtheta,&bx);
    for(int i=0; i<100;i++)
        fscanf(fx, "%d %d %d %d",&e[i].eggx,&e[i].eggy,&e[i].eggtype,&e[i].view);
    fscanf(fx, "%d %d %d %d",&p.px,&p.py,&p.pnum,&p.view);
    fscanf(fx, "%lf",&eggdx);
    fscanf(fx, "%d %d %d %d %d %d",&et,&et1,&eggtimer,&atimer,&ax,&ay);
    fclose(fx);
    itoa(un,s4,10);
    itoa(te,s3,10);
    itoa(hu,s2,10);
    itoa(score,ssc,10);
    itoa(ft,dur,10);
    //eggfall();
    //perkf();
}
void res_w()
{
    fx = fopen("abc.txt","w");

    fprintf( fx , "%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%d \n%lf \n%lf \n%d \n",
            eggtimer,ptimer,bastimer,un,te,hu,iPlay,score,brange,bas_,eggnum,henx[0],henx[1],vtx,vty,ft);
    fprintf( fx , "%lf\n %lf\n",dtheta,bx);
    for(int i=0; i<100;i++)
        fprintf(fx, "%d\n %d\n %d\n %d\n",e[i].eggx,e[i].eggy,e[i].eggtype,e[i].view);
    fprintf(fx, "%d\n %d\n %d\n %d\n",p.px,p.py,p.pnum,p.view);
    fprintf(fx, "%lf\n",eggdx);
    fprintf(fx, "%d\n %d\n %d\n %d\n %d\n %d\n",et,et1,eggtimer,atimer,ax,ay);
    fclose(fx);

}
res_r_check()
{
    fb = fopen("lv.txt","r");
    fscanf(fb,"%d",&lvflag);
    fclose(fb);
}
res_w_check()
{
    fb = fopen("lv.txt","w");
    fprintf(fb,"%d",lvflag);
    fclose(fb);
}
void iDraw()
{
    //place your drawing codes here
    if(read ==-1)
    {
        iClear();

        iShowBMP(0,0,bg[0]);
        iSetColor(255,255,255);
        iText(400,400,"Loading... Please Wait for a few moments",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(400,300,300,50);
        iSetColor(109,190,50);
        iFilledRectangle(400,300,load,50);
        if(load>=300)
            read=0;
        iSetColor(25,25,255);
        iText(105,450,"PRESS DOWN ARROW KEY TO MUTE AND UPPER ARROW TO TURN ON SOUND",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(read ==0 )
    {
        iClear();
        iShowBMP(0,0,bg[0]);
        iSetColor(254,126,0);
        iFilledRectangle(300,550,600,50);
        iFilledCircle(300,575,25);
        iFilledCircle(900,575,25);
        iSetColor(0,200,214);
        iFilledRectangle(300,450,600,50);
        iFilledCircle(300,475,25);
        iFilledCircle(900,475,25);
        iSetColor(200,0,180);
        iFilledRectangle(300,350,600,50);
        iFilledCircle(300,375,25);
        iFilledCircle(900,375,25);
        iSetColor(0,0,235);
        iFilledRectangle(300,250,600,50);
        iFilledCircle(300,275,25);
        iFilledCircle(900,275,25);
        iSetColor(154,52,52);
        iFilledRectangle(300,150,600,50);
        iFilledCircle(300,175,25);
        iFilledCircle(900,175,25);
        iSetColor(255,255,255);
        iText(555,565,"RESUME",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(525,465,"NEW GAME",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(565,365," QUIT ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(515,265,"HIGH SCORES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(515,165,"HOW TO PLAY",GLUT_BITMAP_TIMES_ROMAN_24);


    }
    if(read >= 1 && read<=3)
    {
        iClear();
        itoa(read,sread,10);
        iPlay=read;
        iShowBMP(0,0,bg[1]);

        iShowBMP2(stx,sty,bg[2],0);
        if(read==3)
        {
            iShowBMP2(vtx,vty,henpic[2],0);
            henx[2] =vtx-670;
            heny[2] =vty;
        }
        if(read==2 || read==3)
               iShowBMP2(stx,sty-100,bg[2],0);
        iSetColor(109,190,50);
        iFilledRectangle(390,470,50,40);
        iFilledRectangle(1100,493,50,40);
        if(read==2 || read==3)
        {
            iFilledRectangle(390,380,50,40);
            iFilledRectangle(1100,373,50,40);
        }
        iShowBMP2(670+henx[0],heny[0],henpic[0],0);
        if(read==2 || read==3)
               iShowBMP2(670+henx[1],heny[1],henpic[1],0);
        iSetColor(115,43,20);
        iFilledRectangle(1080,600,240,50);
        iSetColor(255,255,255);
        iText(1100,620,"SCORE :",GLUT_BITMAP_TIMES_ROMAN_24);
        egg();
        perk_pos();
        iShowBMP2(bx,50,baspic[bas_],0);
        peff();
        iSetColor(109,190,50);
        if(read==3)
        {
            for(int n=0;n<50;n++)
            {
                iLine(670+0.1*n,heny[0]+5+0.1*n,vtx+0.1*n,vty+0.1*n);
                iLine(770+0.1*n,heny[0]+5+0.1*n,vtx+100+0.1*n,vty+0.1*n);
            }
        }
        iSetColor(115,43,20);
        if(read ==3 ) iFilledRectangle(vtx,vty,100,10);
        iFilledRectangle(50,600,50,50);
        iFilledRectangle(110,600,50,50);
        iFilledRectangle(200,600,50,50);
        iFilledRectangle(260,600,50,50);
        iFilledRectangle(50,530,260,50);

        iText(650,600,"LVL",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700,600,sread,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iText(175,620,":",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(70,620,s1,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(130,620,s2,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(220,620,s3,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(280,620,s4,GLUT_BITMAP_TIMES_ROMAN_24);

        if (pause ==1)
        {
            //pause=1;
            iText(140,550,"RESUME",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            //pause=0;
            iText(140,550,"PAUSE",GLUT_BITMAP_TIMES_ROMAN_24);
        }




        //iShowBMP2(690+henx,515-eggy,bg[4],0);

    }

    if(read == 6)
    {
        iClear();
        iShowBMP(0,0,bg[1]);
        iSetColor(250,120,0);
        iText(475,365,"Are you sure you want to Quit?",GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(515,265,100,50);
        iFilledRectangle(665,265,100,50);
        iSetColor(255,255,255);
        iText(540,280,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700,280,"NO",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(read ==7)
    {
        iClear();
        iShowBMP(0,0,bg[0]);
        iSetColor(152,52,52);
        iFilledRectangle(475,365,200,50);
        iFilledRectangle(475,265,200,50);
        iFilledRectangle(475,165,200,50);
        iSetColor(200,0,154);
        iText(425,465,"SELECT DURATION IN MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iText(505,385,"3 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(505,285,"4 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(505,185,"5 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if(read ==8 )
        {
        iClear();
        iShowBMP(0,0,bg[1]);
        iShowBMP2(0,0,bg[3],0);

        iText(505,385,"LEVEL ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600,385,sread,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(620,385,"COMPLETED ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(505,345,"CLICK ANYWHERE TO SAVE SCORE OR PRESS ESCAPE ",GLUT_BITMAP_TIMES_ROMAN_24);
        lvflag =1;
        }
    if(read ==9)
    {
        iClear();
        iShowBMP(0,0,bg[0]);
        iSetColor(152,52,52);
        iFilledRectangle(475,415,200,50);
        iFilledRectangle(475,315,200,50);
        iFilledRectangle(475,215,200,50);
        iSetColor(200,0,154);
        iText(425,515,"SELECT LEVEL",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iText(505,440,"LEVEL 1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(505,340,"LEVEL 2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(505,240,"LEVEL 3",GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if(read == 10)
    {
        iClear();
        iShowBMP(0,0,bg[1]);
        iSetColor(255,0,0);
        iText(300,600,"TIME",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,600,dur,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,550,"LEVEL",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,550,sread,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,500,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,500,ssc,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,450,"Enter Your Name.It must be less than 80 characters.Press enter to save.",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(300,300,600,50);
        iText(350,320,name,GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if (read >= 11 && read<=15)
    {
        iClear();
        iSetColor(127,127,127);
        for(int i=1;i<=5;i++)
        iFilledCircle(200*i,40,5);
        iShowBMP(200,200,bg[read-7]);
        if(read == 14)
        iShowBMP(650,200,bg[9]);
        iSetColor(255,0,0);
        iFilledCircle(200*(read-10),40,5);
        iSetColor(255,255,255);
        if(read ==11 )
        {
           iText(100,150,"Chicken are moving on a bark or swing and laying eggs.There is a basket at bottom.You can move it horizontally",GLUT_BITMAP_TIMES_ROMAN_24);
           iText(100,100,"using cursor or left and right keys. On top left there are Timer and Pause/resume menu and level is marked over",GLUT_BITMAP_TIMES_ROMAN_24);
           iText(100, 50,"at the top center. On top right there is score board, you can see your score and time.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(read == 12)
        {
            iText(100,150,"You have to catch the eggs using the basket.Normal eggs offer you 1 point,red offer 5 and golden ones offer 10.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(read == 13)
        {
            iText(100,150,"Sometimes the chickens will poop.Don't catch them.else,you will lose 10 points.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(read == 14)
        {
            iText(100,150,"You can play the game in 3 levels and 3 durations you want to choose.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(read ==15)
        {
            iText(100,150,"Perks will fall from the sky at regular intervals of time and offer you benefits as well as disadvantages.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    if(read == 16)
    {
        iClear();
        iShowBMP(0,0,bg[1]);
        iSetColor(255,0,0);
        iFilledRectangle(300,600,600,40);
        iFilledRectangle(300,550,600,40);
        iFilledRectangle(300,500,600,40);
        iFilledRectangle(300,400,600,40);
        iFilledRectangle(300,350,600,40);
        iFilledRectangle(300,300,600,40);
        iFilledRectangle(300,200,600,40);
        iFilledRectangle(300,150,600,40);
        iFilledRectangle(300,100,600,40);
        iSetColor(255,255,255);
        iText(500,610,"TIME 3 LEVEL 1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,560,"TIME 3 LEVEL 2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,510,"TIME 3 LEVEL 3",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,410,"TIME 4 LEVEL 1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,360,"TIME 4 LEVEL 2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,310,"TIME 4 LEVEL 3",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,210,"TIME 5 LEVEL 1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,160,"TIME 5 LEVEL 2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,110,"TIME 5 LEVEL 3",GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if(read >= 18 && read<=26)
    {
        iClear();
        iSetColor(255,0,0);
        iText(450,650,"TOP 10 SCORES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,600,"RANK",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(550,600,"NAME",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(950,600,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,550,"1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,500,"2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,450,"3",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,400,"4",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,350,"5",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,300,"6",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,250,"7",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,200,"8",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,150,"9",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(250,100,"10",GLUT_BITMAP_TIMES_ROMAN_24);
        if (read == 18)
            fa=fopen("hs31.txt","r");
        if (read == 19)
            fa=fopen("hs32.txt","r");
        if (read == 20)
            fa=fopen("hs33.txt","r");
        if (read == 21)
            fa=fopen("hs41.txt","r");
        if (read == 22)
            fa=fopen("hs42.txt","r");
        if (read == 23)
            fa=fopen("hs43.txt","r");
        if (read == 24)
            fa=fopen("hs51.txt","r");
        if (read == 25)
            fa=fopen("hs52.txt","r");
        if (read == 26)
            fa=fopen("hs53.txt","r");
        savehs si[10];
        char b[10][5];
        for(int i=0;i<10;i++)
            fscanf(fa," %d %[^\n] ",&si[i].sscore,si[i].naam);
        fclose(fa);
        for(int i=0;i<10;i++)
        {
            iText(550,550-50*i,si[i].naam,GLUT_BITMAP_TIMES_ROMAN_24);
            itoa(si[i].sscore,b[i],10);
            iText(950,550-50*i,b[i],GLUT_BITMAP_TIMES_ROMAN_24);
        }

    }
    if(read ==17)
    {
        iClear();
        iShowBMP(0,0,bg[1]);
        iSetColor(255,52,52);
        iText(300,450,"You have no game to resume",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,400,"press Esc to be back to menu",GLUT_BITMAP_TIMES_ROMAN_24);

    }
}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/





void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    if (basket ==1 && pause == 0)
        bx=mx-newbx;

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        if(read==0 && mx>300 && mx<900 && my>450 && my<500)
        {
            read =7;
        }
        if(read ==0 && mx>300 && mx<900 && my>550 && my<600)
        {
           // read =iPlay;
                PlaySound("no_sound.wav",NULL,SND_LOOP | SND_ASYNC);
                res_r_check();
                if(lvflag ==0)
                {
                res_r();
                read=iPlay;
                pause =0;
                }
                else if(lvflag==1)
                   read =17;

        }
        if(read >= 1 && read<=3)
        {

            if( mx>bx && mx<bx+brange && my>50 && my<150)
            {
                basket=1;
                newbx=mx-bx;
            }
            else if(mx>50 && mx<310 && my>530 && my<580)
            {
                pause=(pause+1)%2;
                basket=0;
            }
            else
                 basket=0;
        }
        if(read==0 && mx>300 && mx<900 && my>350 && my<400)
            read =6;
        if(read==0 && mx>300 && mx<900 && my>250 && my<300)
            read =16;
        if(read==0 && mx>300 && mx<900 && my>150 && my<200)
            read =11;

        if( read == 6)
        {
            if (mx>515 && mx<615 && my>265 && my<315)
            {
                exit(0);
            }
            if (mx>665 && mx<765 && my>265 && my<315)
                read =0;
        }
        if(read == 7)
        {
            if( mx>475 && mx<675 && my>365 && my<415)
            {
                strcpy(dur,"3");
                strcpy(s2,dur);
                strcpy(s3,"0");
                strcpy(s4,"0");
                strcpy(ssc,"0");
                ft=3;
                reset();
                read=9;
            }
            if( mx>475 && mx<675 && my>265 && my<315)
            {
                strcpy(dur,"4");
                strcpy(s2,dur);
                strcpy(s3,"0");
                strcpy(s4,"0");
                strcpy(ssc,"0");
                ft=4;
                reset();
                read=9;
            }
            if( mx>475 && mx<675 && my>165 && my<215)
            {
                strcpy(dur,"5");
                strcpy(s2,dur);
                strcpy(s3,"0");
                strcpy(s4,"0");
                strcpy(ssc,"0");
                ft=5;
                reset();
                read=9;
            }

        }
        if(read==8)
        {
            read=10;
        }
        if(read == 9)
        {
            if( mx>475 && mx<675 && my>415 && my<465)
            {
                pause=0;
                read=1;
                PlaySound("Test.wav", NULL, SND_LOOP | SND_ASYNC);
                lvflag=0;
                res_w_check();

            }
            if( mx>475 && mx<675 && my>315 && my<365)
            {
                pause=0;
                read=2;
                PlaySound("Test.wav", NULL, SND_LOOP | SND_ASYNC);
                lvflag=0;
                res_w_check();

            }
            if( mx>475 && mx<675 && my>215 && my<265)
            {
                pause=0;
                read=3;
                PlaySound("Test.wav", NULL, SND_LOOP | SND_ASYNC);
                lvflag=0;
                res_w_check();

            }

        }
        if(read == 16)
        {
             if (mx>300 && mx<900 && my>600 && my<640)
                 read =18;
             if (mx>300 && mx<900 && my>550 && my<590)
                 read =19;
             if (mx>300 && mx<900 && my>500 && my<540)
                 read =20;
             if (mx>300 && mx<900 && my>400 && my<440)
                 read =21;
             if (mx>300 && mx<900 && my>350 && my<390)
                 read =22;
             if (mx>300 && mx<900 && my>300 && my<340)
                 read =23;
             if (mx>300 && mx<900 && my>200 && my<240)
                 read =24;
             if (mx>300 && mx<900 && my>150 && my<190)
                 read =25;
             if (mx>300 && mx<900 && my>100 && my<140)
                 read =26;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        basket=0;
        pause=(pause+1)%2;
    }


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
}
void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        res_w();
        res_w_check();
        exit(0);
    }

    if(read>=1 && read<=3)
    {
        if(key == 'p')
        {
            pause=1;
        }

        if(key == 'r')
        {
            pause=0;
        }
    }
    if(key == 13)
    {
        if(read>=11 && read<=15)
            read=(read+1)%16;
    }
    if(key == 8)
    {
         if(read>11 && read<=15)
             read--;
         else if(read == 11)
             read=0;
    }
    if(key == 27)
    {
        if(read==0)
            read=6;
        else if(read>=6 && read<=17)
        {
            if(read ==8 || read==9 || read==10 || read==17)
            PlaySound("song.wav",NULL,SND_LOOP | SND_ASYNC);
            if(read ==8 || read==10)
            res_w_check();
            read=0;
        }
        else if(read>=1 && read<=3)
        {
            PlaySound("song.wav",NULL,SND_LOOP | SND_ASYNC);
            iPlay=read;
            read=0;
            pause=1;
            res_w();

        }
        else if(read>=18 && read<=26)
        {
            read=16;
        }


    }
    if(read == 10)
    {
       if(key!=8 && key!=13)
       {
        name[len] = key;
        len++;
       }
       else if(key == 8)
       {
           if(len!=0)len--;
           name[len]= ' ';
       }
       else if(key == 13)
       {
           if(ft ==3 && iPlay ==2)
           {

            fa= fopen("hs32.txt","r");
            int Tt,Ll,i=-1,j;
            savehs sc[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc[i].sscore,sc[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc[i].sscore=score;
            strcpy(sc[i].naam, name);


            fa= fopen("hs32.txt","w");
            sort_score(sc,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc[i].sscore,sc[i].naam);
            fclose(fa);
        }



        if(ft ==3 && iPlay ==1)
        {

            fa= fopen("hs31.txt","r");
            int i=-1;
            savehs sc1[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc1[i].sscore,sc1[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc1[i].sscore=score;
            strcpy(sc1[i].naam, name);


            fa= fopen("hs31.txt","w");
            sort_score(sc1,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc1[i].sscore,sc1[i].naam);
            fclose(fa);
        }



         if(ft ==3 && iPlay ==3)
           {

            fa= fopen("hs33.txt","r");
            int i=-1;
            savehs sc3[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc3[i].sscore,sc3[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc3[i].sscore=score;
            strcpy(sc3[i].naam, name);


            fa= fopen("hs33.txt","w");
            sort_score(sc3,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc3[i].sscore,sc3[i].naam);
            fclose(fa);
        }


        if(ft ==4 && iPlay ==1)
        {

            fa= fopen("hs41.txt","r");
            int i=-1;
            savehs sc4[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc4[i].sscore,sc4[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc4[i].sscore=score;
            strcpy(sc4[i].naam, name);


            fa= fopen("hs41.txt","w");
            sort_score(sc4,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc4[i].sscore,sc4[i].naam);
            fclose(fa);
        }



          if(ft ==4 && iPlay ==2)
        {

            fa= fopen("hs42.txt","r");
            int i=-1;
            savehs sc5[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc5[i].sscore,sc5[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc5[i].sscore=score;
            strcpy(sc5[i].naam, name);


            fa= fopen("hs42.txt","w");
            sort_score(sc5,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc5[i].sscore,sc5[i].naam);
            fclose(fa);
        }



          if(ft ==4 && iPlay ==3)
        {

            fa= fopen("hs43.txt","r");
            int i=-1;
            savehs sc6[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc6[i].sscore,sc6[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc6[i].sscore=score;
            strcpy(sc6[i].naam, name);


            fa= fopen("hs43.txt","w");
            sort_score(sc6,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc6[i].sscore,sc6[i].naam);
            fclose(fa);
        }


         if(ft ==5 && iPlay ==1)
           {

            fa= fopen("hs51.txt","r");
            int i=-1;
            savehs sc7[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc7[i].sscore,sc7[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc7[i].sscore=score;
            strcpy(sc7[i].naam, name);


            fa= fopen("hs51.txt","w");
            sort_score(sc7,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc7[i].sscore,sc7[i].naam);
            fclose(fa);
        }



        if(ft ==5 && iPlay ==2)
        {

            fa= fopen("hs52.txt","r");
            int i=-1;
            savehs sc8[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc8[i].sscore,sc8[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc8[i].sscore=score;
            strcpy(sc8[i].naam, name);


            fa= fopen("hs52.txt","w");
            sort_score(sc8,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc8[i].sscore,sc8[i].naam);
            fclose(fa);
        }


        if(ft ==5 && iPlay ==3)
        {

            fa= fopen("hs53.txt","r");
            int i=-1;
            savehs sc9[12]={0};


            while(1)
            {
               i++;
               fscanf(fa," %d %[^\n] ",&sc9[i].sscore,sc9[i].naam);
               if(feof(fa))
                   break;
            }
            fclose(fa);

            sc9[i].sscore=score;
            strcpy(sc9[i].naam, name);


            fa= fopen("hs53.txt","w");
            sort_score(sc9,11);

            for( i=0;i<10;i++)
            fprintf(fa," %d %s \n",sc9[i].sscore,sc9[i].naam);
            fclose(fa);
        }
        res_w_check();
        read = 0;
        PlaySound("song.wav",NULL,SND_LOOP | SND_ASYNC);
       }
    }
    //place your codes for other keys here
}


/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        res_w();
        res_w_check();
        exit(0);
    }
    //place your codes for other keys here
    if(key == GLUT_KEY_UP)
           PlaySound("song.wav",NULL,SND_LOOP | SND_ASYNC);
    if(key == GLUT_KEY_DOWN)
           if(read<1 || read>3)
            PlaySound("no_sound.wav",NULL,SND_LOOP | SND_ASYNC);
    if(key == GLUT_KEY_LEFT)
    {
        if(read>=1 && read<=3)
            bx-=20;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        if(read>=1 && read<=3)
            bx+=20;
    }

}


int main()
{
    //place your own initialization codes here.
    //if(read ==1) hu*60+10*te+un

/*    q= (char**)malloc(100*sizeof(char*));
    for(int i=0;i<100;i++)
    {
        q[i]= (char*)malloc(20*sizeof(char));
        strcpy(q[i],"regg.bmp");

    }

*/
    PlaySound("song.wav",NULL,SND_LOOP | SND_ASYNC);
    //else PlaySound(0,0,0);
    iSetTimer(tim+5*(hu*6+te+0.1*un),hen);
    iSetTimer(tim+7*(hu*6+te+0.1*un),hen1);
    iSetTimer(sec,timpo);
    iSetTimer(200,loading);

  //  iSetTimer(9000,perk_pos);
   // iSetTimer(600,pt);
    iSetTimer(200,vtm);

    iInitialize(1367, 700, "Catch the egg");
 /*   for(int i=0;i<100;i++)
        free(q[i]);
    free(q);*/

    return 0;
}
