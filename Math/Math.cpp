#include "stdafx.h"

const float4 float4::Left = {-1.0f, 0.0f};
const float4 float4::Right = {1.0f, 0.0f};
const float4 float4::Up = {0.0f, -1.0f};
const float4 float4::Down = {0.0f, 1.0f};

Color8Bit Color8Bit::Black = Color8Bit{0, 0, 0, 0};
Color8Bit Color8Bit::White = Color8Bit{255, 255, 255, 0};
Color8Bit Color8Bit::Red = Color8Bit{255, 0, 0, 0};
Color8Bit Color8Bit::Green = Color8Bit{0, 255, 0, 0};
Color8Bit Color8Bit::Blue = Color8Bit{0, 0, 255, 0};
Color8Bit Color8Bit::Yellow = Color8Bit{255, 255, 0, 0};
Color8Bit Color8Bit::Cyan = Color8Bit{0, 255, 255, 0};
Color8Bit Color8Bit::Magenta = Color8Bit{255, 0, 255, 0};

Color8Bit Color8Bit::BlackAlpha = Color8Bit{0, 0, 0, 255};
Color8Bit Color8Bit::WhiteAlpha = Color8Bit{255, 255, 255, 255};
Color8Bit Color8Bit::RedAlpha = Color8Bit{255, 0, 0, 255};
Color8Bit Color8Bit::GreenAlpha = Color8Bit{0, 255, 0, 255};
Color8Bit Color8Bit::BlueAlpha = Color8Bit{0, 0, 255, 255};
Color8Bit Color8Bit::YellowAlpha = Color8Bit{255, 255, 0, 255};
Color8Bit Color8Bit::CyanAlpha = Color8Bit{0, 255, 255, 255};
Color8Bit Color8Bit::MagentaAlpha = Color8Bit{255, 0, 255, 255};

float4& float4::operator+=(const float4& value) {
  X += value.X;
  Y += value.Y;
  Z += value.Z;
  W = 1.0f;
  return *this;
}

float4 float4::operator+(const float4& value) const {
  float4 Result = *this;
  Result.X += value.X;
  Result.Y += value.Y;
  Result.Z += value.Z;
  Result.W = 1.0f;
  return Result;
}

float4 float4::operator+(float value) const {
  float4 Result = *this;
  Result.X += value;
  Result.Y += value;
  Result.Z += value;
  Result.W = 1.0f;
  return Result;
}

float4& float4::operator-=(const float4& value) {
  X -= value.X;
  Y -= value.Y;
  Z -= value.Z;
  W = 1.0f;
  return *this;
}

float4 float4::operator-(const float4& value) const {
  float4 Result = *this;
  Result.X -= value.X;
  Result.Y -= value.Y;
  Result.Z -= value.Z;
  Result.W = 1.0f;
  return Result;
}

float4 float4::operator*(float value) const {
  float4 Result = *this;
  Result.X *= value;
  Result.Y *= value;
  Result.Z *= value;
  Result.W = 1.0f;
  return Result;
}

float4 float4::operator*(const float4& value) const {
  float4 Return;
  Return.X = X * value.X;
  Return.Y = Y * value.Y;
  Return.Z = Z * value.Z;
  return Return;
}

float4 float4::operator-() const {
  float4 Result = *this;
  Result.X = -Result.X;
  Result.Y = -Result.Y;
  Result.Z = -Result.Z;
  return Result;
}

bool float4::operator==(const float4& value) const {
  return X == value.X && Y == value.Y && Z == value.Z;
}
