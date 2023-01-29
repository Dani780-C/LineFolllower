
# Line Follower

### Team *Wings*: Cîrlan Daniel & [Ioniţă Angel](https://github.com/Angel1Ionita)  
This repository presents a Line Follower robot made for the Introduction to Robotics course, 2022-2023.

### Image of the project: 

<div align="center">
<img src="https://github.com/Dani780-C/LineFolllower/blob/main/images/image_03.png" width="800" height="600"/>  
</div>  
<br>
<div align="center">
  <a href="https://github.com/Dani780-C/LineFolllower/blob/main/images">Click for more images.</a>
</div>

### Video of its functionality: [Youtube](https://youtu.be/Yz-4I9gCifg)  

### Components used:  

1. Arduino Uno
2. Zip-ties
3. A LiPo battery
4. Wheels (2)
5. Wires for the line sensor (female - male)
6. QTR-8A reflectance sensor, along with screws
7. Ball caster
8. Extra wires
9. Chassis
10. Breadboard - medium
11. L293D motor driver
12. DC motors (2)

### Line Follower logic

The sensor is used to read the position of the robot relative to the line. It will return a value between 0 and 5000, with 0 meaning that the line follower is at the left of the line and 5000 meaning it is at the right. We map these values to the interval [-2500,2500] by decreasing 2500 from the initial value.

Given the read values, we can control the direction and speed of wheels using a PID (Proportional–Integral–Derivative) controller. 

First we tuned the constant K<sub>p</sub> which controls how much the current error value affects the output. We started with low values and slowly increased them until the robot was no longer leaving the track unless there was a tight curve. We chose K<sub>p</sub>=0.3.

To solve the second issue, we tuned the constant K<sub>d</sub> which controls how much the rate change of the error affects the output. Again, we started with low values and slowly increased them until the robot was no longer leaving the track even for tight curves. We chose K<sub>d</sub>=8.

The constant K<sub>i</sub> controls how much the residual error being corrected over time affects the output. We chose K<sub>i</sub>=0.001, but we didn't notice any significant improvement from K<sub>i</sub>=0.

The track in the video was completed in a little under 15 seconds (14.793 s).


