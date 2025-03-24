#pragma once

class Transform {
 public:
  MATH_API Transform();

  MATH_API Transform(const Vector& position, const Vector& scale);

  MATH_API ~Transform();

  MATH_API void SetScale(const Vector& newScale);

  MATH_API void AddScale(const Vector& addScale);

  MATH_API const Vector& GetScale() const;

  MATH_API void SetPosition(const Vector& newPosition);

  MATH_API void AddPostion(const Vector& addPosition);

  MATH_API const Vector& GetPosition() const;

  MATH_API float Left() const;

  MATH_API float Right() const;

  MATH_API float Top() const;

  MATH_API float Bottom() const;

  MATH_API int IntergerLeft() const;

  MATH_API int IntergerRight() const;

  MATH_API int IntergerTop() const;

  MATH_API int IntergerBottom() const;

 private:
  Vector position_;

  Vector scale_;
};