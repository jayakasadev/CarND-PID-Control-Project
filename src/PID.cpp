#include <cmath>
#include <iostream>
#include <cfloat>
#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    // saving param to object
    this->Kp = Kp; // proportional gain
    this->Ki = Ki; // integral gain
    this->Kd = Kd; // differential gain

    // pre twiddle
    // p_error = d_error = i_error = 0.0;

    // with twiddle
    p_error = d_error = i_error = 1.0;

    // iterations
    // iterations = 0;
    best_error = DBL_MAX;

    // tolerance
    tolerance = 0.001;

    // set the changes
    p_add, i_add, d_add, p_subtract, i_subtract, d_subtract = false;


    count = 0;
}

void PID::UpdateError(double cte) {
    // PID Error Update
    cout << "CTE: " << cte << endl;
    cout << "BEFORE: Kp: " << Kp << " perror: " << p_error << " Kd: " << Kd << " derror: " << d_error <<" Ki: " << Ki << " ierror: " << i_error << endl;

    /*
    // differential cte
    d_error = cte - p_error;
    // saving the current cte as previous
    p_error = cte;
    // interval cte
    i_error += cte;
     */

    // at some point, I have to accept that this is as good as it is gonna get
    // i will stop when I get an error lower than I will tolerate
    if(fabs(cte) > tolerance){

        if(count == 0){
            cout << "Update P" << endl;
            twiddle(cte, Kp, p_error, p_add, p_subtract);
        }
        else if(count == 1){
            cout << "Update D" << endl;
            twiddle(cte, Kd, d_error, d_add, d_subtract);
        }
        else{
            cout << "Update I" << endl;
            twiddle(cte, Ki, i_error, i_add, i_subtract);
        }
        /*
        cout << "Update P" << endl;
        twiddle(cte, Kp, p_error, p_updated);
        cout << "Update D" << endl;
        twiddle(cte, Kd, d_error, d_updated);
        cout << "Update I" << endl;
        twiddle(cte, Ki, i_error, i_updated);
         */
        // iterations++;
    }
    cout << "AFTER: Kp: " << Kp << " perror: " << p_error << " Kd: " << Kd << " derror: " << d_error <<" Ki: " << Ki << " ierror: " << i_error << endl;
}

double PID::TotalError() {
    return fabs(p_error) + fabs(i_error) + fabs(d_error);
}

void PID::twiddle(double cte, double &calculated, double &gain, bool &add, bool &subtract){
    cout << "PID::twiddle -> calculated: " << calculated << " gain " << gain << " cte: " << cte << endl;

    // This version makes you rerun after each update

    // didn't add yet
    if(!add){
        calculated += gain;
        add = true;
        // go reevaluate this change
    }
    else{
        if(fabs(cte) < fabs(best_error) && !subtract){
            // this was a good change, keep it and do nothing else
            best_error = cte;
            gain *= 1.1;
            count = (count + 1) % 3;
            add = false;
            //onto the next one
        }
        else {
            // that last change was bad
            if(!subtract){
                // change directions and try again
                calculated -= 2 * gain;
                subtract = true;
            }
            else{
                if(fabs(cte) < fabs(best_error)){
                    // changing directions went well, keep going
                    best_error = cte;
                    gain *= 1.1;
                }
                else{
                    // back to zero, we undo the change because the current gain value is bad
                    calculated += gain;
                    // reduce the gain value
                    gain *= 0.9;
                }
                count = (count + 1) % 3;
                subtract = false;
                // onto the next one
            }
        }
    }
}
