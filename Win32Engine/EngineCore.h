#pragma once

class Level;
class EngineCore final {
 public:
  JO_API EngineCore();

  JO_API ~EngineCore();

  JO_API bool Initialize(IApplication* application);

  JO_API void EngineLoop();

  JO_API Vector GetBackbufferScale();

  JO_API void SetShowCursor(bool show);

  JO_API const Vector& GetMousePosition() const;

  template <typename LevelType>
  LevelType* ChangeLevel() {
    LevelType* newLevel = new LevelType;
    ChangeLevelInternal(newLevel);
    return newLevel;
  }

 private:
  void GameLoop(unsigned long long curTick);

  void Render();

  JO_API void ChangeLevelInternal(Level* level);

  void Cleanup();

  IApplication* application_;

  Level* currentLevel_;

  Level* nextLevel_;

  unsigned long long prevFrameCheckTick_;  // 1초가 지났는지
  unsigned long long prevUpdateTick_;      // N ms 가 지났는지
  unsigned int frameCount_;                // 1초동안 호출된 횟수
};