int sensorPin = A0;      //pin number to use the ADC
#define COEFNUM 81
#define PI 3.14159265359
unsigned int num = 81;
unsigned long time = 0;
unsigned long a = 0;
float y[COEFNUM];
int sensorValue[COEFNUM];
float h[COEFNUM];

float coef_high[81] = {0.0003, 0.0005, 0.0006, 0.0008, 0.0009, 0.0009, 0.0009, 0.0007, 0.0004, -0.0001, -0.0008, -0.0017, -0.0025, -0.0034, -0.0041, -0.0044, 
-0.0043, -0.0036, -0.0023, -0.0004, 0.0021, 0.0051, 0.0082, 0.0111, 0.0135, 0.0149, 0.0150, 0.0134, 0.0099, 0.0042, 
-0.0035, -0.0130, -0.0242, -0.0363, -0.0490, -0.0613, -0.0727, -0.0823, -0.0898, -0.0944, 0.9038, -0.0944, -0.0898, -0.0823, -0.0727, -0.0613, -0.0490, -0.0363, -0.0242, -0.0130, -0.0035, 0.0042, 0.0099, 0.0134, 0.0150, 0.0149, 0.0135, 0.0111, 0.0082, 0.0051, 0.0021, -0.0004, -0.0023, -0.0036, -0.0043, -0.0044, -0.0041, -0.0034, -0.0025, -0.0017, -0.0008, -0.0001, 0.0004, 0.0007, 0.0009, 0.0009, 0.0009, 0.0008, 0.0006, 0.0005, 0.0003};
float coef2_high[81] = {-0.0004, -0.0003, -0.0001, 0.0002, 0.0005, 0.0008, 0.0011, 0.0014, 0.0016, 0.0016, 0.0013, 0.0007,
-0.0003, -0.0014, -0.0028, -0.0041, -0.0052, -0.0059, -0.0059, -0.0051, -0.0033, -0.0005, 0.0030, 0.0070, 0.0110,
0.0146, 0.0170, 0.0178, 0.0163, 0.0122,    0.0053,   -0.0044,   -0.0165,   -0.0306,   -0.0458,   -0.0612,
-0.0757, -0.0882, -0.0980, -0.1041, 0.8943, -0.1041, -0.0980, -0.0882, -0.0757, -0.0612, -0.0458, -0.0306,
-0.0165, -0.0044, 0.0053, 0.0122, 0.0163, 0.0178, 0.0170, 0.0146, 0.0110, 0.0070, 0.0030, -0.0005,
-0.0033, -0.0051, -0.0059, -0.0059, -0.0052, -0.0041, -0.0028, -0.0014, -0.0003, 0.0007, 0.0013, 0.0016,
0.0016, 0.0014, 0.0011, 0.0008, 0.0005, 0.0002, -0.0001, -0.0003, -0.0004};
float coef_low[81] = {0.0006, 0.0006, 0.0002, -0.0004, -0.0009, -0.0008, -0.0001, 0.0010, 0.0017, 0.0013, -0.0003, -0.0021,
-0.0030, -0.0018, 0.0012, 0.0042, 0.0048, 0.0020, -0.0033, -0.0074, -0.0071, -0.0013, 0.0069, 0.0121,
0.0095, -0.0009, -0.0132, -0.0189, -0.0118, 0.0060, 0.0243, 0.0296, 0.0137, -0.0182, -0.0482, -0.0526,
-0.0150, 0.0625, 0.1573, 0.2352, 0.2652, 0.2352, 0.1573, 0.0625, -0.0150, -0.0526, -0.0482, -0.0182,
0.0137, 0.0296, 0.0243, 0.0060, -0.0118, -0.0189, -0.0132, -0.0009, 0.0095, 0.0121, 0.0069, -0.0013,
-0.0071, -0.0074, -0.0033, 0.0020, 0.0048, 0.0042, 0.0012, -0.0018, -0.0030, -0.0021, -0.0003,  0.0013,
0.0017, 0.0010, -0.0001, -0.0008, -0.0009, -0.0004, 0.0002, 0.0006, 0.0006};
float coef_bp[81] = { 0.0001, 0.0003, 0.0001, -0.0002, -0.0004, -0.0000, 0.0010, 0.0024, 0.0032, 0.0028, 0.0010, -0.0015, -0.0032, -0.0032, 
-0.0015, 0.0001, -0.0004, -0.0039, -0.0091, -0.0125, -0.0103, -0.0019, 0.0099, 0.0190,  0.0205, 0.0137, 0.0038, -0.0011, 0.0045, 0.0182, 0.0296, 
0.0252, -0.0028, -0.0488, -0.0939, -0.1136, -0.0905, -0.0256, 0.0595, 0.1311, 0.1590, 0.1311, 0.0595, -0.0256, -0.0905, -0.1136, -0.0939, -0.0488, 
-0.0028, 0.0252, 0.0296, 0.0182, 0.0045, -0.0011, 0.0038, 0.0137, 0.0205, 0.0190, 0.0099, -0.0019, -0.0103, -0.0125, -0.0091, -0.0039, -0.0004, 0.0001, 
-0.0015, -0.0032, -0.0032, -0.0015, 0.0010, 0.0028, 0.0032, 0.0024, 0.0010, -0.0000, -0.0004, -0.0002, 0.0001, 0.0003, 0.0001};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  
  int i = 0;
  int v = 0;
  int j = 0;

  for (i = 0; i < num; i++) {
     sensorValue[i] = analogRead(sensorPin);    //read the sensor value using ADC
     Serial.print(sensorValue[i]);
     //Serial.print(" ");
     //Serial.println(i);
     //delay(0.5);
   }
  
  /*for (v = 0; v < COEFNUM; v++)
  {
      window[j] = 0.54 + 0.46 * cos(j*PI/COEFNUM);
      h[j] = coef[v] * window[j];
      j++;
  }*/
}

void loop() {
  //time = 0;
  //time = micros();
  // put your main code here, to run repeatedly:
  int n = 0;
  int k = 0;
  int i = 0;

  y[80] = 0;
  for (n = 80; n >= 0; n--) 
   {
      y[80] += sensorValue[n] * coef_bp[n]; 
   }
  
  Serial.print(y[80], 5);
  Serial.print(",");
  Serial.println(sensorValue[80]);

  int temp[1];

  temp[0] = analogRead(sensorPin);

  
  for (int k = 0; k < COEFNUM - 1; k++) 
  {
    sensorValue[k] = sensorValue[k + 1];
  }
  sensorValue[80] = temp[0];*/
  
  //a = micros();
  //Serial.println(a - time);
}
