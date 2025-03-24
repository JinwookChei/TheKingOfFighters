#pragma once

class MATH_API float4 {
 public:
  static const float4 Left;
  static const float4 Right;
  static const float4 Up;
  static const float4 Down;

  union {
    struct {
      float X;
      float Y;
      float Z;
      float W;
    };
    struct {
      float R;
      float G;
      float B;
      float A;
    };
    unsigned long long align[2];
    unsigned int align2[4];
    float Arr1D[4];
  };

  float4()
      : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {
  }

  float4(long _x, long _y)
      : X((float)_x), Y((float)_y), Z(0.0f), W(1.0f) {
  }

  float4(float _x, float _y)
      : X(_x), Y(_y), Z(0.0f), W(1.0f) {
  }

  float4& operator+=(const float4& value);
  float4 operator+(const float4& value) const;

  float4 operator+(float value) const;

  float4& operator-=(const float4& value);
  float4 operator-(const float4& value) const;

  float4 operator*(float value) const;

  float4 operator*(const float4& value) const;

  float4 operator-() const;
  bool operator==(const float4& value) const;

  int IntergerX() const {
    return (int)X;
  }

  float HalfX() const {
    return X * 0.5f;
  }

  int IntergerY() const {
    return (int)Y;
  }

  float HalfY() const {
    return Y * 0.5f;
  }

  float Size() const {
    return std::sqrtf((X * X) + (Y * Y) + (Z * Z));
  }
};

typedef float4 Vector;
using Color = float4;

class Color8Bit {
 public:
  static MATH_API Color8Bit Black;
  static MATH_API Color8Bit White;
  static MATH_API Color8Bit Red;
  static MATH_API Color8Bit Green;
  static MATH_API Color8Bit Blue;
  static MATH_API Color8Bit Yellow;
  static MATH_API Color8Bit Cyan;
  static MATH_API Color8Bit Magenta;

  static MATH_API Color8Bit BlackAlpha;
  static MATH_API Color8Bit WhiteAlpha;
  static MATH_API Color8Bit RedAlpha;
  static MATH_API Color8Bit GreenAlpha;
  static MATH_API Color8Bit BlueAlpha;
  static MATH_API Color8Bit YellowAlpha;
  static MATH_API Color8Bit CyanAlpha;
  static MATH_API Color8Bit MagentaAlpha;

  union {
    struct {
      unsigned char R;
      unsigned char G;
      unsigned char B;
      unsigned char A;
    };
    unsigned char Arr[4];
    unsigned int Color;
  };

  Color8Bit()
      : R(0), G(0), B(0), A(0) {
  }

  Color8Bit(unsigned char _r,
            unsigned char _g,
            unsigned char _b,
            unsigned char _a)
      : R(_r), G(_g), B(_b), A(_a) {
  }

  bool operator==(const Color8Bit& other) {
    return Color == other.Color;
  }
  bool operator!=(const Color8Bit& other) {
    return Color != other.Color;
  }
};

struct CollisionInfo {
  Vector position_;
  Vector scale_;

  float Left() const {
    return position_.X - scale_.HalfX();
  }
  float Right() const {
    return position_.X + scale_.HalfX();
  }
  float Top() const {
    return position_.Y - scale_.HalfY();
  }
  float Bottom() const {
    return position_.Y + scale_.HalfY();
  }
};