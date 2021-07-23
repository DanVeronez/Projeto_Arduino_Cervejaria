float temp;
int tempPin = 0;

int led = 7;

const int motorMoedor = 12;
const int buttonMoedor = 13;
const int valvulaMoagem = 11;

const int buttonMoedor2= 9;
const int valvulaAgua = 10;
const int motorMoedor2 = 8;
const int valvulaLupulo = 6;
const int valvulaEsviaTanque = 2;

const int buttonMoedor3= 3;
const int motorMoedor3 = 4;
const int valvulaLevedura = 5;
const int valvulaEsviaUltimoTanque = 1;

int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup(){
  
	pinMode(buttonMoedor, INPUT);
	pinMode(motorMoedor, OUTPUT);
    pinMode(motorMoedor2, OUTPUT);
    pinMode(motorMoedor3, OUTPUT);
	pinMode(valvulaMoagem, OUTPUT);
  	pinMode(valvulaAgua, OUTPUT);
  	pinMode(valvulaLupulo, OUTPUT);
  	pinMode(valvulaEsviaTanque, OUTPUT);
    pinMode(valvulaLevedura, OUTPUT);
  	pinMode(valvulaEsviaUltimoTanque, OUTPUT);
  
  Serial.begin(9600);
  	
  	pinMode(led, OUTPUT); 
}

void loop() {
 
  Moedor();
  Agua_Moedor();
  Levedura_Misturador();
  
}


void Moedor(){

  buttonState = digitalRead(buttonMoedor);		//lê o pino 13

  if (buttonState == HIGH){

    digitalWrite(motorMoedor, HIGH);		//Liga o motor do Moedor se o estado do botão for 1.

    delay(6000);		//Moe por 6 segundos

    digitalWrite(motorMoedor, LOW);		//para o motor do moedor

    for (int i=0; i<190; i++){		//de 0 a 255 usei 190 para simbolizar uma abertura de 90 graus
      analogWrite(valvulaMoagem, i);		//atualiza a posição do motor para posição i
      delay(10);		//velocidade em que vemos a mudança de posição do motor 
    }

    delay(3000);		//tempo que a valvula fica aberta para expulsar os residos moidos

    for (int i=190; i>=0; i--){
      analogWrite(valvulaMoagem, i);		//fechamento do moedor
      delay(10);
    }   
  }

  else {
    digitalWrite(motorMoedor, LOW);		//Mantem o loop desligado enquanto o estado do botão for 0.
  }
  

}



void Agua_Moedor(){
  
  buttonState2 = digitalRead(buttonMoedor2);
 
   if (buttonState2 == HIGH){
  
     
     
     for (int x=0; x<190; x++){		//de 0 a 255 usei 190 para simbolizar uma abertura de 90 graus
        analogWrite(valvulaAgua, x);		//atualiza a posição do motor para posição i
        delay(10);		//velocidade em que vemos a mudança de posição do motor 
      }

      delay(1000);		//tempo que a valvula fica aberta para expulsar os residos moidos

      for (int x=190; x>=0; x--){
        analogWrite(valvulaAgua, x);		//fechamento do moedor
        delay(10);
      }   
     
     
     
        digitalWrite(motorMoedor2,HIGH);
        //delay(3000);						//liga o misturador por 6 segudos
       // digitalWrite(motorMoedor2,LOW);

     
     
     
  		temp = analogRead(tempPin);
  
  		float tensao = temp*5;
  		tensao/=1024;
  		
  		float temperaturaC = (tensao-0.5)*100;

       Serial.print("Temperatura = ");
       Serial.print(temperaturaC); 
       Serial.print("*C");
       Serial.println();
       delay(1000); 
     
     if(temperaturaC >= 59 && temperaturaC <= 61){		//deixando a temperatura em aproximadamente 60 graus
       
         digitalWrite(led, HIGH);
       
         for (int y=0; y<255; y++){		//de 0 a 255 usei 190 para simbolizar uma abertura de 90 graus
        	analogWrite(valvulaLupulo, y);		//atualiza a posição do motor para posição i
        	delay(10);		//velocidade em que vemos a mudança de posição do motor 
      	 }

      	delay(3000);		//tempo que a valvula fica aberta para expulsar os residos 

        for (int y=255; y>=0; y--){
           analogWrite(valvulaLupulo, y);		//fechamento 
           delay(10);
        }  
        
       delay(3000);		//tempo em que o moedor ficara girando
      
       digitalWrite(motorMoedor2,LOW);
    
       delay(3000);		//tempo para resfriar a mistura
   
   	   for (int w=0; w<256; w++){		//de 0 a 255 usei 190 para simbolizar uma abertura de 90 graus
        	analogWrite(valvulaEsviaTanque, w);		//atualiza a posição do motor para posição i
        	delay(10);		//velocidade em que vemos a mudança de posição do motor 
      	 }

      	delay(3000);		//tempo que a valvula fica aberta para expulsar os residos 

        for (int w=255; w>=0; w--){
           analogWrite(valvulaEsviaTanque, w);		//fechamento
           delay(10);
        }  
     }
     
     else{
     	 digitalWrite(led, LOW);
     }
     
     
   }

}


void Levedura_Misturador(){

 	buttonState3 = digitalRead(buttonMoedor3);
 
   if (buttonState3 == HIGH){
  
     
     
     for (int x=0; x<256; x++){		//de 0 a 255 usei 190 para simbolizar uma abertura de 90 graus
        analogWrite(valvulaLevedura, x);		//atualiza a posição do motor para posição i
        delay(10);		//velocidade em que vemos a mudança de posição do motor 
      }

      delay(3000);		//tempo que a valvula fica aberta para expulsar os residos 

      for (int x=255; x>=0; x--){
        analogWrite(valvulaLevedura, x);		//fechamento 
        delay(10);
      }   
     

        digitalWrite(motorMoedor3,HIGH);
        delay(2000);						//liga o misturador por 6 segudos
        digitalWrite(motorMoedor3,LOW);
 		
     
     delay(4000);//espera de FERMENTAÇÃO
     	
     
     for (int v=0; v<256; v++){		//de 0 a 256 usei 190 para simbolizar uma abertura de 90 graus
        analogWrite(valvulaEsviaUltimoTanque, v);		//atualiza a posição do motor para posição i
        delay(10);		//velocidade em que vemos a mudança de posição do motor 
      }

      delay(3000);		//tempo que a valvula fica aberta para expulsar os residos 

      for (int v=255; v>=0; v--){
        analogWrite(valvulaEsviaUltimoTanque, v);		//fechamento 
        delay(10);
      }   
     

}
}