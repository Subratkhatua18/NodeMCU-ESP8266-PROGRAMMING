void setup() {
// put your setup code here, to run once:
pinMode(0,INPUT); //pin pushbutton
pinMode(2,OUTPUT);
pinMode(16,OUTPUT); //pin LED
}
void loop() {
int a=digitalRead(0);
if(a==0)
{
digitalWrite(2,HIGH);
}
else
{
digitalWrite(2,LOW);
}
 digitalWrite(16,HIGH);
  delay(200);
  digitalWrite(16,LOW);
  delay(200);
}