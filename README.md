## project by Michael Benzekri.
# Summary:
I am a computer science student, in addition I really like the world of aviation and deal a lot with flight simulators.\
I wanted to improve my simulator experience and decided to make a switch panel for myself.\
In addition to the pleasure of this, it is an opportunity to improve programming, construction planning and creativity skills.

At the beginning I planned the functionality that I want to have in the panel, meaning the buttons and actions I want the panel to perform.\
Next I decided on the dimensions of the panel.\
And finally the selection of the parts and components and the beginning of the development itself.

I chose Arduino Leonardo for the controller because it communicates with the computer in the form of HID, so that I can pretend it is a normal joystick and thus make programming easier.\
Since I don't have a laser cutting machine/3D printer, I decided that the panel itself would be made of wood and the work on it would be manual.\
In terms of the other components, I went for classic switches, a potentiometer and an encoder that I purchased online (aliexpress).

# Code:
For the code i used Arduino IDE with C++ and the 'ArduinoJoystickLibrary'.(https://github.com/MHeironimus/ArduinoJoystickLibrary)

Some consts and variables , function to setup all pins (intput/output etc.).\
*in the main loop function:*\
-in the first loop i init all button state and send the info.\
-check every button(switch) state and update it via joystick librery.\
-handle encoder inputs(I did not use interrupt).\
-read potentiometer values and handle it(the potetiometer is simulating the airplane magnetos).


![IMG-20240901-WA0005](https://github.com/user-attachments/assets/ace31e99-d586-4a4f-a224-441e6002d7ce)
![IMG-20240901-WA0007](https://github.com/user-attachments/assets/025677cf-d572-49c3-b232-7c39e80a8d07)
![IMG-20240901-WA0011](https://github.com/user-attachments/assets/1e608103-379e-48b5-9051-4ddac6273647)
![IMG-20240901-WA0004](https://github.com/user-attachments/assets/f5937e7c-ce09-4cc5-9ae5-57138f966c26)



