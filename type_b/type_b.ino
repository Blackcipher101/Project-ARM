#include<VirtualWire.h>
char controller[12];
void setup()
{
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000);
  Serial.begin(9600);
}

char ge;
int i, n;
char val;
void loop()
{
  char ser[7];
  delay(70);
  val = Serial.read();
  if(val >= '0' && val <='9')
  {
    ser[0] = (char)val;
    n = (int)val - 48;
    ser[1] = (char)Serial.read();
    i=0;
    while(i<=n-1)
    {
      ser[i+2] = (char)Serial.read();
      i++;
    }
    ser[i+2] = '\0';
    Serial.print("The message: ");
    Serial.println(ser);
    sprintf(controller, "%s", ser);
    Serial.print("The Sent: ");
    Serial.println(controller);
    vw_send((uint8_t *)controller, strlen(controller));
    vw_wait_tx();
  }
}

