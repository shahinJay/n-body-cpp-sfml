#include <iostream>
#include <math.h>

class Physics {
public:
	double init_velo = 0;
	double init_pos = 500;

	double c_pos = 0;
	double c_radius = 300;
	double c_mass = 1000;

	const double G = 6 * pow(10, 9);

	double step = 0.00001;

	Physics(double v, double p, double c_p, double c_r, double c_m) {
		this->init_velo = v;
		this->init_pos = p;

		this->c_pos = c_p;
		this->c_radius = c_r;
		this->c_mass = c_m;
	}

	double distance_to_central(double self_pos, double c_pos) {
		return (self_pos - c_pos);
	}

	int normalize(double x) {
		if (x < 0)
			return -1;
		else if (x > 0)
			return 1;
		else
			return 0;
	}

	void apply_gravity() {
		double velo = init_velo;
		double pos = init_pos;
		double dist = distance_to_central(pos, this->c_pos);
		int count = 10000;

		while (dist > c_radius && count >= 0) {
			dist = distance_to_central(pos, this->c_pos);
			double force = -normalize(dist) * (this->G * this->c_mass) / (dist * dist);
			
			velo += force * this->step;
			pos += velo * this->step;
			
			std::cout << pos << std::endl;
			count -= 1;
		}
	}
};

int main() {
	Physics phy(50, 560, 0, 120, 1000);

	phy.apply_gravity();
}