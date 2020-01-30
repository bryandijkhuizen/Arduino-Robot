  #include <AFMotor.h>
  #include <Servo.h>
  #include <NewPing.h>
  #include <LiquidCrystal.h>

  #define USTrigger 26
  #define USEcho 28
  #define MaxDistance 400
  #define MAX_SPEED 255

  AF_DCMotor motor1(1);
  AF_DCMotor motor2(2);
  AF_DCMotor motor3(3);
  AF_DCMotor motor4(4);

  Servo servo;

  NewPing sonar(USTrigger, USEcho, MaxDistance);
  LiquidCrystal lcd(40, 38, 30, 32, 34, 36);

  int i;
  unsigned int duration, distance, FrontDistance, LeftDistance, RightDistance, Time, CollisionCounter;

  int ledWitVoorRechts    =  49;
  int ledWitVoorLinks     =  47;
  int ledRoodAchterRechts =  51;
  int ledRoodAchterLinks  =  53;
  int ledFront            =  43;

  void setup() 
  {
      pinMode(ledWitVoorRechts,   OUTPUT);
      pinMode(ledWitVoorLinks,    OUTPUT);  
      pinMode(ledRoodAchterRechts,OUTPUT);  
      pinMode(ledRoodAchterLinks, OUTPUT);  
      pinMode(ledFront, OUTPUT);
      servo.attach(10);
         
      motor1.setSpeed(255); // Links achter
      motor2.setSpeed(255); // Rechts achter
      motor3.setSpeed(255); // Rechts voor
      motor4.setSpeed(255); // Links voor

      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);

  }
    
  //---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
  
  void loop()
  {
    lcd.setCursor(0, 1);
    
    moveForward();

    delay(100);

    servo.write(90);

    delay(100);

    scan();

    FrontDistance = distance;

    delay(200);
    
    if (FrontDistance > 50 || FrontDistance == 0)
    {
        moveForward();
    } else {
        CollisionCounter = CollisionCounter + 1;
        moveStop();                                      
        moveBackward();
        navigate();
    }
  }
 
   void moveStop()
   {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      delay(100);
      return;
   }

   void moveForward()
   {
     for (i=0; i<255; i++)
      digitalWrite(ledWitVoorRechts,   HIGH);
      digitalWrite(ledWitVoorLinks,    HIGH);
      digitalWrite(ledRoodAchterRechts,HIGH);        
      digitalWrite(ledRoodAchterLinks, HIGH);        
      digitalWrite(ledFront, HIGH);
      motor1.setSpeed(i);     
      motor2.setSpeed(i);    
      motor3.setSpeed(i);    
      motor4.setSpeed(255);  
                
      motor1.run(FORWARD); // Links achter    
      motor2.run(FORWARD); // Rechts achter
      motor3.run(FORWARD); // Rechts voor   
      motor4.run(FORWARD); // Links voor
  }

  void moveBackward()
  {
      for (i=0; i<200; i++)
       digitalWrite(ledWitVoorRechts,   LOW);
       digitalWrite(ledWitVoorLinks,    LOW);
       digitalWrite(ledRoodAchterRechts,HIGH);
       digitalWrite(ledRoodAchterLinks, HIGH);
        delay(100);

       motor1.setSpeed(i); // set the speed to 80/255
       motor2.setSpeed(i);
       motor3.setSpeed(i); // set the speed to 80/255
       motor4.setSpeed(i);
       motor1.run(BACKWARD);  // Links achter
       motor2.run(BACKWARD);   // Rechts achter
       motor3.run(BACKWARD);   // Rechts voor
       motor4.run(BACKWARD);   // Links voor
        delay(50);
  }

  void moveRight()
  {
      digitalWrite(ledWitVoorRechts,   HIGH);
      digitalWrite(ledWitVoorLinks,    LOW);       
      digitalWrite(ledRoodAchterRechts,HIGH);        
      digitalWrite(ledRoodAchterLinks, LOW);     
     
      motor1.run(FORWARD); // Links achter 
      motor2.run(RELEASE); // Rechts achter
      motor3.run(RELEASE); // Rechts voor     
      motor4.run(FORWARD); // Links voor  
       delay(1000);
  }

  void moveLeft()
  {
      digitalWrite(ledWitVoorRechts,   LOW);
      digitalWrite(ledWitVoorLinks,    HIGH);       
      digitalWrite(ledRoodAchterRechts,LOW);        
      digitalWrite(ledRoodAchterLinks, HIGH);    

      motor1.run(RELEASE);  // Links achter
      motor2.run(FORWARD);  // Rechts achter
      motor3.run(FORWARD);  // Rechts voor
      motor4.run(RELEASE);  // Links voor
       delay(1000); 
  }  

  void turnAround()
  {
   motor1.run(FORWARD);     // Links achter    
   motor2.run(RELEASE);     // Rechts achter   
   motor3.run(RELEASE);     // Rechts voor    
   motor4.run(FORWARD);     // Links voor 
    delay(50); 
  }

  void scan()
  {
      Time = sonar.ping(); 
      distance = Time / US_ROUNDTRIP_CM;
      delay(300);
  }

  void navigate()
  {
      servo.write(180);
      delay(50);
      scan();
           
      LeftDistance = distance;
      delay(200);

      lcd.begin(16, 2);
      lcd.print("Left = ");
      lcd.begin(0, 3);
      lcd.print(LeftDistance);
      delay(100);
      servo.write(0);
      delay(100);
      scan();
        
      RightDistance = distance;     //Set the variable RightDistance to the distance on the right
      delay(200);    // was 500
      Serial.print("Right = ");
      Serial.println(RightDistance);
      servo.write(80);
      delay(100);   // was 500 wait
      scan();
      FrontDistance = distance;

     if(FrontDistance > 50  || FrontDistance == 0)
     {
       moveForward();
     } else {
       CollisionCounter = CollisionCounter + 1;
       moveStop();
       scan;
     }

     if(RightDistance < LeftDistance )
     {
         moveRight();
         delay(100);
      }
     
    }  
      

    
