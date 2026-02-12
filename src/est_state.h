#ifndef ESTIMATED_STATE
#define ESTIMATED_STATE

class estimated_state{

    public:
        // double time;
        bool has_gps, has_vel;
        double vx;
        double x;
        double ax;
        // double pos_variance, vel_variance, acc_variance;
        double cov_matrix [3][3];

        estimated_state();
        estimated_state(double pos, double vel, double acc, double p_var, double v_var, double a_var);

        estimated_state prediction(double Q_x, double Q_v, double Q_a, double dt);
        estimated_state correction(double x_pred, double vx_pred, double ax_pred, double x_gps, double vx_meas, double R_gps, double R_vel, bool has_gps, bool has_vel);
};

#endif