class Command
{
public:
	enum ECommandType
	{
		CM_INVALID,
		CM_ATTACK,
		CM_MOVE,
		CM_BUILD,
		CM_SWITCHTEAM,
		CM_MEOW
	};

	Command() :
	mCommandType( CM_INVALID ),
	mNetworkId( 0 ),
	mPlayerId( 0 )
	{}

	//given a buffer, will construct the appropriate command subclass
	static shared_ptr< Command > StaticReadAndCreate( InputMemoryBitStream& inInputStream );

	void SetNetworkId( uint32_t inId ) { mNetworkId = inId; }
	int GetNetworkId() const { return mNetworkId; }

	void SetPlayerId( uint32_t inId ) { mPlayerId = inId; }
	int GetPlayerId() const { return mPlayerId; }

	virtual void Write( OutputMemoryBitStream& inOutputStream );
	virtual void ProcessCommand() = 0;
protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) = 0;

	ECommandType mCommandType;
	uint32_t mNetworkId;
	uint32_t mPlayerId;
};

typedef shared_ptr< Command >	CommandPtr;

class AttackCommand : public Command
{
public:
	AttackCommand():
	mTargetNetId(0)
	{
		mCommandType = CM_ATTACK;
	}

	static shared_ptr< AttackCommand > StaticCreate( uint32_t inMyNetId, uint32_t inTargetNetId );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t mTargetNetId;
};

typedef shared_ptr< AttackCommand > AttackCommandPtr;

class MoveCommand : public Command
{
public:
	MoveCommand()
	{
		mCommandType = CM_MOVE;
	}

	static shared_ptr< MoveCommand > StaticCreate( uint32_t inNetworkId, const Vector3& inTarget );

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	Vector3 mTarget;
};

typedef shared_ptr< MoveCommand > MoveCommandPtr;

//build command class
class BuildCommand : public Command
{
public: 
	BuildCommand()
	{
		mCommandType = CM_BUILD;
	}

	static shared_ptr< BuildCommand > StaticCreate(uint32_t inNetworkId, const Vector3& inTarget);

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected: 
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	Vector3 mSpawnLocation;
};

typedef shared_ptr< BuildCommand > BuildCommandPtr;

//switch team command class
class SwitchTeamCommand : public Command
{
public:
	SwitchTeamCommand()
	{
		mCommandType = CM_SWITCHTEAM;
		mTargetTeamId = mPlayerId; //get other player's ID?
	}

	static shared_ptr< SwitchTeamCommand > StaticCreate(uint32_t inNetworkId, const uint32_t& targetTeamId);

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t mTargetTeamId;
};

typedef shared_ptr< SwitchTeamCommand > SwitchTeamCommandPtr;

//meow command class
class MeowCommand : public Command
{
public: 
	MeowCommand()
	{
		mCommandType = CM_MEOW;
	}

	static shared_ptr< MeowCommand > StaticCreate(uint32_t inNetworkId);

	virtual void Write( OutputMemoryBitStream& inOutputStream ) override;

	virtual void ProcessCommand() override;

protected:
	virtual void Read( InputMemoryBitStream& inInputStream ) override;
};

typedef shared_ptr< MeowCommand > MeowCommandPtr;