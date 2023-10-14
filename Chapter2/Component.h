#pragma once
class Component {
protected:
	class Actor* owner;
	int updateOrder;
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void update(float deltaTime);
	int getUpdateOrder() const { return updateOrder; }
};
