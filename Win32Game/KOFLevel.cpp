#include "stdafx.h"
#include "ActorFreezeManager.h"
#include "RestrictionManager.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "KOFPlayer.h"
#include "Iori.h"
#include "Chang.h"
#include "AIiori.h"
#include "BackGround.h"
#include "ScreenMask.h"
#include "HealthBar.h"
#include "Health.h"
#include "MP.h"
#include "SkillPoint.h"
#include "Portrait.h"
#include "Notification.h"
#include "KOFLoby.h"

KOFLevel::KOFLevel()
    : pRestrictionManager_(nullptr),
      pCamera_(nullptr),
      pMouse_(nullptr),
      pBackGround_(nullptr),
      pBackGroundMask_(nullptr),
      pScreenMask_(nullptr),
      pPlayer1_(nullptr),
      pPlayer2_(nullptr),
      HUD_(nullptr),
      systemUI_(nullptr),
      readyNotification_(nullptr),
      goNotification_(nullptr),
      koNotification_(nullptr),
      gameStatus_(GAMESTATUS_None),
      acuumDeltaTick_(0),
      player1SpawnPostion_({0.0f, 0.0f}),
      player2SpawnPostion_({0.0f, 0.0f}),
      levelLeftBoundary_(0.0f),
      levelRightBoundary_(0.0f),
      screenBoundaryWidth_(0.0f) {
}

KOFLevel::~KOFLevel() {
}

void KOFLevel::BeginPlay() {

  Vector backbufferScale = GEngineCore->GetBackbufferScale();
    
  // MANAGER
  pRestrictionManager_ = SpawnActor<RestrictionManager>();
  if (false == pRestrictionManager_->Initialize()) {
    return;
  }

  // MOUSE
  pMouse_ = SpawnMouse();
  pMouse_->SetImage(ImgManager::GetIntance()->GetImg(IMGTYPE_MouseImage));
  pMouse_->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  pMouse_->SetRenderLocalScale(localScale);

  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  pMouse_->SetRenderPosition(newPosition);
  pMouse_->ShowCursor(false);
  pMouse_->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // BLACKBOARD
  pBackGroundMask_ = SpawnActor<ScreenMask>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  pBackGroundMask_->SetPosition({0.0f, 0.0f});
  pScreenMask_ = SpawnActor<ScreenMask>(ActorGroupEngineType::ActorGroupEngineType_Screen);
  pScreenMask_->SetPosition({0.0f, 0.0f});

  // BACKGROUND
  pBackGround_ = SpawnActor<BackGround>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  pBackGround_->SetPosition({0.0f, 0.0f});
  pBackGround_->SetUseCameraposition(true);
  Vector backGroundImageScale = pBackGround_->GetBackGroundScale();

  // PLAYER SET
  pPlayer1_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  player1SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f - 300, groundHeight_);
  pPlayer1_->SetPlayerOnLeft(true);

  pPlayer2_ = SpawnActor<Chang>(ActorGroupEngineType::ActorGroupEngineType_None);
  player2SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f + 300, groundHeight_);
  pPlayer2_->SetPlayerOnLeft(false);

  //pPlayer2_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  //player2SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f + 300, groundHeight_);
  //pPlayer2_->SetPlayerOnLeft(false);
  
  //pPlayer2_ = SpawnActor<AIiori>(ActorGroupEngineType::ActorGroupEngineType_None);
  //player2SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f + 300, groundHeight_);
  //pPlayer2_->SetPlayerOnLeft(false);
  

  pPlayer1_->Initialize(true, player1SpawnPostion_, true, pPlayer2_);
  pPlayer2_->Initialize(false, player2SpawnPostion_, true, pPlayer1_);

  // HUD
  HUD_ = SpawnActor<UI>(ActorGroupEngineType::ActorGroupEngineType_UI);
  HUD_->SetPosition({backbufferScale.HalfX(), backbufferScale.HalfY()});
  HUD_->SetScale({backbufferScale.X, backbufferScale.Y});
  HUD_->SetOriginColor(Color8Bit::White);
  HUD_->ChangeClearColor_(false);
  HUD_->SetActive(false);

  ImageRenderer* pHUDRenderer_ = HUD_->GetImageRenderer();
  if (nullptr == pHUDRenderer_) {
    return;
  }
  pHUDRenderer_->SetTransparentColor(Color8Bit::White);

  // PLAYER_1 UI
  Portrait* portraitPlayer1 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer1->Initialize(IMGTYPE_ChangImage | IMGMOD_FLIPPED, 655, ioriTransparentColor);
  portraitPlayer1->SetPosition({90.0f, 100.0f});
  HealthBar* healthBarPlayer1 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer1->Initialize(IMGTYPE_HealthHUD | IMGMOD_NONE, 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer1->SetPosition({490.0f, 102.0f});
  Health* healthPlayer1 = HUD_->CreateUIComponent<Health>();
  healthPlayer1->Initialize(pPlayer1_, IMGTYPE_HealthHUD | IMGMOD_NONE, 1, Color8Bit(0, 0, 0, 0), {490.0f, 89.45f}, false);
  MP* mpPlayer1 = HUD_->CreateUIComponent<MP>();
  mpPlayer1->Initialize(pPlayer1_, IMGTYPE_HealthHUD | IMGMOD_NONE, 2, Color8Bit(0, 0, 0, 0), {490.0f, 123.5f}, false);
  SkillPoint* skillPoint1Player1 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint1Player1->Initialize(pPlayer1_,0, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint1Player1->SetPosition({190.0f, 170.0f});
  SkillPoint* skillPoint2Player1 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint2Player1->Initialize(pPlayer1_, 1, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint2Player1->SetPosition({250.0f, 170.0f});
  SkillPoint* skillPoint3Player1 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint3Player1->Initialize(pPlayer1_, 2, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint3Player1->SetPosition({310.0f, 170.0f});


  // PLAYER_2 UI
  Portrait* portraitPlayer2 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer2->Initialize(IMGTYPE_ChangImage, 399, changTransparentColor);
  portraitPlayer2->SetPosition({1810.0f, 100.0f});
  HealthBar* healthBarPlayer2 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer2->Initialize((IMGTYPE_HealthHUD | IMGMOD_FLIPPED), 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer2->SetPosition({1415.0f, 102.0f});
  Health* healthPlayer2 = HUD_->CreateUIComponent<Health>();
  healthPlayer2->Initialize(pPlayer2_, (IMGTYPE_HealthHUD | IMGMOD_FLIPPED), 1, Color8Bit(0, 0, 0, 0), {1415.0f, 89.45f}, true);
  MP* mpPlayer2 = HUD_->CreateUIComponent<MP>();
  mpPlayer2->Initialize(pPlayer2_, (IMGTYPE_HealthHUD | IMGMOD_FLIPPED), 2, Color8Bit(0, 0, 0, 0), {1415.0f, 123.5f}, true);
  SkillPoint* skillPoint1Player2 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint1Player2->Initialize(pPlayer2_, 0, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint1Player2->SetPosition({1710.0f, 170.0f});
  SkillPoint* skillPoint2Player2 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint2Player2->Initialize(pPlayer2_, 1, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint2Player2->SetPosition({1650.0f, 170.0f});
  SkillPoint* skillPoint3Player2 = HUD_->CreateUIComponent<SkillPoint>();
  skillPoint3Player2->Initialize(pPlayer2_, 2, IMGTYPE_SkillPoint, 0, Color8Bit(0, 0, 0, 0));
  skillPoint3Player2->SetPosition({1590.0f, 170.0f});


  // System UI
  systemUI_ = SpawnActor<UI>(ActorGroupEngineType::ActorGroupEngineType_UI);
  systemUI_->SetPosition({backbufferScale.HalfX(), backbufferScale.HalfY()});
  systemUI_->SetScale({backbufferScale.X, backbufferScale.Y});
  systemUI_->SetActive(true);

  readyNotification_ = systemUI_->CreateUIComponent<Notification>();
  readyNotification_->Initialize(IMGTYPE_Ready, 0, Color8Bit(0, 0, 0, 0));
  readyNotification_->SetPosition({systemUI_->GetScale().HalfX(), systemUI_->GetScale().HalfY()});
  readyNotification_->SetEnableTick(false);
  readyNotification_->SetEnableRender(false);

  goNotification_ = systemUI_->CreateUIComponent<Notification>();
  goNotification_->Initialize(IMGTYPE_Go, 0, Color8Bit(0, 0, 0, 0));
  goNotification_->SetPosition({systemUI_->GetScale().HalfX(), systemUI_->GetScale().HalfY()});
  goNotification_->SetEnableTick(false);
  goNotification_->SetEnableRender(false);

  koNotification_ = systemUI_->CreateUIComponent<Notification>();
  koNotification_->Initialize(IMGTYPE_KO, 0, Color8Bit(0, 0, 0, 0));
  koNotification_->SetPosition({systemUI_->GetScale().HalfX(), systemUI_->GetScale().HalfY()});
  koNotification_->SetEnableTick(false);
  koNotification_->SetEnableRender(false);


  // CAMERA
  pCamera_ = SpawnActor<CameraTarget>();
  pCamera_->Initialize(backbufferScale.HalfY(), backGroundImageScale.IntergerY() - backbufferScale.HalfY() + 60, backbufferScale.HalfX(), backGroundImageScale.X - backbufferScale.HalfX() + 20);
  pCamera_->SetPosition({backGroundImageScale.X / 2, pCamera_->GetCameraMaxHeight()});
  CameraManager::Instance()->SetTarget(pCamera_);


  // EFFECT
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_1, IMGTYPE_HitEffectImage, SOUNDTYPE_COMMON_Hit02, 7, 10, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_2, IMGTYPE_HitEffectImage, SOUNDTYPE_COMMON_Hit03, 19, 22, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_3, IMGTYPE_HitEffectImage, SOUNDTYPE_COMMON_Hit02, 31, 34, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Guard_1, IMGTYPE_GuardEffectImage01, SOUNDTYPE_COMMON_Hit01, 0, 10, 50, false, {2.1f, 2.1f}, Color8Bit{103, 167, 141, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_1, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 0, 15, 16, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_2, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 16, 31, 16, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_3, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 32, 47, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_4, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 48, 63, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_5, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 64, 79, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_6, IMGTYPE_CastingEffectImage, SOUNDTYPE_COMMON_Casting, 80, 95, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Iori_Explosion, IMGTYPE_ChangImage, SOUNDTYPE_COMMON_Explosion, 387, 405, 20, false, {4.2f, 4.2f}, Color8Bit{0, 0, 0, 0}, true, 1.0f);
  EffectManager::Instance()->RegistEffect(EFTYPE_Iori_Casting_YamiBarai, IMGTYPE_ChangImage, SOUNDTYPE_None, 231, 238, 16, false, {4.2f, 4.2f}, Color8Bit{0, 0, 0, 0}, true, 1.0f);
  
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_1 | EFMOD_FLIPPED, IMGTYPE_HitEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Hit02, 7, 10, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_2 | EFMOD_FLIPPED, IMGTYPE_HitEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Hit03, 19, 22, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Hit_3 | EFMOD_FLIPPED, IMGTYPE_HitEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Hit02, 31, 34, 50, false, {4.2f, 4.2f}, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Guard_1 | EFMOD_FLIPPED, IMGTYPE_GuardEffectImage01 | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Hit01, 0, 10, 50, false, {2.1f, 2.1f}, Color8Bit{103, 167, 141, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_1 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 0, 15, 16, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_2 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 16, 31, 16, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_3 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 32, 47, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_4 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 48, 63, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_5 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 64, 79, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Casting_6 | EFMOD_FLIPPED, IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Casting, 80, 95, 20, false, {4.2f, 4.2f}, Color8Bit{108, 156, 114, 0});
  EffectManager::Instance()->RegistEffect(EFTYPE_Iori_Explosion | EFMOD_FLIPPED, IMGTYPE_ChangImage | IMGMOD_FLIPPED, SOUNDTYPE_COMMON_Explosion, 387, 405, 20, false, {4.2f, 4.2f}, Color8Bit{0, 0, 0, 0}, true, 1.0f);
  EffectManager::Instance()->RegistEffect(EFTYPE_Iori_Casting_YamiBarai | EFMOD_FLIPPED, IMGTYPE_ChangImage | IMGMOD_FLIPPED, SOUNDTYPE_None, 231, 238, 16, false, {4.2f, 4.2f}, Color8Bit{0, 0, 0, 0}, true, 1.0f);
  
  // SOUND
  Path soundPath;
  soundPath.MoveParent();
  soundPath.Move("ContentsResource\\Sound\\");
  soundPath.Move("Kyoku-Gen.mp3");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_BackGround);
  soundPath.MoveParent();
  soundPath.Move("Common\\");
  soundPath.Move("common_Ready.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Ready);
  soundPath.MoveParent();
  soundPath.Move("common_Go.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Go);
  soundPath.MoveParent();
  soundPath.Move("common_KO.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_KO);
  soundPath.MoveParent();
  soundPath.Move("common_System01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_System01);
  soundPath.MoveParent();
  soundPath.Move("common_Jump01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Jump01);
  soundPath.MoveParent();
  soundPath.Move("common_Jump02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Jump02);
  soundPath.MoveParent();
  soundPath.Move("common_Land02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Land);
  soundPath.MoveParent();
  soundPath.Move("common_Footstep.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_FootStep);
  soundPath.MoveParent();
  soundPath.Move("common_Hit01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit01);
  soundPath.MoveParent();
  soundPath.Move("common_Hit02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit02);
  soundPath.MoveParent();
  soundPath.Move("common_Hit03.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit03);
  soundPath.MoveParent();
  soundPath.Move("common_Hit04.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit04);
  soundPath.MoveParent();
  soundPath.Move("common_Hit05.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit05);
  soundPath.MoveParent();
  soundPath.Move("common_Hit06.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Hit06);
  soundPath.MoveParent();
  soundPath.Move("common_Casting.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Casting);
  soundPath.MoveParent();
  soundPath.Move("common_Explosion.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_COMMON_Explosion);
  soundPath.MoveParent();
  soundPath.MoveParent();
  soundPath.Move("Iori\\");
  soundPath.Move("f1f_Kiai_Light01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Light01);
  soundPath.MoveParent();
  soundPath.Move("f1f_Kiai_Light02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Light02);
  soundPath.MoveParent();
  soundPath.Move("f1f_Kiai_Light03.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Light03);
  soundPath.MoveParent();
  soundPath.Move("f1f_Kiai_Heavy01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Heavy01);
  soundPath.MoveParent();
  soundPath.Move("f1f_Kiai_Heavy02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Heavy02);
  soundPath.MoveParent();
  soundPath.Move("f1f_Kiai_Heavy03.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Kiai_Heavy03);
  soundPath.MoveParent();
  soundPath.Move("f1f_Hit_02_Dash.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_Dash);
  soundPath.MoveParent();
  soundPath.Move("f1f_108ShikiYamiBarai.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_108ShikiYamiBarai);
  soundPath.MoveParent();
  soundPath.Move("f1f_HyakushikiOniyaki.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_HyakushikiOniyaki);
  soundPath.MoveParent();
  soundPath.Move("f1f_1211ShikiYaOtome01.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_1211ShikiYaOtome01);
  soundPath.MoveParent();
  soundPath.Move("f1f_1211ShikiYaOtome02.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_1211ShikiYaOtome02);
  soundPath.MoveParent();
  soundPath.Move("f1f_1211ShikiYaOtome03.wav");
  SoundManager::Instance()->Load(soundPath, SOUNDTYPE_IORI_1211ShikiYaOtome03);

  soundPath.MoveParent();
  soundPath.Move("f1f_HyakushikiOniyaki.wav");  // ╠м╫ееб©Л╠Б.

  // LEVEL BOUNDARY SETTING
  levelLeftBoundary_ = levelBoundaryMargin_;
  levelRightBoundary_ = backGroundImageScale.X - levelBoundaryMargin_;

  InitReadyGame();
}

void KOFLevel::SwapPosition() {
  const Vector& player1Postion = pPlayer1_->GetPosition();
  const Vector& player2Postion = pPlayer2_->GetPosition();

  pPlayer1_->SetPlayerOnLeft(player1Postion.X < player2Postion.X);
  pPlayer2_->SetPlayerOnLeft(!(player1Postion.X < player2Postion.X));
}

RestrictionManager* KOFLevel::GetRestrictionManager() const {
  return pRestrictionManager_;
}

void KOFLevel::Tick(unsigned long long deltaTick) {
  SwapPosition();

  if (true == InputManager::Instance()->IsAnyKeyPress()) {
    if (InputManager::Instance()->IsDown(VK_F1)) {
      SetDebugRender(!GetDebugRender());
    }

    if (InputManager::Instance()->IsDown(VK_F2)) {
      SetCollisionRender(!GetCollisionRender());
    }
    if (InputManager::Instance()->IsDown(VK_F3)) {
    }
    if (InputManager::Instance()->IsDown(VK_F4)) {
    }
  }

  switch (gameStatus_) {
    case GAMESTATUS_GameReady:
      ReadyGame(deltaTick);
      break;
    case GAMESTATUS_GameInProgress:
      InProgressGame(deltaTick);
      break;
    case GAMESTATUS_GameEnd:
      EndGame(deltaTick);
      break;
    default:
      break;
  }
}

CameraTarget* KOFLevel::GetCameraTarget() const {
  return pCamera_;
}

ScreenMask* KOFLevel::GetBackGroundMask() const {
  return pBackGroundMask_;
}

float KOFLevel::GetLevelLeftBoundary() const {
  return levelLeftBoundary_;
}

float KOFLevel::GetLevelRightBoundary() const {
  return levelRightBoundary_;
}

float KOFLevel::GetScreenBoundaryWidth() const {
  return screenBoundaryWidth_;
}

void KOFLevel::InitReadyGame() {
  if (nullptr == pPlayer1_ || nullptr == pPlayer2_) {
    return;
  }

  Vector backbufferScale = GEngineCore->GetBackbufferScale();
  screenBoundaryWidth_ = backbufferScale.X - pPlayer1_->CharacterScale().HalfX() - pPlayer2_->CharacterScale().HalfX();

  pPlayer1_->UpdateAnimState(PLAYER_ANIMTYPE_StartPos);
  pPlayer2_->UpdateAnimState(PLAYER_ANIMTYPE_StartPos);

  pScreenMask_->InitAlpha(1.0f);
  pScreenMask_->FadeOut(IMGTYPE_BlackBoardImage, 0.0f);
  pScreenMask_->FadeIn(300.0f);

  gameStatus_ = GAMESTATUS_GameReady;
}

void KOFLevel::ReadyGame(unsigned long long deltaTick) {
  acuumDeltaTick_ += deltaTick;
  if (true == backGroundSoundChannel_.IsEmpty() && 100 <= acuumDeltaTick_ && 200 > acuumDeltaTick_) {
    backGroundSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_COMMON_Ready);
    readyNotification_->SetEnableRender(true);
  }

  if (true == backGroundSoundChannel_.IsEmpty() && 800 <= acuumDeltaTick_ && 900 > acuumDeltaTick_) {
    backGroundSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_COMMON_Go);
    readyNotification_->SetEnableRender(false);
    goNotification_->SetEnableRender(true);
  }

  if (1300 <= acuumDeltaTick_) {
    goNotification_->SetEnableRender(false);
    InitInProgressGame();
  } 
}

void KOFLevel::InitInProgressGame() {
  acuumDeltaTick_ = 0;
  backGroundSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_BackGround);

  HUD_->SetActive(true);
  pPlayer1_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);
  pPlayer2_->UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  gameStatus_ = GAMESTATUS_GameInProgress;
}

void KOFLevel::InProgressGame(unsigned long long deltaTick) {
  Vector backbufferScale = GEngineCore->GetBackbufferScale();
  float cameraHeight = pCamera_->GetCameraMaxHeight();

  pPlayer1_->SetIsAtMapEdge(false);
  pPlayer2_->SetIsAtMapEdge(false);
  screenBoundaryWidth_ = backbufferScale.X - pPlayer1_->CharacterScale().HalfX() - pPlayer2_->CharacterScale().HalfX();

  Vector player1Position = pPlayer1_->GetPosition();
  Vector player2Position = pPlayer2_->GetPosition();

  float player1Left = player1Position.X - pPlayer1_->CharacterScale().HalfX();
  float player2Left = player2Position.X - pPlayer2_->CharacterScale().HalfX();

  float player1Right = player1Position.X + pPlayer1_->CharacterScale().HalfX();
  float player2Right = player2Position.X + pPlayer2_->CharacterScale().HalfX();

  float viewLeft = pCamera_->GetPosition().X - backbufferScale.X / 2;
  float viewRight = pCamera_->GetPosition().X + backbufferScale.X / 2;

  // CameraPosition X
  if (player1Position.X < player2Position.X) {
    if (player1Left < viewLeft) {
      if (viewRight > player2Right && viewLeft > levelLeftBoundary_) {
        pCamera_->SetPosition({player1Left + backbufferScale.X / 2, cameraHeight});
      }
    }
    if (player2Right > viewRight) {
      if (viewLeft < player1Left && viewRight < levelRightBoundary_) {
        pCamera_->SetPosition({player2Right - backbufferScale.X / 2, cameraHeight});
      }
    }
  } else {
    if (player2Left < viewLeft) {
      if (viewRight > player1Right && viewLeft > levelLeftBoundary_) {
        pCamera_->SetPosition({player2Left + backbufferScale.X / 2, cameraHeight});
      }
    }
    if (player1Right > viewRight) {
      if (viewLeft < player2Left && viewRight < levelRightBoundary_) {
        pCamera_->SetPosition({player1Right - backbufferScale.X / 2, cameraHeight});
      }
    }
  }

  // CameraClamp X
  if (pCamera_->GetPosition().X < pCamera_->GetCameraMinWidth()) {
    pCamera_->SetPosition({pCamera_->GetCameraMinWidth(), pCamera_->GetPosition().Y});

  } else if (pCamera_->GetPosition().X > pCamera_->GetCameraMaxWidth()) {
    pCamera_->SetPosition({pCamera_->GetCameraMaxWidth(), pCamera_->GetPosition().Y});
  }

  // CameraPosition Y
  float player1JumpHeight = player1SpawnPostion_.Y - player1Position.Y;
  float player2JumpHeight = player2SpawnPostion_.Y - player2Position.Y;

  if (player1JumpHeight > 0 || player2JumpHeight > 0) {
    float addHeight = (player1JumpHeight > player2JumpHeight) ? player1JumpHeight : player2JumpHeight;
    const Vector& cameraPosition = pCamera_->GetPosition();
    pCamera_->SetPosition({cameraPosition.X, cameraHeight - addHeight / 5});
  }

  // CameraClamp Y
  if (pCamera_->GetPosition().Y < pCamera_->GetCameraMinHeight()) {
    pCamera_->SetPosition({pCamera_->GetPosition().X, pCamera_->GetCameraMinHeight()});

  } else if (pCamera_->GetPosition().Y > pCamera_->GetCameraMaxHeight()) {
    pCamera_->SetPosition({pCamera_->GetPosition().X, pCamera_->GetCameraMaxHeight()});
  }

  // CHECK PlAYER POSITION EDGE
  if (player1Left <= levelLeftBoundary_ || player1Right >= levelRightBoundary_) {
    pPlayer1_->SetIsAtMapEdge(true);
  }
  if (player2Left <= levelLeftBoundary_ || player2Right >= levelRightBoundary_) {
    pPlayer2_->SetIsAtMapEdge(true);
  }
}

void KOFLevel::InitEndGame() {
  acuumDeltaTick_ = 0;
  koNotification_->SetEnableRender(true);
  backGroundSoundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_COMMON_KO);

  std::vector<PLAYER_RESTRICT_TYPE> restrictList;
  restrictList.push_back(PR_LockInput);

  pRestrictionManager_->ApplyExternalRestrict(pPlayer1_->ActorId(), restrictList);
  pRestrictionManager_->ApplyExternalRestrict(pPlayer2_->ActorId(), restrictList);

  gameStatus_ = GAMESTATUS_GameEnd;
}

void KOFLevel::EndGame(unsigned long long deltaTick) {
  acuumDeltaTick_ += deltaTick;

  if (700 < acuumDeltaTick_ && 720 > acuumDeltaTick_) {
    pScreenMask_->FadeOut(IMGTYPE_BlackBoardImage, 500.0f);
    koNotification_->SetEnableRender(false);
  }

  if (1700 < acuumDeltaTick_ && 1716 > acuumDeltaTick_) {
    GEngineCore->ChangeLevel<KOFLobyLevel>();
  }
}
