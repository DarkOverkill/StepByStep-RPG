
class A
{
protected:
	int x;
	friend class change;
public:
	A() :x(10){}
	virtual void Show()
	{
		std::cout << x;
	}
};
class B : public A
{
public:
	void Show()
	{
		std::cout << x << std::endl;
	}
};
