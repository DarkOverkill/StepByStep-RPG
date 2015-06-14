class change
{
private:
	friend class A;
public:
	void Change(A* a)
	{
		a->x /= 2;
	}
};