<h1 align="center">THE REBELLION QUEST</h1>
## Two major modules:
1. Light-chasing
2. Integrating the arm to pick up

_____

### Light-chasing Module:

Its divided into 4 major steps:-
* Construction
* Connections
* Uploading the code
* Powering up the bot and testing(debugging).
<br/>

#### Construction:

1.First job is to build your chassis. All of you have been given two pieces. The smaller piece is going to be your TOP DECK and the bigger piece is going to be your BASE DECK.

2.Take out your L-clamps and screw them using the smaller screws provided. Four screws for 2 L-clamps .It should be such that the horizontal part of the L is inside(which is obvious)

3.After doing this, take out your DC motors and fix them through the L-clamps in such a way that the shaft points outwards. Tighten the nut.Once the DC motors have been fixed tightly enough, you may proceed to the next step.

4.Attach the wheels by screwing in the screw

5.Now take out your first floor(the smaller piece) and fix it on top of your motors. Position for the screws have been given. After having constructed your first floor, you may proceed to the next step.

6.Now take out your castor wheel. Its a small ball which rolls on a red base. Tape the castor wheel under your ground floor in the front  part of the chassis using the double sided tape that has been provided. It should be just behind the rectangular cut. The purpose of the castor wheel is to provide supoort at the front. To know the exact position to fix the castor wheel, follow the demonstration.

7.Take out your L293D motor driver and use double-sided tape to fix it on the first floor. Tape it such that the side containing the V+ and V- is facing backwards.

8.Now take out your Arduino Uno and tape it on the first floor such that the power USB port faces backwards.

9.Now take out your breadboard and fix it on the ground floor. Follow the demonstration or ask a RMI member where to exactly fix the breadboard

10.Once all the above mentioned steps have been completed, the bot construction is now complete. We may now move on to the connections.
<br/>

#### Connections:
A. Breadboard connections
1.Take out your LDRs and connect two male-female jumper wires to their legs. Now take out one straw and pass one of the LDRs with the jumper wires. Do the same with the other straw and LDR.

2.Now tape the straws on the sides of the chassis using  insulation tape. After this is done, move on to the next step.

3.Fix two potentiometers on the breadboard.

4.Now strip some small length of wire and connect the middle leg of the potentiometer to the 5 V line that you would be creating(Dont create it now, we would be doing it later). Repeat this for the other potentiometer. Here, your potentiometer will be used as a variable resistance.

5.Now take one jumper wire coming from one of the legs of the LDR and connect it to either the left or the right leg of the potentiometer(doesnt matter which side).Ground the jumper wire from the other leg of the LDR(connect it to your ground line that you will be creating).

6.Repeat step no.5 for the other LDR.

7.Once this has been done, take a jumper wire (male-male) and connect it to the leg of the potentiometer from which the LEFT LDR is connected. Now give the other end of the jumper wire to A0 of your MCU(its on the analog pins side).(PC0)

8.For the RIGHT LDR, do the same and connect the jumper wire to A1 of the MCU.(PC1)

9.Now use  a LM 7805 and battery to create a 5 V source and GND on your breadboard. This is going to act as your source for the LDRs ( and later the IR sensor). Do not connect the battery until we tell you. Just connect the battery cap for now.

10.If all the above mentioned steps have been completed, you may move von to the motor driver connections.
<br/>

B. Motor Driver connections
1.Give left motor's wires to MB1(black wire) and MB2(red wire) and the right motor's wires to MA1(black wire) and MA2(red wire). Tighten using your screw driver.

2.Take out a battery cap and connect the battery cap correctly to V+ and V-. Dont connect the battery now.

3.Take out 8 male- female jumper wires. Make the following connections

4.A1-GND,A2-PD5,B1-PD6,B2-GND,EN_A-5V,EN_B-5V,GND-GND,Vcc-5V(Here you may use the GND created on the breadboard)

5.Connect V- and the GND created on the breadboard using breadboard wire.(Common Ground Setup)

6.With this, all motor driver connections are complete.  
<br/>

#### Uploading the code:

1.Connect the USB cable and copy paste the code onto your IDE and upload it.
2.Now remove the USB cable
<br/>

#### Testing the bot

1.Keep your bot on top of the genesis kit box such that the wheels are free and floating in the air.
2.Connect your battery cap's positive to the Vin pin and common ground the negative  
3.Now , in order to power up the MCU, take out another battery and wait.
4.Once all the above mentioned steps have been completed, call a RMI member .Your Light-chasing module has been completed.
<br/>

_____

### Module No.2 Integrating the arm to pick up
1.Affix your servo on the GND floor near the rectangular cut. Call a RMI member or follow the demosntartion to find out exactly where to stick the servo. You will be using double tape to fix it.

2.Give the power line of the servo to 5 V on the MCU, the gnd line to the GND of the MCU and the signal line to the 9th pin of the MCU

3.Now its time to attach the arm to the servo. Pull the arm down a little to make sure it scrapes the ground.

4.Fix an IR sensor on the other side of the rectangular cut pointing downwards.

5.Give the Vcc to 5 V on the breadboard , GND to GND of the breadboard and the output line to PD2 on your MCU(the external interrupt pin).

6.Once all the above mentioned steps have been completed, call a RMI member. Your Arm module has also been completed.
