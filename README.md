# NumberBaseBall (숫자 야구 게임)

 - 멀티플레이어에서 중요한 판정 로직의 서버 집중화 및 상티 동기화 메커니즘 이해
 - 언리얼 엔진의 Replcication 및 Role System 이해

# 규칙
- S :숫자와 자리가 모두 맞음
- B :숫자는 맞지만 자리가 다름
- OUT : 입력한 숫자가 다 맞지 않음


# 주요 개념들
## Dedicated Server
 - Server 담당하는 컴퓨타가 따로 있음. Server-Client 구조.
 - GameMode 액터는 전체 컴퓨터 중 Server 에만 존재함. 따라서 GameMode와 Server를 동일시 해도 됨.  PlayerController는 각 Client 자기것만 있음.
 - Client-Client간 통신 불가능 하고 오직 Server와 Client 사이의 통신만 가능함.

## NetMode
 - 해당 프로세스가 네트워크 상에서 어떤 역할을 하고 있는지 의미
 - 싱글(NM_StandAlone) 서버(NM_Listen, NM_DedicatedServer), 클라이언트(NM_Client)

## NetConnection
 - 다른 PC와 연결 발생시 그에 대응하는 UNetConnection 객체 생성.
 - Server에 Client 접속시 서버에 ClientConnection 객체 추가됨. 반대로 Client에는 ServerConnection 객체 생성.
 - 두 PC는 UNetConnection 객체를 통해 통신. UNetDriver는 생성된 UNetConnection 객체를 소유하고 관리.
 - 서버 PC에 생성된 UNetDriver는 접속한 Client 수 만큼 UNetConnection을 관리함.
 - Client PC에 생성된 UNetDriver는 ServerConnection 하나만의 관리.

## Unreal에서의 OwnerShip
 - 하나의 ClientConnection은 하나의 PlayerController를 소유함. PlayerController의 Owning Connection은 ClientConnection.

## NetDriver
 - 언리얼 네트워크 통신에서 로우레벨 동작 관리 class
 - 싱글 플레이에선 생성되지 않고, 멀티에서만 UWorld::Listen() 함수 통해 UNetDriver가 생성됨.
 - 멀티플레이에 참여하는 각 PC마다 UNetDriver 객체 생성됨.

## NetMode에 따른 Actor 위치
 - Server에만 존재: GameMode
 - Server와 모든 Client: 배경 Actor와 Pawn
 - Server와 Client에만: PlayerController
 - Client에만 존재하는 Unreal Object: 애니메이션 BP, UI

## Autority와 Proxy
 - 서버에 스폰 된 Actor가 가진 NetRole 속성값은 언제나 Authority. 서버에 스폰된 Actor에서 수행될 로직은 권한을 가지고 있음 게임 중대한 로직은 NetRole이 Authority일 때 수행해야 함.
 - NetRole이 Authority인 Actor가 Client로 복제되었을 때, 복제된 Actor의 NetRole 속성 값은 Proxy.(주요로직 수행되어선 안 됨)

## 로컬 롤과 리모트 롤
 - Local Role: 현재 동작하는 컴퓨터에서의 Role
 - Remote Role: 커넥션으로 연결된 컴퓨터에서의 Role

## NetRole 종류
| 종류 | 설명 | 예시 |
| ---------------- | ---------------------------------------------------- | -----------------------------------------------|
| None | Actor가 존재하지 않음	| Server에 스폰되고 레플리케이션 되지 않는 Actor, Client에서 스폰된 Actor |
| Authority	| 게임 중대한 영향 로직 작성 가능	| GameMode |
| Autonomous Proxy	| Server로부터 수신 받아 동기화되면서 Server로 송신 가능	| PlayerController |
|Simulated Proxy	|서버로 부터 수신 받아 동기화 됨	|내 화면에 보이는 다른 사람의 PlayerCharacter|

## RPC(Remote Procedure Call)
 - 호출 PC와 실행 PC 달라도 되는 통신 기법
 - Unreal에선 주로 Cosmetic(Sound, Particle 등)에 사용.

*REST와 어떤 차이가 있는지 궁금해서 찾아보았다
https://aws.amazon.com/ko/compare/the-difference-between-rpc-and-rest/

- RPC와 REST 비교 - API 아키텍처 간의 차이점 - AWS
- RPC와 REST의 차이점은 무엇인가요? AWS에서 RPC 및 REST를 사용하는 방법.
 - 여기(aws.amazon.com) 나오는 내용을 토대로 이해해본다면, RPC와 REST의 가장 큰 차이는 사용 목적인 것 같다.
 - RPC: 원격에서 제어하여 작업이 필요한 것(ex: 원격으로 사진찍기, 원격 서버 재시작)
 - REST: 서버 데이터의 CRUD. 데이터 즉, DB와 연관된 작업할떄 쓰임(ex: DB에 데이터 추가, 목록 검색)

## Call
 - 정적인 의미를 가짐 
 - Compile 타임에 어떤 함수인지, 호출하는 곳과 실행하는 곳이 정해져야 함.
 - 일반적인 전역 함수와 멤버함수. 직접적 함수 호출하고 실행해야 함(Direct)

## Invoke
 - 동적인 의미를 가짐
 - Runtime에 어떤 함수인지 호출하는 곳과 실행하는 곳이 어딘지 정해져야 함.
 - 함수 포인터, 동적 바인딩, RPC같은 개념들.
 - 간접적으로 호출, 실행(Indirect)
 
## Actor Ownership
 - 네트워크 멀티플레이어가 적용되려면, Actor는 Server에서 스폰되고, bReplicated가 true여야함.
 - 서버에서 스폰 후 SetOwner(PlayerController) 함수를 호출해야 Client-Owner Actor가 됨.
 - 
   ● PlayerController ＝ Local PlayerController →  호출한 Client가 소유한 Actor가 되어야 함.
   
     ex) 내 Player 캐릭터
   
   ● PlayerController ≠ Local PlayerController → 다른 Client가 소유한 Actor가 되어야 함.
   
     ex) 상대 Player 캐릭터
   
   ● 서버에 스폰됐지만 SetOwner() 함수호출 없음 → Server-Owned Actor가 되어야 함.
   
      ex) 보물상자 Actor
 

## NetMulticast, Server, Client 키워드
 - UFUNCTION() 매크로와 함께 사용되는 키워드들.
 - 해당 원격 PC에서 RPC를 실행시켜 달라는 요청을 나타내야 함.
 - 
  ● NetMulticast: 서버를 포함한 모든 Client를 해당 RPC에서 실행시켜야 한다는 요청을 나타내야 함.

  ● Server: 서버에서 해당 RPC를 실행시켜야 한다는 요청을 나타내야 함

  ● Client: 클라이언트에서 해당 RPC를 실행시켜야 한다는 요청을 나타냄.
