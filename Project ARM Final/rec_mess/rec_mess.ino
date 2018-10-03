#include<VirtualWire.h>
#include<ServoTimer2.h>

ServoTimer2 motor1, motor2, motor3, motor4;

int right_a = 8;
int right_b = 7;
int left_a = 6;
int left_b = 5;

void setup()
{

  pinMode(right_a, OUTPUT);
  pinMode(right_b, OUTPUT);
  pinMode(left_a, OUTPUT);
  pinMode(left_b, OUTPUT);

  motor3.attach(3);
  motor2.attach(10);
  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(12);
  vw_setup(4000);
  pinMode(13, OUTPUT);
  vw_rx_start();

  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
  digitalWrite(13, 0);
}

char val;
char ser[7];
int i, last_pos, power, deg_fin, q;
int digi, deg, store, multi2 = 1500/180;

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;        
  if(vw_get_message(buf, &buflen))
  {
    for(i=0;i<buflen;i++)
    {
      ser[i] = (char)buf[i];
    }
    ser[i] = '\0';
    if(ser[1] == 'e')
    {
      Serial.println("Forward");
      forward();
      delay(20);
    }
    else if(ser[1] == 'f')
    {
      Serial.println("Stopped");
      stp();
      delay(20);
    }
    else if(ser[1] == 'g')
    {
      Serial.println("right");
      right();
      delay(20);
    }
    else if(ser[1] == 'h')
    {
      Serial.println("left");
      left();
      delay(20);
    }
    else if(ser[1] == 'i')
    {
      Serial.println("back");
      back();
      delay(20);
    }
    else if(ser[1] == 'd')
    {
      Serial.println("open");
      digitalWrite(13, 1);
      delay(500);
      digitalWrite(13, 0);
      delay(20);
    }
    else if(ser[i-1] >= '0' && ser[i-1] <= '9' && ser[1] >= 'a' && ser[1] <= 'f')
    {
      Serial.print("The message: ");
      Serial.println(ser);
      Serial.println((int)ser[0]);
      digi = (int)ser[0] - 48;
      val = ser[1];
      if(val == 'a')
      {
        deg = 0;
        power = digi - 1;
        for(i=2;power>=0;i++, power--)
        {
          store = (int)ser[i] - 48;
          store = store*pow(10, power);
          deg+=store;
        }
        deg = deg*(1500/180);
        Serial.print("The sent val: ");
        Serial.print(deg);
        motor1_angle(deg);
        //delay(100);
      }
      else if(val == 'b')
      {
        deg = 0;
        power = digi - 1;
        for(i=2;ser[i] != '\0';i++, power--)
        {
          store = (int)ser[i] - 48;
          store = store*pow(10, power);
          deg = deg + store;
        }
        Serial.print("deg: ");
        Serial.println(deg);
        deg_fin = deg;
        motor2.attach(10);
        delay(20);
        motor2.write(deg_fin+1);
        Serial.print("Val: ");
        Serial.println(deg_fin);
        delay(100);
        motor2.write(1500);
      }
      else if(val == 'c')
      {
        deg = 0;
        power = digi - 1;
        for(i=2;ser[i] != '\0';i++, power--)
        {
          store = (int)ser[i] - 48;
          store = store*pow(10, power);
          deg = deg + store;
        }
        Serial.print("deg: ");
        Serial.println(deg);
        deg_fin = deg;
        motor3.attach(3);
        delay(20);
        motor3.write(deg_fin+1);
        Serial.print("Val: ");
        Serial.println(deg_fin);
        delay(100);
        motor3.write(1500);
      }
    }
    
  }
}

void motor1_angle(int deg)
{
  motor1.attach(9);
  delay(20);
  motor1.write(750+deg);
  delay(100);
  motor1.detach();
  delay(20);
}

void motor4_angle(int deg)
{
  motor4.attach(2);
  delay(20);
  motor4.write(750+deg);
  delay(20);
  motor4.detach();
  delay(20);
}

void forward()
{
  digitalWrite(right_a, 1);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 1);
  digitalWrite(left_b, 0);
  delay(700);
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
}

void stp()
{
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
  delay(700);
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
}

void right()
{
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 1);
  digitalWrite(left_a, 1);
  digitalWrite(left_b, 0);
  delay(700);
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
}

void left()
{
  digitalWrite(right_a, 1);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 1);
  delay(700);
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
}

void back()
{
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 1);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 1);
  delay(700);
  digitalWrite(right_a, 0);
  digitalWrite(right_b, 0);
  digitalWrite(left_a, 0);
  digitalWrite(left_b, 0);
}

