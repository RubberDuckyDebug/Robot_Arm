//#include <Servo.h>
//
//#define _cA 58
//#define _cB 50
//#define _cC 90
//#define _cBASE 46
//#define MAX_ANGLE 180
//#define MAX_DIST 80
//#define MIN_DIST 50
//#define box_HEIGHT 15.5
//
//int boxes = 0;
//
//typedef struct{
//  Servo servo;
//  byte new_pos;
//  byte cur_pos;
//}s_Servo;
//
//typedef struct{
//  byte angle;
//  byte distance;
//}s_Box;
//
//s_Servo unit[5];
//s_Box box[4];
//s_Box* sector_data[6];
//s_Box bad_box;
//int lastSector=5;
//byte move_chk = 0x0;
//char arm_mode;
//
//void setPositions(int distance);  //use math to set servos 1-3 angles
//void moveTo();                    //move servos to there final position
//void outPosition();               //check to see if any of the servos are out of position
//
//
// 
//void setup() {
//  Serial.begin(9600);
//  pinMode(8,INPUT_PULLUP);
//  for(int i=0; i<5; i++){
//     unit[i].servo.attach(i+9);
//     if(i<4){
//        unit[i].servo.write(110); 
//        unit[i].new_pos = 110;
//        unit[i].cur_pos = 110;
//     }
//     else
//        unit[i].servo.write(40);
//        unit[i].new_pos = 40;
//        unit[i].cur_pos = 40;
//  }
//  /*for(int i=0; i<4; i++){
//    box[i].angle = (MAX_ANGLE * i / 6) + (MAX_ANGLE/12);
//    //box[i].distance = random(MIN_DIST,MAX_DIST);
//    box[i].distance = 60;
//    sector_data[i] = &(box[i]);
//  }
//  sector_data[4] = NULL;
//  sector_data[5] = NULL;*/
//  for(int i = 0; i <6; i++){
//    sector_data[i] = &bad_box;
//  }
//}
//
//void loop(){
//  if(Serial.available() > 0){
//    arm_mode = Serial.read();
//  }
//  
//  switch(arm_mode){
//    case '1': shuffle();
//              break;
//    case '2': stack();
//              break;
//    case '3': Scan();
//              MoveTo();
//              break;
//  }
//  
//}
//
//
//int find_Y(int T, int B){
//  return ((_cBASE - (boxes)*(box_HEIGHT)) + sin(T)*_cA)-cos(B)*_cC;
//}
//int find_X(int T, int B){
//  return _cA*cos(T)+_cB+_cC*cos(B);
//}
//float find_C(int x){
//  return acos((pow(_cB,2)+pow(_cA,2)-(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2)))/(2*_cB*_cA));
//}
///*int find_A(int x, int C){
//  return asin((_cB/(sqrt(pow(x,2)+pow(c-_cBASE,2))))*sin(C));
//}
//int find_B(int x, int C){
//  return asin((_cA/(sqrt(pow(x,2)+pow(c-_cBASE,2))))*sin(C));
//}*/
//float find_H(int x, int C){
//  return acos(x/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))+asin(_cB/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2)))*sin(C))+(PI/2);
//}
//float find_M(int x, int C){
//  return asin(x/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))+asin((_cA/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))*sin(C));
//}
//
//void SetServos(int distance){
//  float C = find_C(distance);
//  float H = find_H(distance,C);
//  float M = find_M(distance,C);
////  Serial.print(distance);
////  Serial.print("  ");
////  Serial.print(270-H*180/PI);
////  Serial.print("  ");
////  Serial.print(270-C*180/PI);
////  Serial.print("  ");
////  Serial.println(270-M*180/PI);
//  unit[1].new_pos =270- (H*180/PI);
//  unit[2].new_pos = 270-(C*180/PI);
//  unit[3].new_pos = 270-(M*180/PI);
//}
//
//bool outOfPlace(){
//  for(int i = 0; i<4; i++){
//    if(unit[i].new_pos != unit[i].cur_pos)
//      return true;
//  }
//  return false;
//}
//void MoveTo(){
//  move_chk = 0x0;
//  while(outOfPlace()){
//    for(int j=0; j<4; j++){
//        if(unit[j].new_pos > 179) unit[j].new_pos = 179;
//        if(unit[j].new_pos < 1) unit[j].new_pos = 0;
//        if(unit[j].new_pos < unit[j].cur_pos){
//          unit[j].servo.write(--(unit[j].cur_pos));
//        }
//       else if(unit[j].new_pos > unit[j].cur_pos){
//          unit[j].servo.write(++(unit[j].cur_pos));
//        }
//        delay(5);
//        }
//  }
//}
//void Rotate_to(int sector){
//  unit[1].new_pos = 80;
//  MoveTo();
//  unit[0].new_pos = (180/6)*sector+(180/6)/2;
//  MoveTo();
//}
//void Open_Claw(int x){
//  for(int i = unit[4].servo.read(); i<x; i++){
//    unit[4].servo.write(i);
//    delay(10);
//  }
//}
//void Close_Claw(int x){
//  for(int i = unit[4].servo.read(); i>x; i--){
//    unit[4].servo.write(i);
//    delay(10);
//  }
//}
//void Grab(s_Box box){
//  Open_Claw(90);
//  SetServos(box.distance);
//  MoveTo();
//  Close_Claw(40);
//}
//void Release(s_Box box){
//  SetServos(box.distance);
//  MoveTo();
//  Open_Claw(90);
//  unit[1].new_pos = 80;
//  MoveTo();
//  Close_Claw(30);
//  SetServos(60);
//}
//void shuffle(){
//
//    int currentSector;
//    int newSector;
//    
//    do{
//      currentSector = random(0,5);
//    }while(sector_data[currentSector] == NULL && currentSector != lastSector);// FORCES SELECTION OF A FILLED SECTOR
//    
//
//    Rotate_to(currentSector); // Move to the selected sector
//    Grab(*(sector_data[currentSector])); // GRABS THE BOX
//    do{
//        newSector = random(0,5);
//    }while(sector_data[newSector] != &bad_box);
//    lastSector = newSector;
//    Rotate_to(newSector); // MOVES THE BOX TO THE NEW SECTOR
//    sector_data[newSector]=sector_data[currentSector];
//    sector_data[currentSector] = &bad_box;
//    sector_data[newSector]->angle = (MAX_ANGLE * (newSector) / 6) + (MAX_ANGLE/12);
//    sector_data[newSector]->distance = random(MIN_DIST,MAX_DIST);
//    
//    Release(*(sector_data[newSector])); // RELEASES THE OBJECT
//}
//
//void stack(){
//    int i = 0, j = 0;
//    int box_location[4];
//    
//    
//    for (i; i < 6; i++){
//      if (sector_data[i] != &bad_box){
//        box_location[j] = i;
//        j++;
//      }
//    }
//
//    Rotate_to(box_location[2]); // Start at the second box
//    Grab(*(sector_data[box_location[2]]));
//
//    boxes++;
//    
//    Rotate_to(box_location[1]); // Move to the location of the first box
//    Release(*(sector_data[box_location[1]]));
//
//    boxes = 0;
//}
//
//void Scan(){
//  SetServos(60);
//  byte nose = unit[3].new_pos;
//  byte shoulder = unit[1].new_pos;
//  byte box_index=0;
//  //unit[3].new_pos = 180;
//  //unit[1].new_pos = 90;
//  //MoveTo();
//  for(int i = 0; i < 180; i++){ 
//    unit[3].new_pos = 180;
//    unit[1].new_pos = 87;
//    unit[0].new_pos = i;
//    MoveTo();
//    delay(100);
//    if(!digitalRead(8)){
//      byte sector = unit[0].cur_pos/30;
//      char sectorData = unit[0].cur_pos/30;
//      Serial.write(sectorData);
//      
//      if(sector_data[sector] == &bad_box){
////        Serial.println((int)(sector_data[sector]));
//      if(unit[0].cur_pos>20)
//         unit[0].new_pos = unit[0].cur_pos - 14; 
//      MoveTo();
//      box[box_index].angle = (MAX_ANGLE * (sector) / 6) + (MAX_ANGLE/12);
//      box[box_index].distance = 70;
//      Grab(box[box_index]);
//      Rotate_to(sector);
//      Release(box[box_index]);
//      
//      sector_data[sector] = &(box[box_index]);
//      box_index++;
//      i+=(MAX_ANGLE/6);
//      //delay(10000);
//      }
//    }
//  } 
//
//  Serial.write(6);
//}
//
//void Read(){
//  SetServos(60);
//  byte nose = unit[3].new_pos;
//  byte shoulder = unit[1].new_pos;
//  byte box_index = 0;
//
//  for(int i = 0; i < 180; i++){ 
//    unit[3].new_pos = 180;
//    unit[1].new_pos = 87;
//    unit[2].new_pos = 170;
//    unit[0].new_pos = i;
//    MoveTo();
//    if(!digitalRead(8)){
//      delay(1000);
//      box[box_index].angle = (MAX_ANGLE * (unit[0].cur_pos/30) / 6) + (MAX_ANGLE/12);
//      //box[box_index].distance = 70;
//      sector_data[unit[0].cur_pos/30] = &(box[box_index]);
//      box_index++;
//      i += (MAX_ANGLE/12);
//    }
//  }
//}

#include <Servo.h>

#define _cA 58
#define _cB 50
#define _cC 90
#define _cBASE 46
#define MAX_ANGLE 180
#define MAX_DIST 80
#define MIN_DIST 50
#define box_HEIGHT 15.5

int boxes = 0;

typedef struct{
  
  Servo servo;
  byte new_pos;
  byte cur_pos;
}s_Servo;

typedef struct{
  byte angle;
  byte distance;
  byte sector;
}s_Box;

s_Servo unit[5];
s_Box box[4];
s_Box found_boxes[4];
s_Box* sector_data[6];
s_Box bad_box;
int lastSector=5;
byte move_chk = 0x0;
char arm_mode;

void setPositions(int distance);  //use math to set servos 1-3 angles
void moveTo();                    //move servos to there final position
void outPosition();               //check to see if any of the servos are out of position


 
void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP);
  for(int i=0; i<5; i++){
     unit[i].servo.attach(i+9);
     if(i<4){
        unit[i].servo.write(110); 
        unit[i].new_pos = 110;
        unit[i].cur_pos = 110;
     }
     else
        unit[i].servo.write(40);
        unit[i].new_pos = 40;
        unit[i].cur_pos = 40;
  }
  /*for(int i=0; i<4; i++){
    box[i].angle = (MAX_ANGLE * i / 6) + (MAX_ANGLE/12);
    //box[i].distance = random(MIN_DIST,MAX_DIST);
    box[i].distance = 60;
    sector_data[i] = &(box[i]);
  }
  sector_data[4] = NULL;
  sector_data[5] = NULL;*/
}

void loop(){
  if(Serial.available() > 0){
    arm_mode = Serial.read();
  }
  
  switch(arm_mode){
    case '1': shuffle();
              break;
    case '2': stack();
              break;
    case '3': Scan();
              MoveTo();
              break;
  }
  
}


int find_Y(int T, int B){
  return ((_cBASE - (boxes)*(box_HEIGHT)) + sin(T)*_cA)-cos(B)*_cC;
}
int find_X(int T, int B){
  return _cA*cos(T)+_cB+_cC*cos(B);
}
float find_C(int x){
  return acos((pow(_cB,2)+pow(_cA,2)-(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2)))/(2*_cB*_cA));
}
/*int find_A(int x, int C){
  return asin((_cB/(sqrt(pow(x,2)+pow(c-_cBASE,2))))*sin(C));
}
int find_B(int x, int C){
  return asin((_cA/(sqrt(pow(x,2)+pow(c-_cBASE,2))))*sin(C));
}*/
float find_H(int x, int C){
  return acos(x/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))+asin(_cB/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2)))*sin(C))+(PI/2);
}
float find_M(int x, int C){
  return asin(x/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))+asin((_cA/(sqrt(pow(x,2)+pow(_cC-(_cBASE - (boxes)*(box_HEIGHT)),2))))*sin(C));
}

void SetServos(int distance){
  float C = find_C(distance);
  float H = find_H(distance,C);
  float M = find_M(distance,C);
//  Serial.print(distance);
//  Serial.print("  ");
//  Serial.print(270-H*180/PI);
//  Serial.print("  ");
//  Serial.print(270-C*180/PI);
//  Serial.print("  ");
//  Serial.println(270-M*180/PI);
  unit[1].new_pos =270- (H*180/PI);
  unit[2].new_pos = 270-(C*180/PI);
  unit[3].new_pos = 270-(M*180/PI);
}

bool outOfPlace(){
  for(int i = 0; i<4; i++){
    if(unit[i].new_pos != unit[i].cur_pos)
      return true;
  }
  return false;
}
void MoveTo(){
  move_chk = 0x0;
  while(outOfPlace()){
    for(int j=0; j<4; j++){
        if(unit[j].new_pos > 179) unit[j].new_pos = 179;
        if(unit[j].new_pos < 1) unit[j].new_pos = 0;
        if(unit[j].new_pos < unit[j].cur_pos){
          unit[j].servo.write(--(unit[j].cur_pos));
        }
       else if(unit[j].new_pos > unit[j].cur_pos){
          unit[j].servo.write(++(unit[j].cur_pos));
        }
        delay(5);
        }
  }
}
void Rotate_to(int sector){
  unit[1].new_pos = 80;
  MoveTo();
  unit[0].new_pos = (180/6)*sector+(180/6)/2;
  MoveTo();
}
void Open_Claw(int x){
  for(int i = unit[4].servo.read(); i<x; i++){
    unit[4].servo.write(i);
    delay(10);
  }
}
void Close_Claw(int x){
  for(int i = unit[4].servo.read(); i>x; i--){
    unit[4].servo.write(i);
    delay(10);
  }
}
void Grab(s_Box box){
  Open_Claw(90);
  SetServos(box.distance);
  MoveTo();
  Close_Claw(40);
}
void Release(s_Box box){
  SetServos(box.distance);
  MoveTo();
  Open_Claw(90);
  unit[1].new_pos = 80;
  MoveTo();
  Close_Claw(30);
  SetServos(60);
}
void shuffle(){

    int currentSector;
    int newSector;
    
    do{
      currentSector = random(0,5);
    }while(sector_data[currentSector] == NULL && currentSector != lastSector);// FORCES SELECTION OF A FILLED SECTOR
    

    Rotate_to(currentSector); // Move to the selected sector
    Grab(*(sector_data[currentSector])); // GRABS THE BOX
    do{
        newSector = random(0,5);
    }while(sector_data[newSector] != &bad_box);
    lastSector = newSector;
    Rotate_to(newSector); // MOVES THE BOX TO THE NEW SECTOR
    sector_data[newSector]=sector_data[currentSector];
    sector_data[currentSector] = &bad_box;
    sector_data[newSector]->angle = (MAX_ANGLE * (newSector) / 6) + (MAX_ANGLE/12);
    sector_data[newSector]->distance = random(MIN_DIST,MAX_DIST);
    
    Release(*(sector_data[newSector])); // RELEASES THE OBJECT
}

void stack(){
    int i = 0, j = 0;
    int box_location[4];
    
    
    for (i; i < 6; i++){
      if (sector_data[i] != &bad_box){
        box_location[j] = i;
        j++;
      }
    }

    Rotate_to(box_location[2]); // Start at the second box
    Grab(*(sector_data[box_location[2]]));

    boxes++;
    
    Rotate_to(box_location[1]); // Move to the location of the first box
    Release(*(sector_data[box_location[1]]));

    boxes = 0;
}

boolean check_Box(s_Box target){
  
    for (int i = 0; i < 4; i++){
      s_Box current = found_boxes[i];
      if (current.sector == target.sector)
        return true;
    }
    return false;
}

void Scan(){
  SetServos(60);
  byte nose = unit[3].new_pos;
  byte shoulder = unit[1].new_pos;
  byte box_index=0;
  //unit[3].new_pos = 180;
  //unit[1].new_pos = 90;
  //MoveTo();
  for(int i = 0; i < 180; i++){ 
    unit[3].new_pos = 180;
    unit[1].new_pos = 87;
    unit[0].new_pos = i;
    MoveTo();
    delay(100);
    if(!digitalRead(8)){
      byte sector = unit[0].cur_pos/30;
      char sectorData = unit[0].cur_pos/30;
      
      Serial.write(sectorData);
      if(!check_Box(*sector_data[sector])){
        if(unit[0].cur_pos>20){
           unit[0].new_pos = unit[0].cur_pos - 14; 
        }
        MoveTo();
        box[box_index].angle = (MAX_ANGLE * (sector) / 6) + (MAX_ANGLE/6);
        box[box_index].distance = 70;
        Grab(box[box_index]);
        Rotate_to(sector);
        Release(box[box_index]);
        
        sector_data[sector] = &(box[box_index]);
        found_boxes[box_index] = *sector_data[sector];
        found_boxes[box_index].sector = sector;
        box_index++;
        i+=(MAX_ANGLE/6);
        //delay(10000);
    }
  } 
  
  Serial.write(6);
}
}
void Read(){
  SetServos(60);
  byte nose = unit[3].new_pos;
  byte shoulder = unit[1].new_pos;
  byte box_index = 0;

  for(int i = 0; i < 180; i++){ 
    unit[3].new_pos = 180;
    unit[1].new_pos = 87;
    unit[2].new_pos = 170;
    unit[0].new_pos = i;
    MoveTo();
    if(!digitalRead(8)){
      delay(1000);
      box[box_index].angle = (MAX_ANGLE * (unit[0].cur_pos/30) / 6) + (MAX_ANGLE/12);
      //box[box_index].distance = 70;
      sector_data[unit[0].cur_pos/30] = &(box[box_index]);
      box_index++;
      i += (MAX_ANGLE/12);
    }
  }
}

