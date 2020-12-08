/*
 * fir_tables.c
 *
 *  Created on: Dec 7. 2020
 *      Author: fil
 */

#include "main.h"
#define	winfilter
#ifdef	winfilter
/*
Filter type: Band Pass
Filter model: Rectangular Window
Sampling Frequency: 44 KHz
Fc1 and Fc2 Frequencies: 2.000000 KHz and 3.000000 KHz
Coefficents Quantization: float
*/
#define Ntap 64
uint16_t	NumTaps = Ntap;

float fFIRCoef[Ntap] = {
		-0.00299374423509691370,
		        -0.01012629317716796600,
		        -0.01687709119357825800,
		        -0.02221399126830307000,
		        -0.02519848691704841500,
		        -0.02513809437602897200,
		        -0.02171383483015001300,
		        -0.01506125212163286600,
		        -0.00578925461603628080,
		        0.00507030878965448580,
		        0.01617925127396103700,
		        0.02606251515222676000,
		        0.03330848821536967800,
		        0.03677238072544853500,
		        0.03575303262492331900,
		        0.03011604804453212000,
		        0.02034283668625096200,
		        0.00749512526357823480,
		        -0.00690359477529296600,
		        -0.02105610831431034200,
		        -0.03312491149702222900,
		        -0.04147961942217771900,
		        -0.04492396213470540400,
		        -0.04286993074681247400,
		        -0.03543332123777063300,
		        -0.02343547276449763800,
		        -0.00830894711754478700,
		        0.00808159536078928950,
		        0.02367995228438206400,
		        0.03650804767511220400,
		        0.04492793937995771800,
		        0.04786012305923639800,
		        0.04492793937995771800,
		        0.03650804767511220400,
		        0.02367995228438206400,
		        0.00808159536078928950,
		        -0.00830894711754478700,
		        -0.02343547276449763800,
		        -0.03543332123777063300,
		        -0.04286993074681247400,
		        -0.04492396213470540400,
		        -0.04147961942217771900,
		        -0.03312491149702222900,
		        -0.02105610831431034200,
		        -0.00690359477529296600,
		        0.00749512526357823480,
		        0.02034283668625096200,
		        0.03011604804453212000,
		        0.03575303262492331900,
		        0.03677238072544853500,
		        0.03330848821536967800,
		        0.02606251515222676000,
		        0.01617925127396103700,
		        0.00507030878965448580,
		        -0.00578925461603628080,
		        -0.01506125212163286600,
		        -0.02171383483015001300,
		        -0.02513809437602897200,
		        -0.02519848691704841500,
		        -0.02221399126830307000,
		        -0.01687709119357825800,
		        -0.01012629317716796600,
		        -0.00299374423509691370,
		        0.00354814571279587570		/*
        -0.09576931037259425700,
        -0.09501093141128955100,
        -0.08166300169317042300,
        -0.05693484691582383800,
        -0.02372768239567237700,
        0.01370516104210587300,
        0.05032729191363885500,
        0.08104211770627689500,
        0.10146457084175056000,
        0.10862301625300093000,
        0.10146457084175056000,
        0.08104211770627689500,
        0.05032729191363885500,
        0.01370516104210587300,
        -0.02372768239567237700,
        -0.05693484691582383800,
        -0.08166300169317042300,
        -0.09501093141128955100,
        -0.09576931037259425700,
        -0.08449562858886609800
*/
};
#else
#define Ntap 64
uint16_t	NumTaps = Ntap;

float fFIRCoef[Ntap] = {
161.9124560796063580E-6,
 661.8161284626435190E-6,
 0.001831020364779502,
 0.003988586990194068,
 0.007275960257610184,
 0.011412869536902395,
 0.015494095375713264,
 0.017958645770066971,
 0.016845857992383643,
 0.010369323004159051,
-0.002297275681780484,
-0.020273745849512404,
-0.040594557673642347,
-0.058480764910728206,
-0.068364677994133691,
-0.065488992403631083,
-0.047627599033664508,
-0.016325821981055731,
 0.022879169878200545,
 0.061508401197606755,
 0.090281763767410067,
 0.101749740287639029,
 0.092576549868235047,
 0.064689651956399613,
 0.024858265732699968,
-0.017210360982294275,
-0.051655059357358521,
-0.071219514424757879,
-0.073101986510570385,
-0.059348888274904872,
-0.035763436282565064,
-0.009801810146779886,
 0.011769200226519129,
 0.024675885439358312,
 0.027898111781060012,
 0.023301420295617235,
 0.014449795082212755,
 0.005136911763828746,
-0.001824242216278975,
-0.005205746149968661,
-0.005297951738060089,
-0.003356765498119018,
-880.0325524154332020E-6,
 986.9776662250916390E-6,
 0.001739615867736678,
 0.001478929939900530,
 664.0196026715416340E-6,
-189.3174132698064510E-6,
-730.5693761897522340E-6,
-855.5087237778989220E-6,
-660.6864227922560530E-6,
-332.7066552860691220E-6,
-40.64552167519976680E-6,
 125.0930655871128750E-6,
 159.3813337728891210E-6,
 110.7408347181409880E-6,
 39.55607484314980130E-6,
-11.67153370310840370E-6,
-29.07500769796050830E-6,
-21.32543742006762240E-6,
-5.513866626307585510E-6,
 4.535624418119543750E-6,
 4.304520004369170930E-6,
 18.68183060642794050E-6

};

#endif