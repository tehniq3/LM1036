// sistem comanda LM1036 - sketch sris de BNicu FLORICA (niq_ro)
// ver.0 - sketch initial, 25.02.2017

// definim pini cu control PWN care au frecventa maxima de 32kHz
#define pinvol 3
#define pinbal 9 
#define pinbas 10
#define pinint 11

// defini butoane
#define pinmen 4
#define pinmin 5
#define pinpls 6

int volum=15;
int balans=127;   // balans la jumate
int bas=127;
int inalte=127;

byte nivel = 0; // 0 - functionare normala
                // > 0 modificare valori
                


void setup()
{

Serial.begin(9600);
Serial.println("------------");
Serial.println("Sistem comanda LM1036 ");
  
setPwmFrequency(pinvol, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinbal, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinbas, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinint, 1);  // frecventa pwm 32kHz  

pinMode(pinvol, OUTPUT);
pinMode(pinbal, OUTPUT);
pinMode(pinbas, OUTPUT);
pinMode(pinint, OUTPUT);

analogWrite(pinvol, volum);
analogWrite(pinbal, balans);
analogWrite(pinbas, bas);
analogWrite(pinint, inalte);

pinMode(pinmen, INPUT);
pinMode(pinmin, INPUT);
pinMode(pinpls, INPUT);

digitalWrite(pinmen, HIGH);
digitalWrite(pinmin, HIGH);
digitalWrite(pinpls, HIGH);

} // sfarsit parte setare


void setPwmFrequency(int pin, int divisor) { // http://playground.arduino.cc/Code/PwmFrequency
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}   // terminare subrutina de frecventa



void loop()
{

if (nivel == 0)
{
/*  
analogWrite(pinvol, volum);
analogWrite(pinbal, balans);
analogWrite(pinbas, bas);
analogWrite(pinint, inalte);
*/
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  Serial.println("Reglaj volum");
  delay(250);
}
}  // sfarsit nivel 0

if (nivel == 1)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  Serial.println("Reglaj balans");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  volum = volum - 8;
  Serial.println("Scade volumul");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  volum = volum + 8;
  Serial.println("Creste volumul");
  delay(250);
}

if (volum > 255) volum = 255;
if (volum <0) volum = 0;
analogWrite(pinvol, volum);
}  // sfarsit nivel 1


if (nivel == 2)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  Serial.println("Reglaj bas");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  balans = balans - 8;
  Serial.println("Balans spre stanga");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  balans = balans + 8;
  Serial.println("Balans spre dreapta");
  delay(250);
}

if (balans > 255) balans = 255;
if (balans <0) balans = 0;
analogWrite(pinbal, balans);
}  // sfarsit nivel 2

if (nivel == 3)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  Serial.println("Reglaj inalte");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  bas = bas - 8;
  Serial.println("Scade basul");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  bas = bas + 8;
  Serial.println("Creste basul");
  delay(250);
}

if (bas > 255) bas = 255;
if (bas <0) bas = 0;
analogWrite(pinbas, bas);
}  // sfarsit nivel 3
 

if (nivel == 4)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = 0;
  Serial.println("Functionare normala");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  inalte = inalte - 8;
  Serial.println("Scad inaltele");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  inalte = inalte + 8;
  Serial.println("Cresc inaltele");
  delay(250);
}

if (inalte > 255) inalte = 255;
if (inalte <0) inalte = 0;
analogWrite(pinint, inalte);
}  // sfarsit nivel 3
 

}  // sfarsit program principoal

