#define PIN  32
#define button  0

void Task1code( void * parameter) {

  while(1){
    Serial.print("Voltaje:");
    Serial.println(analogRead(PIN)); 
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }

void Task2code( void * parameter) {
  while(1){
    Serial.print("Estado:");
    Serial.println(digitalRead(button)); 
    vTaskDelay(50/portTICK_PERIOD_MS); 
    }
  }

void setup() {

  TaskHandle_t Task1,Task2;
  
  Serial.begin(115200);
  // Built in led pint as outpt
  pinMode(PIN,OUTPUT);   
  pinMode(PIN,INPUT);   


  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1); /* Core where the task should run */

  xTaskCreatePinnedToCore(
      Task2code, /* Function to implement the task */
      "Task2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task2,  /* Task handle. */
      0); /* Core where the task should run */
}

void loop() {
  // put your main code here, to run repeatedly:
 vTaskDelete(NULL);
}
