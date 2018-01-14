const int light =6;
const int red =5;
const int motor1 =9;
const int motor2 =10;
const int motor3 =11;
const int motor4 =12;


struct mytype1{
  int wait_time;
  int rotate_time;
  int direct_start;
}setting{
  1600,
  45,
  1
};

struct mytpye2{
  String blue_send;
  int motor_flag;
  int direct;
  int light_stat;
  int red_stat;
  int stop_flag;
}temp{
  "",
  0,
  setting.direct_start,
  0,
  0,
  0
};

int light_read(int light){
  int x;
  x=digitalRead(light);
  return x;
}

int red_read(int red){
  int x;
  x=digitalRead(red);
  return x;
}

void stepper_motor(int a,int b,int c,int d,int t,int direct){
  switch(direct){
  case 1:
    digitalWrite(d,0);
    digitalWrite(a,1);
    delayMicroseconds(t);
    
    digitalWrite(b,1);
    delayMicroseconds(t);
    
    digitalWrite(a,0);
    delayMicroseconds(t);
    
    digitalWrite(c,1);
    delayMicroseconds(t);
    
    digitalWrite(b,0);
    delayMicroseconds(t);
    
    digitalWrite(d,1);
    delayMicroseconds(t);
    
    digitalWrite(c,0);
    delayMicroseconds(t);
    
    digitalWrite(a,1);
    delayMicroseconds(t);
    break;

  case -1:
    digitalWrite(b,0);
    digitalWrite(a,1);
    delayMicroseconds(t);
    
    digitalWrite(d,1);
    delayMicroseconds(t);
    
    digitalWrite(a,0);
    delayMicroseconds(t);
    
    digitalWrite(c,1);
    delayMicroseconds(t);
    
    digitalWrite(d,0);
    delayMicroseconds(t);
    
    digitalWrite(b,1);
    delayMicroseconds(t);
    
    digitalWrite(c,0);
    delayMicroseconds(t);
    
    digitalWrite(a,1);
    delayMicroseconds(t);
    break;
  }
  return;
}

void motor_action(int direct,int rotate_time){
  int flag=0;
  while(flag<=rotate_time) {
    stepper_motor(motor1, motor2, motor3, motor4, setting.wait_time, temp.direct);
    flag++;
  }
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  return;  
}

void setup() {
  pinMode(light,INPUT);
  pinMode(red,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);
  pinMode(motor4,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  //delay(60*1000);
}

void loop() {
   while(Serial.available() > 0){
    temp.blue_send += char(Serial.read());
    delay(2);
   }


    if(temp.blue_send=="on" && temp.direct==setting.direct_start){
      temp.motor_flag=1;
    }
    if(temp.blue_send=="off" && temp.direct==-setting.direct_start){
      temp.motor_flag=1;
    }
    if(temp.blue_send=="switch"){
      temp.blue_send="";
      setting.direct_start = -setting.direct_start;
    }
  

  
  if(temp.motor_flag==1){
    temp.motor_flag=0;
    goto action;
  }
  
  temp.light_stat=light_read(light);
  temp.red_stat=red_read(red);

  if(temp.blue_send.length()==0){
    digitalWrite(13,0);
  }
  if(temp.blue_send.length()>0){
    digitalWrite(13,1);
  }
  
  if(temp.light_stat==1 and temp.red_stat==1){
    temp.stop_flag=1;
    action:;
    Serial.println("ok");
    motor_action(temp.direct,setting.rotate_time);
    temp.direct= -temp.direct;
  }

  if(temp.stop_flag==1){
    delay(30*1000);
    temp.stop_flag=0;
  }
  temp.blue_send="";
  delay(1000);
}
