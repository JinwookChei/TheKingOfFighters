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

  JO_API void SetTarget(Actor* target);

  Vector GetRenderPosition(const Vector& position) const;

  Vector GetWorldPosition(const Vector& renderPosition) const;

 private:
  void CalculateTargetDiff();

  Vector lookAt_;

  Vector diff_;

  Actor* target_;
};