#pragma once

struct ImageLineInfo {
  unsigned int startPositionY_;
  unsigned int heightY_; // 마지막 픽셀 위치 - startPositionY_;
  LINK_ITEM link_;
};