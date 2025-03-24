#pragma once

class Actor;
class CameraManager final {
  friend class EngineCore;

 public:
  CameraManager();

  ~CameraManager();

  JO_API static CameraManager* Instance();

  JO_API void SetLookAt(const Vector& newLookAt);

  const Vector& GetLookAt() const;

  JO_API const Vector& GetCenter() const;

  JO_API void SetTarget(Actor* target);

  Vector GetRenderPosition(const Vector& position) const;

  Vector GetWorldPosition(const Vector& renderPosition) const;

 private:
  void BeginPlay();

  void CalculateTargetDiff();

  Vector resolution_;

  Vector center_;

  Vector lookAt_;

  Vector diff_;

  Actor* target_;
};