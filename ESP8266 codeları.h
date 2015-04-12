
AT\r\n

ATE0\r\n
AT+RST\r\n
ATE0\r\n

AT+CWMODE=1\r\n     //station
AT+CWMODE=2\r\n		//Access Point
AT+CWMODE=3\r\n		//Both

AT+CIPMODE=0\r\n	//Normal
AT+CIPMODE=1\r\n	//Unvarnished

AT+CIPMUX=0\r\n 	//Single
AT+CIPMUX=1\r\n 	//Multiple

AT+CWJAP="zcnzkn","Tarantula_oz_10@"\r\n


AT+CWSAP="ttuzz","12345678",6,4 		//channel,4=WPA_WPA'

AT+CIFSR\r\n 		//get ip adress
//_____________________________________________________
AT+CIPSERVER=1,80\r\n 		//add server

AT+CIPSTO=500\r\n 			//server delay time

AT+CIPSEND=0,466\r\n		//0=id , 466=legent

AT+CIPCLOSE="5"

//_____________________________________________________