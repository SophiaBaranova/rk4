# C program for solving a first order differential equation using the fourth order Runge-Kutta method
## Algorithm:
1. Print the given equation
2. Read the end of the integration interval, initial length of subintervals and desired accuracy from user
3. Calculate the initial number of subintervals
4. Calculate х2 and у2 using the fourth order Runge-Kutta method
5. Until the desired accuracy is reached and calculation error stops decreasing:
   1. x1 = x2, y1 = y2, r1 = r2
   2. Double number of subintervals
   3. Calculate length of subintervals
   4. Calculate х2 and у2 using the fourth order Runge-Kutta method
   5. Calculate error r2 using Runge's rule
6. Print results:

   If r1 < r2 then the desired accuracy wasn't reached, print the best approximate solution (x1, y1)
   
   Else print approximate solution that satisfies the desired accuracy (x1, y1)
