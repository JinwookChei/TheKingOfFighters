#pragma once

struct LINK_ITEM {
  LINK_ITEM* prev_;
  LINK_ITEM* next_;
  void* item_;
};

MATH_API void LinkToLinkedList(LINK_ITEM** ppHead, LINK_ITEM** ppTail, LINK_ITEM* pNew);
MATH_API void LinkToLinkedListFIFO(LINK_ITEM** ppHead, LINK_ITEM** ppTail, LINK_ITEM* pNew);
MATH_API void UnLinkFromLinkedList(LINK_ITEM** ppHead, LINK_ITEM** ppTail, LINK_ITEM* pDel);
MATH_API int CountLinkedList(const LINK_ITEM* ppHead);