#include "stdafx.h"
#include "EngineCore.h"
#include "Level.h"

IGraphicDevice* GGraphicDevice = nullptr;
InputManager* GInputManager = nullptr;
EngineCore* GEngine = nullptr;
CameraManager* GCamera = nullptr;
EffectManager* GEffectManager = nullptr;
ImgManager* GImgManager = nullptr;


EngineCore::EngineCore()
    : application_(nullptr),
      currentLevel_(nullptr),
      nextLevel_(nullptr),
      prevFrameCheckTick_(0),
      prevUpdateTick_(0),
      frameCount_(0) {
  GEngine = this;
}

EngineCore::~EngineCore() {
  Cleanup();
}

bool EngineCore::Initialize(IApplication* application) {
  if (nullptr == application) {
    return false;
  }

  application_ = application;

  application_->AddRef();

  if (false == application_->InitializeWindow()) {
    return false;
  }
  GGraphicDevice = application_->InitializeGraphicDevice(Vector(1920.f, 1024.f));
  if (nullptr == GGraphicDevice) {
    __debugbreak();
    return false;
  }
  GGraphicDevice->AddRef();

  GImgManager = new ImgManager;

  if (false == GImgManager->Initialize()) {
    return false;
  }
  GInputManager = new InputManager;
  if (nullptr == GInputManager) {
#ifdef _DEBUG
    __debugbreak();
#endif  // _DEBUG
    return false;
  }
  if (false == GInputManager->Initialize()) {
    return false;
  }

  GCamera = new CameraManager;
  if (nullptr == GCamera) {
#ifdef _DEBUG
    __debugbreak();
#endif  // _DEBUG
    return false;
  }

  return true;
}

void EngineCore::EngineLoop() {
  if (nullptr == application_) {
    return;
  }

  GCamera->BeginPlay();

  while (false == application_->ApplicationQuit()) {
    ++frameCount_;

    application_->WinPumpMessage();

    unsigned long long curTick = GetTickCount64();
    if (prevUpdateTick_ == 0) {
      prevUpdateTick_ = prevFrameCheckTick_ = curTick;
    }

    application_->UpdateMousePosition();

    GameLoop(curTick);

    GCamera->CalculateTargetDiff();

    Render();

    if (curTick - prevFrameCheckTick_ > 1000) {
      prevFrameCheckTick_ = curTick;

      frameCount_ = 0;
    }
  }
}

Vector EngineCore::GetBackbufferScale() {
  if (nullptr == GGraphicDevice) {
    return Vector(0.0f, 0.0f);
  }
  return GGraphicDevice->GetBackbufferScale();
}

void EngineCore::SetShowCursor(bool show) {
  application_->SetShowCursor(show);
}

const Vector& EngineCore::GetMousePosition() const {
  return application_->GetMousePosition();
}

void EngineCore::GameLoop(unsigned long long curTick) {
  unsigned long long deltaTick = curTick - prevUpdateTick_;
  if (deltaTick < 16) {
    return;
  } else if (20 <= deltaTick) {
    deltaTick = 16;
  }

  GInputManager->Tick(deltaTick);

  prevUpdateTick_ = curTick;

  if (nullptr != nextLevel_) {
    nextLevel_->OnBeginPlay();

    if (nullptr != currentLevel_) {
      delete currentLevel_;
      currentLevel_ = nullptr;
    }

    currentLevel_ = nextLevel_;
    nextLevel_ = nullptr;
  }

  if (nullptr != currentLevel_) {
    currentLevel_->OnTick(deltaTick);
  }
}

void EngineCore::Render() {
  GGraphicDevice->BeginRender();

  if (nullptr != currentLevel_) {
    currentLevel_->OnRender();
  }

  GGraphicDevice->EndRender();
}

void EngineCore::ChangeLevelInternal(Level* level) {
  if (nullptr == level) {
    return;
  }
  if (nullptr != nextLevel_) {
    delete nextLevel_;
    nextLevel_ = nullptr;
  }
  nextLevel_ = level;
}

void EngineCore::Cleanup() {
  if (nullptr != nextLevel_) {
    delete nextLevel_;
    nextLevel_ = nullptr;
  }
  if (nullptr != currentLevel_) {
    delete currentLevel_;
    currentLevel_ = nullptr;
  }

  if (nullptr != GImgManager) {
    delete GImgManager;
    GImgManager = nullptr;
  }
  if (nullptr != GInputManager) {
    delete GInputManager;
    GInputManager = nullptr;
  }

  if (nullptr != GCamera) {
    delete GCamera;
    GCamera = nullptr;
  }

  if (nullptr != GGraphicDevice) {
    GGraphicDevice->Release();
  }

  if (nullptr != application_) {
    application_->Release();
  }
}
