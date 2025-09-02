#pragma once

class Actor;
class CameraManager final {
  friend class EngineCore;

 public:
  CameraManager();

  ~CameraManager();

  ENGINE_API static CameraManager* Instance();

  ENGINE_API void SetLookAt(const Vector& newLookAt);

  const Vector& GetLookAt() const;

  ENGINE_API const Vector& GetCenter() const;

  ENGINE_API void SetTarget(Actor* target);

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