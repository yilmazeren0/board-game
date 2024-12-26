// IGameMenuOperations.h
class IGameMenuOperations {
public:
    virtual ~IGameMenuOperations() = default;
    virtual void rollDice() = 0;
    virtual void buildSettlement() = 0;
    virtual void buildRoad() = 0;
    virtual void trade() = 0;
    virtual void endTurn() = 0;
};
