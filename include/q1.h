#ifndef Q1_H
#define Q1_H
#include <cmath>
namespace q1{
    template <typename Func>
    double gradient_descent(double initial, double step_size,Func f)
    {
        double tolerance=1e-7;
        double current = initial;

        for (int i=0;i<1e7;i++)
        {
            double gradient = (f(current+tolerance)-f(current-tolerance))/(2*tolerance);
            double next = current -step_size*gradient;
            if(std::fabs(next-current)<tolerance)
            return current;
            current=next;
        }
        return current;
        
    }
    template <typename num,typename Func>
    num gradient_descent(num initial, num step_size)
    {
        Func f;
        double tolerance=1e-7;
        num current = initial;

        for (int i=0;i<1e7;i++)
        {
            num gradient = (f(current+tolerance)-f(current-tolerance))/(2*tolerance);
            num next = current -step_size*gradient;
            if(std::fabs(next-current)<tolerance)
            return current;
            current=next;
        }
        return current;
        
    }
}

#endif //Q1_H