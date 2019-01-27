
#include <OLED_I2C.h> 

OLED  myOLED(SDA, SCL); 

extern uint8_t SmallFont[]; 
int x=0; 
int artirma=0; 
int ok=0;
int y_eksen=15;
int x_eksen=0;
 int diger=1;
 int diger_1=1;
 int diger_12=1;
 int i=0;
 int referans=30;
 int kp1=0;
 float ki1=0.0;
 float kd1=0.0;
 int ui0=0;
int hata0=0;
void setup()
{
  Serial.begin(9600);
  myOLED.begin(); 
  myOLED.setFont(SmallFont);
  
}

//sıcaklık değeri hesaplama
double Termistor(int analogOkuma)
{
  float sicaklik; 
  sicaklik = log(((10240000 / analogOkuma) - 10000));
  sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik )) * sicaklik );
  sicaklik = sicaklik - 273.15;
  return sicaklik;
}

//pid fonksiyonu
float  pidfonk(float sicaklik,int referans1)
{
   int hata=referans1-sicaklik;
  //p kontrolör
   float up=kp1*hata;

   float ui=(ki1*hata)+ui0; 

   ui0=ui;

   float ud=kd1*(hata-hata0);
   hata0=hata;

   float pid=(up+ui+ud);
   return pid;

}

void loop()
{

  int deger;
  float sicaklik; 
  deger = analogRead(A3);
  sicaklik = Termistor(deger);
  float pid_1=pidfonk(sicaklik,referans);
  pid_1=map(pid_1,0,referans,0,255); 
  if(pid_1>255)
    {
      pid_1=255;
    }
   else if(pid_1<0)
   { 
      pid_1=0;
  
   }
   analogWrite(6,pid_1);
   float pwm=(pid_1/255.0)*4.730;
    Serial.println(sicaklik);  
  //  Serial.println(pid_1);  
  
  myOLED.clrScr(); // Ekran Buffer'ını Temizliyoruz...

   myOLED.print("P.I.D KONTROLOR", CENTER,0);
  myOLED.print("KP:", 8, 15);  
   myOLED.printNumI(kp1, 28, 15);
   myOLED.print("KI:", 8, 32);  
    myOLED.printNumF(ki1,2, 28, 32);
   myOLED.print("KD:", 8, 49);  
    myOLED.printNumF(kd1,1, 28, 49);
    myOLED.print("REF:   C",70,15);
    myOLED.printNumI(referans, 100, 15); 
    myOLED.print("SNSR: ",70,32);
   myOLED.printNumF(sicaklik,1 ,99, 32); 
    myOLED.print("PWM :   V", 70, 49);  
    myOLED.printNumF(pwm,1,99, 49);
 

    myOLED.print(">", x_eksen, y_eksen);  
   
  yon();
  ref();
  kp();
  ki();
 kd();
  myOLED.update(); // Yazımızı ekrana kopyalıyoruz...
  
  
}


void ref(){

   artirma=digitalRead(4);
   ok=digitalRead(5);
   
   if(artirma==0)
   {
      diger_1=0;
   }
   
 if(x_eksen==64 and y_eksen==15 and artirma==1  and diger_1==0) //artırma işlemi

     {
        referans=referans+1;
        diger_1=1;
      }
   else if(referans>=70)
   {
    referans=30;
   }
//eksilme işlemi
 if(ok==0)
   {
      diger_12=0;
   }
   
 if(x_eksen==64 and y_eksen==15 and ok==1  and diger_12==0) //artırma işlemi

     {
        referans=referans-1;
        diger_12=1;
      }
   else if(referans<=30)
   {
    referans=30;
   }


   

   
}

void kp(){

   artirma=digitalRead(4);
   ok=digitalRead(5);
   
   if(artirma==0)
   {
      diger_1=0;
   }
   
 if(x_eksen==0 and y_eksen==15 and artirma==1  and diger_1==0) //artırma işlemi

     {
        kp1=kp1+1;
        diger_1=1;
      }
   else if(kp1>=30)
   {
    kp1=30;
   }
//eksilme işlemi
 if(ok==0)
   {
      diger_12=0;
   }
   
 if(x_eksen==0 and y_eksen==15 and ok==1  and diger_12==0) //artırma işlemi

     {
        kp1=kp1-1;
        diger_12=1;
      }
   else if(kp1<=0)
   {
    kp1=0;
   }


   

   
}
void ki(){

   artirma=digitalRead(4);
   ok=digitalRead(5);
   
   if(artirma==0)
   {
      diger_1=0;
   }
   
 if(x_eksen==0 and y_eksen==32 and artirma==1  and diger_1==0) //artırma işlemi

     {
        ki1=ki1+0.01;
        diger_1=1;
      }
   else if(ki1>=5.0)
   {
    ki1=5.0;
   }
//eksilme işlemi
 if(ok==0)
   {
      diger_12=0;
   }
   
 if(x_eksen==0 and y_eksen==32 and ok==1  and diger_12==0) //artırma işlemi

     {
        ki1=ki1-0.01;
        diger_12=1;
      }
   else if(ki1<=0.00)
   {
    ki1=0.00;
   }

   
}

void kd(){

   artirma=digitalRead(4);
   ok=digitalRead(5);
   
   if(artirma==0)
   {
      diger_1=0;
   }
   
 if(x_eksen==0 and y_eksen==49 and artirma==1  and diger_1==0) //artırma işlemi

     {
        kd1=kd1+0.1;
        diger_1=1;
      }
   else if(kd1>=5.0)
   {
    kd1=5.0;
   }
//eksilme işlemi
 if(ok==0)
   {
      diger_12=0;
   }
   
 if(x_eksen==0 and y_eksen==49 and ok==1  and diger_12==0) //artırma işlemi

     {
        kd1=kd1-0.1;
        diger_12=1;
      }
   else if(kd1<=0.0)
   {
    kd1=0.0;
   }


  
}


void yon(){
  
  x=digitalRead(2); 
 
 
  if(x==0)
  {
    diger=0;
    
  }
  if(x==1 and diger==0 )
  {
    y_eksen=y_eksen+17;
    diger=1;
  }

  if(y_eksen==66 and x_eksen==0)
  {
    y_eksen=15;
    x_eksen=64;
  }
   if(x_eksen==64 and y_eksen==32)

  {
    y_eksen=15;
    x_eksen=0;
  }
  

   }
