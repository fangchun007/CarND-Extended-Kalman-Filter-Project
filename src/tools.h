#ifndef TOOLS_H_
#define TOOLS_H_
#include "Eigen/Dense"
#include <vector>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

class Tools
{
public:
    /**
     * Constructor.
     */
    Tools();

    /**
     * Destructor.
     */
    virtual ~Tools();

    /**
     * A helper method to calculate RMSE.
     */
    VectorXd CalculateRMSE(const vector<VectorXd> &estimations, const vector<VectorXd> &ground_truth);

    /**
     * A helper method to calculate Jacobians.
     */
    MatrixXd CalculateJacobian(const VectorXd &x_state);

    /**
     * A helper method to convert from Cartesian coordinate to polar coordinate
     */
    VectorXd ConvertCartesianToPolar(const VectorXd &x);

    /**
     * A helper method to convert from polar to Cartesian coordinates
     */
    VectorXd ConvertPolarToCartesian(const VectorXd &measurements);

    /**
     * A threshold value that the number smaller than it will be considered as 0
     */
    float epsilon = 0.0001;
};

#endif /* TOOLS_H_ */
