SYSTEM_THREAD(ENABLED);

volatile int counter = 0;
os_thread_t thread1; //defined the first thread
os_thread_t thread2; //defined the second thread
os_thread_t thread3; //defined the third thread

void setup()
{
  Serial.begin(9600);
  pinMode(D7, OUTPUT);
  os_thread_create(&thread1, "myThread1", OS_THREAD_PRIORITY_DEFAULT, myThread1, NULL, 1024); //creates the first thread
  os_thread_create(&thread2, "myThread2", OS_THREAD_PRIORITY_DEFAULT, myThread2, NULL, 1024); //creates the second thread
  os_thread_create(&thread3, "myThread3", OS_THREAD_PRIORITY_DEFAULT, myThread3, NULL, 1024); //creats the third thread
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.
  while (true)
  {
    WITH_LOCK(Serial) //ensures only one thread has access to the serial monitor at once
    {
    }
  }
}

void myThread1(void *args) //thread 1 randomizes a number
{
  while (1)
  {
    double random = rand() % 10 + 1;
    String output = "Thread 1 output: ";
    output += (String)random;
    WITH_LOCK(Serial)
    {
      Serial.println(output);
    }
    delay(1000);
  }
}

void myThread2(void *args) //void 2 adds 1 to a counter
{
  while (1)
  {
    counter += 1;
    String output = "Thread 2 output: ";
    output += (String)counter;
    WITH_LOCK(Serial)
    {
      Serial.println(output);
    }
    delay(500);
  }
}

void myThread3(void *args) //void three flashes the onboard LED
{
  while (1)
  {
    digitalWrite(D7, HIGH);
    delay(125);
    digitalWrite(D7, LOW);
    delay(125);
    //WITH_LOCK(Serial)
    //{
    //Serial.println("Flashing Onboard LED!"); //commented out because it wrote a lot of unneeded information to the serial monitor.
    // }
  }
}