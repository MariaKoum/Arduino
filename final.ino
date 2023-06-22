/* Pin Definitions */
#define LED_1 D1
#define LED_2 D2
#define LED_3 D3
#define LED_4 D4
#define LED_5 D5
#define LED_6 D6
#define sensorPin A0 // Analog input pin that the sensor is attached to

/* Boolean variables to hold the status of the LED pins */
bool ledPin1Status;
bool ledPin2Status;
bool ledPin3Status;
bool ledPin4Status;
bool ledPin5Status;

/* Email libraries and settings */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "maria2001"
#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465
#define sender_email "5seansor@gmail.com"
#define sender_password "lbjikatyzwhfmtre"
#define Recipient_email "mariaakoumidou@gmail.com"

/* Define the triggerEvent() function */
void triggerEvent() {
  ESP_Mail_Session session;

  session.server.host_name = SMTP_server;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  message.sender.name = "SEaNSOR";
  message.sender.email = sender_email;
  message.subject = "SEaNSOR WARNING";
  message.addRecipient("WARNING: PLEASE CHECK THE MONITORED AREA", Recipient_email);

  // Send HTML message
  String htmlMsg = "<div style=\"color:#0000FF;\"><h1>This is an automated message send by SEaNSOR TEAM: PLEASE CHECK THE MONITORED AREA</h1><p> DEVICE CODE: PROTOTYPE</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  SMTPSession smtp;
  if (!smtp.connect(&session))
    return;

  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}

/* Setup function */
void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(sensorPin, INPUT);

  Serial.begin(115200);

  /* Wi-Fi Connection */
  Serial.println();
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("Wi-Fi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

/* Loop function */
void loop() {
  int sensorValue = analogRead(sensorPin);

  Serial.println(sensorValue);

  // Check sensor value and set LED status variables accordingly
  if (sensorValue > 555)
    ledPin1Status = 1;

  if (sensorValue > 558)
    ledPin2Status = 1;

  if (sensorValue > 560)
    ledPin3Status = 1;

  if (sensorValue > 562)
    ledPin4Status = 1;

  if (sensorValue > 564) {
    ledPin5Status = 1;
    
  }

 if (sensorValue > 580) {
    ledPin5Status = 1;
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH); // Set D6 LED HIGH when sensorValue is higher than 580
    delay(4000); // Keep D6 HIGH for 4 seconds
    triggerEvent(); // Call triggerEvent() when sensorValue is higher than 580
  }

  // Turn on LEDs based on LED status variables
  if (ledPin1Status == 1 || ledPin2Status == 1 || ledPin3Status == 1 || ledPin4Status == 1 || ledPin5Status == 1) {
    if (sensorValue > 555 || sensorValue < 537)
      digitalWrite(LED_1, HIGH);

    if (sensorValue > 558 || sensorValue < 534)
      digitalWrite(LED_2, HIGH);

    if (sensorValue > 560 || sensorValue < 534)
      digitalWrite(LED_3, HIGH);

    if (sensorValue > 562 || sensorValue < 531)
      digitalWrite(LED_4, HIGH);

    if (sensorValue > 564 || sensorValue < 528)
      digitalWrite(LED_5, HIGH);

    delay(200);

    // Reset LED status variables
    ledPin5Status = 0;
    ledPin4Status = 0;
    ledPin3Status = 0;
    ledPin2Status = 0;
    ledPin1Status = 0;
  }

  // Turn off all LEDs
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
}
