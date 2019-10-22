  /*
  // Adafruit Motor shield library
  // copyright Adafruit Industries LLC, 2009
  // this code is public domain, enjoy!
  // motor party
  
   Aangepast door Henk
   Werkt met motor shield L293D
  
  */
  
  #include <AFMotor.h>
  #include <Servo.h>
  #include <NewPing.h>
  #include <LiquidCrystal.h>
  AF_DCMotor motor1(1);
  AF_DCMotor motor2(2);
  AF_DCMotor motor3(3);
  AF_DCMotor motor4(4);
  Servo servo;
       #define USTrigger 26
       #define USEcho 28
       #define MaxDistance 400
       #define MAX_SPEED 255    // sets speed of DC traction motors to 180/256 or about 70% of full speed
      
           NewPing sonar(USTrigger, USEcho, MaxDistance);
   LiquidCrystal lcd(40, 38, 30, 32, 34, 36);

  int i;
   //------------------------  
 
    unsigned int duration;
    unsigned int distance;
    unsigned int FrontDistance;
    unsigned int LeftDistance;
    unsigned int RightDistance;
    unsigned int Time;
    unsigned int CollisionCounter;
  //---------------------------------------------------------- 
    int ledWitVoorRechts    =  49;
    int ledWitVoorLinks     =  47;
    int ledRoodAchterRechts =  51;
    int ledRoodAchterLinks  =  53;
    int ledFront            =  43;
    //int ledGrAchterRechts =  53;
    
   //------------------------------------- SETUP LOOP ----------
  
  void setup() 
  {
      pinMode(ledWitVoorRechts,   OUTPUT);  
      pinMode(ledWitVoorLinks,    OUTPUT);  
      pinMode(ledRoodAchterRechts,OUTPUT);  
      pinMode(ledRoodAchterLinks, OUTPUT);  
      pinMode(ledFront, OUTPUT);   
       // Serial.begin(115200);   
       // Serial.println("Motor test!");
//--------------lcd-----------------
    //lcd.begin(16, 2);
    //lcd.print("Motor test!");
//----------------------------------    
    servo.attach(10);
         
        motor1.setSpeed(255); // Links achter  set the speed to 150/255
        motor2.setSpeed(255); // Rechts achter   set the speed to 150/255
        motor3.setSpeed(255); // Rechts voor set the speed to 150/255
        motor4.setSpeed(255); // Links voor  set the speed to 150/255
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
  }
    
  //---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
  
  void loop() 
{
    lcd.setCursor(0, 1);
      //lcd.print(FrontDistance);                    //lcd.print(millis()/1000);
    
    moveForward();
    delay(100);      //500
    servo.write(90); //90 = face the front                  
      delay(100);    // was 500
    scan();          //Go to the scan function
      FrontDistance = distance;       
      delay(200);        //100
        //Serial.print("Front = ");
       //lcd.print(FrontDistance);
    
   if (FrontDistance > 50 || FrontDistance == 0) //If there is nothing infront of the robot within 40cm or the distance value is 0 
      {                                         //(which for the newping libary means no ping was returned) then... 
       moveForward();                          
      } 
      else                                      //Else (if there is something infront of the robot within 40cm) then...
      {
       CollisionCounter = CollisionCounter + 1; //Collision Counter - boting, teller
        moveStop();                                      
       moveBackward();
        navigate();
       } 
  }
  //-----------------------------------------------------------------------
 
   void moveStop()
   {
    motor1.run(RELEASE); 
    motor2.run(RELEASE); 
    motor3.run(RELEASE); 
    motor4.run(RELEASE);
      delay(100);
     return;
   }  
  //-------------------------------------------------------------------------------------------------------------------------------------
  void moveForward() 
   {
     for (i=0; i<255; i++) 
      digitalWrite(ledWitVoorRechts,   HIGH);       
      digitalWrite(ledWitVoorLinks,    HIGH);       
      digitalWrite(ledRoodAchterRechts,HIGH);        
      digitalWrite(ledRoodAchterLinks, HIGH);        
      digitalWrite(ledFront, HIGH);
      motor1.setSpeed(i);     // set the speed to 80/255
      motor2.setSpeed(i);     // set the speed to 175/255
      motor3.setSpeed(i);     // set the speed to 80/255
      motor4.setSpeed(255);     // set the speed to 175/255
                
      motor1.run(FORWARD); // Links achter     turn it on going forward
      motor2.run(FORWARD); // Rechts achter   turn it on going forward
      motor3.run(FORWARD); // Rechts voor      turn it on going forward
      motor4.run(FORWARD); // Links voor   turn it on going forward
        //delay(1000);
  }
  //-------------------------------------------------------------------------------------------------------------------------------------
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
      motor1.run(BACKWARD);  // Links achter     turn it on going backward
      motor2.run(BACKWARD);   // Rechts achter   turn it on going backward
      motor3.run(BACKWARD);   // Rechts voor      turn it on going backward
      motor4.run(BACKWARD);   // Links voor    turn it on going backward
        delay(50);
  //return;
  }  
  //-------------------------------------------------------------------------------------------------------------------------------------
  void moveRight() 
  {
           
      digitalWrite(ledWitVoorRechts,   HIGH);       
      digitalWrite(ledWitVoorLinks,    LOW);       
      digitalWrite(ledRoodAchterRechts,HIGH);        
      digitalWrite(ledRoodAchterLinks, LOW);     
     
      motor1.run(FORWARD); // Links achter    turn it on going forward
      motor2.run(RELEASE); // Rechts achter  turn it on going forward
      motor3.run(RELEASE); // Rechts voor     turn it on going forward
      motor4.run(FORWARD); // Links voor   turn it on going forward
       delay(1000);
  }
    //-------------------------------------------------------------------------------------------------------------------------------------
  void moveLeft() 
  {
      digitalWrite(ledWitVoorRechts,   LOW);       
      digitalWrite(ledWitVoorLinks,    HIGH);       
      digitalWrite(ledRoodAchterRechts,LOW);        
      digitalWrite(ledRoodAchterLinks, HIGH);    
     
     motor1.run(RELEASE);  // Links achter      turn it on going forward
     motor2.run(FORWARD);  // Rechts achter   turn it on going forward
     motor3.run(FORWARD);  // Rechts voor      turn it on going forward
     motor4.run(RELEASE);  // Links voor    turn it on going forward
       delay(1000); 
  }  
  //-------------------------------------------------------------------------------------------------------------------------------------
  void turnAround() 
 {
   motor1.run(FORWARD);     // Links achter    turn motor 1 forward
   motor2.run(RELEASE);     // Rechts achter   turn motor 2 backward
   motor3.run(RELEASE);     // Rechts voor    turn motor 1 forward
   motor4.run(FORWARD);     // Links voor   turn motor 2 backward
    delay(50); // run motors this way for 800ms
  }   
void scan()             //This function determines the distance things are away from the ultrasonic sensor
    {
      Time = sonar.ping(); 
      distance = Time / US_ROUNDTRIP_CM;
      delay(300); //was 500
    }
      void navigate()
    {
        servo.write(180);    // 160  
        delay(50);          // 500 
         scan();                                           
           
           LeftDistance = distance;    //Set the variable LeftDistance to the distance on the left
           delay(200);       // was 500
        lcd.begin(16, 2);//
        lcd.print("Left = ");     //Serial.print("Left = ");
        lcd.begin(0, 3);
        lcd.print(LeftDistance);  //Serial.println(LeftDistance);
           delay(100);        // 500
          servo.write(0);          //Move the servo to the right
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
     if(FrontDistance > 50  || FrontDistance == 0)  //If there is nothing infront robot within 40cm or the distance value is 0 
    {                                            
       moveForward();                                   
     } 
      else                                 //Else (if there is something infront of the robot within 40cm) then...
     {
       CollisionCounter = CollisionCounter + 1;
        moveStop();                        //Go to the moveStop function
          scan;
     }
       if(RightDistance < LeftDistance )//< RightDistance )     //if(analog_in (is greater than) 5);
      {
          moveRight();                                 
          delay(100);                      // 220 || 100 Pause the program for 200 milliseconds to let the robot reverse
      }
         else                               //  < If the distance on the right is less than that on the left then...
        {
           moveLeft();                                    
           delay(100);                                     
        }
 
   
    }  
      

    