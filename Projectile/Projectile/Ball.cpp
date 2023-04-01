
#include "Ball.h"
#include "SDL_image.h"
#include <iostream>




Ball::Ball(double radius, Room *room)
{
	room_ = room;
	radius_ = radius;


	v_[0] = 0;
	v_[1] = 0;

	g_[0] = 0;
	g_[1] = -9.8;

	mass_ = 10; // 10kg
	coeff_of_restitution_ = 0.7;


	ad_ = 1.2;		// air density
	a_ = 3.14 * radius_ * radius_;    // object's area. πr^2 (π ≒ 3.14)
	cd_ = 1.2;	// drag coefficient
	re_ = (1.0 * 2.7) + 5; // Re = 1.0e + 5. (e ≒ 2.7)
	
	// aerodynamic drag
	// fd_[1] = (1 / 2) * ad_ * (v_[1] * v_[1]) * a_ * (cd_ * re_);    // FD = 1/2*p*v^2*A*CD(Re)
	vw_ = -1;		// wind velocity
	va_ = v_[1] - vw_;	// apprent velocity = object velocity - wind velocity
	fd_ = (1 / 2) * ad_ * (va_ * va_) * a_ * (cd_ * re_); 

	Reset();
}

void
Ball::Reset()
{
	p_[0] = radius_;
	p_[1] = radius_;

	v_[0] = 0;
	v_[1] = 0;

	g_[0] = 0;
	g_[1] = -9.8;

	fd_ = 0;
}

void
Ball::Launch(double initial_force_x, double initial_force_y)
{
	v_[0] = v_[0] + (initial_force_x/mass_);
	v_[1] = v_[1] + (initial_force_y/mass_);
}

void 
Ball::Update(unsigned int elapsed_time_ms)
{
	double dt = elapsed_time_ms / 1000.0;	// seconds
	// Gravity
	//속도 = 이전속도 + 시간(dt) * 가속도;
	 v_[0] = v_[0] + dt * g_[0];
	 v_[1] = v_[1] + dt * g_[1];

	// v_[0] = v_[0] + dt * (g_[0] - drag_a);
	// v_[1] = v_[1] + dt * (g_[1] - drag_a);

	// Aerodynamic Drag
	drag_F = fd_;
	drag_a = drag_F / mass_;

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];

	



	// Collision with Ceilling
	if (p_[1] + radius_ > room_->height() && v_[1] > 0)
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1 * v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Ground
	if (p_[1] + radius_ < 8 && v_[1] < 0)
	{
		p_[1] = radius_-0.1;	// Friction with Ground

		v_[1] = -1 * v_[1];
		v_[0] = 1 * v_[0];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Left Wall
	if (p_[0] + radius_ < room_->width() && v_[0] < 0)
	{
		v_[0] = 1 * v_[1];
		v_[1] = 1 * v_[1];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}


	// Collision with Right Wall
	if (p_[0] + radius_ > room_->width() && v_[0] > 0)
	{
		p_[0] = room_->width() - radius_;

		v_[0] = -1 * v_[1];
		v_[1] = -1 * v_[1];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// Collision with Fence
	if ((p_[0] + radius_ > 44 && p_[0] + radius_ < 46 &&  p_[1] + radius_ < 32) && v_[0] > 0)
	{

		v_[0] = -1 * v_[0];
		v_[1] = -1 * v_[1];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
		v_[1] = coeff_of_restitution_ * v_[1];
	}
	
}
