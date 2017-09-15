#ifndef PID_H
#define PID_H

class PID {
private:

    // twiddle parameters
    double tolerance;
    // int iterations;
    double best_error;
    short count;

    bool p_add;
    bool i_add;
    bool d_add;

    bool p_subtract;
    bool i_subtract;
    bool d_subtract;

    double total_error;

    /**
     * Method implements twiddle algorithm for paramter optimization
     *
     * @param cte
     * @param calculated
     * @param gain
     * @param add
     * @param subtract
     */
    void twiddle(double cte, double &calculated, double &gain, bool &add, bool &subtract);

public:

    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;

    /*
    * Coefficients
    */
    double Kp;
    double Ki;
    double Kd;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();
};

#endif /* PID_H */
