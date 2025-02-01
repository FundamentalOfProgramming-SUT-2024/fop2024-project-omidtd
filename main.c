//#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
//#include <ncursesw/curses.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include <unistd.h>
#include <wchar.h>
#include <math.h>
#include <ncursesw/curses.h>

  //wchar_t mace[] ;
int trap[45][184];
int goldcolor[45][184];
int weapon[45][184];
int enemy[45][184];
int myweapon[6]={0,1,0,0,0,0};
int damageweapon[6] = {0,5,12,15,5,10}; 
int food[45][184];
int myfood[5];
int foodnum;
int spell[45][184];
int reversepellchance;
int addweapon[6]={0,0,10,8,20,0};
int weaponlistshow;
int hungry;
int hungrycunter;
int currentweapon;
int flor;
int iattackedfirst;
int waitijustarrived;
int armormassage;
int countarmorloss;
int reversegoldchance;
int reversetrapchance;
int reversefoodchance;
int x,y;
int mainpath;
int invalidcommand;
int maxflorthatiwent;
int showpermission;
int closeenemy;

struct florlocation{

    int x[4];
    int y[4];
};
struct hiddendoors{
int x;
int y;
};

 struct mc {

 char icon ;
int gold;
int hp;
int armor;
int flor;
int power;

 };
 void printmc( struct mc mc) {
    attron(COLOR_PAIR(6)|A_BOLD); 
    mvprintw(x, y, "?");             
    attroff(COLOR_PAIR(6)|A_BOLD); 
    
    
}

void printgold( int x1,int y1) {
    attron(COLOR_PAIR(3)); 
    mvaddch(x1, y1,'g');             
    attroff(COLOR_PAIR(3)); 
}
void printdarkgold( int x1,int y1) {
    attron(COLOR_PAIR(4)|A_BOLD); 
    mvaddch(x1, y1,'$');             
    attroff(COLOR_PAIR(4)|A_BOLD); 
}



void gamestart(int x,int y,struct mc* mc);
void setdifficulty(int x,int y,struct mc * mc);
int exitt=0;
int fakeexit=0;
char map[45][184];
char allmap[4][45][184];
int visible[4][45][184];
int hiddendoor[45][185];
struct room {

int x,y;
int hor,ver;

int door;


};



void signup(int x,int y){
    clear();
    refresh();
    curs_set(1);

char *options[] = {
        "username : ",
        "password : ",
        "gmail    : "
    };
char username[65];
char password[65];
char gmail[65];

 for (int i = 0; i < 3; i++) {
            
                mvprintw(x / 2 - 4 + i * 2, y / 2 - 10, "%s", options[i]);
                
           
        }
        
            
                mvgetstr(x / 2 - 4 , y / 2 +1, username);
                mvgetstr(x / 2 - 2, y / 2 +1, password);
                mvgetstr(x / 2    , y / 2 +1, gmail);

           
           fakeexit=1;
        return;



}

void gamestart(int x, int y,struct mc * mc) {
    curs_set(0); 
    int select = 0; 
    char *options[] = {
        "Create New User",
        "Login",
        "Scoreboard",
        "Play as Guest",
        "Set the Difficulty",
        "Exit"
    };
    int num_options = 6;

    while (1) {
        clear(); 
            attron(COLOR_PAIR(1));


        for (int i = 0; i < 6; i++) {
            if (select == i ) {
                attron(A_BOLD | A_REVERSE | COLOR_PAIR(2)); 
                mvprintw(x / 2 - 4 + i * 2, y / 2 - 10, "%s", options[i]);
                attroff(A_BOLD | A_REVERSE | COLOR_PAIR(2)); 
            } else {
                            attron(COLOR_PAIR(1));

                mvprintw(x / 2 - 4 + i * 2, y / 2 - 10, "%s", options[i]);
            }
        }

        refresh();

        int c = getch();
        switch (c) {
            case KEY_UP: 
                if (select > 0) select--;
                else if(select==0)select=5;
                break;
            case KEY_DOWN: 
                if (select < num_options-1) select++;
                else if(select==5)select=0;
                break;
            case '\n': 
                attroff(COLOR_PAIR(1));

                if (select == 5) { 
                    exitt=1;
                    return;
                }
                else if(select==0){
                clear();
                refresh();

                signup(x,y);
                clear();
                refresh();}

                else if(select==4){
                //clear();
                refresh();

                setdifficulty(x,y,mc);
                clear();
                refresh();
                }

                if(exitt==1)return;
                
                break;

                
        }

        if(fakeexit==1)return;
    }
}


void setdifficulty(int x,int y,struct mc* mc){
    
curs_set(0); 
    int select = 0; 
    char *options[] = {
        "easy",
        "medium",
        "hard",
        "insane",
        
    };
    int num_options = 4;

    while (1) {
        clear(); 
            attron(COLOR_PAIR(1));


        for (int i = 0; i < 4; i++) {
            if (select == i ) {
                attron(A_BOLD | A_REVERSE | COLOR_PAIR(2)); 
                mvprintw(x / 2 - 4 + i * 2, y / 2 - 10, "%s", options[i]);
                attroff(A_BOLD | A_REVERSE | COLOR_PAIR(2)); 
            } else {
                            attron(COLOR_PAIR(1));

                mvprintw(x / 2 - 4 + i * 2, y / 2 - 10, "%s", options[i]);
            }
        }

        refresh();

        int c = getch();
        switch (c) {
            case KEY_UP: 
                if (select > 0) select--;
                else if(select==0)select=3;
                break;
            case KEY_DOWN: 
                if (select < 3) select++;
                else if(select==3)select=0;
                break;
            case '\n': 
                attroff(COLOR_PAIR(1));
                if(select==0){

                    mc->hp=70;
                    mc->armor=10;
                    mc->gold=100;
                    reversetrapchance=80;
                    reversegoldchance=20;
                    reversepellchance=30;
                

                }
                else if(select==1){

                    mc->hp=50;
                    mc->armor=7;
                    mc->gold=80;
                    reversetrapchance=50;
                    reversegoldchance=35;
                    reversepellchance=50;

                }
                else if(select==2){

                    mc->hp=30;
                    mc->armor=4;
                    mc->gold=40;
                    reversetrapchance=25;
                    reversegoldchance=50;
                    reversepellchance=70;

                }
                else if(select==3){

                    mc->hp=10;
                    mc->armor=1;
                    mc->gold=20;
                    reversetrapchance=10;
                    reversegoldchance=70;
                    reversepellchance=90;
                

                }

                return;

                
        }

        
    }

}


void createmap(struct mc mc,struct hiddendoors hiddendoors[8]){

    for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            weapon[i][j]=0;
        }
    }
    for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            spell[i][j]=0;
        }
    }


 for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            map[i][j]=' ';
        }
        
    }


     struct room room[6];
     for(int i=0;i<6;i++){

     room[i].hor=rand()%10+10;
     room[i].ver=rand()%3+5;


     }
     int a=rand()%20+2;
     for(int i=0;i<2;i++){

        room[i].y=a+30;
        room[i].x=rand()%8+2+25*i;

     }
     a=rand()%20+2;
     for(int i=2;i<4;i++){

        room[i].y=a+80;
        room[i].x=rand()%8+2+25*(i-2);

     }

     a=rand()%20+2;
     for(int i=4;i<6;i++){

        room[i].y=a+130;
        room[i].x=rand()%8+2+25*(i-4);

     }

     for(int i=0;i<6;i++){

        for(int j=room[i].x;j<=room[i].ver+room[i].x;j++){

            for(int k=room[i].y;k<=room[i].hor+room[i].y;k++){
                
                if(j==room[i].x||j==room[i].x+room[i].ver){
                    map[j][k]='=';
                }
                else if(k==room[i].y||k==room[i].y+room[i].hor){
                    map[j][k]='|';
                }
                
                else {map[j][k]='.';
                
                int b=rand()%20;
                if(b==1&&weapon[j][k-1]==0&&spell[j][k-1]==0)map[j][k]='O';

                b=rand()%reversetrapchance;
                if(b==1){
                    trap[j][k]=1;
                    map[j][k]='T';
                    }

                    for(int u=1;u<5;u++){
                    b=rand()%reversefoodchance;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]=u+'0';
                        food[j][k]=u;

                    }

                    }


                    b=rand()%100;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]='D';
                        enemy[j][k]=5;


                    }
                    b=rand()%100;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]='F';
                        enemy[j][k]=10;


                    }
                    b=rand()%100;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]='G';
                        enemy[j][k]=15;


                    }
                    b=rand()%100;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]='S';
                        enemy[j][k]=20;


                    }
                    b=rand()%100;
                    if(b==1&&map[j][k]=='.'){

                        map[j][k]='U';
                        enemy[j][k]=30;


                    }
                b=rand()%reversegoldchance;
                if(b==1&&map[j][k]=='.'){
                    map[j][k]='g';
                    goldcolor[i][j]=3;
                    int b=rand()%10;
                    if(b==1){
                        goldcolor[i][j]=4;
                    }
                    

                }
                b=rand()%(reversegoldchance*10);
                if(b==1&&map[j][k]=='.'){
                    map[j][k]='$';
                }

                for(int u=1;u<4;u++){

                b=rand()%reversepellchance;
                if(b==1&&map[j][k]=='.'&&spell[j][k+1]==0&&weapon[j][k+1]==0&&spell[j][k-1]==0&&weapon[j][k-1]==0){
                    spell[j][k]=u;
                }

                }


                for(int q=2;q<5;q++){
                int bb=rand()%70;
                if(bb==1&&map[j][k]=='.'&&weapon[j][k]==0&&spell[j][k+1]==0&&weapon[j][k+1]==0&&spell[j][k-1]==0&&weapon[j][k-1]==0&&k+1!=room[i].y+room[i].hor){
                    weapon[j][k]=q;
                }

                }



                }
            }

        }
        if(i%2==0){
            int temp=room[i].y+rand()%(room[i].hor-4)+2;
            map[  room[i].x+room[i].ver  ][temp]='+';
            room[i].door=temp;
        }
        else if(i%2!=0){
            int temp=room[i].y+rand()%(room[i].hor-4)+2;
            map[  room[i].x ][temp]='+';
        room[i].door=temp;
        }

        if(i==2||i==3){

            int temp=room[i].x+rand()%(room[i].ver-4)+2;
            int temp2=room[i].x+rand()%(room[i].ver-4)+2;
            hiddendoor[temp][room[i].y+room[i].hor]=i+2;
            hiddendoor[temp2][room[i].y]=i;
            hiddendoors[i].x=temp;
            hiddendoors[i].y=room[i].y;
            hiddendoors[i+2].y=temp2;
            hiddendoors[i+2].y=room[i].y+room[i].hor;

        }
        if(i==0||i==1){

            int temp=room[i].x+rand()%(room[i].ver-4)+2;
            hiddendoor[temp][room[i].y+room[i].hor]=i;
            hiddendoors[i].x=temp;
            hiddendoors[i].y=room[i].y+room[i].hor;
            

        }
        if(i==4||i==5){

            int temp=room[i].x+rand()%(room[i].ver-4)+2;
            
            hiddendoor[temp][room[i].y]=i+2;
            hiddendoors[i].x=temp;
            hiddendoors[i].y=room[i].y;

        }


     }

for(int i=2;i<6;i++){
    while(1){
        int e=rand()%45;
        int t=rand()%184;
        if(map[e][t]=='.'&&map[e][t+1]=='.'&&weapon[e][t]==0){
            weapon[e][t]=i;
            //weapon[e][t+1]=2;
            break;
        }
     }

}


     if(mc.flor<3){
     while(1){
        int e=rand()%45;
        int t=rand()%184;
        if(map[e][t]=='.'){
            map[e][t]='N';
            break;
        }
     }
     }
     if(mc.flor>0){
     while(1){
        int e=rand()%45;
        int t=rand()%184;
        if(map[e][t]=='.'){
            map[e][t]='B';
            break;
        }
     }
     }

      mainpath=rand()%5+19;

    for(int i=0;i<184;i++){

     map[mainpath][i]='#';

    }

    for(int i=0;i<184;i++){

        for(int j=0;j<6;j++){

            if(i==room[j].door){

                if(room[j].x+room[j].ver<mainpath){
                    for(int k=room[j].x+room[j].ver+1;k<mainpath;k++){
                        map[k][i]='#';
                    }
                }
                else if(room[j].x + room[j].ver>mainpath){
                    for(int k=mainpath+1;k<room[j].x;k++){
                        map[k][i]='#';
                    }
                }

            }

        }


    }

    /*for(int j=0;j<184;j++){
        for(int i=0;i<45;i++){

            if(hiddendoor[i][j]==1){
                int jc=j;
                int a,b;
                while(1){
                    jc++;
                    for(int ii=i-10;ii<i+10;ii++){
                        if(hiddendoor[ii][jc]==1){
                            a=ii;

                        }
                    }
                }



            }


        }
    }*/
   

    



}

void copy(int flooor){

for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        allmap[flooor][i][j]=map[i][j];
    }
}


}
void loadmap(int flooor){

for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        map[i][j]=allmap[flooor][i][j];
    }
}

}

int abovezero(int a){
    if(a<0)return 0;
    else return a;
}

void showmap(struct mc mc){

    

for(int i=abovezero(x-5);i<x+5;i++){
   for(int j=abovezero(y-5);j<y+5;j++){

    visible[mc.flor][i][j]=1;

   } 
}

for(int i=0;i<45;i++){

    for(int j=0;j<184;j++){

        
        if(showpermission==0){
          if(visible[mc.flor][i][j]==1){

          mvprintw(i,j,"%c",map[i][j]);
          if(map[i][j]=='g')printgold(i,j);
          if(map[i][j]=='$')printdarkgold(i,j);
          attron(COLOR_PAIR(5)|A_BOLD);

                      //if(weapon[i][j]==1&&map[i][j]=='.')mvprintw(i,j,"⚒");
                       if(weapon[i][j]==2&&map[i][j]=='.')mvprintw(i,j,"🗡");
                      else if(weapon[i][j]==3&&map[i][j]=='.')mvprintw(i,j,"!");
                      else if(weapon[i][j]==4&&map[i][j]=='.')mvprintw(i,j,"⟳");
                      else if(weapon[i][j]==5&&map[i][j]=='.')mvprintw(i,j,"⚔");
                      attroff(COLOR_PAIR(5)|A_BOLD);

                      attron(COLOR_PAIR(1)|A_BOLD); 

                      if(spell[i][j]==1&&map[i][j]=='.')mvprintw(i,j,"♥");
                      else if(spell[i][j]==2&&map[i][j]=='.')mvprintw(i,j,"Ϟ");
                      else if(spell[i][j]==3&&map[i][j]=='.')mvprintw(i,j,"♠");

                      attroff(COLOR_PAIR(1)|A_BOLD); 
                      


          }
//⚒🗡,!⟳⚔
          }

          else{

                      mvprintw(i,j,"%c",map[i][j]);
                      if(map[i][j]=='g')printgold(i,j);
                      if(map[i][j]=='$')printdarkgold(i,j);
                      
                      attron(COLOR_PAIR(5)|A_BOLD);

                      //if(weapon[i][j]==1&&map[i][j]=='.')mvprintw(i,j,"⚒");
                       if(weapon[i][j]==2&&map[i][j]=='.')mvprintw(i,j,"🗡");
                      else if(weapon[i][j]==3&&map[i][j]=='.')mvprintw(i,j,"!");
                      else if(weapon[i][j]==4&&map[i][j]=='.')mvprintw(i,j,"⟳");
                      else if(weapon[i][j]==5&&map[i][j]=='.')mvprintw(i,j,"⚔");
                      attroff(COLOR_PAIR(5)|A_BOLD);

                       attron(COLOR_PAIR(1)|A_BOLD); 

                      if(spell[i][j]==1&&map[i][j]=='.')mvprintw(i,j,"♥");
                      else if(spell[i][j]==2&&map[i][j]=='.')mvprintw(i,j,"Ϟ");
                      else if(spell[i][j]==3&&map[i][j]=='.')mvprintw(i,j,"♠");
                      
                      attroff(COLOR_PAIR(1)|A_BOLD); 
                      
                      

          }

    }
}

attron(A_BOLD);
        mvprintw(44,14,"gold:%d",mc.gold);
        mvprintw(44,44,"hp:%d",mc.hp);
        mvprintw(44,74,"armor:%d",mc.armor);
        mvprintw(44,104,"floor:%d",mc.flor);
        attroff(A_BOLD);
 


}



int  moneycode(struct mc mc){char a;
    clear();showmap(mc);printmc(mc);
    if(a=getch()=='o'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='n'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='e'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='y'){
       
       beep();
       return 1;
    }
    }
    }
    }
}

int  destroycode(struct mc mc){char a;
    clear();showmap(mc);printmc(mc);
    if(a=getch()=='e'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='s'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='t'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='r'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='o'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='y'){
       
       for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            if(map[i][j]=='O'){
                map[i][j]='.';
            }
        }
       }

       beep();
       return 1;
    }
    }
    }
    }
    }
    }
}

int  hpcode(int x,int y,struct mc mc){char a;
    clear();showmap(mc);printmc(mc);
    if(a=getch()=='e'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='a'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='l'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='t'){clear();showmap(mc);printmc(mc);
        if(a=getch()=='h'){
       
       beep();
       return 1;
    }
    }
    }
    }
    }
}


void losing(struct mc mc){
    clear();
    //refresh();

mvprintw(10,70,"you lost...");
refresh();
mvprintw(20,70,"calulating you score");
refresh();
int i;
while( i<=mc.gold*mc.gold){

    mvprintw(22,70,"%d",i);
    refresh();
    if(i<20) usleep(100000);
    else if(i<40) usleep(30000);
    else if(i<100) usleep(10000);
    else if(i<1000)usleep(3000);
    else usleep(200);
    i++;

}
getch();



}

void showweapon(){

clear();
char * options[]={" ","mace ⚒       ","Dagger 🗡     ","Magic Wand ! ","Normal Arrow ⟳","sword ⚔      "};
// ⚒ 🗡  !⟳ ⚔
int select=1;

/*attron(COLOR_PAIR(5)|A_BOLD);

for(int i=1;i<6;i++){
mvprintw(2*i+1,1,"%s",options[i]);
mvprintw(2*i+1,17,": %d",myweapon[i]);


}
attroff(COLOR_PAIR(5)|A_BOLD);
refresh;
getch();
return;*/

    while (1) {
        clear(); 
           


        for (int i = 1; i < 6; i++) {
            if (select == i ) {
                attron(A_BOLD | A_REVERSE | COLOR_PAIR(5)); 
                mvprintw(3*i , 1 , "%s", options[i]);
                mvprintw(3*i,18,": %d",myweapon[i]);
                attroff(A_BOLD | A_REVERSE | COLOR_PAIR(5)); 
            } else {
                    attron(A_BOLD);

                mvprintw(3*i , 1 , "%s", options[i]);
                mvprintw(3*i,18,": %d",myweapon[i]);
                    attroff(A_BOLD);
            }
        }

        refresh();

        int c = getch();
        switch (c) {
            case KEY_UP: 
                if (select > 1) select--;
                else if(select==1)select=5;
                break;
            case KEY_DOWN: 
                if (select < 5) select++;
                else if(select==5)select=1;
                break;
            case '\n': 
                clear();
                if(myweapon[select]>0){
                currentweapon=select;
                mvprintw(1,0," now your weapon is %s\n press any key to continiue the game...",options[select]);
                refresh();
                getch();}

                else{

                mvprintw(1,1,"sorry you don't have this weapon");
                refresh();
                usleep(1500000);

                }

                return;

                break;
                case 'i':return;

        }

}

}

int destroyonce(struct mc * mc){
countarmorloss=0;
for(int i=x-1;i<x+2;i++){

    for(int j=y-1;j<y+2;j++){
        if(map[i][j]=='O'){
            
            countarmorloss++;
        }
    }

}
if (mc->armor>=countarmorloss){

for(int i=x-1;i<x+2;i++){

    for(int j=y-1;j<y+2;j++){
        if(map[i][j]=='O'){
            map[i][j]='.';
            
        }
    }

}

mc->armor-= countarmorloss;
return 2;


}
else{
    return 1;
}


}

void createhiddenpath(struct hiddendoors hiddendoors[8]){
//hiddendoors[hiddendoor[x][y]].x=x;
//hiddendoors[hiddendoor[x][y]].y=y;
int xc=x,yc=y;
map[xc][yc+1]='#';
if(hiddendoor[x][y]!=2&&hiddendoor[x][y]!=3&&hiddendoor[x][y]<6){

int d=hiddendoor[x][y]+2;

while(1){

   int a=rand()%4;
    if(a==0&&xc<hiddendoors[d].x){
        int d=hiddendoors[d].x-xc;
        xc+=abs(d)/d;
        map[xc][yc]='#';
        
        continue;

    }

    else if(yc<hiddendoors[d].y){
        yc++;
        map[xc][yc]='#';
        

    }
    
    else return;

}

}


}

int printweapon;
int enemyx,enemyy;

void nearenemy(){

    int countenemy=0;
   
    for(int i=x-1;i<x+2;i++){
        for(int j=y-1;j<y+2;j++){
            
                if (enemy[i][j]>0){
                   // beep();
                    countenemy++;
                    enemyx=i;
                    enemyy=j;
                    
                }
                
            
        }
    }
    if(countenemy>0){
        closeenemy++;
        return;
    }
    else closeenemy=0;

}

void enemyfound(){
    char enemeys[]="DFGSU";
    for(int i=x-1;i<x+2;i++){
        for(int j=y-1;j<y+2;j++){
            for(int k=0;k<5;k++){
                if (enemy[i][j]>0){
                    
                    enemyx=i;
                    enemyy=j;

                    if(myweapon[currentweapon]<=0){
                        printweapon=0;
                        refresh();
                        
                        return;
                    }
                    hungrycunter++;
                    enemy[i][j]-=damageweapon[currentweapon];
                    if(currentweapon!=1&&currentweapon!=5)myweapon[currentweapon]--;
                    printweapon=1;
                    if(enemy[i][j]<=0){
                    map[i][j]='.';}
                    beep();
                    return;
                }
            }
        }
    }
}

void showhungry(){

clear();
attron(COLOR_PAIR(7)|A_BOLD);

for(int i=0;i<100-hungry;i++){
    mvprintw(1,i+1," ");

}
attroff(COLOR_PAIR(7)|A_BOLD);
attron(COLOR_PAIR(8)|A_BOLD);
for(int i=100-hungry;i<100;i++){
    mvprintw(1,i+1," ");

}
attroff(COLOR_PAIR(8)|A_BOLD);
if(hungry>50){
    attron(COLOR_PAIR(1)|A_BOLD);
    mvprintw(3,20,"you havn't eat for too long,your hp will decrease");
    refresh();
    attroff(COLOR_PAIR(1)|A_BOLD);
}

for(int i=0;i<foodnum;i++){

mvprintw(5,i+1,"🍔 ");

}

refresh();
getch();
return;


}

void show_temp_message( const char *message, int duration_ms) {
    static time_t start_time = 0;
    static int showing = 0;  // آیا پیام در حال نمایش است؟

    if (!showing) {  // اگر پیام نمایش داده نشده، آن را نمایش بده
        mvprintw(2, 0, "%s", message);
        refresh();
        start_time = time(NULL);
        showing = 1;
    } else {
        time_t current_time = time(NULL);
        if ((current_time - start_time) * 1000 >= duration_ms) {  
            // پاک کردن پیام با نوشتن فضای خالی
            for (int i = 0; i < strlen(message); i++) {
                mvprintw(y, x + i, " ");
            }
            refresh();
            showing = 0;  // پیام حذف شد
        }
    }
}

int main() {
    
    setlocale(LC_ALL,"");
    initscr();
    start_color();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);   
    init_pair(2, COLOR_GREEN, COLOR_WHITE); 
    init_color(10, 1000, 843, 0);//طلایی
    init_color(12, 1000, 1000, 700 );  // سبزابی
    init_color(11, 1000, 500, 0);//orange
    init_pair(3,10, COLOR_BLACK);
    init_pair(4,COLOR_GREEN,COLOR_BLACK);
    init_pair(5,11,COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);  
    init_pair(7, COLOR_GREEN, COLOR_GREEN);  
     init_pair(8, COLOR_RED, COLOR_RED);
    closeenemy=-1; 

    srand(time(NULL));

       //wchar_t mace[] = L"\u2692";
    // mvaddstr(5,7,"..........");
     //mvaddstr(6,7,"..........");
     //mvaddwstr(5,10,mace);
     
      //mvprintw(0, 0, "🥓\n...");
     refresh();
     getch();

for(int ii=0;ii<4;ii++){
for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        visible[ii][i][j]=0;
    }
}   
}
for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        food[i][j]=-1;
    }
}
for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        hiddendoor[i][j]=-3;
    }
} 
for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        enemy[i][j]=0;
    }
} 

for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            weapon[i][j]=0;
        }
    }
    for(int i=0;i<45;i++){
        for(int j=0;j<184;j++){
            spell[i][j]=0;
        }
    }


weaponlistshow=0;
struct mc mc;
struct florlocation florlocation;
struct hiddendoors hiddendoors[8];
mc.icon='@';
mc.gold=100;
mc.hp=70;
mc.armor=10;
mc.power=1;
hungry=0;
hungrycunter=0;
reversetrapchance=60;
reversegoldchance=20;
reversepellchance=40;
reversefoodchance=70;
currentweapon=1;
iattackedfirst=0;
foodnum=0;
mc.flor=0;
flor=0;
 showpermission=0;

int intcheat=0;
invalidcommand=0;
waitijustarrived=0;
maxflorthatiwent=0;
printweapon=-1;
/*printw("salam");
refresh();*/

    keypad(stdscr, TRUE); 
    int r, c;
    getmaxyx(stdscr, r, c); 
    //getch();
    gamestart(r, c,&mc); 
    if(exitt==1){
        endwin();
        return 0;
    };
    clear;
    refresh();


    
    curs_set(0);
    createmap(mc,hiddendoors);

 /*   for(int i=0;i<45;i++){
    for(int j=0;j<184;j++){
        mvprintw(i,j,"%d",hiddendoor[i][j]);
    }
} 
refresh();getch();*/

     x=mainpath,y=0;
    showmap(mc);
    printmc(mc);
    refresh();



    while(1){

        nearenemy();

        if(closeenemy>1&&iattackedfirst==0){


            if(mc.armor>0){
                mc.armor-=1;
            }
            else{
            mc.hp-=enemy[enemyx][enemyy];
            }
            beep();
            

        }
        iattackedfirst=0;

        

        clear();
        showmap(mc);

        
        

        if(trap[x][y]==1){
            if(mc.armor<=0){
            int loss=rand()%10+1;
            mc.hp-=loss;
            showmap(mc);
            mvprintw(0,0,"you stepped on a trap and lost %d hp",loss);}
            else{
                mc.armor--;
                showmap(mc);
                mvprintw(0,0,"you stepped on a trap and lost 1 armor");
            }
            
            trap[x][y]=0;
        }

        if(intcheat==1){
            mvprintw(0,0,"cheat has activated");       
            intcheat=0;
        }
        if(invalidcommand==1){
            mvprintw(0,0,"invalid command");       
            invalidcommand=0;
        }
        if(map[x][y]=='N'&&waitijustarrived==0){

            
            
            copy(mc.flor);
            florlocation.x[mc.flor]=x;
            florlocation.y[mc.flor]=y;

            clear();
            mc.flor++;
            if(mc.flor>maxflorthatiwent){
                maxflorthatiwent=mc.flor;
                createmap(mc,hiddendoors);
            }
            else{

                loadmap(mc.flor);

            }
            mvprintw(22,70,"moving to the next floor...");
            refresh();
            usleep(2000000);

            

            x=mainpath;
            y=0;
            waitijustarrived=1;
            continue;



        }

        if(food[x][y]>0){
            if(foodnum<5){
                foodnum++;
                map[x][y]='.';
                food[x][y]=0;
            }
            myfood[food[x][y]]++;


        }

         if(map[x][y]=='B'){
            waitijustarrived=1;
            
            clear();
            copy(mc.flor);
            mc.flor--;
            loadmap(mc.flor);
            x=florlocation.x[mc.flor];
            y=florlocation.y[mc.flor];
            mvprintw(22,70,"moving to the previous floor...");
            refresh();
            usleep(2000000);
            
            continue;



        }


        if(map[x][y]=='g'){
        
            int goldvalue=rand()%10+1;
            mc.gold+=goldvalue;
            showmap(mc);
            mvprintw(0,0,"you found %d gold",goldvalue);
            
            map[x][y]='.';
            
            }
            if(map[x][y]=='$'){
        
            int darkgoldvalue=rand()%100+1;
            mc.gold+=darkgoldvalue;
            showmap(mc);
            mvprintw(0,0,"you found %d darkgold",darkgoldvalue);
            
            map[x][y]='.';
            
            }
            if(weapon[x][y]>0){

                myweapon[weapon[x][y]]+=addweapon[weapon[x][y]];
                if(weapon[x][y]==5&&myweapon[5]==0)myweapon[5]++;;
                weapon[x][y]=0;


            }

             if(spell[x][y]>0){

                

             spell[x][y]=0;

            }
            if(armormassage==2){

                mvprintw(0,0,"you lost %d armor",countarmorloss);
                refresh();
                
            }
            if(armormassage==1){
               mvprintw(0,0,"not enough armor");
               beep();
               refresh();
            }
            if(printweapon==1){
                mvprintw(0,0,"you dealed %d damage to your enemy",damageweapon[currentweapon]);
                if(enemy[enemyx][enemyy]>0)mvprintw(1,0,"enemy's hp : %d",enemy[enemyx][enemyy]);
                else mvprintw(1,0,"enemy is dead");

            }

            if(hungrycunter>=10){
                hungry++;
                hungrycunter=0;
                if(hungry>50){
                    
                    mc.hp-=rand()%3+1;
                    mvprintw(2,0,"hp decreased due to hunger\nyou can press w to eat food and decrease hunger");

                }
            }

            if(printweapon==0){
                mvprintw(0,0,"not enough weapon");
            }
            /*if(hiddendoor[x][y]>-1){

                createhiddenpath(hiddendoors);

            }*/


        if(mc.hp<=0){
            clear();
            
            losing(mc);
            endwin();
            return 0;
        }

        

        
        
   
    printmc(mc);
    

    int loc=getch();
    waitijustarrived=0;
    armormassage=0;
    printweapon=-1;
    

    switch(loc){

    case KEY_UP : if(x>0){

        if(map[x-1][y]!=' '&&map[x-1][y]!='='&&map[x-1][y]!='|'&&map[x-1][y]!='O'){
            x--;
            hungrycunter++;
        }
    }    
    refresh();
    break;

    case '9' : if(x>0&&y<c-1){
        if(map[x-1][y+1]!=' '&&map[x-1][y+1]!='='&&map[x-1][y+1]!='|'&&map[x-1][y+1]!='O'){
            x--;
            y++;
            hungrycunter++;
        }
    }
    refresh();
    break;

    case '7' : if(x>0&&y>0){
        if(map[x-1][y-1]!=' '&&map[x-1][y-1]!='='&&map[x-1][y-1]!='|'&&map[x-1][y-1]!='O'){
            x--;
            y--;
            hungrycunter++;
        }
    }
     refresh();
    break;

    case '3' : if(x<r-1&&y<c-1){
        if(map[x+1][y+1]!=' '&&map[x+1][y+1]!='='&&map[x+1][y+1]!='|'&&map[x+1][y+1]!='O'){
            x++;
            y++;
            hungrycunter++;
        }
    }
    refresh();
    break;

    case '1' : if(x<r-1){
        if(map[x+1][y-1]!=' '&&map[x+1][y-1]!='='&&map[x+1][y-1]!='|'&&map[x+1][y-1]!='O'){
            x++;
            y--;
            hungrycunter++;
        }
    }

    refresh();
    break;

    case KEY_DOWN : if(x<r-1){
        if(map[x+1][y]!=' '&&map[x+1][y]!='='&&map[x+1][y]!='|'&&map[x+1][y]!='O'){
            x++;
            hungrycunter++;
        }
    }
    refresh();
    break;

    case KEY_LEFT : if(y>0){

        if(hiddendoor[x][y-1]>-1){
            y--;
            hungrycunter++;
            refresh();
            continue;
            break;
        }

        else if(map[x][y-1]!=' '&&map[x][y-1]!='='&&map[x][y-1]!='|'&&map[x][y-1]!='O'){
            y--;
            hungrycunter++;
        }
    }
    refresh();
    break;

    case KEY_RIGHT : if(y<c-1){

        if(hiddendoor[x][y+1]>-1){
            y++;
            hungrycunter++;
            refresh();
            continue;
            break;
        }

        else if(map[x][y+1]!=' ' && map[x][y+1]!='='&&map[x][y+1]!='|'&&map[x][y+1]!='O'){
            y++;
            hungrycunter++;
        }
    }
    refresh();
    break;
    case 'q' : endwin();
    return 0;
    break;

    case 'm':if(moneycode(mc)){
        mc.gold+=100;
        intcheat=1;
        
        }
    break;
    case'r': createmap(mc,hiddendoors);
    x=mainpath;
    break;

    case 'h' :
        if(hpcode(x,y,mc)){
            mc.hp+=5;
            intcheat=1;
        }
    break;

    case 's' :
    if(showpermission==0){
        showpermission=1;
    }
    else showpermission=0;
    break;

    case 'd':destroycode(mc);
    break;

    case 'i':
        showweapon();
        
    break;

    case 'f':armormassage=destroyonce(&mc);
    hungrycunter++;
    break;

    case ' ' : enemyfound();
    iattackedfirst=1;
    break;

    case 'e':showhungry();
    break;

    case 'w' : if(foodnum>0){
    foodnum--;
    hungry-=15;
    }
    break;

    /*case 'w' : gamestart(r,c,&mc);
    break;*/


    default : invalidcommand=1;
    
    break;




    }

    }
    endwin(); 
    return 0;
}
