#pragma once

enum CollisionGroupType {
  CollisionGroupType_Player = CollisionGroupEngineType::CollisionGroupEngineType_MAX + 1,
  CollisionGroupType_Monster,
  CollisionGroupType_MAX
};