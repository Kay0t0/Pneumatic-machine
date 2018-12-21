

#include <Stepper.h>  // no drive tb6600, a entrada dir+ é ligada na porta 8, a entrada pul+ é ligada na porta 9, a entrada en+ é ligada na porta 7, todas no arduino mega.
const int stepsPerRevolution = 500; 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 
#include <Servo.h> 
#include "pitches.h"
#include <Keypad.h>  // Keypad Library
int LED = 13;
int porta = 30;
int botaomudo = 0;
int rele = 6;
int pos = 0;
Servo myservo ;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


 
// Variables to hold entered number on Keypad
volatile int firstnumber=99;  // used to tell how many numbers were entered on keypad
volatile int secondnumber=99;
volatile int thirdnumber=99;
volatile int quarternumber=99;
 
// Variables to hold Distance and CurrentPosition
int keyfullnumber=0;  // used to store the final calculated distance value

String currentposition = "";  // Used for display on Nokia LCD
 
 
// Keypad Setup
const byte ROWS = 4; // Four Rows
const byte COLS = 4; // Four Columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; // Arduino pins connected to the row pins of the keypad
byte colPins[COLS] = {26,27,28,29}; // Arduino pins connected to the column pins of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  // Keypad Library definition
 
 
// U8glib Setup for  LCD

 
void setup(void) {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(rele, OUTPUT);
  lcd.begin (16,2);
  myservo.attach(5);
  myservo.write(10);

  ///Mostra na tela ao iniciar
  lcd.setCursor(0,0);
  lcd.print("Digite uma");
  lcd.setCursor(0,12);
  lcd.print("quantia");
  //////////////////////////
  

}
 
  
void loop(){

digitalWrite(LED, LOW);




int TOM = 6000; // tom das teclas 1,2,3,4,5,6,7,8,9,0
int TEMPO = 100; 


  
  
  char keypressed = keypad.getKey();  // Get value of keypad button if pressed
 
 if (keypressed != NO_KEY){  // If keypad button pressed check which key it was
    
    switch (keypressed) {
      
      case '1':
      tone(porta, TOM, TEMPO);
        checknumber(1); //manda o digito para a função checknumber
        lcd.print(1);
      break;
        
      case '2':
        tone(porta, TOM, TEMPO);
        checknumber(2);
        lcd.print(2);
      break;
 
      case '3':
        tone(porta, TOM, TEMPO);
        checknumber(3);
        lcd.print(3);
      break;
 
      case '4':
        tone(porta, TOM, TEMPO);
        checknumber(4);
        lcd.print(4);
      break;
 
      case '5':
        tone(porta, TOM, TEMPO);
        checknumber(5);
        lcd.print(5);
      break;
 
      case '6':
        tone(porta, TOM, TEMPO);
        checknumber(6);
        lcd.print(6);
      break;
 
      case '7':
        tone(porta, TOM, TEMPO);
        checknumber(7);
        lcd.print(7);
      break;
 
      case '8':
        tone(porta, TOM, TEMPO);
        checknumber(8);
        lcd.print(8);
      break;
 
      case '9':
        tone(porta, TOM, TEMPO);
        checknumber(9);
        lcd.print(9);
      break;
 
      case '0':
        tone(porta, TOM, TEMPO);
        checknumber(0);
        lcd.print(0);
      break;
       case '*':
        tone(porta, 3000, 500);
        delay(500);
        
        finals();
      break;
      case '#':
        tone(porta, 1000, TEMPO);
         resetnumbers();
      break;

       case 'A':
    
        steppermotorAvanco(55);
        break;

        case 'B':
   
        steppermotorRecuo(55);
        break;

          case 'C':
   
        mudo();
        break;

        case 'D':
   
        corte();
        break;

        
        
   
    }
  }
 
}

///////////Avanço do motor de passo/////////

void steppermotorAvanco(int botao){
  if (botao==55){
   myStepper.setSpeed(1000);
    myStepper.step(-1000);
  
  }
  digitalWrite(LED, LOW);
  
////////////////////////////////////////////  


}
//////////Recuo do motor de passo////////////

void steppermotorRecuo(int botao2){
  if (botao2==55){
    myStepper.setSpeed(1000);
    myStepper.step(1000);
  }
  
}
///////////////////////////////////////////

/////////modo mudo////////////////////////

void corte(){

  for (pos = 0; pos <= 155; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 155; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  
  
}

void mudo (){
  digitalWrite(rele, HIGH);
  delay(100);
  digitalWrite(rele,LOW);
 if (botaomudo==0){ // o valor do botaomudo inicia como zero, entao quando é executado essa função (mudo) ele muda o valor da 'porta' deixando o buser desligado ou seja, mudo.
   porta = 0;
   botaomudo++;  // acrescenta +1 na variavel botaomudo.
}else{  // quando o void mudo é executado pela segunda vez, não sendo mais 0 o valor da variavel botaomudo, ele executa somente esta parte.
  porta = 30;
  delay(10);
  botaomudo--; // botamudo passa a ser zero novamente.
  }
}



 
void checknumber(int x){ // o primeiro digito vem para essa função 

  
  if (firstnumber == 99) { // o valor é verdadeiro
    firstnumber=x;                                //então fisrtnumber recebe o valor da variavel x que é o primeiro botao digitado no keypad
    String displayvalue = String(firstnumber);  //  Transform int to a string for display
lcd.clear();
Serial.println(displayvalue);

    
  } else {  // quando o proximo botao é digitado, ele da falso no if, pois não é mais == a 99 
    checknumber2(x); // entao manda o valor da variavel x para a variavel da função checknumber2
  }
 }
   
void checknumber2(int valor){
  if (secondnumber == 99) {
  secondnumber=valor;
      String displayvalue = (String(firstnumber) + String(secondnumber));
     Serial.println(displayvalue);
     } else { 
    checknumber3(valor);
   
}
}
void checknumber3(int valor2){

   if (thirdnumber == 99){  // It must be the 3rd number entered
      thirdnumber=valor2;
      String displayvalue = (String(firstnumber) + String(secondnumber) + String(thirdnumber));
      Serial.println(displayvalue);
      
 }  else { 
    checknumber4(valor2);
   
  
  }
}

void checknumber4(int valor3) {
 if (quarternumber == 99){  // It must be the 3rd number entered
      quarternumber=valor3;
      String displayvalue = (String(firstnumber) + String(secondnumber) + String(thirdnumber)+ String(quarternumber));
      Serial.println(displayvalue); 
}
}


    
  
  


void finals(){
      //unidade
     if (thirdnumber == 99 && secondnumber == 99 && firstnumber != 99 && quarternumber==99) {
      keyfullnumber=firstnumber;
      movestepper(keyfullnumber);
     movestepper(firstnumber);
    }
    //dezena
    if (secondnumber != 99 && thirdnumber == 99) {
      keyfullnumber=(firstnumber*10)+secondnumber;
      movestepper(keyfullnumber);
    }
    //centena
    if (firstnumber != 99 && thirdnumber != 99 && secondnumber != 99 && quarternumber== 99 ) {
      keyfullnumber=(firstnumber*100)+(secondnumber*10)+thirdnumber;
      movestepper(keyfullnumber);
    }
    //milhar
    if (thirdnumber != 99 && secondnumber != 99 && firstnumber != 99 && quarternumber!=99) {
      keyfullnumber=(firstnumber*1000)+(secondnumber*100)+(thirdnumber*10)+quarternumber;
      movestepper(keyfullnumber);
    }
    resetnumbers(); // Reset numbers to get ready for new entry
  } 


 
 
void movestepper(int quantiaFinal) {  

    for(keyfullnumber; keyfullnumber >0 ;keyfullnumber--){

// a ser exibido na tela
 Serial.println(keyfullnumber);
  lcd.setCursor(0,0);
  lcd.print("Faltam:");
  lcd.setCursor(7,0);
  lcd.print(keyfullnumber);
    lcd.setCursor(11,0);
  lcd.print("itens");
    lcd.setCursor(0,1);
    lcd.print("de:");
    lcd.setCursor(4,9);
    lcd.print(quantiaFinal);
     
//////////////////////////////
 
// Oque irá fazer 
//Gira o motor no sentido horario a 90 graus
 int velocidade = 1500;
  myStepper.setSpeed(velocidade); // velocidade do motor de passo

  
//1ª etapa, avança o tamanho a ser descascado

for (int i = 0; i<=500; i++)

 { 
    myStepper.setSpeed(velocidade); // velocidade do motor de passo
 myStepper.step(-5);
 velocidade ++;
 
 }
  myStepper.step(-2000);
  

  

    delay(100);

    // 2ª etapa, alicate preciona o fio

    for (pos = 20; pos <= 112; pos += 1) { // quanto maior o numero mais o alicate aperta
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  delay(300);

  //3ª etapa, aciona o pistao

  digitalWrite(rele,  HIGH);
  

 

//4ª etapa, abre o alicate
  
  for (pos = 112; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);// waits 15ms for the servo to reach the position
  }
  delay(300);

  //5ª etapa, retorna o pistao

  digitalWrite(rele, LOW);

  //delay(50); // remover!!!
 
 
 
 //6ª etapa, avança o tamanho do cabo
 for (int i = 0; i<=500; i++)

 { 
    myStepper.setSpeed(velocidade); // velocidade do motor de passo
 myStepper.step(-5);
 velocidade ++;
 
 }
  myStepper.step(-9000);
  myStepper.step(-9000);
  myStepper.step(-9000);
    myStepper.step(-9000);

      myStepper.step(-9000);
  

    delay(10);
    
    //7ª etapa, corta o fio

    for (pos = 0; pos <= 155; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 155; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

   myStepper.setSpeed(1000);
    myStepper.step(1000);
  

    
    

  


 lcd.clear();

  
///////////////////////////// 
    }

// a ser exibido na tela no final   

lcd.clear();



//////////////////////////
}



  

void resetnumbers() {  // Reseta os numeros e apaga da tela
  firstnumber=99;
  secondnumber=99;
  thirdnumber=99;
  lcd.clear();
   ///Mostra na tela ao iniciar
  lcd.setCursor(0,0);
  lcd.print("Digite uma");
  lcd.setCursor(0,12);
  lcd.print("quantia");
  //////////////////////////

} 
   
    
     
  

 
 


 
