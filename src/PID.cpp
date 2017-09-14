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

    p_error = d_error = i_error = 0.0;

    // iterations
    iterations = 0;

    // tolerance
    tolerance = 0.01;


}

void PID::UpdateError(double cte) {
    // PID Error Update

    // pre twiddle
    // differential cte
    d_error = cte - p_error;
    // saving the current cte as previous
    p_error = cte;
    // interval cte
    i_error += cte;
}

double PID::TotalError() {
    return p_error;
}

void PID::twiddle(double &p, double &dp){

}
