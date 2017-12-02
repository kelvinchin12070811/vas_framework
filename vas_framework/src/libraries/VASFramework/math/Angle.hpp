#pragma once

namespace vas
{
	class Angle
	{
	public:
		Angle();
		explicit Angle(double value);

		const double& get() const;
		double& get();
		const Angle& operator=(const Angle& rhs);

		const Angle& operator++(int);
		const Angle& operator--(int);

		Angle operator+(const Angle& rhs) const;
		Angle operator-(const Angle& rhs) const;
		Angle operator*(const Angle& rhs) const;
		Angle operator/(const Angle& rhs) const;

		const Angle& operator+=(const Angle& rhs);
		const Angle& operator-=(const Angle& rhs);
		const Angle& operator*=(const Angle& rhs);
		const Angle& operator/=(const Angle& rhs);

		bool operator>=(const Angle& rhs) const;
		bool operator<=(const Angle& rhs) const;
		bool operator>(const Angle& rhs) const;
		bool operator<(const Angle& rhs) const;
		bool operator==(const Angle& rhs) const;
		bool operator!=(const Angle& rhs) const;

		~Angle();
	private:
		double value = 0;

		void clampValue();
	};
}