#ifndef ESTIMATED_STATE
#define ESTIMATED_STATE

class estimated_state{

    public:
        // double time;
        bool has_gps, has_vel;
        static const int STATE_SIZE = 6; //x, vx, ax, y, vy, ay

        // double pos_variance, vel_variance, acc_variance;
        double state[STATE_SIZE];
        double cov_matrix[STATE_SIZE][STATE_SIZE];

        estimated_state();
        estimated_state(double initial_state[STATE_SIZE], double initial_variance[STATE_SIZE]);

        estimated_state prediction(double process_noise[STATE_SIZE], double dt);
        estimated_state correction(double gps_measurement[2], double vel_measurement[2], double gps_variance, double vel_variance, bool has_gps, bool has_vel);
};

#endif