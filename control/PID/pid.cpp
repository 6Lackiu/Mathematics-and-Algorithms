#include <iostream>
#include <ctime>

class PID {
public:
    PID(double P = 10, double I = 1, double D = 5) {
        Kp = P;
        Ki = I;
        Kd = D;

        current_time = std::time(0);
        last_time = current_time;
        sample_time = 0;
        setPoint = 0;

        clear();
    }

    void clear() {
        PTerm = 0;
        ITerm = 0;
        DTerm = 0;

        setPoint = 0;
        last_error = 0;
        windup_guard = 20;
        output = 0;

        throttle_ = 0;
        brake_ = 0;
    }

    void update(double feedback_value) {
        double error = setPoint - feedback_value;

        double delta_time = current_time - last_time;
        double delta_error = error - last_error;

        if(delta_time >= sample_time) {
            PTerm = error;
            ITerm += error * delta_time;

            if(ITerm < -windup_guard) {
                ITerm = -windup_guard;
            }
            else if(ITerm > windup_guard) {
                ITerm = windup_guard;
            }

            if(delta_time > 0) {
                DTerm = delta_error / delta_time;
            }
        }

        last_time = current_time;
        last_error = error;

        output = Kp * PTerm + Ki * ITerm + Kd * DTerm;
    }

    double getOutput() {
        return output;
    }


    double Kp, Ki, Kd;
    double current_time, last_time, sample_time;
    double setPoint;

    double PTerm, ITerm, DTerm;

    double last_error;
    double windup_guard;
    double output;

    double throttle_, brake_;
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
    double target_speed = 55.0; // Target speed (input)

    lontitudeControlSpeed(speed, target_speed, lonPid);

    // Access the throttle and brake values after the control function
    double throttle = lonPid.throttle_;
    double brake = lonPid.brake_;

    std::cout << "Throttle: " << throttle << ", Brake: " << brake << std::endl;

    return 0;
}