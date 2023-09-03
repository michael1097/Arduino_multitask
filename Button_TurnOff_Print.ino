#define PIN  32
#define button  0

bool on_off = false;
int state = 0;

void Task1code( void * parameter) {

  while(1){

    if(on_off == false){
      Serial.print("Voltaje:");
      Serial.println(analogRead(PIN)); 
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Task2code( void * parameter) {
  while(1){
    switch(state){
      case 0:
        if (digitalRead(button) == 0){
          Serial.println("Press");
          state = 1; 
        }else state = 0;
        break;

      case 1:
        if (digitalRead(button) == 1) state = 2;
        else state = 1; 
        break;

      case 2:
        if(on_off==true)Serial.println("On");
        else Serial.println("Off");

        on_off = !on_off;
        state = 0;
        break;
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
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
