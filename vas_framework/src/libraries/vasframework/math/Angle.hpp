#pragma once
namespace vas
{
	class Angle
	{
	public:
		Angle();
		Angle(const Angle& rhs);
		explicit Angle(double rhs);
		~Angle();

		bool operator==(const Angle& rhs) const;
		bool operator!=(const Angle& rhs) const;
		const Angle& operator=(const Angle& rhs);
		
		Angle operator+(const Angle& rhs) const;
		Angle operator-(const Angle& rhs) const;
		Angle operator*(const Angle& rhs) const;
		Angle operator/(const Angle& rhs) const;

		const Angle& operator+=(const Angle& rhs);
		const Angle& operator-=(const Angle& rhs);
		const Angle& operator*=(const Angle& rhs);
		const Angle& operator/=(const Angle& rhs);

		explicit operator double() const;
	private:
		void clampValue();

		double value{ 0 };
	};
}