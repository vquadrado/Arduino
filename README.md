# Arduino

EXERCÍCIOS DE TREINAMENTO

RT00000001: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Printar no console serial (sem as aspas) 100 vezes: "RT00000001 xxx", onde xxx = contador de vezes.
APRENDIZADO:
  Implementação de loop finito.
  Funções "built-in" da interface Serial de Print.
  Familiaridade com Software Arduino IDE.

RT00000002: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Printar no console serial infinitas vezes, 1 vez a cada 100ms: "RT00000002 xxx", onde xxx = contador de vezes.
APRENDIZADO:
  Implementação de loop infinito.
  Temporização.
  
RT00000003: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Printar no console serial 1 vez: "RT00000003 OK" sempre ao receber pelo console serial um caracter "p" (sem as aspas).
APRENDIZADO:
  Funções "built-in" da interface Serial de Read.

RT00000003: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Printar no console serial 1 vez: "RT00000003 OK" sempre ao receber pelo console serial um caracter "p" (sem as aspas).
APRENDIZADO:
  Funções "built-in" da interface Serial de Read.
  
RT00000004: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Printar no console serial 1 vez: "RT00000004 OK" ao receber pelo console serial uma string "ping" (sem as aspas).
  Nota: string nesse contexto se refere a uma sequencia de caracteres que o usuário envia pelo console serial. Dentro do programa pode ser tratado como quiser, como tipo "String",           como tipo "array/vetor de caracteres", ou simplesmente comparar caracter por caracter do buffer de recepção.
APRENDIZADO:
  Sequencia de caracteres.
  Aprendizado secreto:
    Terminador de linha: '\r', '\n', "\r\n".
    Terminador de string: '\0'.

RT00000005: INTERFACE SERIAL
HARDWARE: Somente Arduino Uno.
  Ao receber uma string pelo console serial com terminação '\n', imprimir no console serial: "[START][xxx][yyy][END]\n"
    xxx = contador que sempre incrementa
    yyy = string recebida pelo console serial sem o '\n' (ou seja, remover o '\n')
APRENDIZADO:
  Manipulação de sequencia de caracteres.
  
RT00000006: INTERFACE SERIAL E GPIO
HARDWARE: Somente Arduino Uno.
  Ao receber uma string pelo console serial:
    "led on" com terminação '\n', acender o LED built-in da placa Arduino Uno.
    "led off" com terminação '\n', apagar o LED "built-in" da placa Arduino Uno.
APRENDIZADO:
  Uso do LED built-in.
  Controle de saída digital.

RT00000007: INTERFACE SERIAL E GPIO
HARDWARE: Somente Arduino Uno.
  Mesmos comandos do RT00000006 (led on, led off).
  Adicionar o comando "led blink xxx", onde xxx = tempo em milisegundos que o LED fica apagado ou aceso entre as piscadas.
    Com esse comando, o LED built-in tem que ficar piscando com o intervalo escolhido em milissegundos, infinitas vezes.
      xxx Minimo = 100
      xxx Maximo = 2000
      xxx fora do intervalo [Minimo,Maximo], não mexer no LED e retornar no console "erro"
    O comando led off e led on ainda tem que funcionar, mesmo se enviados enquanto o LED estiver piscando.
APRENDIZADO:
  Delay não bloqueante.
  
RT00000008: INTERFACE SERIAL, GPIO E PWM
HARDWARE: Arduino Uno, LED, resistor, protoboard.
  Conectar um LED e resistor em um pino GPIO com capacidade de gerar PWM.
  Comandos:
    led on: liga o LED na luminosidade máxima.
    led off: desliga o LED.
    led xxx: energiza o LED pelo PWM com o duty cycle representado por xxx em porcentagem.
      xxx = número inteiro entre 0 e 100 que representa o duty cycle em porcentagem da onda gerada pelo PWM.
      xxx = 0: duty cycle = 0% (LED apagado).
      xxx = 100: duty cycle = 100% (LED aceso com luminosidade máxima).
      xxx = 50: duty cycle = 50% (LED aceso com luminosidade intermediária).
APRENDIZADO:
  LED tem polaridade e dimensionamento do resistor série.
  PWM.
NOTAS:
  PWM é uma onda quadrada com determinado periodo e duty cycle.
  Periodo é o tempo de 1 ciclo de uma onda que se repete.
  Duty cycle é o resultado da divisão do tempo ativo pelo periodo. 50% significa uma onda quadrada perfeita.
  O LED tem "sentido" correto para ser energizado (polaridade).
  O cálculo do resistor é feito:
    ([Tensão total] - [Tensão forward do LED])/[corrente do LED]
    Os LEDS comuns tem tensão forward entre 2V a 3V, e acendem com corrente de poucos mA (2mA a 20mA por exemplo).
    Porém pode considerar que foi fornecido no "kit" um resistor de valor adequado (680ohm).
PARTNUMBER:
  LED amarelo 5mm: OVLFY3C7
  LED vermelho 3mm: 151034RS03000
  LED vermelho 5mm: 333-2SDRD/S530-A3/TR1-13

RT00000009: INTERFACE SERIAL, GPIO E PWM
HARDWARE: Arduino Uno, LED, resistor, protoboard. Mesma montagem do RT00000008.
  Mesmos comandos da atividade RT00000008.
  Comando adicional: "led fade xxx yyy".
    Faz o LED oscilar entre luminosidade 0 e luminosidade xxx porcento, com intervalos de yyy milisegundos, infinitamente.
    O efeito de "fade" tem que ser visto no acendimento e no apagamento do LED.
    Ainda tem que funcionar os comandos da atividade RT00000008 se enviados a qualquer momento.
    xxx = 0 a 100.
    yyy = 1 a 50.
APRENDIZADO:
  PWM.
  Delay não bloqueante.

RT00000010: INTERFACE SERIAL, GPIO, PWM
HARDWARE: Arduino Uno, LED, resistor, protoboard, Buzzer passivo, push button. Mesma montagem de RT00000008 + Buzzer e botão.
  Mesmos comandos da atividade RT00000009.
  Comando adicional: "buzzer xxx yyy".
    Não toca o buzzer passivo.
    Somente configura o tempo em milisegundos que o buzzer toca, e quantas vezes o buzzer toca.
  Ao apertar o botão, tem que tocar o buzzer passivo pelo tempo configurado pelo último xxx recebido, e pelo número de vezes configurado pelo último yyy recebido. Se nenhum xxx foi recebido e o usuário apertar o botão, assumir valor inicial xxx = 500 ms e yyy = 2 vezes.
APRENDIZADO:
  Buzzer passivo.
  Push button.
NOTA:
  Buzzer ativo: possui oscilador interno; basta aplicar alimentação contínua que o buzzer emite som.
  Buzzer passivo: conhecido como "Sounder", não possui o circuito oscilador interno; é uma membrana que se deforma com tensão, então para emitir som precisa de um estímulo de tensão periódico (ex: onda quadrada; ex: PWM).
PARTNUMBER:
  Buzzer passivo: PKM13EPYH4000-A0

RT00000011: INTERFACE SERIAL, INTERFACE SPI, DISPLAY OLED
HARDWARE: Arduino Uno, Display OLED SPI
  Ao receber um comando pela serial "oled hello": printar no display oled: "hello world".
  Ao receber um comando pela serial "oled clear": limpar a tela do display oled.
APRENDIZADO:
  Noção superficial de interface SPI.
  Introdução a display OLED.
NOTA:
  Display OLED com interface SPI.
    OLED: Considerado baixo consumo se comparado ao LCD comum.
    Chip controlador SSD1306.
    Interface SPI: interface serial full-duplex, com 4 fios:
      CS: Chip Select (Slave Select): Ativo baixo, indica que o master quer comunicar com aquele slave.
      SCLK: Pulsos de clock enviados do master para o slave.
      MOSI: Dado serial enviado do master para o slave.
      MISO: Dado serial enviado do slave para o master.
    Como o display é um dispositivo de "somente saída", a interface SPI dele não possui MISO.
    BIBLIOTECA RECOMENDADA PELO OKADA: SSD1306Ascii.
https://www.arduino.cc/en/guide/libraries  ---> Guia para instalar bibliotecas; recomendado "Library Manager" (Gerenciador de bibliotecas).

RT10000002: TELNET
HARDWARE: ESP32 DevKitC com ESP32-WROOM-32U + LED + resistor.
  Conectar a rede wifi da sua casa em modo STA (Station).
  Iniciar um servidor de Telnet.
  Aceitar comandos via Telnet:
    led on: liga o led e retorna via telnet: "led on ok".
    led off: desliga o led e retorna via telnet "led off ok".
    qualquer outro comando ENVIADO PELO USUÁRIO: retorna "erro".
    caracteres de controle do protocolo Telnet enviados pelo Putty devem ser ignorados, e não podem ser reportados como erro.
APRENDIZADO:
    Protocolo Telnet tem sequencia de comandos especiais que começam com 0xFF: https://tools.ietf.org/html/rfc854 .
DICA:
    Exemplo: WiFi ---> WiFiTelnetToSerial

RT10000003: WEB SERVER
HARDWARE: ESP32 DevKitC com ESP32-WROOM-32U.
  Criar uma rede WiFi no ESP32 em modo AP (Access Point). É como se ESP32 funcionasse como um roteador.
  O IP do ESP32 tem que ser 192.168.4.1.
  O nome da rede tem que ser: esp32_xxxxxxxxxxxx, onde xxxxxxxxxxxx é o endereço MAC da interface WiFi do ESP32 (sem os "dois pontos").
  Criar um servidor "Web" no ESP32 com uma página inicial.
  Com um celular ou computador, conectar na rede esp32_xxxxxxxxxxxx, acessar com o Browser de internet a página "192.168.4.1".
  Deve ser exibida a página inicial que foi configurada.
APRENDIZADO:
  Access Point.
  Web Server.

RT10000004: WEB SERVER
HARDWARE: ESP32 DevKitC com ESP32-WROOM-32U + LED + resistor.
  Mesmo Access Point do exercício RT10000003.
  Mesmo servidor Web do exercício RT10000003.
  Modificar a página inicial para exibir dois "botões": "LEDON" e "LEDOFF".
  Com um celular ou computador, acessar a página do web server.
    Ao pressionar o botão "LEDON", o LED deverá acender.
    Ao pressionar o botão "LEDOFF", o LED deverá apagar.
APRENDIZADO:
  Web Server.
  Noção básica de HTML.

RT10000005: BLE
HARDWARE: ESP32 DevKitC com ESP32-WROOM-32U.
  Implementar um Beacon BLE (dispositivo básico que faz Advertising BLE) não-conectável.
  O dado do Advertising tem que ser do tipo NOME, com o nome: ESP32_xxxxxxxxxxxx, onde xxxxxxxxxxxx é o endereço MAC da interface BLE do ESP32 (sem os "dois pontos").
  Escanear com o celular, com o aplicativo nRF Connect da Nordic: https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=en .
APRENDIZADO:
  BLE Advertising.
REFERÊNCIAS:
  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_gap_ble.html
  https://github.com/espressif/esp-idf/tree/2e14149bff63fe211d6d30ff0cd84c90b5fface9/examples/bluetooth/bluedroid/ble/ble_ibeacon/main 
  Exemplo: https://drive.google.com/drive/folders/1l8jz9p4S1pDAKxsvikTfqsSrETdQosvT?usp=sharing 


RT10000006: BLE
HARDWARE: ESP32 DevKitC com ESP32-WROOM-32U.
  Beacon BLE não-conectável.
  Advertising Interval de 200ms.
  O dado do Advertising tem que ser do tipo NOME, com o nome: ESP32_xxxxxxxxxxxx_yyyy.
    xxxxxxxxxxxx é o endereço MAC da interface BLE do ESP32 (sem os "dois pontos").
    yyyy é um contador com dígitos decimais:
      começando em 0000.
      Depois do 9999 voltar ao 0000 e continuar.
      Incrementado a cada Advertising (ou seja, a cada 200ms vai ter um valor).
  Escanear com celular, com o aplicativo nRF Connect da Nordic.
APRENDIZADO:
  BLE Advertising.

