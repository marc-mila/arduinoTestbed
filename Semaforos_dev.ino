


//Definir pines de los LEDs de cada semáforo

int green = 0;
int yellow =1;
int red = 2;
int blue = 3;
int pinini = 2;                                                         // pin inicial
int salt = 4;                                                           // cada 4 salta el seguent semàfor
int SEM1 = 0;
int SEM2 = 1;
int SEM3 = 2;

int SEM_p[3] = {0,0,0};                                                //quin semàfor parpadeja (1,2,3)
int SEM_lp[3][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};                  //quin color dels semàfors parpadeja (g,y,r,b)


int count = 13;                                                        // contador
int estat = 0;                                                         // estat en el que ens trobem

void changeSem(int sem, int g, int y, int r, int b) {                  // variable on elegim el semàfor i el color del red (parpadeja
        if (g)
          digitalWrite(pinini+salt*sem+green, g && (count % 2));       //encenem (2+4* numero del semàford+ pin del led verd) l'encenem nomès els numeros parells del contador ex( 2+4+0*2, HIGH nombres parells) = semàford 1 pin (2+0+0)= 2 (pin 2 és el pin del verd)
        if (y)
          digitalWrite(pinini+salt*sem+yellow,y && (count % 2));
        if (r)
          digitalWrite(pinini+salt*sem+red,r && (count % 2));
        if (b)
          digitalWrite(pinini+salt*sem+blue,b && (count % 2));
}

void clean_arrays(){                                                  //funció per posar les arrays a 0
  for (int i=0; i < 3; i++){                                          // i=0( estat inicial) i més petita que 3 (condició) i++ (finalització)  recorre tots els semàfors
    for (int j=0; j < 4; j++)                                         //  j=0 (estat inicial) j més petita que 4 (condició) j++ (finalització) recorre tots els colors del semàfor
      SEM_lp[i][j] = 0;                                               // SEM_lp [i][j] posar el color j del semàfor i a 0
    SEM_p[i] = 0;                                                     // SEM_p[i] = 0  semàfor i a 0
  }
}

void setup () {                                                       
  
    for ( int i = pinini; i<=13; i++){                                // i = pin inicial (2) (inicialització) si la i és més petita o igual que 13 (condició) i++ (finaalització)                    
      pinMode(i,OUTPUT);                                              // totes les i ( del pin 2 al 13 ) són sortides
      digitalWrite(i, LOW);                                           //podem totes les sortides (leds) apagats
    }
  
   Serial.begin(9600);                                                //Iniciar puerto serial a 9600 baudios por segundo
   
}

void loop () {
    //Serial.print(count);                                               // veiem per quin numero va el contador per el serial
    //Serial.println(";");       
    String s1 = String(digitalRead(pinini+salt*SEM1+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM1+yellow)) + 
        String(digitalRead(pinini+salt*SEM1+red)) + 
        String(digitalRead(pinini+salt*SEM1+blue));
    String s2 = String(digitalRead(pinini+salt*SEM2+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM2+yellow)) + 
        String(digitalRead(pinini+salt*SEM2+red)) + 
        String(digitalRead(pinini+salt*SEM2+blue));
    Serial.println("1" + s1 + "/" + "2" + s2);
    

    //int bytes1 = Serial.write(s1);
    //int bytes = Serial.write(s2);
//escrivim ; per diferenciar els numeros ex: 1;2;3....
   String s = Serial.readString();
   if (s != "") {  // si s és diferent de res        
      
      int sem = s.substring(0,1).toInt() - 1;                          // agafar un caràter com string i posar-lo com un numero,  (-1) nomenclatura interna del semàfor ex: semàfor1 = sem 0 
      int g = s.substring(1,2).toInt();                                //(1,2) de la posició 1 inclosa a la 2 exclosa = a 1
      int y = s.substring(2,3).toInt();
      int r = s.substring(3,4).toInt();
      int b = s.substring(4,5).toInt();

      Serial.print("\n");                                              // saltar de linea
      Serial.print(sem);                                               // printar per el serial el sem
      Serial.print(g);                                                 // printar per el serial el led verd
      Serial.print(y);                                                 // printar per el serial el led groc
      Serial.print(r);                                                 // printar per el serial el led vermell
      Serial.print(b);  
      bool second = false;

      int sem2;
      int g2;
      int y2;
      int r2;
      int b2;
      if (s.length() == 10){
         Serial.print("dos");
         second = true;
         Serial.print("\n");   
         sem2 = s.substring(5,6).toInt() - 1;                          // agafar un caràter com string i posar-lo com un numero,  (-1) nomenclatura interna del semàfor ex: semàfor1 = sem 0 
         g2 = s.substring(6,7).toInt();                                //(1,2) de la posició 1 inclosa a la 2 exclosa = a 1
         y2 = s.substring(7,8).toInt();
         r2 = s.substring(8,9).toInt();
         b2 = s.substring(9,10).toInt();
         Serial.print(sem2);                                               // printar per el serial el sem
         Serial.print(g2);                                                 // printar per el serial el led verd
         Serial.print(y2);                                                 // printar per el serial el led groc
         Serial.print(r2);                                                 // printar per el serial el led vermell
         Serial.print(b2); 
         Serial.print("\n");   

         Serial.print("\n");                                              // saltar de linea
         Serial.print(sem2);                                               // printar per el serial el sem
         Serial.print(g2);                                                 // printar per el serial el led verd
         Serial.print(y2);                                                 // printar per el serial el led groc
         Serial.print(r2);                                                 // printar per el serial el led vermell
         Serial.print(b2);  
      }
                                                     // printar per el serial el led blau
      

      if (sem == 3){                                                    //  ?????
        count = 13;                                                     // que el contador conti fins a 13
      } else {                                     
        if (g == 1 || g == 0)                                           // si el led verd éstà encès o apagat
          digitalWrite(pinini+salt*sem+green, g);                       // encenc/apago el led verd 
        else if (g == 2){                                               // sino si el led verd parpadeja
          SEM_lp[sem][green] = 1;                                       // semàfor que sigui (en aquesdt cas el 1) el colro verd
          SEM_p[sem] = 1;                                               // que parpadegi
        }

        if (y == 1 || y == 0)
          digitalWrite(pinini+salt*sem+yellow,y);
        else if (y == 2){
          SEM_lp[sem][yellow] = 1;
          SEM_p[sem] = 1;
        }

        if (r == 1 || r == 0)
          digitalWrite(pinini+salt*sem+red,r);
        else if (r == 2){
          SEM_lp[sem][red] = 1;
          SEM_p[sem] = 1;
        }

        if (b == 1 || b == 0)
          digitalWrite(pinini+salt*sem+blue,b);
        else if (b == 2){
          SEM_lp[sem][blue] = 1;
          SEM_p[sem] = 1;
        }

        if (second==true) {
          Serial.print("in");
          if (g2 == 1 || g2 == 0)                                           // si el led verd éstà encès o apagat
            digitalWrite(pinini+salt*sem2+green, g2);                       // encenc/apago el led verd 
          else if (g2 == 2){                                               // sino si el led verd parpadeja
            SEM_lp[sem2][green] = 1;                                       // semàfor que sigui (en aquesdt cas el 1) el colro verd
            SEM_p[sem2] = 1;                                               // que parpadegi
          }

          if (y2 == 1 || y2 == 0)
            digitalWrite(pinini+salt*sem2+yellow,y2);
          else if (y2 == 2){
            SEM_lp[sem2][yellow] = 1;
            SEM_p[sem2] = 1;
          }
  
          if (r2 == 1 || r2 == 0)
            digitalWrite(pinini+salt*sem2+red,r2);
          else if (r2 == 2){
            SEM_lp[sem2][red] = 1;
            SEM_p[sem2] = 1;
          }
  
          if (b2 == 1 || b2 == 0)
            digitalWrite(pinini+salt*sem2+blue,b2);
          else if (b2 == 2){
            SEM_lp[sem2][blue] = 1;
            SEM_p[sem2] = 1;
          }
        }
        count = -5;                                                        // contador canviarà quan conti fins a 30
      }

      
   }
   else if (count == 13) {                                                   // si el contador arriba a 13
      clean_arrays();                                                        // és posen a 0 les arrays
      if (estat == 0){                                                       // si l'estat és 0
        //Serial.print("estat 0");
        digitalWrite(pinini+salt*SEM1+green, LOW);                           // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        digitalWrite(pinini+salt*SEM1+yellow,HIGH);
        digitalWrite(pinini+salt*SEM1+red,LOW);
        digitalWrite(pinini+salt*SEM1+blue,LOW);

        digitalWrite(pinini+salt*SEM3+green, LOW);                            // semàfor 3 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        digitalWrite(pinini+salt*SEM3+yellow,HIGH);
        digitalWrite(pinini+salt*SEM3+red,LOW);
        digitalWrite(pinini+salt*SEM3+blue,LOW);

        digitalWrite(pinini+salt*SEM2+green, LOW);                             // semàfor 2 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        digitalWrite(pinini+salt*SEM2+yellow,LOW);
        digitalWrite(pinini+salt*SEM2+red,HIGH);
        digitalWrite(pinini+salt*SEM2+blue,LOW);

String s1 = String(digitalRead(pinini+salt*SEM1+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM1+yellow)) + 
        String(digitalRead(pinini+salt*SEM1+red)) + 
        String(digitalRead(pinini+salt*SEM1+blue));
    String s2 = String(digitalRead(pinini+salt*SEM2+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM2+yellow)) + 
        String(digitalRead(pinini+salt*SEM2+red)) + 
        String(digitalRead(pinini+salt*SEM2+blue));
    Serial.println("1" + s1 + "/" + "2" + s2);
        delay (3000);                                                           // retard de 3 segons

     
        
        
        digitalWrite(pinini+salt*SEM1+yellow,LOW);                              // led groc del semàford 1 s'apagarà
        digitalWrite(pinini+salt*SEM1+red,HIGH);                                // led vermell del semàford 1 s'encendrà


        digitalWrite(pinini+salt*SEM3+yellow,LOW);                              // led groc del semàford 3 s'apagarà
        digitalWrite(pinini+salt*SEM3+red,HIGH);                                // led vermell del semàford 3 s'encendrà

        digitalWrite(pinini+salt*SEM2+green, HIGH);                             // led verd del semàford 2 s'encendrà
        digitalWrite(pinini+salt*SEM2+red,LOW);                                 // led vermell del semàford 2 s'apagarà
        
        count=0;                                                                // posem el contador a 0

        estat=1;                                                                 // canviem l'estat a 1
        
        
      }
      else if ( estat==1){
        //Serial.print("estat 1");
        digitalWrite(pinini+salt*SEM2+green, LOW);
        digitalWrite(pinini+salt*SEM2+yellow,HIGH);
        digitalWrite(pinini+salt*SEM2+red,LOW);
        digitalWrite(pinini+salt*SEM2+blue,LOW);

        digitalWrite(pinini+salt*SEM1+green, LOW);
        digitalWrite(pinini+salt*SEM1+yellow,LOW);
        digitalWrite(pinini+salt*SEM1+red,HIGH);
        digitalWrite(pinini+salt*SEM1+blue,LOW);
        
        digitalWrite(pinini+salt*SEM3+green, LOW);
        digitalWrite(pinini+salt*SEM3+yellow,LOW);
        digitalWrite(pinini+salt*SEM3+red,HIGH);
        digitalWrite(pinini+salt*SEM3+blue,LOW);

    String s1 = String(digitalRead(pinini+salt*SEM1+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM1+yellow)) + 
        String(digitalRead(pinini+salt*SEM1+red)) + 
        String(digitalRead(pinini+salt*SEM1+blue));
    String s2 = String(digitalRead(pinini+salt*SEM2+green)) +                            // semàfor 1 amb els seus corresponens pins (2-5) s'encendran o s'apagaran
        String(digitalRead(pinini+salt*SEM2+yellow)) + 
        String(digitalRead(pinini+salt*SEM2+red)) + 
        String(digitalRead(pinini+salt*SEM2+blue));
    Serial.println("1" + s1 + "/" + "2" + s2);
    
        delay (3000);
        
        
        digitalWrite(pinini+salt*SEM2+yellow,LOW);
        digitalWrite(pinini+salt*SEM2+red,HIGH);

        digitalWrite(pinini+salt*SEM1+green, HIGH);
        digitalWrite(pinini+salt*SEM1+red,LOW);

        
        digitalWrite(pinini+salt*SEM3+green, HIGH);
        digitalWrite(pinini+salt*SEM3+red,LOW);
        
        count=0;

        estat=0;
        
      }
    
   }
   else {
    if (SEM_p[SEM1]){                                                                              //si el semàfor 1 ha de parpadejà aleshores 
      changeSem(SEM1, SEM_lp[SEM1][0], SEM_lp[SEM1][1], SEM_lp[SEM1][2], SEM_lp[SEM1][3]);         //fes parpadejà els color que facin falta
    } if (SEM_p[SEM2]){                                                                            
      changeSem(SEM2, SEM_lp[SEM2][0], SEM_lp[SEM2][1], SEM_lp[SEM2][2], SEM_lp[SEM2][3]);
    } if (SEM_p[SEM3]) {
      changeSem(SEM3, SEM_lp[SEM3][0], SEM_lp[SEM3][1], SEM_lp[SEM3][2], SEM_lp[SEM3][3]);
    }
    count++;                                                                                        // sumem el contador 
   }
}

//primer numero és el semàfor, els altres 4 són els leds(green ,yellow, red, blue, en aquest ordre), el 0 significa parat i el 1 encès i el 2 parpadeja
//ex: 10201 semàfor 1, el verd i el vermell parat, el groc parpadeja i el blau encès.
