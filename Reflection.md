# Reflection
In this section, I will discuss the effects of the different componenets of a PID controller on the vehicle's steering.

A PID controller relies on the Cross-Track Error to check if it is on the right path. Cross-Track Error is the lateral distance between the vehicle and the reference trajectory or desider path. In other words, Cross-Track error is the distance between the car and the center of the desired path.

PID controllers consist of 3 static values(P, I, D) and take the Cross-Track Error(CTE) as input. 
The P stands for proportional gain. 
The D stands for differential gain. 
The I stands for integral gain.
These gain terms dictate how much information we get about our current situation from the CTE.
I will discuss what each one is and its effect on the steering angle below.

## Effect of Proportional Gain (P) on Steering Angle
P has the most obvious effect on the steering angle. 
It makes the car steer in proportion to the car's CTE, and in the opposite direction of its current trajectory(back to the desired path).
However, this value is insufficient for making the car drive in a straight line after correcting. 
Alone, the P value will cause the vehicle to overshoot the desired path everytime it corrects itself. 
The car will never converge on a straight path. 
You will only oscilate back and forth around the desired path.

* large P
  * faster oscillations
  * If the car is too far from the desired path and it has a high P value. It will spin out. 
* small P
  * slower oscillations
  
## Effect of Differential Gain (D) on Steering Angle
D smoothes out the oscillations by taking advantage of the fact that CTE is getting smaller as the car gets closer to the desired path. 
As the CTE gets smaller, the D value counters the effect of the P term.
This leads to a smoother path and lets the car converge on the desired path.

* large D
  * more resistance to moving quickly to the desired path
* small D
  * less resistance to moving quickly to the desired path
  
Combined with P, P-D controllers will drive relatively smooth. 
When you turn, they will still oscillate, but, they will eventually smooth out to straight line. 
However, this does not guarantee that your vehicle will be on the right path. 
Your vehicle may end up on one side or the other of the desired path and never fully correct for this, causing a build up of error.

## Effect of Integral Gain (I) on Steering Angle
The I term is used to counteract systematic bias.

For example: 
* Bad Wheel Allignment
* Strong Winds
* Wet Roads

These situations will cause your car to have a very high CTE because there will be a build up for lane offset(Steady State Error).
We handle these situations by summing up the CTE to tell us if we are stending mroe time on one side of the desired path or the other.
This will tell us if we need to steer harder to adjust to the bias.

* large I
  * controller can become unstable because normal fluctuations will become exaggerated
* small I
  * controller will take too long to respond to any dynamic changes

Combined with P, and D, you have your PID controller which will drive smoothly and do it's best to follow the desired path.
With the right I term, the car will reduce oscillations around the right path and keep your car closer to the desired path. 

## Choosing Hyperparameters

### Staring Point
To start, I used the hyperparameters used in the PID control module. 
They performed decently on sraight roads with minor fluctuations. 
However, the car would swerve excessively on turns. 
THe upside was that these values still kept the car on the road the entire time. 

### Manual Experimentation
My current final P, I and D values were found by manually experimenting with these values.
The goal is to eventually implement an automated process like Twiddle, which will find the best values iteratively. 

### Twiddle
Twiddle is a optimization algorithm for choosing the P, I and D values based on how the car behaves after one of them is modified. 
It is an iterative process that continues until you find that your car is driving in a stable fashion.

However, in a real world situation, it may be beneficial to let this algorithm run forever and save results periodically. 
This way, your car can adjust to new environments or any structural changes.
Even when there are no changes, the adjustments made by this algorithm would be so minute that the passenger may not notice any visible changes.