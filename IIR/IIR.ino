int sensorPin = A0;
unsigned long time = 0;
unsigned long count = 0;
unsigned long analog = 0;
unsigned long old = 0;
unsigned long rez = 0;
unsigned long c = 0;
int x[3] = {0,0,0};
float y[3] = {0,0,0};
float z[3] = {0,0,0};
float bl[3] = {0.0295, 0.0589, 0.0295};
float bh[3] = {0.8958,-1.7915, 0.8958};
float al[3] = {1.0000, -1.4591, 0.5770};
float ah[3] = {1.0000, -1.7807, 0.8024};
float bBP[3] = {0.1050, 0, -0.1050};
float aBP[3] = {1.0000, -1.7359, 0.7901};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  int i = 0;

  for (i = 0; i < 3; i++) {
     x[i] = analogRead(sensorPin);    //read the sensor value using ADC
     //Serial.println(x[i]);
    }

  y[0] = 0 + bl[0]*x[0];
  y[1] = bl[1]*x[0] + bl[0]*x[1] - al[1]*y[0];
  y[2] = bl[2]*x[0] + bl[1]*x[1] + bl[0]*x[2] - al[2]*y[0] - al[1]*y[1];
  //y[3] = b[3]*x[0] + b[2]*x[1] + b[1]*x[2] + b[0]*x[3] - a[3]*y[0] - a[2]*y[1] - a[1]*y[2];
  //y[4] = b[4]*x[0] + b[3]*x[1] + b[2]*x[2] + b[1]*x[3] + b[0]*x[4] - a[4]*y[0] - a[3]*y[1] - a[2]*y[2] - a[1]*y[3];
  //y[5] = b[5]*x[0] + b[4]*x[1] + b[3]*x[2] + b[2]*x[3] + b[1]*x[4] + b[0]*x[5] - a[5]*y[0] - a[4]*y[1] - a[3]*y[2] - a[2]*y[3] - a[1]*y[4];
}

void loop() {
  // put your main code here, to run repeatedly:
  time = 0;
  time = micros();
  count = count + 1;

  if (((z[0] && z[1] && z[2]) == 0) && (count == 1))
  {
    z[0] = 0 + bh[0]*y[0];
    z[1] = bh[1]*y[0] + bh[0]*y[1] - ah[1]*z[0];
    z[2] = bh[2]*y[0] + bh[1]*y[1] + bh[0]*y[2] - ah[2]*z[0] - ah[1]*z[1];
  }

  Serial.print(z[2]);
  Serial.print(",");
  Serial.println(x[2]);


  int temp[1];

  temp[0] = analogRead(sensorPin);
  old = analog;
  analog = micros();
  //Serial.println(analog - old);

  for (int k = 0; k < 3 - 1; k++) 
  {
    x[k] = x[k + 1];
    y[k] = y[k + 1];
    z[k] = z[k + 1];
  }

  x[2] = temp[0];
  //y[3] = 2 + 12 + 3 + 4 + 7 + 7 + 4;
  //y[1] = b[1]*x[0] + b[0]*x[1] - a[1]*y[0];
  y[2] = bl[2]*x[0] + bl[1]*x[1] + bl[0]*x[2] - al[2]*y[0] - al[1]*y[1];
  z[2] = bh[2]*y[0] + bh[1]*y[1] + bh[0]*y[2] - ah[2]*z[0] - ah[1]*z[1];
  //y[3] = b[3]*x[0] + b[2]*x[1] + b[1]*x[2] + b[0]*x[3] - a[3]*y[0] - a[2]*y[1] - a[1]*y[2];
  //y[5] = b[5]*x[0] + b[4]*x[1] + b[3]*x[2] + b[2]*x[3] + b[1]*x[4] + b[0]*x[5] - a[5]*y[0] - a[4]*y[1] - a[3]*y[2] - a[2]*y[3] - a[1]*y[4];
  //y[4] = b[4]*x[0] + b[3]*x[1] + b[2]*x[2] + b[1]*x[3] + b[0]*x[4] - a[4]*y[0] - a[3]*y[1] - a[2]*y[2] - a[1]*y[3];

  c = micros();
  //Serial.println(c - time);
}
