# Kail_Sleep_Monitor
Req: NodeMCU 12E v1, Accelerometer sensor, Android phone.
Senses a typical function of movement and alerts the caretaker that a sleeping baby is now awake, enabling them to tend to it. 
File sensornode.ino is to be dumped inside the NodeMCU uC (connected with the accelerometer) and WiFi must be made sure to be switched ON. The online SQL database is used from webhost000.com site and the details are available in dbconfig.php file. db_connect.php takes in credentials from dbconfig.php file and establishes a connection. For reading (parsing from time to time for alarm) the current status read_all.php is used and update.php is used to update (for override button and to push 'awake' message from WiFi client to db). 

The app is made from MIT App inventor. Feel free to use the codes and apk/aia files; Maybe drop a suggestion/query/appreciation message @ sounderajendran@gmail.com

Youtube video of working and explanation: https://youtu.be/mB_um_2ukqg
