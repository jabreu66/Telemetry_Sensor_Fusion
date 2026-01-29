#ifndef ESTIMATED_STATE
#define ESTIMATED_STATE

class estimated_state{

    public:
        // double time;
        double vx;
        double x;
        double pos_variance, vel_variance;

        estimated_state();
        estimated_state(double pos, double vel, double p_var, double v_var);

        estimated_state prediction(double x_hat, double vx_hat, double Q_x, double Q_v, double dt);
        estimated_state correction(double x_pred, double vx_pred, double x_gps, double vx_meas, double tru_weight);
};

#endif