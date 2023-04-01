#pragma once

#include "SDL.h"
#include "Room.h"


class Ball
{
public:
	Ball(double radius, Room* room);

	void Reset();
	virtual void Update(unsigned int elapsed_time_ms);
	void Launch(double initial_force_x, double initial_force_y);


	void velocity(double x, double y) { v_[0] = x; v_[1] = y; }
	double radius() const { return radius_; }
	double mass() const { return mass_; }
	double coeff_of_restitution() { return coeff_of_restitution_; }

	double pos_x() const { return p_[0]; }
	double pos_y() const { return p_[1]; }

protected:
	Room* room_;
	
	double radius_;	// meter
	double mass_;	// kg
	double coeff_of_restitution_; // from 0 o 1

	double g_[2]; // gravity

	// position
	double p_[2];	// x, y

	// velocity
	double v_[2];	// x, y

	// aerodynamic drag
	double fd_;

	// air density
	double ad_;

	// object's area
	double a_;

	// drag coefficient
	double cd_;
	double re_;

	// wind velocity
	double vw_;

	// apparent velocity
	double va_;

	double drag_F;
	double drag_a;
};

