#include <iostream>
#include <ctime>

class PID {
public:
    PID(double P = 1.35, double I = 0.06, double D = 6.2) {
        Kp = P;
        Ki = I;
        Kd = D;

        SetPoint = 0.0;
        sample_time = 0.00;
        current_time = std::time(0);
        last_time = current_time;

        clear();
    }

    void clear() {
        SetPoint = 0.0;

        PTerm = 0.0;
        ITerm = 0.0;
        DTerm = 0.0;
        last_error = 0.0;

        windup_guard = 20.0;

        output = 0.0;

        throttle_ = 0.0;
        brake_ = 0.0;
        steer_ = 0.0;
        laststeer_ = 0.0;
        yrsteer_ = 0.0;
    }

    void update(double feedback_value) {
        double error = SetPoint - feedback_value;

        current_time = std::time(0);
        double delta_time = difftime(current_time, last_time);
        double delta_error = error - last_error;

        if (delta_time >= sample_time) {
            PTerm = error;
            ITerm += error * delta_time;

            if (ITerm < -windup_guard) {
                ITerm = -windup_guard;
            } else if (ITerm > windup_guard) {
                ITerm = windup_guard;
            }

            DTerm = 0.0;
            if (delta_time > 0) {
                DTerm = delta_error / delta_time;
            }

            // Remember last time and last error for next calculation
            last_time = current_time;
            last_error = error;

            output = Kp * PTerm + Ki * ITerm + Kd * DTerm;
        }
    }

    double getOutput() const {
        return output;
    }


    double Kp;
    double Ki;
    double Kd;

    double SetPoint;
    double sample_time;
    time_t current_time;
    time_t last_time;

    double PTerm;
    double ITerm;
    double DTerm;
    double last_error;

    double windup_guard;

    double output;

    double throttle_;
    double brake_;
    double steer_;
    double laststeer_;
    double yrsteer_;
};

void lontitudeControlSpeed(double speed, double target_speed, PID& lonPid) {
    // Define the speedPidThread_1 and speedPidThread_2 values here if needed.
    // double speedPidThread_1 = 100.0;
    // double speedPidThread_2 = 50.0;

    double speedPidThread_1 = 10;
    double speedPidThread_2 = 2;

    lonPid.update(speed - target_speed);
    if (lonPid.getOutput() > speedPidThread_1) {
        // Stage 1 - Acceleration
        lonPid.throttle_ = 0.1;
        lonPid.brake_ = 0.0;
    } else if (lonPid.getOutput() > speedPidThread_2) {
        // Stage 2 - Stable Speed Control
        lonPid.throttle_ = std::min((lonPid.getOutput() / speedPidThread_1) * 0.85, 1.0);
        lonPid.brake_ = std::min(((speedPidThread_1 - lonPid.getOutput()) / speedPidThread_1) * 0.1, 1.0);
    } else if (lonPid.getOutput() > 0) {
        // Stage 3 - Fine-tuning
        lonPid.throttle_ = (lonPid.getOutput() / speedPidThread_2) * 0.3;
        lonPid.brake_ = ((speedPidThread_2 - lonPid.getOutput()) / speedPidThread_2) * 0.5;
    } else if (lonPid.getOutput() < -1 * speedPidThread_1) {
        // Stage 4 - Emergency Brake
        lonPid.throttle_ = (-1 * lonPid.getOutput() / 5) * 0.3;
        lonPid.brake_ = 4.0;
    } else {
        // Stage 5 - Brake Fine-tuning
        lonPid.throttle_ = (-1 * lonPid.getOutput() / speedPidThread_2) * 0.15;
        lonPid.brake_ = 4.0;
    }
}

int main() {
    PID lonPid;  // Initialize the PID controller

    double speed = 50.0;         // Current car speed (input)
    double target_speed = 50.0; // Target speed (input)

    lontitudeControlSpeed(speed, target_speed, lonPid);

    // Access the throttle and brake values after the control function
    double throttle = lonPid.throttle_;
    double brake = lonPid.brake_;

    std::cout << "Throttle: " << throttle << ", Brake: " << brake << std::endl;

    return 0;
}
