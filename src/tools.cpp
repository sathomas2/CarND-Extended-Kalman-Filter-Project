#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
  VectorXd rmse(4);
  rmse << 0,0,0,0;
  if (estimations.size() != 0 && estimations.size() == ground_truth.size())
  {
    VectorXd error(4);
    VectorXd sqError(4);
    for (int i=0; i<estimations.size(); ++i)
    {
      error = estimations[i] - ground_truth[i];
      sqError = error.array()*error.array();
      rmse += sqError;
    }
    rmse = rmse / estimations.size();
    rmse = rmse.array().sqrt();
    return rmse;
  }
  else
  {
    std::cout << "Invalid size for estimation vector!" << endl;
    return rmse;
  }
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
  TODO:
    * Calculate a Jacobian here.
  */
  MatrixXd Hj(3,4);
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);
  
  // calculate denominator terms to avoid repeat calculations
  float c1 = px*px + py*py;
  float c2 = sqrt(c1);
  float c3 = c1*c2;
  
  // check division by 0
  if (fabs(c1) < 0.0001)
  {
    std::cout << "CalculateJacobian() Error: division by zero!" << endl;
    return Hj;
  }
  
  Hj << (px/c2), (py/c2), 0, 0,
        -(py/c1), (px/c1), 0, 0,
        py*(vx*py - vy*px)/c3, px*(vy*px - vx*py)/c3, (px/c2), (py/c2);
  return Hj;
}
