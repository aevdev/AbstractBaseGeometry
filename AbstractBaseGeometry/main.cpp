#define _USE_MATH_DEFINES //����� ��� ����, ����� � ������ ������ �� ����� ������������ ����� Pi
#define M_SORT3 1.73205080757
#pragma warning(disable:4326)

#include<Windows.h>
#include <iostream>
#include <math.h>

using namespace std;

//������� ��� ������ Color
namespace Geometry
{
	enum Color //					<<--���� ��������� ������ - �������� ������ class ������
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,

		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_default = 0x07
	};

	class Shape
	{
	protected:
		size_t start_x;
		size_t start_y;
		size_t line_width;
		Color color;
	public:
		void set_start_x(size_t start_x)
		{
			if (start_x > 300) start_x = 300;
			this->start_x = start_x;
		}
		void set_start_y(size_t start_y)
		{
			if (start_y > 300) start_y = 300;
			this->start_y = start_y;
		}
		void set_line_width(size_t line_width)
		{
			if (line_width > 20) line_width = 20;
			this->line_width = line_width;
		}
		Shape(Color color, size_t start_x, size_t start_y, size_t line_width) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area() const = 0; //����� ����������� ������ ������� ������
		virtual double get_perimeter() const = 0; //����� ����������� ������ ��������� ������
		virtual void draw() const = 0;

		virtual void info()const
		{
			cout << "Area:\t\t" << get_area() << endl;
			cout << "Perimeter:\t" << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0) side = 10;
			this->side = side;
		}
		Square(double side,
			Color color,
			size_t start_x, size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}

		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; ++i)
			{
				for (int i = 0; i < side; ++i)
					cout << "* ";
				cout << '\n';
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/

			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			//!!!! ������ ������� ��������� ����� ���������� ���������� ������������ ����.
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);					//������ �������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side size:\t" << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0) width = 20;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0) length = 10;
			this->length = length;
		}

		Rectangle(double width, double length,
			Color color, size_t start_x,
			size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			//!!!! ������ ������� ��������� ����� ���������� ���������� ������������ ����.
			//! ��� �� ���������� ��� ����, ����� ���������� � ���������� ������� Rectangle, � �� � ������������ ������ Rectangle � ����� ������������ ���.
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);					//������ �������������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Width:\t" << width << endl;
			cout << "Length:\t" << length << endl;
			Shape::info();
		}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0) radius = 10;
			this->radius = radius;
		}
		Circle(double radius, Color color,
			size_t start_x, size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}
		~Circle() {}

		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}

		void draw()const
		{
			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			//!!!! ������ ������� ��������� ����� ���������� ���������� ������������ ����.
			//! ��� �� ���������� ��� ����, ����� ���������� � ���������� ������� Rectangle, � �� � ������������ ������ Rectangle � ����� ������������ ���.
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());					//������ �������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius:\t" << radius << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
		double a_side;
		double b_side;
		double c_side;
	public:
		double get_a_side()const
		{
			return a_side;
		}
		double get_b_side()const
		{
			return b_side;
		}
		double get_c_side()const
		{
			return c_side;
		}

		void set_a_side(double a_side)
		{
			this->a_side = a_side;
		}
		void set_b_side(double b_side)
		{
			this->b_side = b_side;
		}
		void set_c_side(double c_side)
		{
			this->c_side = c_side;
		}

		double get_semip()const
		{
			return (a_side + b_side + c_side) / 2;
		}
		double get_height()const
		{
			return 2 * sqrt(
				get_semip() * (get_semip() - a_side) * (get_semip() - b_side) * (get_semip() - c_side)
			) / a_side;
		}
		Triangle(double a_side, double b_side, double c_side,
			Color color, size_t start_x, size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_a_side(a_side);
			set_b_side(b_side);
			set_c_side(c_side);
		}
		~Triangle() {}

		double get_area()const
		{
			return 0.5 * a_side * get_height();
		}
		double get_perimeter()const
		{
			return a_side + b_side + c_side;
		}

		void draw()const
		{
			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			POINT* Temp = new POINT(start_x, start_y); 
			::Polygon(hdc, Temp, 3);					//������ �����������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(this).name() << endl;
			cout << "A side:\t" << a_side << endl;
			cout << "B side:\t" << b_side << endl;
			cout << "C side:\t" << c_side << endl;
			Shape::info();
		}
	};

	class EquilateralTriangle : public Shape
	{
		double a_side;
	public:
		double get_a_side()const
		{
			return a_side;
		}

		void set_a_side(double a_side)
		{
			this->a_side = a_side;
		}

		EquilateralTriangle (double a_side,
			Color color, size_t start_x, size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_a_side(a_side);
		}
		~EquilateralTriangle() {}

		double get_area()const
		{
			return (M_SORT3 / 4) * (a_side * a_side);
		}
		double get_perimeter()const
		{
			return a_side + a_side + a_side;
		}

		void draw()const
		{
			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			POINT* Temp = new POINT(start_x, start_y);
			::Polygon(hdc, Temp, 3);					//������ �����������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(this).name() << endl;
			cout << "Equilateral triangle side:\t" << a_side << endl;
			Shape::info();
		}
	};

	class IsoscalesTriangle : public Shape
	{
		double a_side;
		double b_side;
	public:
		double get_a_side()const
		{
			return a_side;
		}
		double get_b_side()const
		{
			return b_side;
		}

		void set_a_side(double a_side)
		{
			this->a_side = a_side;
		}
		void set_b_side(double b_side)
		{
			this->b_side = b_side;
		}

		double get_height()const
		{
			return 2 * sqrt((a_side * a_side) - (b_side * 0.5) * (b_side * 0.5));
		}

		IsoscalesTriangle(double a_side, double b_side,
			Color color, size_t start_x, size_t start_y, size_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_a_side(a_side);
			set_b_side(b_side);
		}
		~IsoscalesTriangle() {}

		double get_area()const
		{
			return 0.5 * a_side * get_height();
		}
		double get_perimeter()const
		{
			return a_side + a_side + b_side;
		}

		void draw()const
		{
			//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
			HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
			HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
			//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
			SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
			HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
			SelectObject(hdc, hBrush);							//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

			POINT* Temp = new POINT(start_x, start_y);
			::Polygon(hdc, Temp, 3);					//������ �����������

			//������� ��������� ����� � ��������:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(this).name() << endl;
			cout << "Side:\t" << a_side << endl;
			cout << "Bottom side:\t" << b_side << endl;
			Shape::info();
		}

		class RightTriangle : public Shape
		{
			double a_side;
			double b_side;
			double c_side;
		public:
			double get_a_side()const
			{
				return a_side;
			}
			double get_b_side()const
			{
				return b_side;
			}
			double get_c_side()const
			{
				return c_side;
			}

			void set_a_side(double a_side)
			{
				this->a_side = a_side;
			}
			void set_b_side(double b_side)
			{
				this->b_side = b_side;
			}
			void set_c_side(double a_side, double b_side)
			{
				this->c_side = sqrt((a_side * a_side) + (b_side * b_side));
			}

			RightTriangle(double a_side, double b_side,
				Color color, size_t start_x, size_t start_y, size_t line_width)
				:Shape(color, start_x, start_y, line_width)
			{
				set_a_side(a_side);
				set_b_side(b_side);
				set_c_side(a_side, b_side);
			}
			~RightTriangle() {}

			double get_area()const
			{
				return (a_side * b_side) * 0.5;
			}
			double get_perimeter()const
			{
				return a_side + b_side + c_side;
			}

			void draw()const
			{
				//H - Handle(����������/��������). � ����� ������, ��� �����, ����� ������� �� ����� ���������� � ����, ��������� ����������, ���������(pen) � �.�.
				HWND hConsole = GetConsoleWindow();					//�������� ���� �������, ����� � ���� ����� ���� ����������.
				HDC hdc = GetDC(hConsole);							// ������� �������� ���������� ��� ����������� ����
				HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//������� ��������, ������� ����� �������� ������
				//PS_SOLID - �������� �����, 5 - ������� ����� 5 ���������, RGB(...) - ����.
				SelectObject(hdc, hPen);							//��������  ��������� ��������, ����� �� ����� ���� ��������
				HBRUSH hBrush = CreateSolidBrush(color);	//������� �����. ����� ����������� ��������� ������
				SelectObject(hdc, hBrush);							//�������� ��������� �����
				//����� � �������� ���������� ��� ����, ����� ������� Rectangle �������� ��� ��������

				POINT* Temp = new POINT(start_x, start_y);
				::Polygon(hdc, Temp, 3);					//������ �����������

				//������� ��������� ����� � ��������:
				DeleteObject(hBrush);
				DeleteObject(hPen);
				//����������� �������� ����������: (�������� ���������� - ��� ��, �� ��� �� ������. � ���� ���� �������� � �� ��� ����� ��������)
				ReleaseDC(hConsole, hdc);
			}

			void info()const
			{
				cout << typeid(this).name() << endl;
				cout << "A side:\t" << a_side << endl;
				cout << "B side:\t" << b_side << endl;
				cout << "C side:\t" << c_side << endl;
				Shape::info();
			}
	};
}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16, 16 };
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);

	Geometry::Square square(250, Geometry::Color::green, 100, 200, 5);
	/*cout << "Square side:\t\t" << square.get_side() << endl;
	cout << "Square area:\t\t" << square.get_area() << endl;
	cout << "Square perimeter:\t" << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(200, 100, Geometry::Color::red, 200, 400, 5);
	rect.info();

	Geometry::Circle circle(50, Geometry::Color::blue, 300, 400, 5);
	circle.info();
	return 0;
}