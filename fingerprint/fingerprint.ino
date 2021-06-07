#include "FPS_GT511C3.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial SIM800(6, 7); // RX, TX
#define SS_RX 10
#define SS_TX 11

FPS_GT511C3 fps(SS_RX, SS_TX); // (Arduino SS_RX, Arduino SS_TX)

byte inChar, inByte;

const byte buflen1 = 16;
const byte buflen2 = 12;
const byte buflen3 = 8;
// creating struct to store customer data
struct customer_data {
  char customer_name[buflen1];
  char customer_number[buflen2];
  char customer_balance[buflen3];
};

customer_data data[5]; //data[0].customer_name; for testing keeping only 5
// depending your fingerprint sensor you can set it to 20 or 200

customer_data tempData;
const byte buflen = buflen1  + buflen2 + buflen3;

byte decision = 0;

const byte IN2 = 15;        //A1 arduino pin connected to motor driver IN1 pin
const byte IN1 = 14;        //A0 arduino pin connected to motor driver IN2 pin
const byte statusLed = 13;   //D13 arduino pin connected to onboard led

void setup() {
  // put your setup code here, to run once:
  SIM800.begin(9600);   // setting the baud rate of GSM module
  Serial.begin(9600); //set up Arduino's hardware serial UART
  fps.UseSerialDebug = false; // so you can't see the messages in the serial debug screen
  fps.Open(); //send serial command to initialize fps

  fingerPrintBlink(2);
  fps.SetLED(true);   //turn on LED so fps can see fingerprint

  pinMode(statusLed, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //Serial.print(F("Buffer Length:- "));
  //Serial.println(buflen);
  Serial.println(F("-------------- Welcome to Secure APNA Central Banking ----------------"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( decision == 0) {
    Serial.println(F("Enter Choice to Perform Operations:"));
    Serial.println(F("1. Enrolling"));
    Serial.println(F("2. Checking"));
    Serial.println(F("3. Deleting Single BioMetrics"));
    Serial.println(F("4. Deleting All BioMetrics"));
    Serial.println(F("5. Banking"));
    while (!Serial.available()) {};
    // Read serial input:
    while (Serial.available() > 0) {
      inChar = Serial.read();

      switch (inChar) {
        case '1':
          Enroll();
          digitalWrite(statusLed, HIGH);
          delay(1000);
          digitalWrite(statusLed, LOW);
          break;

        case '2':
          Check();
          digitalWrite(statusLed, HIGH);
          delay(1000);
          digitalWrite(statusLed, LOW);
          break;

        case '3':
          Serial.println(F("Deleting Single Enroll ID"));
          DeleteFingerPrint();
          digitalWrite(statusLed, HIGH);
          delay(1000);
          digitalWrite(statusLed, LOW);
          break;

        case '4':
          Serial.println(F("Deleting All Enroll ID's"));
          DeleteAllFingerprintID();
          digitalWrite(statusLed, HIGH);
          delay(1000);
          digitalWrite(statusLed, LOW);
          break;

        case '5':
          decision = 1;
          BankingOperation();
          digitalWrite(statusLed, HIGH);
          delay(1000);
          digitalWrite(statusLed, LOW);
          break;

        default :
          Serial.println(F("Please Select Valid Option!"));
          break;
      }
    }
  }
  else {
    Serial.println(F("-------------- Welcome to Secure APNA Central Banking ----------------"));
    BankingOperation();
  }
  delay(1);
}



void fingerPrintBlink(int times)
{
  for (int i = 0; i < times; i++)
  {
    // FPS Blink LED Test
    fps.SetLED(true); // turn on the LED inside the fps
    delay(500);
    fps.SetLED(false);// turn off the LED inside the fps
    delay(500);
  }
}

void recCustomerDetails(int EnrollId)
{
  String stringData;
  Serial.print(F("Enter Customer Name: "));

  while (!Serial.available());

  // Read serial input:
  while (Serial.available() > 0) {
    stringData = Serial.readString();
    stringData.trim();
    //Serial.print(F("String: "));
    Serial.println(stringData);
    stringData.toCharArray(data[EnrollId].customer_name, buflen1);
  }

  Serial.print(F("Enter Customer Mobile No.: "));

  while (!Serial.available());

  // Read serial input:
  while (Serial.available() > 0) {
    stringData = Serial.readString();
    stringData.trim();
    //Serial.print(F("String: "));
    Serial.println(stringData);
    stringData.toCharArray(data[EnrollId].customer_number, buflen2);
  }

  Serial.print(F("Enter Customer Balance: "));

  while (!Serial.available());

  // Read serial input:
  while (Serial.available() > 0) {
    stringData = Serial.readString();
    stringData.trim();
    //Serial.print(F("String: "));
    Serial.println(stringData);
    stringData.toCharArray(data[EnrollId].customer_balance, buflen3);
  }

  int addrr = EnrollId * buflen;
  EEPROM.put(addrr, data[EnrollId]);
}

void Enroll()
{
  // Enroll test

  // find open enroll id
  int enrollid = -1;
  bool usedid = true;
  String EnrollIdString = "", stringData = "";
  int recData = -1;

  Serial.print(F("Enter the Enroll ID: "));
  delay(1000);

  while (!Serial.available());

  // Read serial input:
  while (Serial.available() > 0) {
    EnrollIdString = Serial.readString();
    enrollid = EnrollIdString.toInt();
    Serial.println(enrollid);
  }

  usedid = fps.CheckEnrolled(enrollid);

  if (usedid == true)
  {
    Serial.println(F("The Enroll Id is Previously Enrolled!!"));
    Serial.println(F("If you want to go ahead press 1 or if you want to cancel press 0"));

    while (!Serial.available());

    // Read serial input:
    while (Serial.available() > 0) {
      stringData = Serial.readString();
      //Serial.print("Int Value: ");
      recData = stringData.toInt();
      //Serial.println(recData);
    }

    if (recData == 1)
    {
      Serial.println(F("You pressed 1!!"));
      DeleteFingerPrintId(enrollid);
    }
    else if (recData == 0)
    {
      Serial.println(F("You pressed 0!!"));
    }

  }
  else
  {
    recData = 1;
    Serial.println(F("The Enroll Id is not Previously Enrolled!!"));
  }

  if (recData == 1)
  {
    Serial.println(F("Let's Start Enrolling Process: "));

    fps.EnrollStart(enrollid);

    // enroll
    Serial.print(F("Press finger to Enroll #"));
    Serial.println(enrollid);
    while (fps.IsPressFinger() == false) delay(100);
    bool bret = fps.CaptureFinger(true);
    int iret = 0;
    if (bret != false)
    {
      Serial.println(F("Remove finger"));
      fps.Enroll1();
      while (fps.IsPressFinger() == true) delay(100);
      Serial.println(F("Press same finger again"));
      while (fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        Serial.println(F("Remove finger"));
        fps.Enroll2();
        while (fps.IsPressFinger() == true) delay(100);
        Serial.println(F("Press same finger yet again"));
        while (fps.IsPressFinger() == false) delay(100);
        bret = fps.CaptureFinger(true);
        if (bret != false)
        {
          Serial.println(F("Remove finger"));
          iret = fps.Enroll3();
          if (iret == 0)
          {
            Serial.println(F("Enrolling Successful"));
            recCustomerDetails(enrollid);
          }
          else
          {
            Serial.print(F("Enrolling Failed with error code:"));
            Serial.println(iret);
          }
        }
        else Serial.println(F("Failed to capture third finger"));
      }
      else Serial.println(F("Failed to capture second finger"));
    }
    else Serial.println(F("Failed to capture first finger"));
  }
  else
  {
    Serial.println(F("You cancelled!!"));
  }
  Serial.println(F("******************************************************************************"));
}


void Check()
{
  /*
     Note : GT-511C3 can hold 200 fingerprint templates.
     GT-511C1R can hold 20 fingerprint templates.
     Make sure to change the id depending on what model you are using
  */

  // Identify fingerprint test
  Serial.println(F("Please press finger"));

  while (fps.IsPressFinger() == false) delay(100);

  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id < 200)
    {
      Serial.print(F("Verified ID:"));
      Serial.println(id);
      int addrr = id * buflen;
      EEPROM.get(addrr, tempData);
      String Cstname = tempData.customer_name;
      Serial.println(Cstname);
      String Cstkey = tempData.customer_number;
      Serial.println(Cstkey);
      String Cstbalance = tempData.customer_balance;
      Serial.println(Cstbalance);
    }
    else
    {
      Serial.println(F("Finger not found"));
    }
  }

  delay(100);
  Serial.println(F("******************************************************************************"));
}


void DeleteFingerPrintId(int enrollid)
{
  bool erased = fps.DeleteID(enrollid);
  if (erased == true)
  {
    Serial.print(F("Deleted the Enroll ID:- "));
    Serial.println(enrollid);
  }
}

void DeleteAllFingerprintID(void)
{
  bool erased = fps.DeleteAll();
  if (erased == true)
  {
    Serial.println(F("Deleted all the Enroll ID's"));
  }
  Serial.println(F("******************************************************************************"));
}

void DeleteFingerPrint(void)
{
  String EnrollIdString = "";
  int enrollid = -1;

  Serial.print(F("Enter the Enroll ID: "));
  delay(1000);

  while (!Serial.available());

  // Read serial input:
  while (Serial.available() > 0) {
    EnrollIdString = Serial.readString();
    enrollid = EnrollIdString.toInt();
    Serial.println(enrollid);
  }

  DeleteFingerPrintId(enrollid);
  Serial.println(F("******************************************************************************"));

}

void cashDispense() {
  digitalWrite(statusLed, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(2000);
  digitalWrite(statusLed, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
}

void sendOtpMessage(int genOTP, String number) {
  String msg = "";
  msg = "Your OTP is :" + String(genOTP) + " From APNA Central Bank, Do not share your OTP";
  Serial.println(msg);

  String cmd = "";
  SIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);     // Delay of 1000 milli seconds or 1 second
  cmd = "AT+CMGS=\""  + number + "\"";
  SIM800.println(cmd);
  delay(1000);

  SIM800.println(msg);   // The SMS text you want to send
  delay(100);
  SIM800.println((char)26); // ASCII code of CTRL + Z
  delay(2000);
}

void sendUpdatedBalance(String currentBal, String deduction, String number) {
  String msg = "";
  msg = "Amount " + String(deduction) + "INR has withdrawn using xyzATM " + ", current Balance is INR" + String(currentBal) + " of Account No.xxxxxxxx678, APNA Central Bank";
  Serial.println(msg);

  String cmd = "";
  SIM800.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);     // Delay of 1000 milli seconds or 1 second
  cmd = "AT+CMGS=\""  + number + "\"";
  SIM800.println(cmd);
  delay(1000);

  SIM800.println(msg);   // The SMS text you want to send
  delay(100);
  SIM800.println((char)26); // ASCII code of CTRL + Z
  delay(2000);
}

void BankingOperation() {
  Serial.println(F("Select Choice:"));
  Serial.println(F("1.Balance Enquiry"));
  Serial.println(F("2.Cash Withdraw"));

  while (!Serial.available());
  char tempstr;
  // Read serial input:
  while (Serial.available() > 0) {
    tempstr = Serial.read();
  }

  switch (tempstr) {
    case '1': Serial.println(F("\nBalance Enquiry"));
      verifyCustomer(1);
      break;
    case '2': Serial.println(F("\nCash Withdraw"));
      verifyCustomer(2);
      break;
  }

}

void verifyCustomer(byte opChoice)
{

  String stringData;
  // Identify fingerprint test
  unsigned int otpvalue, tempotp, amtwithdraw;
  /*
     Note : GT-511C3 can hold 200 fingerprint templates.
     GT-511C1R can hold 20 fingerprint templates.
     Make sure to change the id depending on what model you are using
  */

  // Identify fingerprint test
  Serial.println(F("Please press finger"));

  while (fps.IsPressFinger() == false) delay(100);

  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    int addrr = id * buflen;
    EEPROM.get(addrr, tempData);
    String CstRegNum = tempData.customer_number;
    if (id < 5)       // for testing we are using only 5 but here also depending on your finger module you can change it
    {
      otpvalue = random(1000, 9999);
      //Serial.println(otpvalue);
      sendOtpMessage(otpvalue, CstRegNum);
      Serial.println(F("Please Enter OTP sent to Registered Number "));
      //Serial.print(F("Enter OTP: "));
      delay(2000);
    }
    else
    {
      Serial.println(F("No Record found"));
      return;
    }

    while (!Serial.available());

    // Read serial input:
    while (Serial.available() > 0) {
      stringData = Serial.readString();
      stringData.trim();
      Serial.println(stringData);
      tempotp = stringData.toInt();
    }

    if (otpvalue == tempotp) {       // OTP validity check
      if (opChoice == 1) {
        Serial.print(F("Account ID:"));
        Serial.println(id);
        String Cstname = tempData.customer_name;
        String Cstbalance = tempData.customer_balance;
        Serial.print(F("Customer Name: ")); Serial.println(Cstname);
        Serial.print(F("Account Balance: ")); Serial.println(Cstbalance);
      }

      if (opChoice == 2) {
        String Cstname = tempData.customer_name;
        String Cstbalance = tempData.customer_balance;
        //Serial.println(Cstname);
        //Serial.println(Cstbalance);

        Serial.println(F("Enter Amount to Withdraw(in multiple 100, 500, 2000)"));
        while (!Serial.available());
        // Read serial input:
        while (Serial.available() > 0) {
          stringData = Serial.readString();
          stringData.trim();
          Serial.println(stringData);
          Serial.println("wait...");
          delay(2000);
          if (stringData.toInt() > Cstbalance.toInt()) {
            Serial.println(F("Insufficient Balance"));
            delay(1000);
          }
          else {
            Cstbalance = (Cstbalance.toInt() - stringData.toInt());
            cashDispense();
            //Serial.println(Cstbalance);
            Serial.println(F("Collect Your Cash"));
            delay(2000);
            Serial.println(F("Thank You!"));

            //Cstname.toCharArray(data[id].customer_name,buflen1);
            //stringData.toCharArray(data[id].customer_number,buflen2);
            Cstbalance.toCharArray(data[id].customer_balance, buflen3);
            addrr = addrr + buflen1 + buflen2;
            EEPROM.put(addrr, data[id].customer_balance);
            sendUpdatedBalance(Cstbalance, stringData, CstRegNum);

          }

        }

      }

    }
    else {
      Serial.println(F("Invalid OTP"));
    }


  }

  delay(100);
  Serial.println(F("******************************************************************************"));
}
