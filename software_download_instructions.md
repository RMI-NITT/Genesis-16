1. Ubuntu 12.04 and newer
    - Install the package using the Ubuntu package manager.
    The command is
    ```bash
    sudo apt-get update && sudo apt-get install arduino arduino-core
    ```

    - Open the installed ide, and open an existing code file by
    ```
    File > examples > Basics > blink.
    ```

    - Compile, and run it. Make sure the aduino is connected to the USB port of your laptop.
     If the onboard LED blinks on and off successfully, consider the setup as successful.

    - Else, if there is a problem with the USB being recognized, do the following -
    ```
    Tools > Board > Arduino/Genuino Uno
    Tools > Programmer > AVR ISP
    Tools > Port > <Your port>
    ```

    - If there is a problem with the permissions to access the USB port, run the following commands
    ```bash
    sudo usermod -a -G dialout <username>
    sudo chmod a+rw /dev/ttyACM0
    ```

    - Please look at the following [link](http://playground.arduino.cc/Linux/Ubuntu) for more instructions.

2. Windows
    - Install the software from this [link](https://www.arduino.cc/en/Main/Software)

    -  Follow the instruction wizard for installation to successfully complete.
    
    - Please look at the following [link](https://www.arduino.cc/en/Guide/Windows) for more instructions.
