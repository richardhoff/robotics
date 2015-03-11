// Chair Pins
// |2 1|
// |4 3 
// |6 5 
// |8 7|

// 1 = 5V
// 2 = Left_Right 1
// 3 = 0V
// 4 = Fore_Aft 1
// 5 = Fore_Aft 2
// 6 = Center
// 7 = Left_Right 2
// 8 = Not connected
//yellow y axis
// blue x axis


int Reference_PWM  = 9;
int Fore_Aft_PWM   = 10;
int Left_Right_PWM = 11;

//int JazzyNeutral = 250; // Volts * 100
//int JazzyLower   = 111; // Volts * 100
//int JazzyUpper   = 389; // Volts * 100
//int JazzyNeutral = 320; // Volts * 100
//int JazzyLower   = 280; // Volts * 100
//int JazzyUpper   = 370; // Volts * 100
int JazzyNeutral = 195; // Volts * 100
int JazzyLower   = 90; // Volts * 100
int JazzyUpper   = 293; // Volts * 100

int PWMLower = 0;
int PWMUpper = 255;

int VoltsLower = 0;
int VoltsUpper = 500;

void setup() {
  Neutral(JazzyNeutral);
  delay(5000); // Allow time to turn on the control stalk
  Serial.begin(9600);
  while (! Serial); 
  Serial.println("Robot Is Online!");
  Serial.println("Chassis manual control");
  Serial.println("Enter Direction");
  Serial.println("  f");
  Serial.println("l s r");
  Serial.println("  b ");
}

void loop() 
{
  while(1)
  {
    if (Serial.available())
    {
      int direction = Serial.read();
      Serial.println("Moving");
      switch (direction)
      {
      case 'f':
        Serial.println("Forward");
        // Forward
        Fore_Aft(JazzyUpper);
        delay(5000);
        break;
      case 's':
        Serial.println("Stop");
        // Stop
        Left_Right(JazzyNeutral);
        Fore_Aft(JazzyNeutral);
        delay(5000);
        break;
      case 'b':
        Serial.println("Backward");
        // Reverse
        Fore_Aft(JazzyLower);
        delay(5000);
        break;
      case 'r':
        Serial.println("Right");    
        // Right
        Left_Right(JazzyUpper);
        delay(5000);
        break;
      case 'l':
        Serial.println("Left");
        // Left
        Left_Right(JazzyLower);
        delay(5000);
        break; 
      } 
    }
  }
}
void Neutral(int Volts){
  Reference(Volts);
  Fore_Aft(Volts);
  Left_Right(Volts);
}

void Reference(int Volts){
  int Pulses = map(Volts, VoltsLower, VoltsUpper, PWMLower, PWMUpper);
  analogWrite(Reference_PWM, Pulses);
}

void Fore_Aft(int Volts){
  int Pulses = map(Volts, VoltsLower, VoltsUpper, PWMLower, PWMUpper);
  analogWrite(Fore_Aft_PWM, Pulses);
}

void Left_Right(int Volts){
  int Pulses = map(Volts, VoltsLower, VoltsUpper, PWMLower, PWMUpper);
  analogWrite(Left_Right_PWM, Pulses);
}


