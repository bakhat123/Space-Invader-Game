#include <iostream>
#include <raylib.h>

using namespace std;
int score = 10000;
int health = 100;
int screen1 = 0;

class spacecraft{
public:
float x,y;
float width,height;
float speed;



void draw(){
   DrawRectangle(x,y,90,140,WHITE);
}

void update(){
if(IsKeyDown(KEY_UP)){
  y-=speed;
}
if(IsKeyDown(KEY_DOWN)){
  y+=speed;
}
if(IsKeyDown(KEY_LEFT)){
  x-=speed;
}
if(IsKeyDown(KEY_RIGHT)){
  x+=speed;
}

if(x>=GetScreenWidth()-90){
  x = GetScreenWidth()-90;
}
if(x<=0){
  x=0;
}

if(y>=GetScreenHeight()-140){
  y = GetScreenHeight()-140;
}
if(y<=0+170){
  y=0+170;
}

}


};

spacecraft player;




class fire : public spacecraft {
public:
    float x1, y1, x2, y2;
    float radius = 7;
    float speed = 90;

    fire() {
        x1 = player.x + 9;
        y1 = player.y;
        x2 = player.x + 79;
        y2 = player.y;
    }

    void draw() {
        //  DrawCircle(x1, y1, radius, WHITE);
        //  DrawCircle(x2, y2, radius, WHITE);
        
        y1 -= speed;
        y2 -= speed;
    }

    void update() {
      


        if(CheckCollisionCircleRec(Vector2{x1,y1},radius,Rectangle{0,0,1100,170}) ){
            y1 = player.y;
            y2 = player.y;
            x1 = player.x + 9;
            x2 = player.x + 79;
      
            score = score -10;

        }
    }
};

fire bullet;

class Backfire {
public:
    float x = 100;
    float y = 10;
    float speed = 30;
    float radius = 15;

    void draw() {

 
    if(score<=1500 ){
        speed = 150;
        radius = 10;
      }
    }
    void update() {
        y += speed;
        if (y > GetScreenHeight()) {
            float array[] = {100, 200, 300, 400, 500, 600, 700, 800, 900};           
            x = array[GetRandomValue(0, 8)];
            y = 10;
        }
    }

};


Backfire bullet2;

int main() {

    const int screenwidth = 1100;
    const int screenheight = 1000;

   player.x = screenwidth/3;
   player.y = screenheight/2;
   player.speed = 15;


    InitWindow(screenwidth, screenheight, "Project 2");
    InitAudioDevice();
    SetTargetFPS(60);
    Image image = LoadImage("image.png");
    ImageResizeNN(&image,1100,1000);
    Texture2D i = LoadTextureFromImage(image);
    UnloadImage(image);
    Image image2 = LoadImage("Mclaren_P1-removebg.png");
    ImageResizeNN(&image2,110,140);
    Texture2D car = LoadTextureFromImage(image2);
    UnloadImage(image2);
    Image image3 = LoadImage("spaceship2.png");
    ImageResizeNN(&image3,1100,300);
    Texture2D spaceship = LoadTextureFromImage(image3);
    UnloadImage(image3);
    Image image4 = LoadImage("bul.png");
    ImageResizeNN(&image4,30,50);
    Texture2D bul = LoadTextureFromImage(image4);
    UnloadImage(image4);
    Image image5 = LoadImage("bul2.png");
    ImageResizeNN(&image5,60,80);
    Texture2D bul2 = LoadTextureFromImage(image5);
    UnloadImage(image5);
    Image image6 = LoadImage("frontscreen.png");
    ImageResizeNN(&image6,1100,1000);
    Texture2D front = LoadTextureFromImage(image6);
    UnloadImage(image6);
    Sound sound4 = LoadSound("light.wav");
    Sound sound3 = LoadSound("explosion.wav");
    Sound sound2 = LoadSound("shoot.wav");
    Sound sound = LoadSound("sol.mp3");

   PlaySound(sound);

    while (!WindowShouldClose()) {
      switch (screen1){
  
case 0:
BeginDrawing();
    DrawTexture(front,0,0,WHITE);
    DrawText("Death Invaders ",screenwidth/3,screenheight/3,80,RED);
    DrawText("Press enter to continue",screenwidth/3-40,screenheight/3+100,30,RED);


    if(IsKeyPressed(KEY_ENTER)){
      screen1 = 1;
    }
  EndDrawing();
  break;
case 1:

  if(CheckCollisionCircleRec(Vector2{bullet2.x,bullet2.y},15,(Rectangle){player.x,player.y,90,140}) == true){
    health = health - 1;
    bullet2.y = 10;
    bullet2.x = 100;
    PlaySound(sound3);
if(score<=1500 ){
      health = health -1;
      }
  }



        ClearBackground(BLACK);
        BeginDrawing();

         player.update();
         bullet.update();
         bullet2.update();
       
        DrawTexture(i,0,0,WHITE);

        DrawTexture(car,player.x,player.y,WHITE);
    

        
    
     
         if(IsKeyDown(KEY_SPACE)){
           DrawTexture(bul,bullet.x1, bullet.y1, WHITE);
           DrawTexture(bul,bullet.x2, bullet.y2, WHITE);
    
       
      
         bullet.draw(); 
         PlaySound(sound2);
         }
        DrawTexture(bul2,bullet2.x,bullet2.y,WHITE);
        bullet2.draw(); 
     DrawTexture(spaceship,0,-40,WHITE);
       
     DrawText(TextFormat("Death Star:%i%",score),(screenwidth/4)-180,20,40,WHITE);
     DrawText(TextFormat("Health:%i%",health),(screenwidth/4)-180,screenheight-180,40,WHITE);
 
        EndDrawing();
      if(health<=0){
        screen1 = 2;
      }
      if(score<=0){
        screen1 =3;
      }
        
        break;

      case 2:
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("You Lost !",screenwidth/2-100,screenheight/2,80,RED);
      EndDrawing();
      
      break;

      case 3:
      BeginDrawing();
      ClearBackground(WHITE);
      DrawText("You Won Earh is save!",screenwidth/2-200,screenheight/2,60,RED);
      EndDrawing();
      
      break;

      
      }

      }


    UnloadTexture(i);
    UnloadTexture(car);
    UnloadTexture(spaceship);
    UnloadTexture(bul);
    UnloadTexture(bul2);
  
    UnloadSound(sound);
    UnloadSound(sound2);
    UnloadSound(sound3);
    UnloadSound(sound4);
    
    CloseAudioDevice();
    CloseWindow();


    return 0;
}
 