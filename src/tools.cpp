#include "tools.h"
#include <iostream>
#include <math.h> //atan2

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth)
{
    /**
     * Calculate the RMSE here.
     */
    VectorXd rmse(4);
    rmse << 0, 0, 0, 0;
    // check the validity of the inputs:
    // * the estimation vector size should not be zero
    // * the estimation vector size should equal ground truth vector size
    if (estimations.size() != ground_truth.size() || estimations.size() == 0)
    {
        cout << "Invalid estimation or ground_truth data" << endl;
        return rmse;
    }

    VectorXd residual(4);
    // accumulate squared residuals
    for (unsigned int i = 0; i < estimations.size(); ++i)
    {

        residual = estimations[i] - ground_truth[i];

        // coefficient-wise multiplication
        residual = residual.array() * residual.array();
        rmse += residual;
    }

    // calculate the mean
    rmse = rmse / estimations.size();

    // calculate the squared root
    rmse = rmse.array().sqrt();

    // return the result
    return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd &x_state)
{
    /**
     TODO:
     * Calculate a Jacobian here.
     */
    MatrixXd Hj(3, 4);
    // recover state parameters
    float px = x_state(0);
    float py = x_state(1);
    float vx = x_state(2);
    float vy = x_state(3);

    float c1 = px * px + py * py;
    float c2 = sqrt(c1);
    float c3 = c1 * c2;

    // check division by zero
    if (fabs(c1) < 0.0001)
    {
        std::cout << "CalculateJacobian() - Error - Division by Zero" << std::endl;
        return Hj;
    }

    // compute the Jacobian matrix
    Hj << (px / c2), (py / c2), 0, 0,
        -(py / c1), (px / c1), 0, 0,
        py * (vx * py - vy * px) / c3, px * (px * vy - py * vx) / c3, px / c2, py / c2;

    return Hj;
}

VectorXd Tools::ConvertCartesianToPolar(const VectorXd &x)
{
    VectorXd polar = VectorXd::Zero(3);
    float rho = sqrt(x[0] * x[0] + x[1] * x[1]);
    if (rho > epsilon)
    {
        polar << rho, atan2(x[1], x[0]), (x[0] * x[2] + x[1] * x[3]) / rho;
    }
    return polar;
}

VectorXd Tools::ConvertPolarToCartesian(const VectorXd &measurements)
{
    float rho = measurements[0];
    float phi = measurements[1];
    float rho_dot = measurements[2];
    VectorXd cartesian = VectorXd(4);
    cartesian << rho * cos(phi), rho * sin(phi), rho_dot * cos(phi), rho_dot * sin(phi);
    return cartesian;
}
