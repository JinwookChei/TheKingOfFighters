<div align="center">
<h2>🥊 King of Fighters 2003 (모작) - Win32 2D Game Framework</h2>

<div align="center">
  <h3>
    <img src="https://upload.wikimedia.org/wikipedia/commons/0/09/YouTube_full-color_icon_%282017%29.svg" width="30" alt="YouTube Icon" align="absmiddle"/>
    King of Fighters 2003 Demo
  </h3>

  <a href="https://youtu.be/rZeRdkoJKsQ?si=B5Ez7J7bEngthRr9" target="_blank">
    <img src="./Preview/title.png" alt="King of Fighters 2003 Demo" width="700" />
  </a>

  <p><i>이미지를 클릭하시면 유튜브 데모 영상으로 이동합니다.</i></p>

  <br/>
  본 프로젝트는 상용 엔진 없이 C/C++, Win32 API를 사용하여 간단한 2D 게임 프레임워크를 제작하고,<br>
  그 프레임워크 위에서 동작하는 King of Fighters 2003을 모작한 개인 프로젝트입니다.
</div>

<!-- 기술스택 -->
<div align="center">
  <img src="https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=white" alt="C"/><img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" alt="C++"/><img src="https://img.shields.io/badge/Win32_API-0078D4?style=flat-square&logo=windows&logoColor=white" alt="Win32 API"/>
</div>

<br>

<div align="center">
  <b>Team Size</b> : 개인 프로젝트 &nbsp;|&nbsp; <b>Dev Period</b> : 2025.03 ~ 2025.08
</div>
</div>

<br>
<br>

## 🚀 구현 기능

<div align="center">
  <h3>Atlas Animation</h3>

  <img src="./Preview/Atlas.png" alt="Atlas Animation" width="700" />

  <br/>
  스프라이트 아틀라스를 활용하여 애니메이션을 구현했습니다.<br>
  단일 텍스처에서 UV 좌표를 계산해 원하는 이미지 인덱스로 전환하는 방식으로 애니메이션 시스템을 제작했습니다.
</div><br>
<br/>

<div align="center">


<div align="left">

#### 🚨 문제 상황
* 리소스 사이트로부터 받은 Atlas Image의 상하좌우 Padding 값이 일정하게 정렬되어 있지 않았습니다.
* 따라서 Atlas Image의 UV 값을 각각 계산해야 했습니다.

</div>

<div align="center">
  <img src="./Preview/UV_Problem.png" alt="UV Problem" width="500" />
</div>
<br>

<div align="left">

#### 💡 해결 방안
* 모든 픽셀을 탐색하는 계산을 줄이기 위해, <b>보조선을 그어 그 내부 범위에서 BoundBox UV 좌표</b>를 얻었습니다.

</div>

<div align="center">
  <img src="./Preview/UV_Solution.png" alt="UV Solution" width="500" />
  <br><br>
  <img src="./Preview/UV_BoundBox.png" alt="BoundBox UV" width="150" />
  <p><i>보조선 내부에서 얻은 BoundBox UV</i></p>
</div>
<br><br>

---

<div align="center">
  <h3>
    <img src="https://upload.wikimedia.org/wikipedia/commons/0/09/YouTube_full-color_icon_%282017%29.svg" width="30" alt="YouTube Icon" align="absmiddle"/>
    🚨 문제 - 애니메이션 발 미끄러짐 현상 해결 (Pivot Offset)
  </h3>

  <a href="https://youtube.com/shorts/CDv2IbMH8_U?si=uwe0s13LtzgfGdS4" target="_blank">
    <img src="./Preview/ProblemPivot.png" alt="Pivot Before / After" width="700" />
  </a>

  <p><i>이미지를 클릭하시면 유튜브 데모 영상으로 이동합니다.</i></p>
</div><br>



<div align="center">
  <img src="./Preview/PivotTool.png" alt="Pivot Offset Tool" width="700" />
  <p><i>Pivot Offset 조정 툴 제작</i></p>
</div>
<br><br>

---




---
<div align="left">


<div align="center">
  <h3>🚨 문제 - 캐릭터의 실제 움직임과 애니메이션 상태의 불일치</h3>

  <img src="./Preview/FSM.png" alt="Animation FSM" width="700" />

  <br/>
  캐릭터의 실제 움직임과 애니메이션 상태를 일치시키기 위해 <b>FSM(Finite State Machine)</b>을 구현했습니다.
</div><br>


<div align="center">
  <img src="./Preview/FSM_Structure.png" alt="Animation FSM 구조도" width="700" />
</div>

<div align="center">
<b>AnimStateTransMachine:</b> HashTable로 AnimTransState를 관리하는 컴포넌트입니다.<br>
<b>AnimTransState:</b> 현재 AnimState를 Key로 검색되며, 해당 상태에서 전이 가능한 AnimTransRule 목록을 가집니다.<br>
<b>AnimTransRule:</b> 비트마스크로 된 전이 조건(E_ANIM_TRANS_COND)과 전이할 AnimState를 가집니다. 매 Tick 전이 조건을 만족하면 애니메이션 상태 전이가 발생합니다.<br>
</div>
<br><br>

<!-- ---
<div align="left">

#### 🚨 기존 문제
* 캐릭터의 점프 동작을 단일 애니메이션으로만 구현하여, 실제 움직임과 애니메이션 상태가 일치하지 않았습니다.
* 예를 들어 점프 중 상승할 때와 착지할 때가 구분되지 않았습니다.

<div align="center">
  <h3>Animation FSM</h3>

  <img src="./Preview/FSM_Before.png" alt="Animation FSM" width="700" />

  <br/>
  캐릭터의 실제 움직임과 애니메이션 상태를 일치시키기 위해 <b>FSM(Finite State Machine)</b>을 구현했습니다.
</div><br>


<div align="left">
#### 💡 해결 방안
* FSM을 구현하여 점프를 <code>JumpUp</code>, <code>JumpDown</code>, <code>JumpLand</code>로 나누었습니다.
</div>

<div align="center">
  <img src="./Preview/FSM_Structure.png" alt="Animation FSM 구조도" width="700" />
</div>

<div align="left">
<b>AnimStateTransMachine:</b> HashTable로 AnimTransState를 관리하는 컴포넌트입니다.<br>
<b>AnimTransState:</b> 현재 AnimState를 Key로 검색되며, 해당 상태에서 전이 가능한 AnimTransRule 목록을 가집니다.<br>
<b>AnimTransRule:</b> 비트마스크로 된 전이 조건(E_ANIM_TRANS_COND)과 전이할 AnimState를 가집니다. 매 Tick 전이 조건을 만족하면 애니메이션 상태 전이가 발생합니다.<br>
</div>
<br><br> -->
---

<div align="center">
  <h3>Collision</h3>

  <img src="./Preview/Collision.png" alt="Collision" width="700" />

  <br/>
  플레이어 간 충돌을 처리하기 위해 <b>AABB(사각형) 충돌</b>을 구현했습니다.<br>
  또한 애니메이션마다 충돌 범위를 지정하기 위해 <b>충돌 에디터 툴</b>을 제작하여 충돌 범위를 지정했습니다.
</div>
<br><br>

---

<div align="center">
  <h3>Command</h3>

  <img src="./Preview/Command.png" alt="Command Tree" width="700" />

  <br/>
  King of Fighters 2003에는 지정된 Command를 입력하면 해당 스킬이 나가는 Command 입력 시스템이 있습니다.<br>
  Command 검색을 위해 <b>Tree 구조</b>를 사용하여 Command 기능을 구현했습니다.
</div><br>

<div align="left">
<b>RegistCommand:</b> 입력 키 순서대로 트리를 탐색하고, 키에 해당하는 자식 노드가 없으면 새 노드를 생성합니다. 마지막 노드에 Command를 연결합니다.<br>
<b>JumpNode:</b> 입력된 키에 해당하는 자식 노드로 이동합니다. 자식 노드가 없으면 루트 노드로 돌아갑니다. 이동한 노드에 Command가 있으면 Command를 예약하고 루트 노드로 돌아갑니다.<br>
<b>Input Timer:</b> 키 입력 간격이 임계값을 넘으면 루트 노드로 초기화됩니다.<br>
</div>
<br><br>
